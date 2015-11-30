
# Core Concepts

Before diving into the meat of the guide, it’s a good idea familiarize yourself with the following concepts.

[insert graphical representation of the three sections as colored boxes with titles and a few bullets of their responsibilities]

## Voice Requests

The user speech-end of a SayKit app revolves around the VoiceRequest class. A VoiceRequest encapsulates the entire process between the application prompting the user for speech and the actions the application takes in response to that speech.

If the application needs a yes or no confirmation, the application can issue a `ConfirmationRequest` to ask the user. If the application would like the user to select a choice from a predefined list, it can start a `SelectRequest`. SayKit provides many pre-built requests like these, as well as the ability to extend a `VoiceRequest` as needed by the application developer.

[insert flow of a simple request with diagram]

For more information, skip straight to the [Voice Request section](../VoiceRequests/).

## Producing Audio

The other end of a conversational interface is the audio output through the device speakers. SayKit offers a unified approach to presenting all audio output via the `AudioTrack`  class.

In essence, an `AudioTrack`  is a queue of `AudioEvent`s. Such an event can take many forms: a speech utterance, musical tone, or even a duration of silence is considered an Audio Event. Each event added to an `AudioTrack` is presented to the user in a first-in first-out order.

[insert visualization of a track with a few events]

By managing a collection of `AudioTrack`s, SayKit allows developers to define complex audible feedback for users via a simple programming interface with predictable behavior. For more details, skip to the [Audio Production section](../AudioProduction/).

## User Commands

One of the major benefits of a conversational UI is that it gives users the ability to issue commands directly with verbal commands. To give the user this ability, a special kind of `VoiceRequest` is initiated, the `VerbalCommandRequest`.

Most types of requests are intended to prompt for specific, directed input from the user -- for example, a `ConfirmationRequest` is often used to receive a yes/no answer before continuing with an action. In contrast, a `VerbalCommandRequest` may be initiated by the user at any time to issue a completely unconstrained directive to the application. Different contexts can result in different interpretations and intended responses.

SayKit offers a collection of tools to help manage this dynamic command processing behavior, which are divided into two stages. At a high-level, text is first resolved into a set of potential commands by the *Command Resolution* tools. These commands are then sent to the proper responder in the application by the *Command Responding* tools. A user’s context can have an affect on both stages of this pipeline.

[insert simple command pipeline visualization]

For more information, skip to the [Handling User Commands section](../HandlingUserCommands/).

Next
