---
layout: default
title: "SayKit Tour - Command Recognition: Part 1"
permalink: /tour/command-recognition-pt1/
---

# Command Recognition: Part 1

One of the major benefits of a conversational UI is giving users the ability to issue commands using plain old human languages. Users are not required to tap around their screens to accomplish a task: they can simply tell the app what they want done. While that might be great for users, it opens up a whole world of complexity for developers. Managing this complexity is one of SayKit’s primary goals.

These *command requests* have very different properties than the typical *voice request*, described in the last section. First off, the user could literally say anything, so the app has to interpret a wide range of speech without much context to go on. Secondly, since this request started with the user, the app doesn't have a simple callback waiting to directly handle the input.

## Command Recognizers

SayKit provides the **Command Recognizer** classes, which are specifically designed to handle these needs. A `SAYCommandRecognizer` subclass knows how to look out for specific speech patterns, and instances of them know exactly where commands should be delivered to. For example, in Swift:

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

Remember our friend [`SAYConversationManager`]({{ "/tour/overview/" | prepend: site.baseurl }})? One of its properties is a `SAYCommandRegistry`, which is a protocol that describes types capable of holding a collection of recognizers. When the user speaks the command, all the recognizers attached to this registry will be consulted to interpret the speech.

Simple apps can get by with a basic `SAYCommandRecognizerCatalog` as a registry, which is a basic class that wraps a list of recognizers. As your app grows, however, your registry will need a bit more structure. We'll get into that later in the tour when we talk about [Command Topics]({{ "/tour/conversation-topics/" | prepend: site.baseurl }}).

A typical pattern is to set the system manager's registry when the application is loading:

```swift
// Swift
func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
    ...
    let catalog = SAYCommandRecognizerCatalog()
    SAYConversationManager.systemManager().commandRegistry = catalog
    
    // for the example, let's add a help recognizer right away
    catalog.addRecognizer(SAYHelpCommandRecognizer()) {/* do something! */}
}
```

---

We'll continue with even more about command recognitions in the next stop on our tour.

[Next - Command Recognition: Part 2 >>]({{ "/tour/command-recognition-pt2/" | prepend: site.baseurl }})
