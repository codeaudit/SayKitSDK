# Command Recognition

One of the major benefits of a conversational UI is giving users the ability to issue commands using plain old human languages. Users are not required to tap around their screens to accomplish a task: they can simply tell the app what they want done. While that might be great news for users, it opens up a whole world of complexity for developers. Managing this complexity is one of SayKit’s primary goals.

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

## Extending Command Recognizers

SayKit doesn't restrict you to its built-in library, however. Standard recognizers can be extended to handle broader speech patterns and you can even create your own recognizers to handle custom commands.

As a quick example let's say we're building a Pokémon-themed email app (as you do), and we want it to recognize the following command: "I choose you, John Smith!" to add a recepient to a message. SayKit already provides the `SAYSelectCommandRecognizer`, which recognizes when the user wants to make a selection, but it wasn't necessarily built with Pokémon trainers in mind. So what can we do?

````objc
// Objective-C

// create the recognizer with an action block
SAYCommandRecognizer *selectRecognizer;
selectRecognizer = [SAYSelectCommandRecognizer alloc] initWithActionBlock:^(SAYCommand *) { 
	NSString *name = command.parameters[@"name"];
	/* ... */
};

// add our special pattern, note the "name" parameter
NSString *pattern = @"i choose you @name";
selectRecognizer.addTextMatcher([SAYPatternCommandMatcher matcherWithPattern:pattern]);
````

````swift
// Swift

// create the recognizer with an action block
let selectRecognizer = SAYSelectCommandRecognizer() { command in
	if let name = command.parameters["name"] { /* ... */ }
}

// add our special pattern, note the "name" parameter
let pattern = "i choose you @name"
selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
````

Done! Assuming if you have a bunch of Pokémon in your address book, you've now got the perfect email client.

This just scratches the surface of customizing command recognizers. To learn more, check out our developer guide on the topic (coming soon!).

[Next - Audio Output >>](./04-audio-output.md)
