# Command Recognizers - Part 3

## Extending Standard Command Recognizers

These standard command recognizers are great! But of course they're not going to cover every situation, so let's look at how we can make our own.

The most straightforward way to add our customization is to piggy-back on an existing standard command recognizer. Suppose we have a `SAYSelectCommandRecognizer` setup like so:
```swift
let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
    if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
        self.presentResultText("Received command:\n[Select \(itemName)]")
    }
    else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
        self.presentResultText("Received command:\n[Select item number \(itemNumber)]")
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
        self.presentResultText("Received command:\n[Choose \(name)!]")
    }
    else if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
        self.presentResultText("Received command:\n[Select \(itemName)]")
    }
    else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
        self.presentResultText("Received command:\n[Select item number \(itemNumber)]")
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

> Other parameter types will be supported in the near future.

Now let's leave Standard command recognizers behind, and learn how to create your very own custom command recognizers!

[Next - Custom Command Recognizers >>](./06-command-recognizers-part-4.md)
