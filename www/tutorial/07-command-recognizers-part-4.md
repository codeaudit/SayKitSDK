---
layout: default
title: "SayKit Tutorial -- Command Recognizers: Part 4"
permalink: "/tutorial/07-command-recognizers-part-4/"
---

# Command Recognizers - Part 4

## Custom Command Recognizers

### Using `SAYCustomCommandRecognizer`

Another way to customize our recognizers is to make our own! The procedure is almost identical to the previous `selectRecognizer` example, but our new recognizer will rely completely on text matchers. 

Say we want to recognize when the user says "Hello". We can do that by defining our own `SAYCustomCommandRecognizer`, which is a subclass of `SAYVerbalCommandRecognizer` with no predefined notion of what command it should recognize nor how to recognize it. We define these ourselves via its `customType` and a `SAYPatternCommandMatcher`:

```swift
let greetingsRecognizer = SAYCustomCommandRecognizer(customType: "Greeting") { command in
    self.presentResultText("Received command:\n[Greetings!]")
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


Now that our command registry is loaded up with command recognizers, our app can recognize what's being said and act accordingly.

With these basic building blocks in place, we can start talking about organizing our conversations at a higher level. Our main tool for that is the Conversation Topic!

[Next - Conversation Topics >>]({{ "/tutorial/08-conversation-topics/" | prepend: site.baseurl }})
