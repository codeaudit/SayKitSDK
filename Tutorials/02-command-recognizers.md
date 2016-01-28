# Command Recognizers

In visual-based apps, users interact by tapping or swiping the screen. If they tap a button, they probably intend to trigger an action associated with that button, which makes our job simple: do the action!

Contrast this with conversational apps, where users interact by speaking. When they say something we recognize, we interpret their intent as a command and execute the command.

This encompasses several steps as the user’s speech is converted to text (`SAYSpeechTranscript`), interpreted as an intent (`SAYSpeechIntent`), and finally converted to a command (`SAYCommand`) that is associated with an app-defined action. This is analogous to UIKit's progression of user taps being translated into screen coordinates as a tap event, which is passed to the encompassing view that reacts to the event.

But we don't typically worry about these steps when we create a visual app using UIKit, and creating a conversational app with SayKit is no different. All we need to do is register a `SAYCommandRecognizer` and a corresponding action with the Conversation Manager's command registry. SayKit consults the registry whenever it receives an intent from the user to determine what action to take.

## Standard Command Recognizers

SayKit has a set of predefined commands that it can recognize, like "Help", "Search", and "Select". Each of these standard recognizers is a subclass of `SAYVerbalCommandRecognizer`, which knows what to do with commands of its assigned `commandType`. We'll demonstrate how to use standard command recognizers, as well as how to add our own customizations.

In this part of the tutorial, we'll add command recognizers directly to the Conversation Manager's command registry, since we're using a flat `SAYCommandRecognizerCatalog`. In more complex apps, we might register command recognizers with a Conversation Topic instead. Check out the [Conversation Topic Tutorial](./04-conversation-topics.md) for more information.

First, let's get a handle on the system's conversation manager. In `ViewController`'s `viewDidLoad`:

```swift
    let commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
```

Add a `SAYAvailableCommandsCommandRecognizer` to the registry, and define its `responseTarget` and `action`. This recognizer will respond to speech like "What can I say?" and "What are the available commands?".

```swift
override func viewDidLoad() {
    /* ... */
    commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "availableCommandsRequested"))
    /* ... */
}

/* ... */

func availableCommandsRequested() {
    updateAppResultLabelWithText("Received command:\n[Available Commands]")
}

/* ... */
```

Recall that our `updateAppResultLabelWithText:` method is just a helper that updates our feedback UILabel. In a *real* app, you could take this opportunity to present a list of available commands to the user (check out [how SayKit can help with that](#)!).

Commands that include parameters, such as the speech rate in the built-in "Set Speech Rate to X" command, can be accessed in the action method by including a `SAYCommand` argument. In a visual-based app, we would grab the parameter from a UITextField. Using SayKit, we can simply access the `SAYCommand`'s `parameters` property and extract the parameter that we need.

A `SAYCommand` is a representation of a command issued by the user, and consists of an identifying `type` and a `parameters` dictionary. In this example, our `SAYSetSpeechRateCommandRecognizer` is preconfigured to respond to commands with the type `SAYStandardCommandSetSpeechRate`. We can expect to find the new speech rate stored in `parameters` with the key `SAYSetSpeechRateCommandRecognizerParameterSpeechRate`. Take a look at the [`SAYStandardCommandLibrary.h`](https://github.com/ConversantLabs/SayKitSDK/blob/master/SayKit.framework/Headers/SAYStandardCommandLibrary.h) header for a full list of standard command string constants.

```swift
override func viewDidLoad() {
    /* ... */
    commandRegistry.addCommandRecognizer(SAYSetSpeechRateCommandRecognizer(responseTarget: self, action: "setSpeechRateRequested:"))
    /* ... */
}

/* ... */

func setSpeechRateRequested(command: SAYCommand)
{
    if let newSpeechRate = command.parameters[SAYSetSpeechRateCommandRecognizerParameterSpeechRate] {
        self.updateAppResultLabelWithText("Received command:\n[Set speech rate to \(newSpeechRate)]")
    }
    else {
        /* ... */
    }
}

/* ... */
```

In addition to the `target:action:` initializer for command recognizers, you can also create them by defining an `actionBlock`. This works especially well in Swift:

```swift
    commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
        if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
            self.updateAppResultLabelWithText("Received command:\n[Search for \(searchQuery)]")
        }
        else {
            /* ... */
        }
    }))    
```

## Followup Requests

Sometimes we may need to prompt the user for clarification. A common scenario is when the user leaves out some information that we need (User: "I choose you, Pikachu!", App: "Did you mean Toby Pikachu or Susan Pikachu?"). In such cases, we can respond to the user with a followup voice request.

In previous examples we created our command recognizers using the `target:action:` initializer and the `actionBlock` initializer. Here we'll use the `responseBuilder` initializer, which is simply a block that accepts a `SAYCommand` and returns a `SAYVoiceRequestResponse`. 

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

Note that you could accomplish the same effect while still initializing the command recognizer using the `target:action:` paradigm by ensuring that your `action` method has one of the following signatures:
```swift
func responseToCommand() -> SAYVerbalCommandResponse
```
or
```swift
func responseToCommand(command: SAYCommand) -> SAYVerbalCommandResponse
```

In addition to a followup request, we can also create a feedback prompt to be presented with our response.

```swift
// ...
let feedbackPrompt = SAYVoicePrompt(message: "Go away!")
return SAYVoiceRequestResponse(feedbackPrompt: feedbackPrompt, followupRequest: nil, action: nil)
// ...
```

## Custom Command Recognizers

### Extending Standard Command Recognizers

These standard command recognizers are great! But of course they're not going to cover every situation, so let's look at how we can make our own.

The most straightforward way to add our customization is to piggy-back on an existing standard command recognizer. Suppose we have a `SAYSelectCommandRecognizer` setup like so:
```swift
let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
    if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
        self.updateAppResultLabelWithText("Received command:\n[Select \(itemName)]")
    }
    else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
        self.updateAppResultLabelWithText("Received command:\n[Select item number \(itemNumber)]")
    }
    else {
        /* ... */
    }
})
commandRegistry.addCommandRecognizer(selectRecognizer)
```

This will recognize phrases like "Select the third one" or "Select Jiffy", but maybe we know our users tend to make selections using some other phrase. We can simply add a `SAYTextCommandMatcher` to the selectRecognizer. Text matchers give command recognizers another way to identify when to respond to user speech.

Objects conforming to the `SAYTextCommandMatcher` protocol will process a user's speech transcript and return the likelihood that the given text corresponds to some command. Here we'll use the implementation `SAYPatternCommandMatcher`, which is initialized with an array of text "patterns" that are used to process the speech transcript. If the transcript matches any of the patterns, then the Matcher returns a positive response along with any pattern parameters, marked by an "@" prefix.

Adding a text matcher is a good way to handle simple speech patterns, and requires very little setup. With a little more setup we can define how to process the text ourselves using a `SAYBlockCommandMatcher` (see below). If you find yourself in need of more flexibility when interpreting a user’s intent, you may want to consider setting up and linking to your own intent recognition service [(coming soon!)](https://github.com/ConversantLabs/SayKitSDK/blob/master/roadmap.md#cloud-based-intent-recognition-services).

```swift
let pattern = "i choose you @name"  // Note our custom parameter, "name"
selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
```

Phrases matching our new pattern will now be recognized by our selectRecognizer, and we can handle our new custom parameter, "name". Our entire setup should now look like this:

```swift
let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
    if let name = command.parameters["name"] {  // Note our custom parameter, "name"
        self.updateAppResultLabelWithText("Received command:\n[Choose \(name)!]")
    }
    else if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
        self.updateAppResultLabelWithText("Received command:\n[Select \(itemName)]")
    }
    else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
        self.updateAppResultLabelWithText("Received command:\n[Select item number \(itemNumber)]")
    }
    else {
        /* ... */
    }
})
let pattern = "i choose you @name"  // Note our custom parameter, "name"
selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
commandRegistry.addCommandRecognizer(selectRecognizer)
```

>  In general, the syntax of a pattern is "@parameterName:ParameterType", where ParameterType can be either "String" or "Number". If ":ParameterType" is omitted, the parameter is assumed to be a String.

> Here are a few examples:

>>"Call @recipient:String."

>>"Ask @nameOfFriend for @cookieCount:Number cookies."

>>"@payer gave @payee @amount:Number dollars."

>>"@payee received @amount:Number dollars from @payer."  

### Implementing `SAYCustomCommandRecognizer`

Another way to customize our recognizers is to make our own! The procedure is almost identical to the previous `selectRecognizer` example, but our new recognizer will rely completely on text matchers. 

Say we want to recognize when the user says "Hello". We can do that by defining our own `SAYCustomCommandRecognizer`, which is a subclass of `SAYVerbalCommandRecognizer` with no predefined notion of what command it should recognize nor how to recognize it. We define these ourselves via its `customType` and a `SAYPatternCommandMatcher`:

```swift
let greetingsRecognizer = SAYCustomCommandRecognizer(customType: "Greeting") { command in
    self.updateAppResultLabelWithText("Received command:\n[Greetings!]")
}
let patterns = ["hello", "hey", "what's up", "greetings"]
greetingsRecognizer.addTextMatcher(SAYPatternCommandMatcher(forPatterns: patterns))
commandRegistry.addCommandRecognizer(greetingsRecognizer)
```

Another way to think of what's going on here is, "If the user says any of these patterns, it's a "Greeting" command, so execute this action block".

If we want to process spoken text in a way that's difficult to express in a simple pattern, we can instead use a `SAYBlockCommandMatcher`. It defines a block that passes in the spoken transcript and returns a `SAYCommandSuggestion`, which is a struct-like class that contains the likelihood of a match and any relevant parameters.

```swift
greetingsRecognizer.addTextMatcher(SAYBlockCommandMatcher { text -> SAYCommandSuggestion? in
    return text.containsString("hi") ? SAYCommandSuggestion(confidence: kSAYCommandConfidenceLikely) :
                                       SAYCommandSuggestion(confidence: kSAYCommandConfidenceUnlikely)
})
```

___

Now that our command registry is loaded up with command recognizers, our app can recognize what's being said and act accordingly. But what if the app already knows that the user wants to, say, perform a search, and just needs to prompt them for the search query? 

That sounds like a job for voice requests!

[Next - Voice Requests >>](./03-voice-requests.md)