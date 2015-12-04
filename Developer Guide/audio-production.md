# Audio Production

One major hurdle in building applications with rich speech & audio output is that timing concerns begin to dominate application logic. Synchronizing queued speech utterances, multiple sound clips, and background music with an interactive application is very challenging to get right. SayKit’s audio UI tools are built with an eye towards reducing this friction so a developer can concentrate more on user experience and less on nuts and bolts. 

A key way SayKit helps encourage maintainable audio output is by wrapping up all audio production sources into the same paradigm. Rather than considering speech synthesizers, audio files, system timers, and other sources as separate systems in need of coordination, all sounds follow the same pattern to the speaker: as `AudioEvent`s on `AudioTrack`s.

## Audio Out Anatomy

All audio production by SayKit revolves around the following classes:
- `AudioTrack`: manages a queue of `AudioEvent` instances
- `AudioEvent`: represents an audible message
- `AudioOperation`: carries out the actual mechanics to send information to the speaker

[insert Figure AP 1: class diagram: AudioEvent, AudioOperation, & AudioTrack]

### Audio Events & Operations

Each `AudioEvent` represents an audible message to be conveyed to the user. This message can take the form of synthesized speech, a musical tone, or even a duration of silence (at times, the absence of sound can convey meaning). All that truly typifies an `AudioEvent` is that it represents a non-instantaneous event: its occurrence has a beginning and a non-zero duration.

Technically speaking, the only strict requirement of an `AudioEvent` is that it provides an operations property, which is an array of `AudioOperation` instances. An `AudioOperation` is a subclass of Cocoa's `NSOperation` class, with one additional capability: it offers the ability to have its execution suspended and resumed. An event begins and ends when its series of underlying operations start and finish execution.

### Audio Tracks

An `AudioTrack` manages a sequence of `AudioEvent`s. The track regulates the queueing of events, controlling when each event starts in a serial order. Each track has a single cursor placed at the currently executing event. When an event’s operation completes, the track starts the subsequent event in the sequence and moves the cursor forward. A track is considered live when its cursor is not at the end of its sequence.

Tracks can be suspended and resumed. When suspended, their currently executing operation is suspended as well. Tracks can be both live and suspended, meaning they have pending events that will be played as soon as they are resumed.

[insert code sample filling a track, followed by diagram of the resulting track]
 
## Audio Event Classes

SayKit comes pre-packaged with a collection of useful `AudioEvent` classes. The `AudioEvent` type is actually a protocol, to which the following classes conform.

`SpeechEvent`: produces an operation that uses the system’s `AVSpeechSynthesizer` to speech text utterances
`ToneEvent`: plays a sound contained in an audio file
`MusicalEvent`: similar to a `ToneEvent`, but for longer clips that will repeat continuously
`SilenceEvent`: produces an operation that does nothing (and therefore keeps the speaker idle) for a specified duration
`CompositeEvent`: packages up multiple events into a single divisible unit

### Custom Events

If the built-in events are insufficient, a custom event type can be created by simply implementing the `AudioEvent` protocol (i.e. defining an associated `AudioOperation` class). This custom type will then be handled like any other event. For more implementation details, see the API documentation for `AudioOperation`.

## Coordinating Multiple Tracks

For simple purposes, a single application-wide `AudioTrack` might be all that is necessary. However, this single queue model starts to break down quickly when implementing a truly robust conversational UI.

For example, most SayKit applications have at least 3 different sources of audio output. Let’s discuss these in the context of a theoretical e-mail application.

The basic application audio; this could be used for speaking subject lines or reading email bodies.
Notification audio; to be used for short notifications, e.g. when a new message is received
`VoiceRequest`-related audio; this includes microphone activity tones or direct questions prompts

Each of these sources takes priority over the preceding source. The first is baseline audio, the second is a timely notification, and the third produces realtime audio feedback. A reasonable design choice would only allow one of them to produce sounds at a time, temporarily pausing lower priority sources until higher priority sources are idle.

It is difficult to use a single track to sequence and suspend events from these three dynamic sources. Instead, a better fit is to give each source its own `AudioTrack`. To coordinate this multiple-track paradigm, SayKit introduces the `AudioTrackCoordinator` class.

Applications typically have a single `AudioTrackCoordinator`, which acts as the system-wide traffic cop for managing the application’s tracks. Only one track has permission to access the speaker at a time. Each track is assigned a priority, and a track is given permission to send its queued events to the device speaker as long as no higher-priority tracks are live.

[insert Figure AP 2: diagram of three channels being coordinated into a output single stream]

## Improving Generated Speech

Because conversational apps attempt to present interactions as a verbal conversation, users expect application speech to be expressed in more natural language than they might expect for visual text. Otherwise, the interactions tend to feel a bit robotic.

SayKit provides tools to help facilitate these kinds of natural application responses. Many of these techniques are integrated with localization features in iOS, so their use goes hand-in-hand with general best practices for UI design.

[insert more specific discussion of speech generating tools]

## Multi-modal interfaces

In conversation apps with a heavy visual component, spoken information is often displayed on screen as well. While SayKit’s audio output functionality is completely independant of UIKit’s display functionality, there are many times where dealing with each system in isolation would involve a lot of repetition.

As a result, SayKit offers functionality to bridge the gap so as to avoid specifying application content more than once. For a simple example, a `UILabel` can be designated to fire a `SpeechEvent` to speak its contents when first displayed. Even complex UIKit structures that take advantage of delegation to derive their content can be bridged to SayKit audio. For example, SayKit offers `SAYTableDataSource` as a protocol derived from `UITableViewDataSource`, which allows an existing table view’s **dataSource** to provide a spoken interface with very little modification.

[insert diagrams or code samples of multi-modal presentation examples]

[Next - Handling User Commands](../handling-user-commands/)
