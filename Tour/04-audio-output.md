# Audio Output

One major hurdle in building applications with rich speech & audio output is that timing concerns begin to dominate application logic. Synchronizing queued speech utterances, multiple sound clips, and background music with an interactive application is very challenging to get right. SayKit’s audio UI tools are built with an eye towards reducing this friction so a developer can concentrate more on user experience and less on nuts and bolts. 

To achieve this, all of the sounds that SayKit produces is made of the same "stuff": **Audio Events**. Rather than considering speech synthesizers, audio files, and even durations of silence as separate entities in need of coordination, all of these concepts are exposed as subclasses of `SAYAudioEvent.

// TODO: add figure showing Event traveling from Source --> Listener/Manager --> Track


Events are transformed into actual sound after being queued up on *Audio Tracks*. Each *event* added to an `SAYAudioTrack` is presented through the speaker, one-by-one. The *conversation manager* coordinates a prioritized set of these tracks. Higher priority tracks are permitted to play sounds before lower priority ones.

Who produces these *events*? Well, *Audio Event Sources*, of course. Classes that implement the `SAYAudioEventSource` protocol post audio events to anyone listening. The *conversation manager* is one such listener, and it associates each source with one of it's *audio tracks*. It sends each *event* it receives to the *source*'s corresponding *track*.

Let's sum it all up with an example:

````swift
// A Sound Board can create basic audio events. It conforms to SAYAudioEventSource.
let soundBoard = SAYSoundBoard()	

// The system manager has a "Main" track built-in.
let manager = SAYConversationManager.systemManager()
manager.addAudioSource(soundBoard, forTrack:SAYAudioTrackMainIdentifier)	

// It speaks! (Well, technically the track speaks.) It *indirectly* speaks!
soundBoard.speakText("Hello nurse!")	
````

While this might seem like a bit of overheard just to play a sound, when an application finds itself with a set of priority-driven, hierarchically-structured audio sources (and as it grows, *it will*), boiling eveything down into events, tracks, and sources pays huge dividends.

... But we'll get to that.

We've got the basics down now. But don't leave the tour quite yet. At the next stop, we'll bring it all together when we introduce SayKit's secret weapon, Conversation Topics.

[Next - Conversation Topics >>](./05-audio-output.md)
