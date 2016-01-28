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

### Event Handler

### Command Recognizers

### SAYAudioEventSequence and postEvents (speakProductTitles)

## Product Search Topic
As supertopic

### Setup
Set as root topic, add list sub topic

### subtopic:didPostEventSequence:

## Wrapping Up