---
layout: default
title: "SayKit Tutorial -- Voice Request Responses and Turn-Taking"
permalink: "/tutorial/03-voice-request-responses/"
---

# Voice Request Responses and Turn-Taking

Recall the [String Request (with Followup Request)]({{ "/tutorial/02-voice-requests#string-request-with-followup-request" | prepend: site.baseurl }}) that we created using the convenience initializer, `initWithPromptText:action:`. In that example, we directly presented a followup confirmation request from within the action block via `SAYConversationManager`'s `presentVoiceRequest:` method. This is a fairly inflexible solution, though it worked fine in that simple case.

But what if we want to give the user a chance to change their answer? What if we want to customize how we respond to the user beyond what the standard voice requests do? We could maybe pull this off through some messy if/else statements, but there's a better way!

#### Responder and Responses

SayKit helps construct a back-and-forth dialogue by allowing us to define our own implementation of `SAYVoiceRequestResponder`. The responder is responsible for deciding what to do with the interpreted result of the [voice request session]({{ "/tour/voice-requests#voice-request-flow" | prepend: site.baseurl }}).

All of the standard requests we've used so far have actually shared an implementation of `SAYVoiceRequestResponder` called `SAYStandardRequestResponder`, which lives in the standard request base class, `SAYStandardVoiceRequest`. When we initialize a standard request, we can customize the standard responder via `SAYStandardVoiceRequest`'s `initWithPrompt:responder:` initializer.

So what's the output of a `SAYVoiceRequestResponder`? Why, a `SAYVoiceRequestResponse`, of course! A response can contain a feedback prompt to present to the user, a followup request to continue the turn-taking dialogue, and a user action. The exact contents of these components are defined by the *responder* when it handles the voice request's session interpeted result.

A responder interprets the session's results via three components:

- `successResponder` - a block that accepts an interpreted result and returns a `SAYVoiceRequestResponse`
- `invalidResponder` - a block that accepts the session's validation errors and returns a `SAYVoiceRequestResponse`
- `failureAction` - a block that is triggered after the session failures or is cancelled

So our first step is to build our responder using `SAYStandardRequestResponder`'s initializer, `initWithSuccessResponder:invalidResponder:failureAction:`.

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

Let's fill in the components of the responder!

```swift
let selectResponder = 
    SAYStandardRequestResponder(successResponder: /*...*/, 
                                invalidResponder: /*...*/, 
                                failureAction: /*...*/)
```

#### Success Responder

All of the fun stuff happens within the `successResponder`. This is where we take the interpreted result and create any followups we might want. In this case, let's include a feedback prompt that tells the user what we think they selected, as well as a followup request to confirm that's what they wanted.

This is a responder for a `SAYSelectRequest`, so we know that `interpretationValue` is going to be a `SAYSelectResult`. If all goes well, the result should contain a `SAYSelectOption`, which itself has the `label`, or name, of the selected item.

```swift
let selectResponder = 
    SAYStandardRequestResponder(successResponder: { (interpretationValue, voiceRequest) -> SAYVoiceRequestResponse in
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
        }, 
        invalidResponder: /*...*/, 
        failureAction: /*...*/)
```

Our helper method `followupRequest:toConfirmSelection:` builds a `SAYConfirmationRequest` to ask the user if they're sure about their selection. If they are, we're done! Otherwise, we repeat the original request so they can make another choice.

We do this by creating another custom responder, this time for a confirmation request, and handling the interpreted result just like we did in the select request. If the user responds yes, we return a terminal response and let app logic take over. If the user responds no, we return a `SAYVoiceRequestResponse` with a followup request.

```swift
private func followupRequest(selectionRequest: SAYVoiceRequest, toConfirmSelection selectedColor: String) -> SAYConfirmationRequest
{
    let prompt = SAYVoicePrompt(message: "Are you sure?")
    
    let confirmationResponder = SAYStandardRequestResponder(successResponder: { (interpretationValue, voiceRequest) -> SAYVoiceRequestResponse in
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
    }, invalidResponder: /*...*/,
       failureAction: /*...*/)
    
    return SAYConfirmationRequest(prompt: prompt, responder: confirmationResponder)
}
```

#### Invalid Responder

Sometimes the user will say something we weren't expecting. The `invalidResponder` defines how we want to handle it. Requests can interpret the unexpected as *validation errors*, which are represented by a `SAYValidationError`. Associated with each error is a `type`, such as "Invalid input", and a `reason`, such as "Was expecting a number, but got a string".

We'll respond to invalid errors with a feedback prompt containing the reason, and with the original request as a followup request.

```swift
let selectResponder = SAYStandardRequestResponder(successResponder: /*...*/,
    invalidResponder: { (validationErrors, voiceRequest) -> SAYVoiceRequestResponse in
        if let validationErrorReason = validationErrors.first?.reason {
            let feedbackPrompt = SAYVoicePrompt(message: validationErrorReason)
            return SAYVoiceRequestResponse(feedbackPrompt: feedbackPrompt, followupRequest: voiceRequest, action: nil)
        }
        else {
            // Something went wrong. Repeat the request.
            return SAYVoiceRequestResponse(followupRequest: voiceRequest)
        }
    },
    failureAction: /*...*/)
```

#### Failure Action

The final component is to define what to do when the voice request fails, typically due to the user cancelling the request. Here we'll just let the user know that they've aborted the request.

```swift
let selectResponder = SAYStandardRequestResponder(successResponder: /*...*/, invalidResponder: /*...*/,
    failureAction: { () -> Void in
        self.presentResultText("Aborted your color selection request.")
    })
```

Or the Swift-ier version:

```swift
let selectResponder = SAYStandardRequestResponder(successResponder: /*...*/, invalidResponder: /*...*/) {
    self.presentResultText("Aborted your color selection request.")
}
```

With our new responder fully in place, we can now create our own version of `SAYSelectRequest` that will respond exactly how we want it do, followups and all! We're constantly working to [improve the process]( {{"/roadmap#declarative-dialogues" | prepend: site.baseurl }}) of defining a dialogue flow, and a `SAYVoiceRequestResponse`-based procedure is a well-structured improvement over, say, scattered calls to the Conversation Manager's `presentVoiceRequest:`.

____

Voice requests are great for asking the user for information, but how do we know what the user wants to do in the first place? If you guessed Command Recognizers, you're right!

[Next - Command Recognizers >>]({{"/tutorial/04-command-recognizers-part-1" | prepend: site.baseurl }})