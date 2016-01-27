# SayKit Tutorial Part I: Building Blocks of a Fully Conversational App

## Table of Contents
1. General Plan
2. Setup
        a. GUI Setup
        b. Conversation Manager Setup
3. Available Commands (Verbal Command Request)
4. Search for Recipes (Verbal Command Request)
5. Search for Recipes (String Request)
6. View Saved Recipes (Select Request)
7. Recipe Ingredients (Pattern Match Resolver)


## General plan:
In this tutorial we'll walk through how to use some of the most important features of SayKit. In Part I we'll treat each feature in isolation, and in Part II we'll put them all together into a full app.

The tutorial workspace, `SayKitTutorials.xcworkspace`, contains two projects: `SayKit Requests and Recognizers` and `SayKit Conversation Topics`. The first project demonstrates the use of several standard voice requests and command recognizers, while the second provides an example of a simple Conversation Topic hierarchy. 

We begin with `SayKit Requests and Recognizers`. Open it up and play around as you follow along!


## Setup
In visual apps, we use `AppDelegate`'s `application:didFinishLaunchingWithOptions:` method to initialize our graphical user interface, all contained within a `UIWindow`. This is also a great place to set up SayKit's conversational equivalent, the `SAYConversationManager`.

### GUI Setup

The first thing we’ll do is add a UILabel as a quick way for us to get feedback on what the app's doing. In these examples, you'll see us finish our conversations with anticlimactic calls to `updateAppResultLabelWithText:`. This is where your app's logic would take over and do something amazing!

The rest of the GUI will be a series of UIButtons that we'll use to start sample voice requests.

Finally, we need one last button that the user can tap to begin talking to the app. Luckily for us, SayKit comes with a pre-packaged microphone button as part of the `SAYCommandBarController` container class. All we need to do is set our `ViewController` as the content of a Command Bar Controller.

// TODO: Insert image of storyboard

Let’s get started!

- Create a new single-view application
- Add the SayKit framework, following the [Getting Started instructions](#)
- Setup the GUI like in the image above. We'll hook up the buttons' IBActions shortly.
- In `AppDelegate.m`, setup a `SAYCommandBarController` as the window's root view controller. The `SAYCommandBarController` behaves like a container view controller similar to a `UITabBarController`. In this case, the `contentViewController` is our `ViewController`.

    ```swift
    func application(application: UIApplication, 
        didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        
            // Initialize GUI
            window = UIWindow(frame: UIScreen.mainScreen().bounds)
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            let viewController = storyboard.instantiateInitialViewController()
            
            // Wrap initial view controller in a command bar controller
            let commandBarController = SAYCommandBarController()
            commandBarController.contentViewController = viewController
            
            window?.rootViewController = commandBarController
            window?.makeKeyAndVisible()
            
            /* ...setup Conversation Manager... */
    }
    ```

### Conversation Manager Setup

The `SAYConversationManager` is the highest-level manager of a conversation, coordinating input (listening) and output (speaking). To do its job, we have to define its `commandRegistry` and at least one `audioSource`, which are involved in the input and output aspects of a conversation, respectively.

In this example, we'll use the simplest stand-ins for these properties. (Later on, we'll show how a Conversation Topic can fill both these roles.) A `SAYCommandRecognizerCatalog` stores a flat array of `SAYCommandRecognizer`s that we'll populate shortly. A `SAYSoundBoard` is an implementation of an audio source (`SAYAudioEventSource`) that enables the Conversation Manager to post audio events.

The last line is an optional optimization that improves the performance of calls to the standard speech recognition service.

```swift
func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
    
    /* ...setup GUI... */
    
    // Initial setup of the SAYConversationManager
    let catalog = SAYCommandRecognizerCatalog()
    SAYConversationManager.systemManager().commandRegistry = catalog
    
    let soundBoard = SAYSoundBoard()
    SAYConversationManager.systemManager().addAudioSource(soundBoard, forTrack:SAYAudioTrackMainIdentifier)
    
    // Optional optimization
    SAYAPIKeyManager.sharedInstance().prefetchAPIKeys()
    
    return true
}
```

Now that we're all set up, let's get to the real meat of a conversational interface: command recognizers and voice requests!

// TODO: Snip here and link to next page.

## Command Recognizers

In visual-based apps, users interact by tapping or swiping the screen. If they tap a button, they probably intend to trigger an action associated with that button, which makes our job simple: do the action!

Contrast this with conversational apps, where users interact by speaking. When they say something we recognize, we interpret their intent as a command and execute the command.

This encompasses several steps as the user’s speech is converted to text (`SAYSpeechTranscript`), interpreted as an intent (`SAYSpeechIntent`), and finally converted to a command (`SAYCommand`) that is associated with an app-defined action. This is analogous to UIKit's progression of user taps being translated into screen coordinates as a tap event, which is passed to the encompassing view that reacts to the event.

But we don't typically worry about these steps when we create a visual app using UIKit, and creating a conversational app with SayKit is no different. All we need to do is register a `SAYCommandRecognizer` and a corresponding action with the Conversation Manager's command registry. SayKit consults the registry whenever it receives an intent from the user to determine what action to take.

### Standard Command Recognizers

SayKit has a set of predefined commands that it can recognize, like "Help", "Search", and "Select". Each of these standard recognizers is a subclass of `SAYVerbalCommandRecognizer`, which knows what to do with commands of its assigned `commandType`. We'll demonstrate how to use standard command recognizers, as well as how to add our own customizations.

In this part of the tutorial, we'll add command recognizers directly to the Conversation Manager's command registry, since we're using a flat `SAYCommandRecognizerCatalog`. In more complex apps, we might register command recognizers with a Conversation Topic instead. Check out the [Conversation Topic Tutorial](#) for more information.

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

A `SAYCommand` is a representation of a command issued by the user, and consists of an identifying `type` and a `parameters` dictionary. In this example, our `SAYSetSpeechRateCommandRecognizer` is preconfigured to respond to commands with the type `SAYStandardCommandSetSpeechRate`. We can expect to find the new speech rate stored in `parameters` with the key `SAYSetSpeechRateCommandRecognizerParameterSpeechRate`. Take a look at the [`SAYStandardCommandLibrary.h`](#) header for a full list of standard command string constants.

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

### Followup Requests

Sometimes we may need to prompt the user for clarification. A common scenario is when the user leaves out some information that we need (User: "I choose you, Pikachu!", App: "Did you mean Toby Pikachu or Susan Pikachu?"). In such cases, we can respond to the user with a followup voice request.

In previous examples we created our command recognizers using the `target:action:` initializer and the `actionBlock` initializer. Here we'll use the `responseBuilder` initializer, which is simply a block that accepts a `SAYCommand` and returns a `SAYVoiceRequestResponse`. A voice request response contains everything we need to know to respond to the user, including an `action` block, a `followupRequest`, and a `feedbackPrompt`, all of which are optional and can be mixed and matched to the desired effect.

```swift
commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
    let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: { result in
        self.updateAppResultLabelWithText("Received command:\n[Help with \"\(result)\"")
    })
    return SAYVoiceRequestResponse(followupRequest: followupRequest)
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

### Custom Command Recognizers

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

Objects conforming to the `SAYTextCommandMatcher` protocol will process a user's speech transcript and return the likelihood that the given text corresponds to some command. Here we'll use the implementation `SAYPatternCommandMatcher`, which is initialized with an array of text "patterns" that are used to process the speech transcript. If the transcript matches any of the patterns, then the Matcher returns a positive response along with any pattern parameters.

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

____

Now that our command registry is loaded up with command recognizers, our app can recognize what's being said and act accordingly. But what if the app already knows that the user wants to, say, perform a search, and just needs to prompt them for the search query? 

That sounds like a job for voice requests!

// TODO: Snip here and link to next page

## Voice Requests

Finally, we get to hook up those UIButtons we created way back in the Setup section! Hold on for a few more paragraphs, though - we need to cover some voice request basics:

Voice requests play an important role in the question-and-answer process. We've actually interacted with them already in our previous discussion on command recognizers. Every time you've tapped the microphone button, you were presented with a *command* request, implicitly asking the question "What would you like to do next?". As you'll see in this section, we can also create parameter-focused voice requests that ask much more specific questions like "What color would you like?", "How many servings?", or "Are you sure?".

`SAYVoiceRequest` is a protocol whose implementations define a `prompt` to present to the user, and have underlying components that can recognize speech (`recognitionService`), interpret speech into text (`interpreter`), and react to the interpreted result (`responder`). Using these components, SayKit creates a cohesive dialogue flow for your users.

The request presented on a microphone tap is a `SAYVerbalCommandRequest`, which implements the `SAYVoiceRequest` protocol. Its creation and presentation was handled behind-the-scenes in the previous section on command recognizers, though in the upcoming parameter requests we are responsible for the creation and presentation of the request.

SayKit comes with several other `SAYVoiceRequest` implementations, including `SAYStringRequest`, `SAYSelectRequest`, `SAYNumericalRequest`, `SAYConfirmationRequest`, and `SAYPatternMatchRequest`. Your own [custom parameter requests](#) can be created by implementing the `SAYVoiceRequest` methods. The `result` in each's `action` block is relevant to its corresponding request. For example, a `SAYNumericalRequest`'s result is a number, while a `SAYStringRequest`'s result is a string.

For these examples, we're simply presenting requests as the result of button taps. In your own apps, they might be triggered by some other event, or as part of a [followup request](#).


### Confirmation Request

A confirmation request will ask the user a question and expect a yes-or-no response in return. If we get an invalid response, the request will try again (though this behavior can be tweaked). In this case, the `action` block's `result` represents a Bool (though wrapped in an NSNumber for some fiddly reasons).

Once we create the request, we call our the `presentVoiceRequest:` method of the system's `SAYConversationManager`. And that's it!

```swift
@IBAction func confirmationRequestButtonTapped(sender: AnyObject)
{
    let request = SAYConfirmationRequest(promptText: "Are you sure?") { result in
        if let doIt = result as? Bool {
            if doIt { self.updateAppResultLabelWithText("Received command:\n[Do it!]") }
            else    { self.updateAppResultLabelWithText("Received command:\n[Don't do it!]") }
        }
        else {
            /* ... */
        }
    }
    
    SAYConversationManager.systemManager().presentVoiceRequest(request)
}
```


--------------------------------------------------------------------------------





## View Saved Recipes (Select Request)
How do we present the user with a list of options to choose from?

In a visual-based app, we might build a table view with cells corresponding to each choice, present it with a table view controller, and respond to a tap on one of the cells. Using SayKit, all we need is a `SAYSelectRequest` and an array of options.

In this example, we'll ask the user to select from a list of saved recipes. We'll reuse the same setup we had in the previous example: when we tap the microphone button, the user will be asked to make the selection. As before, we'll simply update the `resultsLabel` with the user's selection.

- In a full app, we would probably have some logic to maintain, store, or fetch the user's saved recipes (and that's what we'll do in Part II of this tutorial). Here, we'll simply call a helper/dummy function to serve us the list:

    ``` objc
    - (NSArray<NSString *> *)retrieveSavedRecipeLabels
    {
        return @[@"Chocolate Butterscotch Cookies",
                 @"Beef Lasagna",
                 @"Tuna Casserole"];
    }
    ```
- Pass the list to `SAYSelectRequest`'s initializer:

    ``` objc
    NSArray<NSString *> *itemLabels = [self retrieveSavedRecipeLabels];
    SAYSelectRequest *request = [[SAYSelectRequest alloc] initWithItemLabels:itemLabels promptText:@"Which of your saved recipes would you like details on?" completionBlock:^(SAYSelectResult * _Nullable result) {
        /* ... */
    }];
    ```
- There is an alternative initializer for `SAYSelectRequest` that can handle aliases for each item, `initWithOptions:promptText:completionBlock`. Check it out at the end of this section. (TODO: Link)
- We'll handle the result in another helper function:

    ``` objc
    - (void)handleSelectResultWithOption:(SAYSelectOption *)selectedOption atIndex:(NSUInteger)selectedIndex
    {
        NSString *recipeName = selectedOption.label;
        
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"Selected \"%@\" (Index %lu)", recipeName, selectedIndex];
        });
        
        // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
    }
    ```
- Our `commandBarDidSelectMicrophone:` method should now look like:

    ``` objc
    - (void)commandBarDidSelectMicrophone:(SAYCommandBar *)commandBar
    {    
        NSArray<NSString *> *itemLabels = [self retrieveSavedRecipeLabels];
        SAYSelectRequest *request = [[SAYSelectRequest alloc] initWithItemLabels:itemLabels promptText:@"Which of your saved recipes would you like details on?" completionBlock:^(SAYSelectResult * _Nullable result) {
            if (result.error) {
                // Handle error
            }
            else {
                SAYSelectOption *selectedOption = result.selectedOption;
                NSUInteger selectedIndex = result.selectedIndex;
                
                [self handleSelectResultWithOption:selectedOption atIndex:selectedIndex];
            }
        }];
        
        [[SAYVoiceRequestPresenter defaultPresenter] presentRequest:request];
    }
    ```

### Alternative Initializer for `SAYSelectRequest`
Instead of using a flat list of item labels to select from, we can also define aliases for each label. If the user speaks an item's alias, it is treated the same as if they selected the item directly. Using aliases, you can easily handle alternative names for the same item.

In the example below, we provide an alias for “Beef Lasagna” as “Pasta”. If the user speaks either of these phrases, we’ll know they meant to select the second option, “Beef Lasagna.”

- Create a dummy helper function to return the selectable options. In a full app, this would interact with the app logic to retrieve the options:

    ``` objc
    - (NSArray<SAYSelectOption *> *)retrieveSavedRecipeOptions
    {
        return @[[[SAYSelectOption alloc] initWithLabel:@"Chocolate Butterscotch Cookies" aliases:@[@"Grandma's Cookies"]],
                 [[SAYSelectOption alloc] initWithLabel:@"Beef Lasagna" aliases:@[@"Pasta", @"My Favorite Dish"]],
                 [SAYSelectOption optionWithLabel:@"Tuna Casserole"]];
    }
    ```
- Replace our earlier initialization of the `SAYSelectRequest`:

    ``` objc
    NSArray<SAYSelectOption *> *options = [self retrieveSavedRecipeOptions];
    SAYSelectRequest *request = [[SAYSelectRequest alloc] initWithOptions:options promptText:@"Which of your saved recipes would you like details on?" completionBlock:^(SAYSelectResult * _Nullable result) {
        /* ... */
    }];
    ```

#### Classes used:
	- SAYSelectRequest
    - SAYSelectOption
    - SAYSelectResult


## Recipe Ingredients (Pattern Match Resolver)
An alternative to using SayKit Standard verbal command requests is to construct your own text resolver. Custom text resolvers are a good way to handle simple speech patterns, and require very little setup. If you find yourself in need of more flexibility when interpreting a user’s intent, you may want to consider setting up your own intent recognition service (which we’ll cover in a later tutorial).

For this example, suppose the user is working their way through a recipe. We can handle a query like "How much baking powder do I need?" using a `SAYPatternTextResolver`. A pattern resolver is initialized with a template string that marks entities that we want to capture for later use. (The template string is resolved to a regular expression behind the scenes, which is used to perform the actual check against the user's speech.)

In this case, we'll create a template string "How much @ingredient do I need?". If user speech is found to match this template, then we'll handle it with the completion block associated with the pattern resolver. In this case, that means updating `resultLabel` with the proper response (as determined by the app).

- In `AppDelegate.m`, make sure we're not overriding `SAYCommandBarController`'s delegate from the previous example. We want the microphone button's original behavior of initiating a `SAYVerbalCommandRequest`:
    ``` objc
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        
        self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        
        UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        
        ViewController *vc = [mainStoryboard instantiateInitialViewController];
        
        SAYCommandBarController *commandBarController = [[SAYCommandBarController alloc] init];
        
        commandBarController.contentViewController = vc;
        
        // UIView *v = commandBarController.view;    // Force commandBarController to load.
        // commandBarController.commandBar.delegate = vc;
        
        self.window.rootViewController = commandBarController;
        [self.window makeKeyAndVisible];
        
        return YES;
    }
    ```
- In `ViewController.m`'s `viewDidLoad` method, we register our resolver via a helper function:
    ``` objc
    - (void)viewDidLoad {
        [super viewDidLoad];

        [self respondToCustomPatternResolver];
    }
    ```
- In `respondToCustomPatternResolver`, we build the pattern resolver itself. The commandType parameter will be used a little later when we define our response.

    ``` objc
    NSArray<NSString *> *templates = @[@"How much @ingredient do I need?",
                                       @"How many @ingredient in the recipe?"];
    SAYPatternTextResolver *resolver = [[SAYPatternTextResolver alloc] initWithTemplates:templates forCommandType:@"RecipeIngredientQuery"];
    ```
- Create a new `SAYDomain` to manage the resolver, and register it with the default `SAYDomainRegistry`:

    ``` objc
    SAYDomain* domain = [[SAYDomain alloc] init];
    [domain registerResolver:resolver];

    SAYDomainRegistry *domainRegistry = [SAYVerbalCommandRequestManager defaultManager].customCommandResolver;

    [domainRegistry addDomain:domain];
    ```
- Create a helper function that looks up the ingredient the user requested, and displays its required quantity:

    ``` objc
    - (void)handleRecipeIngredientQueryForIngredient:(NSString *)ingredient
    {
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [self ingredientLookupForIngredient:ingredient];
        });
        
        // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
    }
    ```
- In a full app, the `ingredientLookupForIngredient:` method would query the app logic to determine the required amount of the given ingredient. In this example, we'll just return a hard-wired value:

    ``` objc
    - (NSString *)ingredientLookupForIngredient:(NSString *)ingredient
    {
        // ...insert app logic here to determine how much of the ingredient we need...
        
        NSString *units = @"cups";
        NSString *quantity = @"5";
        
        return [NSString stringWithFormat:@"You need %@ %@ of %@.", quantity, units, ingredient];
    }
    ```
- Finally, back in `respondToCustomPatternResolver`, we add the actual response to the command we defined earlier. The ingredient spoken by the user is stored in `command.parameters` under the name we defined in the pattern resolver, "ingredient".

    ``` objc
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];

    [commandRegistry addResponseForCommandType:@"RecipeIngredientQuery" responseBlock:^(SAYCommand * _Nonnull command) {
        NSString *ingredient = command.parameters[@"ingredient"];
        [self handleRecipeIngredientQueryForIngredient:ingredient];
    }];
    ```
- `respondToCustomPatternResolver` should now look like this:

    ``` objc
    - (void)respondToCustomPatternResolver
    {
        // Build and register a domain with the pattern resolver.
        NSArray<NSString *> *templates = @[@"How much @ingredient do I need?",
                                           @"How many @ingredient in the recipe?"];
        SAYPatternTextResolver *resolver = [[SAYPatternTextResolver alloc] initWithTemplates:templates forCommandType:@"RecipeIngredientQuery"];
        
        SAYDomain* domain = [[SAYDomain alloc] init];
        [domain registerResolver:resolver];
        
        SAYDomainRegistry *domainRegistry = [SAYVerbalCommandRequestManager defaultManager].customCommandResolver;
        
        [domainRegistry addDomain:domain];
        
        
        // Add a response for the newly-created command type.
        SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
        
        [commandRegistry addResponseForCommandType:@"RecipeIngredientQuery" responseBlock:^(SAYCommand * _Nonnull command) {
            NSString *ingredient = command.parameters[@"ingredient"];
            [self handleRecipeIngredientQueryForIngredient:ingredient];
        }];
    }
    ```
- TODO - Confirm that pattern matching works with spaces! Since I think I'm just replacing @thing with \w+ regex

#### Classes used:
- SAYPatternTextResolver
- SAYDomain
- SAYDomainRegistry
- SAYCommandResponseRegistry

## Wrapping Up!

That’s it for the first part of our tutorial! By now you should have a nice playground for exploring SayKit. You can download the whole project at /* TODO - LINK */. With some minor tweaks, you can play around with each of the features that we went over. 

Verbal command requests, entity requests, and text resolvers are some of the essentials in the SayKit toolbox, but they only scratch the surface of what SayKit can do.

Stick around for Part II, where we’ll put it all together into a fully fledged app! We’ll discuss how to structure a conversational app, including how to manage intent domains, how to balance the conversational flow with the visual flow, and some design patterns to help along the way.
