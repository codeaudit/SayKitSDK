# Command Recognition

One of the major benefits of a conversational UI is giving users the ability to issue commands using plain old human languages. Users are not required to tap around their screens to accomplish a task: they can simply tell the app what they want done. While that might be great news for users, it opens up a whole world of complexity for developers. Managing this complexity is one of SayKit’s primary goals.

These *command requests* have very different properties than the typical *voice request*, described in the last section. First off, the user could literally say anything, so the app has to interpret a wide range of speech without much context to go on. Secondly, since this request started with the user, the app doesn't have a simple callback waiting to directly handle the input.

SayKit provides the **Command Recognizer** classes, which are specficially designed to handle these needs. A `SAYCommandRecognizer` subclass knows how to look out for specific speech patterns, and instances of them know exactly where commands should be delivered to. For example:

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

This should ring a bell to those familiar UIKit users: the `SAYCommandRecognizer` class is similiar in spirit (and in syntax) to the `UIGestureRecognizer` class, so recognizing a search command is as easy as recognizing a swipe.

(And yes, Swift fans, the Command Recognizers can be defined with a tidy closure-based syntax as well.)

````swift
let searchRecognizer = SAYSearchCommandRecognizer() { command in 
	// run a search with a query string inside `command`
}
````

SayKit comes with a large number of pre-built command recognizers, but you can modify them to handle broader speech input, or even create your own recognizers to handle custom commands. To learn more, let's dive a bit deeper into the command recognition tools.

// TODO

[Next - Audio Output >>](./04-audio-output.md)
