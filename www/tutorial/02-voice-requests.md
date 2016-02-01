---
layout: default
title: SayKit Tutorial -- Voice Requests
permalink: "/tutorial/02-voice-requests/"
---

# Voice Requests

Before we hook up those UIButtons we need to cover some voice request basics:

Voice requests play an important role in the question-and-answer process.  As you'll see in this section, we can also create parameter-focused voice requests that ask much more specific questions like "What color would you like?", "How many servings?", or "Are you sure?".

`SAYVoiceRequest` is a protocol whose implementations define a `prompt` to present to the user, and have underlying components that can recognize speech (`recognitionService`), interpret speech into text (`interpreter`), and react to the interpreted result (`responder`). Using these components, SayKit creates a cohesive dialogue flow.

## Standard Voice Requests

SayKit comes with several preconfigured `SAYVoiceRequest` implementations, including `SAYStringRequest`, `SAYSelectRequest`, `SAYNumericalRequest`, `SAYConfirmationRequest`, and `SAYPatternMatchRequest`. Your own custom parameter requests can be created by implementing the `SAYVoiceRequest` protocol. The type of the `result` in each's `action` block depends on its request. For example, a `SAYNumericalRequest`'s result is a number, while a `SAYStringRequest`'s result is a string.

For these examples, we're simply presenting requests as the result of button taps. In your own apps, they might be triggered by some other event, or as part of a [followup request]({{ "/tutorial/04-command-recognizers-part-2" | prepend: site.baseurl }}).


### Confirmation Request

A confirmation request will ask the user a question and expect a yes-or-no response in return. If we get an invalid response, the request will try again (though this behavior can be tweaked). In this case, the `action` block's `result` represents a Bool (though wrapped in an NSNumber because SayKit is an Objective-C SDK).

Once we create the request, we call our the `presentVoiceRequest:` method of the system's `SAYConversationManager`. And that's it!

```swift
@IBAction func confirmationRequestButtonTapped(sender: AnyObject)
{
    let request = SAYConfirmationRequest(promptText: "Are you sure?") { result in
        if let doIt = result as? Bool {
            if doIt { self.presentResultText("Received command:\n[Do it!]") }
            else    { self.presentResultText("Received command:\n[Don't do it!]") }
        }
        else {
            /* ... */
        }
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}
```

### String Request

A string request does what it sounds like: it asks the user for a string! The `action` block's `result` is a String.

```swift
@IBAction func stringRequestButtonTapped(sender: AnyObject)
{
    let request = SAYStringRequest(promptText:"What recipe would you like to search for?") { result in
        if let recipeString = result {
            self.presentResultText("Received command:\n[Search for \(recipeString)]")
        }
        else {
            /* ... */
        }
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}
```

#### String Request (with Followup Request)

Sometimes we may need to prompt the user for clarification. A common scenario is when the user leaves out some information that we need (User: _"I choose you, Pikachu!"_, App: _"Did you mean Toby Pikachu or Susan Pikachu?"_). In such cases, we can respond to the user with a followup voice request.

Let's add a followup to the string request we just made:

```swift
@IBAction func stringRequestButtonTapped(sender: AnyObject)
{
    let request = SAYStringRequest(promptText:"What recipe would you like to search for?") { result in
        if let recipeString = result {
            let followupRequest = self.followupRequestForRecipe(recipeString)
            SAYConversationManager.systemManager().presentVoiceRequest(followupRequest)
        }
        else {
            /* ... */
        }
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}

private func followupRequestForRecipe(recipe: String) -> SAYConfirmationRequest
{
    let followupRequest = SAYConfirmationRequest(promptText: "Are you sure you want to search for \"\(recipe)\"?", action: { result in
        if let doIt = result as? Bool {
            if doIt { self.presentResultText("Received command:\n[Search for \(recipe)]") }
            else    { self.presentResultText("Received command:\n[Don't search for \(recipe)]") }
        }
    })
    
    return followupRequest
}
```

Be sure to check out the [next section]({{ "/tutorial/03-voice-request-responses" | prepend: site.baseurl }}) for a more in-depth discussion on turn-taking dialogues.

### Select Request
How do we present the user with a list of options to choose from?

In a visual-based app, we might build a table view, hook it up to a data source, present it with a table view controller, and respond to a tap on one of the cells via its delegate. Using SayKit, all we need is a `SAYSelectRequest` and an array of options.

Any speech matching one of the options will result in a `SAYSelectResult`, which is a struct-like class containing the selected option and its index. If no matches are found, the request will try again by default.

```swift
@IBAction func selectRequestButtonTapped(sender: AnyObject)
{
    let request = SAYSelectRequest(itemLabels: ["Blue", "Green", "Purple"], promptText: "What color would you like?") { result in
        if
            let selectedItemName = result?.selectedOption.label,
            let selectedIndex = result?.selectedIndex
        {
            self.presentResultText("Received command:\n[Pick color \(selectedItemName) at index \(selectedIndex)]")
        }
        else {
            /* ... */
        }
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}
```

#### Select Request (with Aliases)

Instead of using a flat array of item labels to select from, we can also define aliases for each label. If the user speaks an item's alias, it is treated the same as if they selected the item directly. Using aliases, you can easily handle alternative names for the same item. 

We organize our labels and aliases using a struct-like class, `SAYSelectOption`, which we can use in an alternate initializer of `SAYSelectRequest`:

```swift
@IBAction func selectRequestAliasesButtonTapped(sender: AnyObject)
{
    let options = [SAYSelectOption(label: "Blue", aliases: ["Ocean"]),
                   SAYSelectOption(label: "Green", aliases: ["Forest", "Emerald"]),
                   SAYSelectOption(label: "Purple")]
    
    let request = SAYSelectRequest(options: options, promptText: "What color would you like?") { result in
        self.handleSelectionWithResult(result)
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}
```


____

// TODO: Revise transition

Voice requests are great for asking the user for information, but how do we know what the user wants to do in the first place? If you guessed Command Recognizers, you're right!

[Next - Command Recognizers >>]({{"/tutorial/03-command-recognizers-part-1" | prepend: site.baseurl }})
