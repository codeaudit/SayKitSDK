# Voice Requests


The user speech-end of a SayKit app revolves around the `SAYVoiceRequest` class. A **Voice Request** encapsulates the entire "question-answer" process of a dialogue turn: everything between a presenting prompt asking the user for speech to triggering the actions in response to that speech.

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

SayKit provides many pre-built requests like these, as well as providing tools to create custom voice requests tailored to a developer's needs.

Voice requests are versitile. They can be presented along with related visual controls, they can be extended to provide customized speech interpretation, they be chained together to provide continuous back-and-forth dialogues, To learn about these features and more, let's take a deeper look at voice requests.

// TODO: discuss the voice request flow (Prompt->ASR->Interp->Responding->Repeat), turn-taking support, supplemental visual controls

[Next - Command Recognition >>](./03-command-recognition.md)
