# SayKit Overview

## Conversation Manager

The `SAYConversationManager` is the keystone of the SayKit framework. Much like `UIWindow`, it acts as the logical root of the user interface, administering and coordinating both the "input" and "output" sides of the audio UI.

On the "input" side, the *manager* is responsible for initiating question-and-answer prompts, and interpreting commands spoken by the user.
As for the "output" side, the *manager* received audible events from various sources and schedules them to be played on their assigned audio tracks.

Each SayKit app has a default `systemManager` ready and waiting, accessibile as a class-level property on `SAYConversationManager`.

But enough about the foundation. Let's go over all these interface components in a bit more detail to really highlight what SayKit is all about.

## Voice Requests

The user speech-end of a SayKit app revolves around the `SAYVoiceRequest` class. A *Voice Request* encapsulates the entire "question-answer" process of a dialogue turn: everything between a presenting prompt asking the user for speech to triggering the actions in response to that speech.

// TODO: add figure depicting scenarios for sample requests

For example, if the application needs to ask the user for permission to do something, it can create a `SAYConfirmationRequest`, like so:

````swift
let request = SAYConfirmationRequest(promptText: "Are you sure?") { doIt: Bool in
	if doIt { /* do it! */ }
	else    { /* don't do it */ }
}
````

If the app needs the user to choose a color for the shirt she just added to her cart, it can use a `SAYSelectRequest`:

````swift
let request = SAYSelectRequest(
	options: ["Blue", "Green", "Purple"],
	promptText: "What color would you like?") { option: SAYSelectOption in
		// add it to the cart with the given color choice
	}
````

*Voice requests* are versitile. They can be presented along with related visual controls, they can be extended to provide customized speech interpretation, they be chained together to provide continuous back-and-forth dialogues, and much more. To learn more, [skip straight to the *Voice Requests* page](./02-voice-requests.md).

## Command Recognizers

Sometimes, the user will want to issue a voice command to the app directly. These *Command Requests* have very different properties than the typical *voice request* described above. First off, the user could literally say anything, so the app has to interpret the speech without much context to go on. Secondly, since the user initiated this request, the app doesn't have a callback waiting to directly handle the response.

SayKit provides the `SAYCommandRecognizer` class to handle this situation. A `SAYCommandRecognizer` subclass knows how to look out for specific speech patterns, and instances of them know exactly where commands should be delivered to. For example:

````swift
init() {
	let searchRecognizer = SAYSearchCommandRecognizer(
		responseTarget: self, 
		action: "searchRequested:")
    ...
}

func searchRequested(command: SAYCommand) {
	// run a search with a query string inside `command`
}
````

This should ring a bell to those familiar UIKit users: the `SAYCommandRecognizer` class is similiar in spirit (and in syntax) to the `UIGestureRecognizer` class, so recognizing a search command is as easy as recognizing a swipe.

(And yes, Swift fans, the Command Recognizers can be defined with a tidy closure-based syntax as well.)

````swift
let searchRecognizer = SAYSearchCommandRecognizer() { command in ... }
````

SayKit comes with a large number of pre-built command recognizers, but you can modify them to handle broader speech input, or even create your own recognizers to handle custom commands. For more details, [skip to the *Command Recognition* section](./03-command-recognition.md).

## Audio Events

All of the sounds that SayKit produces is made of the same "stuff": subclasses of `SAYAudioEvent`. Rather than considering speech synthesizers, audio files, and even durations of silence as separate entities in need of coordination, all of these concepts are exposed as an *Audio Event*.

Events are transformed into actual sound after being queued up on *Audio Tracks*. Each Event added to an `SAYAudioTrack` is presented through the speaker, one-by-one. The *conversation manager* coordinates a set of these tracks.

Who produces these *events*? Well, *Audio Event Sources*, of course. Classes that implement the `SAYAudioEventSource` protocol post audio events to anyone listening. The *conversation manager* is one such listener, and it associates each source with one of it's *audio tracks*. It sends each *event* it receives to the *source*'s corresponding *track*.

// TODO: add figure showing Event traveling from Source --> Listener/Manager --> Track

Let's sum it all up with an example:

````swift
// A Sound Board can create basic audio events. It conforms to SAYAudioEventSource.
let soundBoard = SAYSoundBoard()	

// The system manager has a "Main" track built-in
let manager = SAYConversationManager.systemManager()
manager.addAudioSource(soundBoard, forTrack:SAYAudioTrackMainIdentifier)	

// It speaks!
soundBoard.speakText("Hello nurse!")	
````

While this might seem like a lot of overheard just to play a sound, when an application finds itself with a set of priority-driven, hierarchically-structured audio sources (and as it grows, *it will*), boiling eveything down into events, tracks, and sources pays huge dividends.

... But we'll get to that. To learn more about the basics of audio production, [head straight to the *Audio Output* section](./audio-output.md).

Otherwise, let's dive a little deeper into all of these concepts, one-by-one, as we continue the tour.

[Next - Voice Requests >>](./02-voice-requests.md)
