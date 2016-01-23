Actively under construction at the moment -- will be fleshed out soon.

## `SAYCommand`

The `SAYCommand` class provides the common currency for recognizing and responding to user commands. It's a simple type with two properties: `type` and `parameters`. Commands are differentiated by their `type`, and they can have any number of arguments associated with them, stored in the `parameters` dictionary. Think of them as SayKit's equivalent to the `UIEvent` class.

Each command recognizer specializes in producing commands of a particular type (declared as the recognizer's `commandType` property). Under the hood, the recognizers need to consider a user speech utteranace and decide two things:

1. How likely is it that the user is issuing a command of my type?
2. Does this utterance include parameters to go along with the command? If so, what are they?

During their recognition process, the recognizers use the `SAYCommandSuggestion` class to collect these two pieces of information as the following properties:

- `confidence`: a floating point value between 0.0 and 1.0. 1.0 denotes 100% certainty that the utterance was the given command, while 0.0 denotes the opposite.
- `parameters`: a dictionary of associated parameters extracted from the utterance

If you're looking to extend SayKit's command recognizers or build your own from scratch, your job will be to map user speech to a `SAYCommandSuggestion`.

## Extending Built-in Recognizers

Oftentimes, you'll find that an existing SayKit command recognizer will suit your needs with just a bit of adjustment. 

- TODO: talk about text matchers. the two concrete types we offer

## Building Custom Recognizers

- TODO: introduce SAYCustomCommandRecognizer. talk about forthcoming subclassing capabilities for more robust recognition (e.g. third-party intent recognizers)
