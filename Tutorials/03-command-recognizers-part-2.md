# Command Recognizers - Part 2

## Followup Requests

Sometimes we may need to prompt the user for clarification. A common scenario is when the user leaves out some information that we need (User: _"I choose you, Pikachu!"_, App: _"Did you mean Toby Pikachu or Susan Pikachu?"_). In such cases, we can respond to the user with a followup voice request.

In previous examples we created our command recognizers using the `initWithResponseTarget:action:` initializer and the `initWithActionBlock:` initializer. Here we'll use a third alternative: the `initWithResponseBuilder` initializer, which accepts a block that accepts a `SAYCommand` and returns a `SAYVoiceRequestResponse`. Given a user command, this block _builds_ a _response_ for the app, hence the name "response builder".

A voice request response contains everything we need to know to respond to the user, including an `action` block, a `followupRequest`, and a `feedbackPrompt`, all of which are optional and can be mixed and matched to the desired effect. There is also a convenience method `terminalResponseWithAction:` if an `action` is all that's needed.

```swift
let helpIsAvailable = true
// Note the action block's signature: we're returning a response now
commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
    if helpIsAvailable {
        // respond with a new voice request
        let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: { result in
            self.updateAppResultLabelWithText("Received command:\n[Help with \"\(result)\"")
        })
        return SAYVoiceRequestResponse(followupRequest: followupRequest)
    }
    else {
        // no need to follow up, just terminate the request and run the given action block
        return SAYVoiceRequestResponse.terminalResponseWithAction({
            self.updateAppResultLabelWithText("Received command:\n[Help, but none is available]")
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

We can do a lot using standard recognizers, but let's look into how we can customize command recognizers even more.

[Next - Extending Standard Command Recognizers >>](./02-command-recognizers-part-3.md)