# Command Recognition

One of the major benefits of a conversational UI is giving users the ability to issue commands using plain old human languages. Users are not required to tap around their screens to accomplish a task: they can simply tell the app what they want done. While that might be great for users, it opens up a whole world of complexity for developers. Managing this complexity is one of SayKit’s primary goals.

These *command requests* have very different properties than the typical *voice request*, described in the last section. First off, the user could literally say anything, so the app has to interpret a wide range of speech without much context to go on. Secondly, since this request started with the user, the app doesn't have a simple callback waiting to directly handle the input.

SayKit provides the **Command Recognizer** classes, which are specficially designed to handle these needs. A `SAYCommandRecognizer` subclass knows how to look out for specific speech patterns, and instances of them know exactly where commands should be delivered to. For example, in Swift:

````swift
init() {
	let searchRecognizer = SAYSearchCommandRecognizer(
		responseTarget: self, 
		action: "searchRequested:")
    ...
}

func searchRequested(command: SAYCommand) {
	// run a search with a query string inside `command.parameters`
}
````

This should ring a bell to those familiar with UIKit: the `SAYCommandRecognizer` class is similiar in spirit (and in syntax) to the `UIGestureRecognizer` class, so recognizing a search command is as easy as recognizing a swipe.

(And yes, Swift fans, the recognizers can be defined with a tidy closure-based syntax as well.)

````swift
let searchRecognizer = SAYSearchCommandRecognizer() { command in 
	// run a search with a query string inside `command.parameters`
}
````

SayKit comes with a number of these pre-built standard command recognizers, and that list is actively growing. Even the existing recognizers are constantly being improved as we actively train them on actual usage behind the scenes.

## Command Registry

Remember our friend `SAYConversationManager`? One of its properties is a `SAYCommandRegistry`, which is a protocol that describes types capable of holding a collection of recognizers. When the user speaks the command, all the recognizers attached to this registry will be consulted to interpret the speech.

Simple apps can get by with a basic `SAYCommandRecognizerCatalog` as a registry, which is a basic class that wraps a list of recognizers. As your app grows, however, your registry will need a bit more structure. We'll get into that later in the tour when we talk about [Command Topics](./05-command-topics.md).

A typical pattern is to set the system manager's registry when the application is loading:

```swift
func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
    ...
    let catalog = SAYCommandRecognizerCatalog()
    SAYConversationManager.systemManager().commandRegistry = catalog
    
    // for the example, let's add a help recognizer right away
    catalog.addRecognizer(SAYHelpCommandRecognizer()) {/* do something! */}
}
```


*TODO: discuss the command bar and the available commands menu*

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

[Next - Audio Output >>](./04-audio-output.md)
