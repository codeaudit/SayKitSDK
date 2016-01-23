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
	// run a search with a query string inside `command`
}
````

This should ring a bell to those familiar with UIKit: the `SAYCommandRecognizer` class is similiar in spirit (and in syntax) to the `UIGestureRecognizer` class, so recognizing a search command is as easy as recognizing a swipe.

(And yes, Swift fans, the recognizers can be defined with a tidy closure-based syntax as well.)

````swift
let searchRecognizer = SAYSearchCommandRecognizer() { command in 
	// run a search with a query string inside `command`
}
````

SayKit comes with a large number of pre-built command recognizers, but you can modify them to handle broader speech input, or even create your own recognizers to handle custom commands. 

If you'd like to learn a bit more, let's dive a bit deeper into the command recognition system.

## `SAYCommand`

The `SAYCommand` class provides the common currency for recognizing and responding to user commands. It's a simple type with two properties: `type` and `parameters`. Commands are differentiated by their `type`, and they can have any number of arguments associated with them, stored in the `parameters` dictionary. Think of them as SayKit's equivalent to the `UIEvent` class.

Each command recognizer specializes in producing commands of a particular type (declared as the recognizer's `commandType` property). Under the hood, the recognizers need to consider a user speech utteranace and decide two things:

1. How likely is it that the user is issuing a command of my type?
2. Does this utterance include parameters to go along with the command? If so, what are they?

During their recognition process, the recognizers use the `SAYCommandSuggestion` class to collect these two pieces of information as the following properties:

- `confidence`: a floating point value between 0.0 and 1.0. 1.0 denotes 100% certainty that the utterance was the given command, while 0.0 denotes the opposite.
- `parameters`: a dictionary of associated parameters extracted from the utterance

If you're looking to extend SayKit's command recognizers or build your own from scratch, your job will be to map user speech to a `SAYCommandSuggestion`.

## Extending Built-in Recognizers

Oftentimes, you'll find that an existing SayKit command recognizer will suit your needs with just a bit of adjustment. 

- talk about text matchers. the two concrete types we offer

## Building Custom Recognizers

- refer again to text matchers

## Turn taking

[Next - Audio Output >>](./04-audio-output.md)
