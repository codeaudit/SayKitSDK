# SayKit Overview

## Conversation Management

SayKit enables developers to create applications where the user interaction is as natural as having a conversation. Fittingly, at the base of this conversational UI you'll find an agent called the **Conversation Manager**.

The `SAYConversationManager` is the keystone of the SayKit framework. Each SayKit app has a default manager ready and waiting, accessible as a class-level property:

````objc
// Objective-C
[SAYConversationManager systemManager]
````

````swift
// Swift
SAYConversationManager.systemManager()
````

Much like `UIWindow` for UIKit, the manager acts as the logical root of the user interface, administering and coordinating both the input (listening) and output (speaking) roles of the conversational UI. Also, much like `UIWindow`, you can ignore it's presence most of the time after some minor configuration at app launch.

Now, let's have a quick overview of the systems that the manager is in charge of coordinating.

### Voice Requests

In SayKit applications, all voice input from the user is handled by a **Voice Request**. Voice Requests ask the user a question, direct speech recognition and interpretation, decide how to respond, and perform many other duties.

SayKit provides a collection of built-in voice requests for common inquiries (such as the `SAYConfirmationRequest`, which asks the user a yes-or-no question), as well as extensive options for customizing your own.

To read more about this, [skip to the Voice Requests Section](./02-voice-requests.md).

### Command Recognizers

On the other hand, what if the user wants to start the conversation by issuing a command? SayKit provides **Command Recognizers** to listen for these commands at any time. The recognizers are able to interpret user speech as commands and send these commands to any interested parties.

Again, SayKit provides a selection of extendable built-in recognizers (such as the `SAYSearchCommandRecognizer` or `SAYHelpCommandRecognizer`) that are capable of understanding a variety of user speech patterns, and tools exist to create your own recognizers as well.

To read more about this, [skip to the Command Recognition Section](./03-command-recognition.md).

### Audio Output

At the other end of a conversational interface is the audio that is presented through the device speakers. The app's voice.

Of course, SayKit includes all the nuts and bolts required to manage an audio queue -- providing a speech synthesizer, feeding .wav files to audio players, handling timing issues -- but it also presents a higher-level API to let a developer forget about mechanics and focus on user experience.

To read more about this, [skip to the Audio Output Section](./04-audio-output.md).

### Conversation Topics

GUI developers have it made with a feast of patterns and tools to help structure their applications. Visual hierarchies. View controllers. Interface Builder. Storyboards.

If you've ever tried to develop a non-trivial conversational app before, perhaps you had some problems keeping your codebase under control. Don't worry, it used to happen to us too. Logic split between clients and servers, regular expressions around every corner, callback functions strewn around everywhere. There's got to be a better way!

That's where **Conversation Topics** come in. Just like a view packages up all the input/output details for a particular area of your screen, a conversation topic coordinates all the audio I/O related to a particular subject in your app. By adding or removing a topic from your app's topic hierarchy, you can change the conversation with a line of code.

To read more about this, [skip to the Conversation Topics Section](./05-conversation-topics.md).

___

Now, let's take a closer look at each of these components one-by-one as we continue the tour.

[Next - Voice Requests >>](./02-voice-requests.md)
