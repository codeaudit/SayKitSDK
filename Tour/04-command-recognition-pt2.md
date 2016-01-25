## Extending Command Recognizers

SayKit doesn't restrict you to its built-in library, however. Standard recognizers can be extended to handle broader speech patterns and you can even create your own recognizers to handle custom commands.

As a quick example let's say we're building a Pokémon-themed email app (as you do), and we want it to recognize the following command: "I choose you, John Smith!" to add a recepient to a message. SayKit already provides the `SAYSelectCommandRecognizer`, which recognizes when the user wants to make a selection, but it wasn't necessarily built with Pokémon trainers in mind. So what can we do?

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

Done! Assuming if you have a bunch of Pokémon in your address book, you've now got the perfect email client.

This just scratches the surface of customizing command recognizers. To learn more, check out our developer guide on the topic (coming soon!).

## Command Dialogues

The app listens for a user command via the same mechanism it uses for listening to all user speech: as part of a `SAYVoiceRequest` session. Specifically, it uses a `SAYVerbalCommandRequest`.

Just like every other voice request, a `SAYVerbalCommandRequest` has a *responding* stage. And just like any other voice request, the response can include a follow-up request, which causes the app to ask the user a new question. This means the app can jump straight into a conversation with the user directly in response to a command. To pull this off, simply return the followup request from your recognizer instance's action method/block.

We'll illustrate by continuing with the previous example. Let's say your user has two friends named "Pikachu" in her address book: Toby Pikachu and Susan Pikachu. If the user says "I choose you, Pikachu!", the app needs to know if she means Toby or Susan.

Let's find out which one by asking her directly. Followup responses to the rescue!

````swift
// Swift, using a closure-style callback

// Note the action block's signature: we're returning a response now
let selectRecognizer = SAYSelectCommandRecognizer() { command -> SAYVoiceRequestResponse in
    let matchingNames = /* find names that match */
	if (matchingNames.count) {
		// respond with a new voice request 
		let request = SAYSelectRequest(itemLabels:matchingNames
                                       promptText:@"Which one?") {/* ... add selected name ... */};
		return SAYVoiceRequestResponse(followupRequest:request);
	}
	else {
		// no need to follow up, just terminate the request and run the given action block
		SAYVoiceRequestResponse.terminalResponseWithAction() {/* ... add name ... */};
	}
}
````

````objc
// Objective-C, using a target/action-style callback

// Note the signature: action selectors can have a (SAYVoiceCommandResponse *) return type
- (SAYVoiceRequestResponse *)addRecipent:(SAYCommand *command) {
	NSArray <NSString *> *matchingNames = /* find names that match */
	if (matchingNames.count) {
		// respond with a new voice request 
		SAYSelectRequest *request = [[SAYSelectRequest alloc] initWithItemLabels:matchingNames
                                                                      promptText:@"Which one?" 
                                                                          action:/* ... add selected name ... */];
		return [SAYVoiceRequestResponse responseWithFollowupRequest:request];
	}
	else {
		// no need to follow up, just terminate the request and run the given action block
		return [SAYVoiceRequestResponse terminalResponseWithAction:^{/* ... add name ... */}];
	}
}

...
	selectRecognizer = [[SAYSelectCommandRecognizer alloc] initWithResponseTarget:self 
                                                                           action:@selector(addRecipient:)];
...
````

Sure, it's a bit more involved, but your app just got a lot more responsive with those few new lines of code.

---

Now let's take a deep breath before we switch contexts completely. Up until now, the app only speaks question prompts to the user. How do break from that mold and let the app speak freely?

[Next - Audio Output >>](./05-audio-output.md)
