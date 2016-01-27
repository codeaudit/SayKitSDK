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

Now that we're all set up, let's get to the real meat of a conversational interface: voice requests and command recognizers!

// TODO: Snip here and link to next page.

## Command Recognizers

In visual-based apps, users interact by tapping or swiping the screen. If they tap a button, they probably intend to trigger an action associated with that button, which makes our job simple: do the action!

Contrast this with conversational apps, where users interact by speaking. When they say something we recognize, we interpret their intent as a command and execute the command.

This encompasses several steps as the user’s speech is converted to text (`SAYSpeechTranscript`), interpreted as an intent (`SAYSpeechIntent`), and finally converted to a command (`SAYCommand`) that is associated with an app-defined action. This is analogous to UIKit's progression of user taps being translated into screen coordinates as a tap event, which is passed to the encompassing view that reacts to the event.

But we don't typically worry about these steps when we create a visual app using UIKit, and creating a conversational app with SayKit is no different. All we need to do is register a `SAYCommandRecognizer` and a corresponding action with the Conversation Manager's command registry. SayKit consults the registry whenever it receives an intent from the user to determine what action to take.

### Standard Command Recognizers

SayKit has a set of predefined commands that it can recognize, like "Help", "Search", and "Select". We'll demonstrate how to use these, as well as how to add our own customizations.

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

Commands that include parameters, such as the speech rate in the built-in "Set Speech Rate" command, can be accessed in the action method by including a `SAYCommand` argument. 

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

### Custom Command Recognizers


--------------------------------------------------------------------------------
In this example, we’ll register a response for SayKit’s standard “Available Commands” command. This command is the eventual result of the user speaking utterances like “What can I say?” and “Available Commands”. Our response will simply update our UILabels with what was said.

    ```
    Aside: You can find a full list of standard commands at TODO.
    ```

- Create a helper function to add the response to the default command registry:
    ``` objc
    - (void)respondToAvailableCommands
    {
        SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
        
        // Respond to speech that asks about available commands, such as "What can I say?" and "Available Commands".
        [commandRegistry addResponseForCommandType:SAYStandardCommandAvailableCommands responseBlock:^(SAYCommand * _Nonnull command) {
            [self handleAvailableCommandsCommand];
        }];
    }
    ```
- The `handleAvailableCommandsCommand` helper function simply updates the results label. Later, we'll go over how to query SayKit for the currently available commands and present them to the user as speech, a table view, or both.
    ``` objc
    - (void)handleAvailableCommandsCommand
    {
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = @"Received command: Available Commands";
        });
        
        // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
    }
    ```
- Finally, we'll call `respondToAvailableCommands` as soon as the view controller loads. In a full app, this might be managed by its own set of dedicated controllers. (TODO: Create and link to a discussion on hierarchies, and managing the list of available commands)
    ``` objc
    - (void)viewDidLoad {
        [super viewDidLoad];

        [self respondToAvailableCommands];
    }
    ```
- TODO: Discuss how to present available commands in Command Bar's menu button
- TODO: Bonus points: make the list dynamically update with whatever domains/resolvers we have. Would be a useful pattern for developers to know.

#### Classes used:
- SAYCommandResponseRegistry
- SAYCommand
- SAYStandardCommandLibrary


## Search for Recipes (Verbal Command Request)
In the previous example, we responded to the standard "Available Commands" command. But what if a command requires an input parameter, like "Search for X"? In a visual-based app, we could grab the parameter from a UITextField. Using SayKit, we can simply access the `SAYCommand` parameter of our response block and extract the parameter that we need. 

In this example, we'll respond to the standard "Search" command, which includes a parameter for the search query.

- As in the previous example, create a helper function to setup our response to the standard "Search" command. Notice that we extract the query string by accessing `command`'s `parameters` dictionary with the standard key `SAYStandardCommandSearchParameterQuery`:

    ```objc
    - (void)respondToSearchCommand
    {
        SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
        
        // Respond to a search query, such as "Search for Chinese food" or "I want Italian".
        [commandRegistry addResponseForCommandType:SAYStandardCommandSearch responseBlock:^(SAYCommand * _Nonnull command) {
            NSString *query = command.parameters[SAYStandardCommandSearchParameterQuery];
            
            [self handleSearchCommandForQuery:query];
        }];
    }
    ```
- The `handleSearchCommandForQuery:` function simply takes the extracted query and presents it via the `resultsLabel`:

    ```objc
    - (void)handleSearchCommandForQuery:(NSString *)query
    {
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"Received command: Search for %@", query];
        });
        
        // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
    }
    ```
- Finally, call our setup function from `viewDidLoad`:

    ```objc
    - (void)viewDidLoad {
        [super viewDidLoad];
        [self respondToSearchCommand];
    }
    ```


#### Classes used:
- Same as in Available Commands


## Search for Recipes (String Request)
What if the app already knows that the user wants to perform a search, and just needs to prompt them for the search query? This sounds like a job for a `SAYStringRequest`!

A `SAYStringRequest` does what it sounds like: it asks the user for a string. We can present the string request in a few different ways, including via a button tap or as a followup to a previous request (maybe our Search command from the previous example needed a clarification).

For this example, we'll present the request when the microphone button is tapped. We start by overriding `SAYCommandBarController`'s delegate, and implementing the `SAYCommandBarDelegate` methods in `ViewController.m`.

    ```
    *Aside: Verbal Command Requests vs. Parameter Requests

    An app can request different spoken information from the user: commands or parameters. A command request can generally be thought as answering the question, "What would you like to do next?", while a parameter request can answer questions like "What would you like to search for?", "How many servings?", or "Are you sure you want to continue?".

    Command requests are defined by the class `SAYVerbalCommandRequest`. By default, when the microphone button of the `SAYCommandBarController` is tapped, a `SAYVerbalCommandRequest` is created and presented to the user. This was handled behind-the-scenes in the previous examples, though in the upcoming parameter requests we are responsible for the creation and presentation of the request.

    Parameter requests are subclasses of `SAYVoiceRequest`. SayKit comes with several already defined, including `SAYStringRequest`, `SAYSelectRequest`, `SAYNumericalRequest`, `SAYConfirmationRequest`, and `SAYPatternMatchRequest`. Custom parameter requests can be created by simply subclassing `SAYVoiceRequest` and overriding the `didActivate` and `willDeactivate` methods. See the example where we create a custom voice request (TODO: create and link this example)
    ```

- In `ViewController.h`, subscribe to the `SAYCommandBarDelegate` protocol.
    ``` objc
    #import <UIKit/UIKit.h>
    #import <SayKit/SayKit.h>

    @interface ViewController : UIViewController <SAYCommandBarDelegate>

    @end
    ```
- In `AppDelegate.m`'s `application:didFinishLaunchingWithOptions:`, override the `SAYCommandBarController`'s delegate with the view controller:
    ``` objc
    commandBarController.commandBar.delegate = vc;
    ```
The entire method should look like:
    ``` objc
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        
        self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        
        UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        
        ViewController *vc = [mainStoryboard instantiateInitialViewController];
        
        SAYCommandBarController *commandBarController = [[SAYCommandBarController alloc] init];
        
        commandBarController.contentViewController = vc;
        
        UIView *v = commandBarController.view;    // Force commandBarController to load.
        commandBarController.commandBar.delegate = vc;
        
        self.window.rootViewController = commandBarController;
        [self.window makeKeyAndVisible];
        
        return YES;
    }
    ```
- In `ViewController.m`, implement the `SAYCommandBarDelegate` methods:
    ``` objc
    @implementation ViewController

    /* ... */

    #pragma mark - SAYCommandBarDelegate Methods

    - (void)commandBarDidSelectMicrophone:(SAYCommandBar *)commandBar
    {
        // Present the recipe string request
    }

    - (void)commandBarDidSelectCommandMenu:(SAYCommandBar *)commandBar
    {
        // Do nothing for now.
    }

    /* ... */

    ```
- In `commandBarDidSelectMicrophone:`, we'll create the string request and present it using the default voice request presenter:
    ``` objc
    - (void)commandBarDidSelectMicrophone:(SAYCommandBar *)commandBar
    {
        SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:@"What recipe would you like to search for?" completionBlock:^(SAYStringResult * _Nullable result) {
            if (result.error) {
                // Handle error
            }
            else {
                NSString *query = result.transcription;
                [self handleSearchCommandForQuery:query];
            }
        }];
        
        [[SAYVoiceRequestPresenter defaultPresenter] presentRequest:request];
    }
    ```
- Implement a helper function `handleSearchCommandForQuery:` that simply updates the text of `resultsLabel`:
    ``` objc
    - (void)handleSearchCommandForQuery:(NSString *)query
    {
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"Received command: Search for %@", query];
        });
        
        // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
    }
    ```
- Run the app, tap the microphone, and say anything!

#### Classes used:
- SAYCommandBarDelegate
- SAYVoiceRequestPresenter
- SAYStringRequest


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