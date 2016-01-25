# Voice Requests

## Basics

The user speech-end of a SayKit app revolves around the `SAYVoiceRequest` class. A **Voice Request** encapsulates the entire "question-answer" process of a dialogue turn: everything between a asking the user a question to triggering an action in response to their answer.

// TODO: add figure depicting scenarios for sample requests

For example, if the application needs to ask the user for permission to do something, it can create a `SAYConfirmationRequest`, like so:

````swift
// Swift
let request = SAYConfirmationRequest(promptText: "Are you sure?") { doIt: Bool in
	if doIt { /* do it! */ }
	else    { /* don't do it */ }
}
````

If the app needs the user to choose a color for the shirt she just added to her cart, it can use a `SAYSelectRequest`:

````swift
// Swift
let request = SAYSelectRequest(
    itemLabels: ["Small", "Medium", "Large"],
    promptText: "What color would you like?") { result in
        // add it to the cart with the given color choice
    }
````

Many voice requests have supplemental visual controls that are automatically presented to the screen when a question is asked. In the case of the select request above, a set of tappable buttons will appear on screen, one per option.

![Select request view](./assets/select-request.png)

SayKit provides many pre-built requests like these, but voice requests are versatile. They can be extended to provide customized speech interpretation, they can be chained together to provide continuous back-and-forth dialogues, their visual components can be customized, and much more. To learn about these features, let's peek under the hood of the voice request session.

## Voice Request Flow

// TODO: insert graphical representation of the flow

Each voice request session has 4 stages:

1. **Prompting** (optional): The app prompts the user for some speech, typically with a question. This may also include presenting visual controls to support touch responses.
2. **Speech recognition**: The microphone activates and accepts user speech. That speech is transformed into meaningful data, typically a string.
3. **Interpretation**: The speech string is interpreted into a useful value. For example, the `SAYConfirmationRequest` transforms the string into a `Bool` value. If no value can be interpreted, a validation error is produced instead.
4. **Responding**: The application decides what to do with the interpreted value (or validation error). This could take the form of spoken feedback, arbitrary application code, the transition to another voice request, or a combination of these.

These stages are handled by a suite of collaborators connected to every `SAYVoiceRequest`, but the details aren't important for simply initiating a standard request. In the `SAYConfirmationRequest` example above, we simply had to provide a prompt message (used for **Prompting**), and a completion block (used in the **Responding** stage).

However, if you need more control, you're free to modify any or all the collaborators driving a voice request. For the particulars, check out the [header documentation for the `SAYVoiceRequest` protocol](#) and the [developer guide post on customizing voice requests](#) (coming soon).

## Responses & Turn-taking

As mentioned above, a response consists of any combination of these 3 factors:

1. A feedback message (with an optional supplemental view): the **feedback prompt**
2. Arbitrary application code: the **action**
3. A new voice request: the **followup request**

The third item there is the key to creating a turn-taking dialogue. By providing a followup request, a request session turns into a cycle, with the app and user taking turns speaking to each other.

// TODO: show request as a cycle with similar style as above figure

Forthcoming SayKit releases will introduce higher-level abstractions that take advantage of this turn-taking mechanism, allowing developers to create entire dialogue trees without dealing with the particulars of inidivudal response handling.

[Next - Command Recognition >>](./03-command-recognition-pt1.md)
