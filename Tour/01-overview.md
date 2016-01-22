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

TODO: Paragraph about what VReqs are. A super quick example.

### Command Recognizers

TODO: Paragraph about command recognitions.

### Audio Output

TODO: Introduce audio events, tracks, and sources, but don't get too jargon-y. Just a couple sentences.

### Conversation Topics

TODO: Mention architecture

Now, let's take a closer look at each of these components one-by-one as we continue the tour.

[Next - Voice Requests >>](./02-voice-requests.md)
