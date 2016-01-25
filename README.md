# SayKit SDK (Developer Preview)
The conversational UI framework for voice enabled applications on iOS.

Currently available as a developer preview (version 0.8).

## <a name="developer-resources"></a> Developer Resources

What are you looking to do?

- **Jump in**: [Installation guide](#installation-guide)
- **Familiarize yourself**: [SayKit tour](./Tour/00-intro.md)
- **Learn by doing**: [Step-by-step tutorial](#)
- **Read the headers**: [API documentation](#)
- **Go deep**: [In-depth Developer guides](#) *(coming soon)*
- **Glimpse the future**: [Feature roadmap](#) *(coming soon)*

## <a name="installation-guide"></a> Installation Guide

### 1. Download the SDK

Download the SayKit SDK [here](https://github.com/ConversantLabs/SayKitSDK/archive/master.zip).

### 2. Add the SayKit framework to your project

- In Xcode, File -> Add Files to "Project".
- Navigate to where you downloaded the framework, and select `SayKitSDK.framework`. The framework should now appear on the left, in Xcode's Project Navigator pane.
- Select the project in the Navigator pane, select your target, and go to the Build Phases tab.
- Under "Link Binary With Libraries", make sure `SayKitSDK.framework` is in the list.
- Under "Embed Frameworks", make sure `SayKitSDK.framework` is in the list.
- If using Swift, create a bridging header that includes `<SayKit/SayKit.h>`. See [Apple's guide on Importing Objective-C into Swift](https://developer.apple.com/library/ios/documentation/Swift/Conceptual/BuildingCocoaApps/MixandMatch.html#//apple_ref/doc/uid/TP40014216-CH10-ID156) for more details.

*// TODO: add Xcode screenshots/video*

### 3. Configure the Conversation Manager

The conversation manager provides the foundation for SayKit's integration with your application code.

> If this is the first you're hearing about a so-called "Conversation Manager", you need to stop and learn a bit more about SayKit! [Take a look at our developer resources](#developer-resources).

Each SayKit app has a default manager ready and waiting, accessibile as `[SAYConversationManager systemManager]`. A typical app will require two pieces of configuration on this manager:

1. An audio event source (conforming to the `SAYAudioEventSource` protocol). This provides an outlet for audible events (e.g. speech, sound effects) to be presented to the user. These are 
2. A command registry (conforming to the `SAYVerbalCommandRegistry` protocol). This provides SayKit's speech recognition systems with a set of command recognizers.

The particular configuration you'll want will depend on your application's needs, but as a simple example, let's set up the manager to use a simple flat command recognizer catalog (`SAYCommandRecognizerCatalog`) and sound board (`SAYSoundBoard`) on the main audio track.

Objective-C:
````objc
SAYCommandRecognizerCatalog *catalog = [[SAYCommandRecognizerCatalog alloc] init];
[[SAYConversationManager systemManager] addAudioSource:soundBoard forTrack:SAYAudioTrackMainIdentifier];

SAYSoundBoard *soundBoard = [[SAYSoundBoard alloc] init];
[[SAYConversationManager systemManager] setCommandRegistry:catalog];
````

Swift:
````swift
let catalog = SAYCommandRecognizerCatalog()
SAYConversationManager.systemManager().commandRegistry = catalog

let soundBoard = SAYSoundBoard()
SAYConversationManager.systemManager().addAudioSource(soundBoard, forTrack:SAYAudioTrackMainIdentifier)
````

Typically, this configuration would go in your AppDelegate's `application:didFinishLaunchingWithOptions:` method.

### 4. Go!

Now you're all ready to go!

Add voice commands to your Todo list app. Make your RSS app read the news aloud. Create a chat bot friend. The sky's the limit.

Now, if you are looking for a bit more help on where to go next: [check out our developer resources](#developer-resources).
