# Feature Roadmap

## To Version 1.0

We're actively iterating the SayKit iOS SDK as we march to version 1.0. Here are a few features you can expect as we prepare for that release.

#### Cloud-based intent recognition services

Lately, a collection of cloud-based products have been appearing that provide intent recognition as a service (e.g. [Microsoft's LUIS](https://www.luis.ai), [Wit.ai](https://wit.ai)). While SayKit has been designed specifically to keep as much logic as possible on-device, these services offer a robust natural language understanding that is difficult to replicate. We will soon open up our `SAYCommandRecognizer` class to support using these types of services as a backend.

#### Deeper UIKit integration

It's no accident that many SayKit APIs bear a resemblance to UIKit APIs. These parallels allow for intuitive integrations between the two interface modalities. This kind of union is already possible with minimal overhead, but we'll soon be introducing standard patterns and tools to streamline the process even further.

#### Standard Conversation Topics

As mentioned in [our tour](./Tour/06-conversation-topics.md), there are plenty of patterns for which general pre-built `SAYConversationTopic` classes would be useful (e.g. a *ListTopic* class containing interface logic around navigating lists).

#### More Standard Command Recognizers

We're continuously adding more general-use command recognizers that are ready to be used out-of-the-box.

#### Improved voice recognition latency

Expect improvements in latency of voice requests as we revisit the speech recognition services utilized by SayKit.

## Beyond 1.0

We have plans to enhance SayKit well beyond version 1.0. Here is just a few of the features on our roadmap after our initial release.

#### Declarative Dialogues

Modern iOS developers expect to build their graphical UIs in a declarative-style, using visual tools like Interface Builder instead of large blocks of view configuration code. We think defining conversational interfaces in imperative clode blocks is less than ideal as wellclumsy, and aim to provide declarative tools to define dialogue flows.

#### Always-on Listening Mode

The ability to speak to an app without using your hands opens up the possibility for much more natural interaction with a dialogue system. At the moment, the SayKit preview only supports a "tap-to-speak" mode, but always-listening mode is in the works.

#### Context Sensitive Help

The first thing many new users of an app want is some orientation: discover what they can say and discover what the app can tell them. SayKit's "conversation hiearchy" approach to application state provides a natural way to offer context-senstive help in a standardized way. Expect new features on the `SAYConversationTopic` class to support this functionality.

#### Native Swift framework

While our Objective-C framework is perfectly usable from Swift, there are a few Swift-only features that taking advantage of would further improve the clarity and simplicity of our iOS SDK (e.g. generics, protocol extensions).
