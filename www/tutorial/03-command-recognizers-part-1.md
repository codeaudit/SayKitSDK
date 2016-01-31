---
layout: default
title: "SayKit Tutorial -- Command Recognizers: Part 1"
permalink: "/tutorial/03-command-recognizers-part-1/"
---

# Command Recognizers - Part 1

In graphical apps, users interact by tapping or swiping the screen. If they tap a button, they probably intend to trigger an action associated with that button, which makes our job simple: do the action!

Contrast this with conversational apps, where users interact by speaking. When they say something we recognize, we need to interpret their intent as a command and execute the command.

This encompasses several steps as the user’s speech is converted to text (`SAYSpeechTranscript`), interpreted as an intent (`SAYSpeechIntent`), and finally converted to a command (`SAYCommand`) that is associated with an app-defined action. This is analogous to UIKit's progression of user taps being translated from electrical impulses to screen coordinates to gesture events, which is passed to the encompassing view that reacts to the event.

But we don't typically worry about these steps when we create a visual app using UIKit, and creating a conversational app with SayKit is no different. All we need to do is create a `SAYCommandRecognizer` with a corresponding action. After registering the recognizer with the Conversation Manager's command registry, it will be ready to interpret user speech. When SayKit receives a message that the user is speaking a command, it consults the registry user to determine what action to take.

## Standard Command Recognizers

SayKit has a set of predefined commands that it can recognize, like "Help", "Search", and "Select". Each of these standard recognizers is a subclass of `SAYVerbalCommandRecognizer`, which knows what to do with commands of its assigned `commandType`. We'll demonstrate how to use standard command recognizers, as well as how to add our own customizations.

In this part of the tutorial, we'll add command recognizers directly to the Conversation Manager's command registry, since we're using a flat `SAYCommandRecognizerCatalog`. In more complex apps, we might register command recognizers with a Conversation Topic instead. Check out the [Conversation Topic Tutorial]({{ "/tutorial/07-conversation-topics/" | prepend: site.baseurl }}) for more information.

First, let's get a handle on the system's conversation manager. In `ViewController`'s `viewDidLoad`:

```swift
    let commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
```

Add a `SAYAvailableCommandsCommandRecognizer` to the registry, and define its `responseTarget` and `action`. This recognizer will respond to speech like "What can I say?" and "What are the available commands?".

```swift
override func viewDidLoad() {
    /* ... */
    commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "availableCommandsRequested"))
    /* ... */
}

/* ... */

func availableCommandsRequested() {
    presentResultText("Received command:\n[Available Commands]")
}

/* ... */
```

Recall that our `presentResultText:` method is just a helper that updates our feedback UILabel and speaks via our soundBoard. In a *real* app, you could take this opportunity to present a list of available commands to the user.

Commands that include parameters, such as the speech rate in the built-in "Set Speech Rate to X" command, can be accessed in the action method by including a `SAYCommand` argument in the method signature.

A `SAYCommand` is a representation of a command issued by the user, and consists of an identifying `type` and a `parameters` dictionary. In this example, our `SAYSetSpeechRateCommandRecognizer` is preconfigured to respond to commands with the type `SAYStandardCommandSetSpeechRate`. We can expect to find the new speech rate stored in `parameters` with the key `SAYSetSpeechRateCommandRecognizerParameterSpeechRate`. Take a look at _SAYStandardCommandLibrary.h_ for a full list of standard command string constants.

```swift
override func viewDidLoad() {
    /* ... */
    commandRegistry.addCommandRecognizer(SAYSetSpeechRateCommandRecognizer(responseTarget: self, action: "setSpeechRateRequested:"))
    /* ... */
}

/* ... */

func setSpeechRateRequested(command: SAYCommand)
{
    if let newSpeechRate = command.parameters[SAYSetSpeechRateCommandRecognizerParameterSpeechRate] {
        self.presentResultText("Received command:\n[Set speech rate to \(newSpeechRate)]")
    }
    else {
        /* ... */
    }
}

/* ... */
```

In addition to the target/action-style initializer for command recognizers, you can also create them by defining an `actionBlock`. This works especially well in Swift:

```swift
    commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
        if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
            self.presentResultText("Received command:\n[Search for \(searchQuery)]")
        }
        else {
            /* ... */
        }
    }))    
```

But wait, there's more we can do with standard command recognizers, and it involves followup requests!

[Next - Command Recognizers with Followup Requests >>]({{ "/tutorial/04-command-recognizers-part-2/" | prepend: site.baseurl }})
