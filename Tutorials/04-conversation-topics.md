# Conversation Topics
[Conversation Topics](https://github.com/ConversantLabs/SayKitSDK/blob/tutorial/Tour/06-conversation-topics.md) give us an easy way to structure complex conversations. As our apps become more involved, we don't want to rely only on a flat list of command recognizers and a simple sound board (like we did in the [first tutorial](./01-setup.md#conversation-manager-setup)). Instead, we can leverage Conversation Topics' [capabilities](https://github.com/ConversantLabs/SayKitSDK/blob/tutorial/Tour/06-conversation-topics.md#responsibilities) of defining audio output via event sequences, handling voice input via their own set of command recognizers, and managing their place in the hierarchy via subtopic composition.

This example will walkthrough a simple Conversation Topic hierarchy that will let us interact with a list of items. We'll begin with a single Topic, and then demonstrate how to add a subtopic.

## Setup
If you haven't already, open up the `SayKit Conversation Topics` project, which is part of the `SayKitTutorials` workspace.

### GUI Setup
We'll setup the GUI components of the app identically to the [previous tutorial](./01-setup.md#gui-setup), wrapping our main `ViewController` in a `SAYCommandBarController` so we can use the built-in microphone button. 

`AppDelegate`'s `application:didFinishLaunchingWithOptions:` method should look something like this:

```swift
// AppDelegate.swift
func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
    
    // Initialize GUI
    window = UIWindow(frame: UIScreen.mainScreen().bounds)
    let storyboard = UIStoryboard(name: "Main", bundle: nil)
    let viewController = storyboard.instantiateInitialViewController() as! ViewController
    
    // Wrap initial view controller in a command bar controller
    let commandBarController = SAYCommandBarController()
    commandBarController.contentViewController = viewController
    
    window?.rootViewController = commandBarController
    window?.makeKeyAndVisible()
    
    // ...setup Conversation Manager (see below)...
    
    return true
}
```

### Conversation Manager (ViewController)
[Previously](./01-setup.md#conversation-manager-setup), we used a `SAYCommandRecognizerCatalog` as the Conversation Manager's `commandRegistry`, and a `SAYSoundBoard` as its main audio source. Here we'll use a `SAYConversationTopic` to fill both roles.

Specifically, we'll use our own subclass, `ProductListTopic`, which we'll go over very soon!

```swift
// ViewController.swift
override func viewDidLoad() {
    // ...setup GUI...
    
    // Initial setup of the SAYConversationManager, with a Conversation Topic 
    // as command registry and main audio source.
    let rootTopic = ProductListTopic(/*...*/)
    let systemManager = SAYConversationManager.systemManager()
    systemManager.commandRegistry = rootTopic
    systemManager.addAudioSource(rootTopic, forTrack:SAYAudioTrackMainIdentifier)
    
    // ...
}
```

## Product List Topic
We want our conversation topic to do two main things: recognize commands that we can use to interact with a list of items, and to post a list of items as a sequence of audio events.

### Command Recognizers

We don't necessarily want the topic itself to handle the response to a recognized command, so let's include an `eventHandler` property that implements the `ProductTopicEventHandler` protocol.

```swift
protocol ProductTopicEventHandler: class
{
    func handlePlay()    
    func handlePrevious()
    func handleNext()
    func handleSelect()
}
```

Then we can add command recognizers for the standard commands "Play", "Next", "Previous" and "Select" in `ProductListTopic`'s initializer. Note that the `responseTarget` is set to `eventHandler`:

```swift
class ProductListTopic: SAYConversationTopic
{
    let eventHandler: ProductTopicEventHandler
    init(eventHandler: ProductTopicEventHandler)
    {
        self.eventHandler = eventHandler
        super.init()
    
        // add a recognizer for "play" commands, to begin reading the items in the list
        self.addCommandRecognizer(SAYPlayCommandRecognizer(responseTarget:eventHandler,
            action:"handlePlay"))

        // ...add the remaining command recognizers...
    }
}
```

### Audio Events

The `SAYConversationTopic` base class has a `postEvents:` method that we can use to output a sequence `SAYAudioEvent`s to any registered listeners. An audio event represents a piece of audible information, and can encompass speech (`SAYSpeechEvent`), a tone (`SAYToneEvent`), a duration of silence (`SAYSilenceEvent`), or a combination of the above (`SAYCompositeEvent`).

Typically you won't want collaborators accessing a topic's `postEvents:` method directly, so let's keep it clean by providing a `speakProductTitles:` method as part of our `ProductListTopic` subclass. It will take an array of strings and build them into a sequence of `SAYSpeechEvent`s:

```swift
// ProductListTopic.swift
func speakProductTitles(titles: [String])
{
    let sequence = SAYAudioEventSequence()
    for title in titles {
        sequence.addEvent(SAYSpeechEvent(utteranceString: title))
    }
    
    // this is a method defined on the `SAYConversationTopic` base class that posts events to listeners
    self.postEvents(sequence)
}
```

Our event handler can now respond to a "Play" command and pass the `ProductListTopic` a list of items to speak.

```swift
// ViewController.swift
class ViewController: UIViewController, ProductTopicEventHandler {
    // ...
    var listTopic: ProductListTopic?    
    func handlePlay()
    {
        updateAppResultLabelWithText("Received List Topic Command:\n[Play]")        
        listTopic?.speakProductTitles(["Apples", "Waffles", "Pancakes", "Toast", "Bananas"])
    }
    // ...
}
```

Don't forget to set `ViewController`'s `listTopic` in the `AppDelegate` as part of our setup:

```swift
let rootTopic = ProductListTopic(eventHandler: viewController)
// ...
viewController.listTopic = rootTopic
```

## Product Search Topic
We now have an app with a single Conversation that manages some basic interactions with a list of items. What if instead we want a conversation topic that can perform a search and return a list of results? Almost all of the functionality we need is already there in `ProductListTopic`, so we could keep adding to it. But let's avoid bloat and explore [conversation topic hierarchies](https://github.com/ConversantLabs/SayKitSDK/blob/tutorial/Tour/06-conversation-topics.md#managing-the-interface-hierarchy) by creating a new topic, `ProductSearchTopic`. We'll set its subtopic to `ProductListTopic`, which will let us easily compose our final response to our new "Search" command.

### Setup
Let's replace our rootTopic with an instance of `ProductSearchTopic`, and add a subtopic to it:

```swift
// AppDelegate.swift
    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        
        // ...setup GUI...
        
        // Initial setup of the SAYConversationManager, with a Conversation Topic as
        // command registry and main audio source.
        let rootTopic = ProductSearchTopic(eventHandler: viewController)
        let systemManager = SAYConversationManager.systemManager()
        systemManager.commandRegistry = rootTopic
        systemManager.addAudioSource(rootTopic, forTrack:SAYAudioTrackMainIdentifier)
        
        // create the subtopic to handle the list of results
        let listTopic = ProductListTopic(eventHandler: viewController)

        // by adding it as a subtopic, we are implicitly doing two things:
        // 1. adding its command recognizers to our collection
        // 2. listening for, and passing on, our subtopic's audio events (potentially with modification: see below)        
        rootTopic.addSubtopic(listTopic)
        
        viewController.listTopic = listTopic
        
        // ...
    }
```

We add a command recognizer for the standard "Search" command in `ProductSearchTopic`'s initializer, as well as add "handleSearch:" to our preexisting event handler protocol.

```swift
// ProductSearchTopic.swift
init(eventHandler: ProductTopicEventHandler)
{
    self.eventHandler = eventHandler
    super.init()
    
    // set up the search recognizer
    self.addCommandRecognizer(SAYSearchCommandRecognizer(responseTarget: eventHandler,
        action: "handleSearch:"))
}
```

```swift
protocol ProductTopicEventHandler: class
{
    // ...    
    func handleSearch(command: SAYCommand)
}
```

```swift
// ViewController.swift
func handleSearch(command: SAYCommand)
{
    if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] as? String {
        let matchingItems = self.searchAppUsingQuery(searchQuery)  // app logic
        listTopic?.speakProductTitles(matchingItems)
        updateAppResultLabelWithText("Received Search Topic Command:\n[Search for \(searchQuery)]")
    }
    else {
        /* ... */
    }
}
```

### Prefacing Subtopic Events
All posted events of `ProductListTopic` will pass to the listener of the topic's audio source. Earlier, this was the Conversation Manager, but now as a subtopic, the events are passed to its parent, the `ProductSearchTopic`.

The `SAYConversationTopic` base class has a method `subtopic:didPostEventSequence:` that we can override to customize how we handle the output of a topic's subtopics.

Let's add a little introduction ("Here's what I found matching your query") to the subtopic's list of items.

```swift
// ProductSearchTopic.swift
override func subtopic(subtopic: SAYConversationTopic,
    didPostEventSequence incomingSeq: SAYAudioEventSequence) {
        
        // preface the message with this introduction
        let prefaceEvent = SAYSpeechEvent(utteranceString: "Here's what I found matching your query:")
        let outgoingSeq = SAYAudioEventSequence(events:[prefaceEvent])
        
        // the incoming sequence is our subtopic's list of search results
        // add them to our outgoing sequence
        outgoingSeq.appendSequence(incomingSeq)
        
        self.postEvents(outgoingSeq)
}
```

Now, if we call `ProductListTopic`'s `speakProductTitles:` method, we'll hear the introductory speech supplied by the `ProductSearchTopic`, followed by the speech supplies by the `ProductListTopic`.

## Wrapping Up