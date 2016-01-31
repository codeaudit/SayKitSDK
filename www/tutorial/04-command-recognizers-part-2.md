# Command Recognizers - Part 2

## Followup Requests

[Followup requests](./02-voice-requests.md#string-request-with-followup-request) are useful when we need to prompt the user for clarification and can be included as part of our response to a user's command.

In previous examples we created our command recognizers using the `initWithResponseTarget:action:` initializer and the `initWithActionBlock:` initializer. Here we'll use a third alternative: the `initWithResponseBuilder` initializer, which accepts a block that accepts a `SAYCommand` and returns a `SAYVoiceRequestResponse`. Given a user command, this block _builds_ a _response_ for the app, hence the name "response builder".

A voice request response contains everything we need to know to respond to the user, including an `action` block, a `followupRequest`, and a `feedbackPrompt`, all of which are optional and can be mixed and matched to the desired effect. There is also a convenience method `terminalResponseWithAction:` if an `action` is all that's needed.

```swift
let helpIsAvailable = true
// Note the action block's signature: we're returning a response now
commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
    if helpIsAvailable {
        // respond with a new voice request
        let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: { result in
            self.presentResultText("Received command:\n[Help with \"\(result)\"")
        })
        return SAYVoiceRequestResponse(followupRequest: followupRequest)
    }
    else {
        // no need to follow up, just terminate the request and run the given action block
        return SAYVoiceRequestResponse.terminalResponseWithAction({
            self.presentResultText("Received command:\n[Help, but none is available]")
        })
    }
})
```

Note that you could accomplish the same effect while still using the target/action-style initializer by ensuring that your `action` method has one of the following signatures:
```swift
func responseToCommand() -> SAYVerbalCommandResponse
```
or
```swift
func responseToCommand(command: SAYCommand) -> SAYVerbalCommandResponse
```

In addition to a followup request, we can also create a feedback prompt to be presented with our response. This will simply respond to the command with a simple spoken message, nothing more.

```swift
// ...
let feedbackPrompt = SAYVoicePrompt(message: "Go away!")
return SAYVoiceRequestResponse(feedbackPrompt: feedbackPrompt, followupRequest: nil, action: nil)
// ...
```

>On the topic of voice requests, recall from our [earlier discussion](./02-voice-requests.md) that we use voice requests to ask the user parameter-focused questions like "What color would you like?" or "How many servings?". Turns out that voice requests still play an important role with command recognition! Every time you've tapped the microphone button, you were presented with a *command* request, implicitly asking the question "What would you like to do next?".

>The request presented on a microphone tap is a `SAYVerbalCommandRequest`, which implements the `SAYVoiceRequest` protocol. Its creation and presentation is handled behind-the-scenes, unlike other voice requests that we're responsible for creating and presenting.

We can do a lot using standard recognizers, but let's look into how we can customize command recognizers even more.

[Next - Extending Standard Command Recognizers >>](./05-command-recognizers-part-3.md)