# Conversation Topics

At this point, we've know more than enough to be dangerous. We can build apps that ask questions, understand commands, and can make any sound they want.

But where should all of this conversational UI logic code go? If try to build a conversational agent with just a flat `SAYCommandRecognizerCatalog` and a simple `SAYSoundBoard` in our app delegate, we're going have a monolithic monster on our hands as our app grows.

## Keep 'em Separated

We need a better separation of concerns. Not only do we need to keep UI logic distinct from the business logic, but we also need to keep the UI logic underlying distinct app features from each other.

When it comes to graphical UI development, there are well-established patterns to handle this. For example, Apple designed it's UIKit classes to encourage iOS developers to follow the MVC paradigm (Model-View-Controller), so view code is typically well-separated from the rest of the app's data and logic. In addition, the `UIView` class supports a hierarchical structure, so a view is only directly responsible for a describing part of the scene: it can delegate the lower level details to its subviews.

We need something similar, but it should be concerned with the speaker and mircophone, not the display and touch sensors. We need something conversationally-oriented and capable of keeping distinct topics seperate. We need **Conversation Topics**.

## Responsibilities

Staying with UIKit for a moment, let's highlight what could be considered `UIView`'s three major responsibilities:

1. Defining visual output: drawing their visual content to their frame on screen
2. Handling screen input: configuring touch event-recognizing behavior (taps, gestures, etc.)
3. Managing the interface hierarchy: composing subviews capable of handling lower-level UI concerns

With those capabilities, a `UIView` instance is able to fulfill its specific duties as the link between the user and application for a particular rectangle of screen real estate. No more, no less.

The `SAYConversationTopic` has similar roles, but with an audio-oriented twist:

1. **Defining audio output**: posting their audio content as an event sequence
2. **Handling voice input**: configuring voice command-recognizing behavior
3. **Managing the interface hierarchy**: composing subtopics capable of handling lower-level UI concerns

To learn more, let's discuss each of these responsibilities in turn.

### Defining Audio Output

Topics conform to the `SAYAudioEventSource` protocol, so they can post event sequences relevant only to their part of the interface. 

For example, a shopping app may need to present a list of product titles to the user. Let's wrap this up in a `SAYConversationTopic` subclass called `ProductListTopic`, and give it a method that speaks a list of product titles:

```swift
// Swift
func speakProductTitles(titles: [String]) {
	var sequence = SAYAudioEventSequence()
	for title in titles {
		sequence.addEvent(SAYSpeechEvent(utteranceString: title))
	}
	self.postEvents(sequence)	// a method defined on the `SAYConversationTopic` base class
}
```

```objc
// Objective-C
- (void)speakProductTitles:(NSArray<NSString *> *)titles {
	SAYAudioEventSequence *sequence = [[SAYAudioEventSequence alloc] init];
	for (NSString *title in titles) {
		[sequence addEvent:[SAYSpeechEvent eventWithUtteranceString: title]];
	}
	[self postEvents:sequence];	// a method defined on the `SAYConversationTopic` base class
}
```

Now, any time we tell our topic to speak its product titles, a sequence of events is posted to whoever is listening.

### Handling Voice Input

Topics also conform to the `SAYCommandRegistry` protocol, so they are able to provide a collection of command recognizers relevant to their subject. In the product list example above, you could assign list-navigation commands to your topic to allow the user to browse the list on command.

To continue with the example, let's assume we have some kind of event handler class (like a controller in MVC-terms) capable of handling commands events recognized by our `ProductListTopic`. Then it's initializer could include the following configuration:

```swift
// Swift
init(eventHandler: ProductsEventHandler) {
	...
    // add a recognizer for "previous" commands, to go back in the list
    self.addCommandRecognizer(SAYPreviousCommandRecognizer(responseTarget:self, 
	                                                               action:"handlePrevious:"))
    
    // add a recognizer to "next" commands, to go forward in the list
    self.addCommandRecognizer(SAYNextCommandRecognizer(responseTarget:self, 
                                                               action:"handleNext:"))
    
    // add a recognizer for "select" commands, to select an item in the list
    self.addCommandRecognizer(SAYSelectCommandRecognizer(responseTarget:self, 
                                                                 action:"handleSelect:"))
	...
}
```

```objc
// Objective-C
- (instancetype)initWithEventHandler:(ProductTopicEventHandler *eventHandler) {
    ...
    // add a recognizer for "previous" commands, to go back in the list
    [self addCommandRecognizer:
        [[SAYPreviousCommandRecognizer alloc] initWithResponseTarget:self, 
                                                              action:@selector(handlePrevious:)]];
    
    // add a recognizer to "next" commands, to go forward in the list
    [self addCommandRecognizer:
        [[SAYNextCommandRecognizer alloc] initWithResponseTarget:self, 
                                                          action:@selector(handleNext:)]];
    
    // add a recognizer for "select" commands, to select an item in the list
    [self addCommandRecognizer:
        [[SAYSelectCommandRecognizer alloc] initWithResponseTarget:self, 
                                                            action:@selector(handleSelect:)]];
    ...
}
```

And with that, we have a tidy conversation topic encapsulating all the input and output logic to allow a user to interface with a list of items.

### Managing the interface hierarchy

The final responsibility of a conversation topic is to manage its collection of subtopics. It can fold its subtopics' command recognizers into its own and arrange their audio events into a single sequence to be posted. This capability lets us take advantage of the power of composition to build complex conversational interfaces from simple building blocks.

At first blush, this might not be as intuitive as composing a hierarchy of subviews, so let's make it more concrete by adding search capabilities to shopping app example. When the user issues a search command, let's make the app search the product database and a list of matches to the user. We could pull this off by just modifying our `ProductListTopic` class to recognize search commands. We could also change our `speakProductTitles:` method to be a bit more conversational and add an introduction such as "Here's what I found matching *query*" to the list.

Or, a better idea would be to just leave our perfectly-simple `ProductListTopic` class as-is, and instead use it as a subtopic of a new class that includes the search commands and introductory message. We'll call this new class the `ProductSearchTopic`, and we can implement it (loosely) like this:

**insert implementation example**

**talk about adding root topic conversation manager's registry and to its audio sources**
