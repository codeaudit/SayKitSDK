---
layout: default
title: "SayKit Tutorial -- Voice Request Responses and Turn-Taking"
permalink: "/tutorial/03-voice-request-responses/"
---

# Voice Request Responses and Turn-Taking

In the last section, we responded to our voice requests with simple action blocks. It was a nice clean way to respond to a basic request, but what if you want to do soemthing more involved? What if the user's speech didn't make sense? What if there was an error somewhere along the line? What if you wanted to respond with another question for the user? That's where `VoiceRequestResponse`s come in.

A `SAYVoiceRequestResponse` defines behavior for SayKit to follow to finish up a voice request session. As mentioned in the [Tour]({{"/tour/voice-requests#responses--turn-taking" | prepend: site.baseurl }}), This includes the following 3 components:

1. A feedback message (with an optional supplemental view): the **feedback prompt**
2. Arbitrary application code: the **action**
3. A new voice request: the **followup request**

Under the hood, the completion blocks we used in the last section when creating our requests were wrapped up and used as the **action** block of a formal response. All of SayKit's built-in request classes offer this convenience.

All requests have a component that implements the `SAYVoiceRequestResponder` protocol, which is responsible for building the response. Basically, a responder defines how to handle the outcome of a request and turn it into a usable `SAYVoiceRequestResponse`. Check out the [protocol header](https://github.com/ConversantLabs/SayKitSDK/blob/master/SayKit.framework/Headers/SAYVoiceRequestResponder.h) for all the juicy details.

#### Standard Request Responder

But who wants to build a responder class from scratch for every custom request we make? Especially if your error handling, for example, will be the same in every case. That's where `SAYStandardRequestResponder` comes in! It implements the `SAYVoiceRequestResponder` protocol with sane default behavior that you can customize piece by piece as needed.

The `SAYStandardRequestResponder` is designed to handle three typical response outcomes:

- **Success**: User speech was successfully interpreted
- **Invalid**: User speech was recognized, but wasn't understood in the current context (for example: *App: "Are you sure?" User: "Peanut butter!" App: "Huh?"*)
- **Failure**: Request either reached its retry limit, was cancelled by the user, or encountered a fatal error

We can customize any (or all, or none!) of these behaviors via their corresponding properties:

- `successResponder` - a block that accepts an interpreted result and returns a `SAYVoiceRequestResponse`
- `invalidResponder` - a block that accepts the session's validation errors and returns a `SAYVoiceRequestResponse`
- `failureAction` - an arbitrary action block

#### Select Request with Turn-Taking

But first, here's the setup. As in the other requests, we'll hook this request up to a button press. We'll use our earlier "Select" example as a starting point:

```swift
@IBAction func selectRequestWithTurnTaking(sender: AnyObject)
{
    let options = [SAYSelectOption(label: "Blue", aliases: ["Ocean"]),
                   SAYSelectOption(label: "Green", aliases: ["Forest", "Emerald"]),
                   SAYSelectOption(label: "Purple")]
    
    let selectPrompt = SAYVoicePrompt(message: "What color would you like?")
    
    let selectResponder = /*...*/
    
    let selectRequest = SAYSelectRequest(options: options, prompt: selectPrompt, responder: selectResponder)
    
    SAYConversationManager.systemManager().presentVoiceRequest(selectRequest)
}
```

Now let's fill in the components of the responder! We'll leave the `invalidResponder` alone, but let's override the `successResponder` and `failureAction` blocks:

```swift
let selectResponder = SAYStandardRequestResponder()
selectResponder.successResponder = /*...*/
selectResponder.failureAction = /*...*/
```

#### Success Responder

All of the fun stuff happens within the `successResponder`. This is where we take the interpreted result and create any followups we might want. In this case, let's include a feedback prompt that tells the user what we think they selected, as well as a followup request to confirm that's what they wanted.

This is a responder for a `SAYSelectRequest`, so we know that `interpretationValue` is going to be a `SAYSelectResult`. If all goes well, the result should contain a `SAYSelectOption`, which itself has the `label`, or name, of the selected item.

```swift
selectResponder.successResponder = { (interpretationValue, voiceRequest) -> SAYVoiceRequestResponse in
    if let selectedOption = interpretationValue?.selectedOption {
        let selectedColor = selectedOption.label
        
        let feedbackPrompt = SAYVoicePrompt(message: "You picked: \"\(selectedColor)\".")
        let followupRequest = self.followupRequest(voiceRequest, toConfirmSelection: selectedColor)
        
        return SAYVoiceRequestResponse(feedbackPrompt: feedbackPrompt, followupRequest: followupRequest, action: nil)
    }
    else {
        // Something went wrong. Repeat the request.
        return SAYVoiceRequestResponse(followupRequest: voiceRequest)
    }
}
```

Our helper method `followupRequest:toConfirmSelection:` builds a `SAYConfirmationRequest` to ask the user if they're sure about their selection. If they are, we're done! Otherwise, we repeat the original request so they can make another choice.

We do this by creating another custom responder, this time for a confirmation request, and handling the interpreted result just like we did in the select request. If the user responds yes, we return a terminal response and let app logic take over. If the user responds no, we return a `SAYVoiceRequestResponse` with a followup request.

```swift
private func followupRequest(selectionRequest: SAYVoiceRequest, toConfirmSelection selectedColor: String) -> SAYConfirmationRequest
{
    let prompt = SAYVoicePrompt(message: "Are you sure?")
    
    let confirmationResponder = SAYStandardRequestResponder()
    confirmationResponder.successResponder = { (interpretationValue, voiceRequest) -> SAYVoiceRequestResponse in
        if let doIt = interpretationValue as? Bool {
            if doIt {
                // Success! Done.
                self.presentResultText("Received command:\n[Select color: \"\(selectedColor)\"]")
                return SAYVoiceRequestResponse.terminalResponseWithAction(nil)
            }
            else {
                // Let the user pick a different color. Repeat the original request.
                return SAYVoiceRequestResponse(followupRequest: selectionRequest)
            }
        }
        else {
            // Something went wrong. Repeat the request.
            return SAYVoiceRequestResponse(followupRequest: voiceRequest)
        }
    }
    confirmationResponder.failureAction = /*...*/
    
    return SAYConfirmationRequest(prompt: prompt, responder: confirmationResponder)
}
```

#### Invalid Responder

Sometimes the user will say something we weren't expecting. The `invalidResponder` defines how we want to handle it. Requests can interpret the unexpected as *validation errors*, which are represented by a `SAYValidationError`. Associated with each error is a `type`, such as "Invalid input", and a `reason`, such as "Was expecting a number, but got a string".

The default implementation of the `invalidResponder` will create a feedback prompt depending on the validation error and repeat the original request. We'll leave it alone.

#### Failure Action

The final component is to define what to do when the voice request fails, typically due to the user cancelling the request. Here we'll just let the user know that they've aborted the request.

```swift
selectResponder.failureAction = { voiceRequest in
    self.presentResultText("Aborted your color selection request")
}
```

With our new responder fully in place, we can now create our own version of `SAYSelectRequest` that will respond exactly how we want it do, followups and all! We're constantly working to [improve the process]( {{"/roadmap#declarative-dialogues" | prepend: site.baseurl }}) of defining a dialogue flow, and a `SAYVoiceRequestResponse`-based procedure is a well-structured improvement over, say, scattered calls to the Conversation Manager's `presentVoiceRequest:`.

____

Voice requests are great for asking the user for information, but how do we know what the user wants to do in the first place? If you guessed Command Recognizers, you're right!

[Next - Command Recognizers >>]({{"/tutorial/04-command-recognizers-part-1" | prepend: site.baseurl }})