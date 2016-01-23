# Audio Output

One major hurdle in building applications with rich speech & audio output is that timing concerns begin to dominate application logic. Synchronizing queued speech utterances, multiple sound clips, and background music with an interactive application is very challenging to get right. SayKit’s audio UI tools are built with an eye towards reducing this friction so a developer can concentrate more on user experience and less on nuts and bolts. 

## Audio Flow

// TODO: add figure showing Event traveling from Source --> Listener/Manager --> Track

### Events

To achieve this, all of the sounds that SayKit produces is made of the same "stuff": **Audio Events**. Rather than considering speech synthesizers, audio files, and even durations of silence as separate entities in need of coordination, all of these concepts are exposed as subclasses of `SAYAudioEvent.

### Tracks
Events are transformed into actual sound after being queued up on *Audio Tracks*. Each *event* added to an `SAYAudioTrack` is presented through the speaker, one-by-one. The *conversation manager* coordinates a prioritized set of these tracks. Higher priority tracks are permitted to play sounds before lower priority ones.

### Sources

Who produces these *events*? Well, *Audio Event Sources*, of course. Classes that implement the `SAYAudioEventSource` protocol post sequences of audio events to anyone listening. The *conversation manager* is one such listener, and it associates each source with one of it's *audio tracks*. It queues up each sequence of *events* it receives from a *source* to its corresponding *track*.

One example source is a class called the `SAYSoundBoard`. Sound boards are simple objects that can produce individual sounds: specifically speech and tones. When a sound board is asked to produce a sound, it creates the corresponding audio event and posts it to all of it's listeners.

Let's use a sound board to sum it all up with an example:

````swift
let soundBoard = SAYSoundBoard()	

// The system manager has a "Main" track built-in.
let manager = SAYConversationManager.systemManager()
manager.addAudioSource(soundBoard, forTrack:SAYAudioTrackMainIdentifier)	

soundBoard.speakText("Hello nurse!")	

// It speaks! 
// (Well, technically it tells the manager what it wants to say, and the manager queues it up.) 
// It *indirectly* speaks!
````

While this might seem like a bit of overheard just to play a sound, when an application finds itself with a set of priority-driven, hierarchically-structured audio sources (and as it grows, *it will*), boiling eveything down into events, tracks, and sources pays huge dividends.

... But we'll get to that.

---

We've got the basics down now. But don't leave the tour quite yet. At the next stop, we'll bring it all together when we introduce SayKit's secret weapon, Conversation Topics.

[Next - Conversation Topics >>](./05-audio-output.md)
