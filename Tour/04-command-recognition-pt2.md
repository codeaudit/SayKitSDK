# Command Recognition: Part 2

## Extending Command Recognizers

SayKit doesn't restrict you to its built-in library of recognizers. Standard recognizers can be extended to handle broader speech patterns and you can even create your own recognizers to handle custom commands.

Recognizer instances can be modified by adding **Text Matchers** to them. In essence, a text matcher is a simple agent that processes a string of text and decides how likely it is to match the relevant command. A few types of built-in text matchers exist, most notably the `SAYPatternCommandMatcher`, which uses a set of pattern templates to match user speech. We'll use one in a moment below.

As a quick example let's say we're building a Pokémon-themed email app (as you do), and we want to add a recipient to a message by recognizing the following command: "I choose you, John Smith!". SayKit already provides the `SAYSelectCommandRecognizer`, which recognizes when the user wants to make a selection, but it wasn't necessarily built with Pokémon trainers in mind. So what can we do?

````swift
// Swift, using a closure-style callback

// create the recognizer with an action block
let selectRecognizer = SAYSelectCommandRecognizer() { command in
	if let name = command.parameters["name"] { /* ... */ }
}

// add our special pattern, note the "name" parameter
let pattern = "i choose you @name"
selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
````

````objc
// Objective-C, using a target/action-style callback

- (void)addRecipent:(SAYCommand *command) {
	NSString *name = command.parameters[@"name"];
	/* ... */
}

...

	// create the recognizer with an target/action selector
	SAYCommandRecognizer *selectRecognizer;
	selectRecognizer = [[SAYSelectCommandRecognizer alloc] initWithResponseTarget:self 
                                                                           action:@selector(addRecipient:)]
	
	// add our special pattern, note the "name" parameter
	NSString *pattern = @"i choose you @name";
	selectRecognizer.addTextMatcher([SAYPatternCommandMatcher matcherWithPattern:pattern]);
````

Done! Assuming you have a bunch of Pokémon in your address book, you've now got the very best email client.

## Custom Commands

It's fairly likely that you'll need to employ recognizers for commands that SayKit does not provide. For these cases, the `SAYCustomCommandRecognizer` is available. For instance, here's a quick recognizer that attempts to recognize greetings, using the custom command type "Greeting":

```Swift
// Swift
let greetingsRecognizer = SAYCustomCommandRecognizer(customType: "Greeting") { cmd in /* ... */ }
let patterns = ["hello", "hey", "what's up"]
greetingsRecognizer.addTextMatcher(SAYPatternCommandMatcher(patterns:patterns))
```

```objc
// Objective-C
SAYCustomCommandRecognizer *greetingsRecognizer = 
	[[SAYCustomCommandRecognizer alloc] initWithCustomType:@"Greeting"
				                                actionBlock:^(SAYCommand * _Nonnull) { /* ... */ }];
NSArray *patterns = @[@"hello", @"hey", @"what's up", "greetings"];
[greetingsRecognizer addTextMatcher:[SAYPatternCommandMatcher matcherWithPatterns:patterns]];
```

In the near future, we'll be previewing more robust custom command recognition tools, including the intregration of third-party intent recognition services.

This just scratches the surface of customizing command recognizers. To learn more, check out our developer guide on the topic (coming soon!).

## Command Dialogues

The app listens for a user command via the same mechanism it uses for listening to all user speech: as part of a `SAYVoiceRequest` session. Specifically, it uses a `SAYVerbalCommandRequest`.

Just like [any other voice request](./02-voice-requests.md#voice-request-flow), a `SAYVerbalCommandRequest` has a *responding* stage. And just like any other voice request, the response can include a follow-up request, which causes the app to ask the user a new question. This means the app can jump straight into a conversation with the user directly in response to a command. To pull this off, simply return the followup request from your recognizer instance's action method/block.

We'll illustrate with an example of a "Help" command. If we're able to help, the app needs to know what the user needs help with. Let's find out by asking directly. Followup responses to the rescue!

````swift
// Swift, using a closure-style callback

// Of course, we're here to help!
let helpIsAvailable = true

// Note the action block's signature: we're returning a response now
commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
    if helpIsAvailable {
        // respond with a new voice request
        let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: {/* ...provide help... */}
        return SAYVoiceRequestResponse(followupRequest: followupRequest)
    }
    else {
        // no need to follow up, just terminate the request and run the given action block
        return SAYVoiceRequestResponse.terminalResponseWithAction({/* ... */})
    }
})
````

````objc
// Objective-C, using a target/action-style callback

// Note the signature: action selectors can have a (SAYVoiceCommandResponse *) return type
- (SAYVoiceRequestResponse *)provideHelp:(SAYCommand *command) {
	if (helpIsAvailable) {
        // respond with a new voice request
		SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:@"What would you like help with?",
									  									  action:/* ...provide help... */]; 
		return [SAYVoiceRequestResponse responseWithFollowupRequest:request];
	}
	else {
		// no need to follow up, just terminate the request and run the given action block
		return [SAYVoiceRequestResponse terminalResponseWithAction:^{/* ... */}];
	}
}

...
	helpRecognizer = [[SAYHelpCommandRecognizer alloc] initWithResponseTarget:self 
                                                                           action:@selector(provideHelp:)];
...
````

Sure, it's a bit more involved, but your app just got a lot more responsive with those few new lines of code.

---

Now let's take a deep breath before we switch contexts completely. Up until now, the app only speaks question prompts to the user. How do break from that mold and let the app speak freely?

[Next - Audio Output >>](./05-audio-output.md)
