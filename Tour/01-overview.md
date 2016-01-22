# SayKit Overview

## Conversation Management

SayKit exists to enable developers to create applications where interacting with the user interace is as natual as having a conversation. Fittingly, at the base of the SayKit SDK you'll find an agent called the *Conversation Manager*.

The `SAYConversationManager` is the keystone of the SayKit framework. Each SayKit app has a default *manager* ready and waiting, accessibile as a class-level property:

Objective-C:
````objc
[SAYConversationManager systemManager]
````

Swift:
````swift
SAYConversationManager.systemManager()
````

Much like `UIWindow` for UIKit, the manager acts as the logical root of the user interface, administering and coordinating both the input (listening) and output (speaking) roles of the conversational UI. 

To be more concrete, let's introduce the systems that the manager is in charge of coordinating.

### Voice Requests

In SayKit applications, all voice input from the user is handled by the **Voice Request** system. Voice Requests are able to ask the user a question, direct speech recognition and interpretation, decide how to respond, and perform many other duties.

SayKit provides a collection of built-in voice requests for common inqueries (such as the `SAYConfirmationRequest`, which asks the user a yes-or-no question), as well as extensive options for customizing your own.

To read more about this, [skip to the Voice Requests Section](./02-voice-requests.md).

### Command Recognizers

On the other hand, what if the user wants to start the conversation by issuing a command? SayKit provides **Command Recognizers** to listen for these commands at any time. The recognizers are able to interpret user speech as commands and send these commands to any interested parties. 

To read more about this, [skip to the Command Recognition Section](./03-command-recognition.md).

### Audio Output

TODO: Introduce audio events, tracks, and sources, but don't get too jargon-y. Just a couple sentences.

To read more about this, [skip to the Audio Output Section](./04-audio-output.md).

### Conversation Topics

TODO: Mention architecture

To read more about this, [skip to the Conversation Topics Section](./05-conversation-topics.md).

Now, let's take a closer look at each of these components one-by-one as we continue the tour.

[Next - Voice Requests >>](./02-voice-requests.md)
