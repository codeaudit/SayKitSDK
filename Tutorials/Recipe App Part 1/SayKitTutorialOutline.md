# SayKit Tutorial Outline


## General plan:
In this tutorial we'll walk through how to use some of the most important features of SayKit. In Part I we'll treat each feature in isolation, and in Part II we'll put them all together into a full app.
For now, in Part I, components will be swapped out by simply changing lines of code.


## Setup
The backbone of our Part I tutorial app is a single view controller contained within an instance of a `SAYCommandBarController`, which provides a simple interface for the user to start speech recognition. We'll rely on a couple of UILabels for simple feedback to test each feature as we go.

- Create a new single-view application
- Add the SayKit framework, following the Getting Started instructions here // TODO - Link
- In `Main.storyboard`'s View Controller Scene:
    + Add a UILabel and hook it up to a new property in `ViewController.m` called `recognizedSpeechLabel`.
    + Add a UILabel and hook it up to a new property in `ViewController.m` called `interpretedCommandLabel`.
- In `AppDelegate.m`, setup a `SAYCommandBarController` as the window's root view controller. The `SAYCommandBarController` behaves like a container view controller similar to a `UITabBarController`. In this case, the content view controller is our `ViewController`.
    ``` objc
    #import <SayKit/SayKit.h>

    /* ... */

    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
    {
        self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        
        UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        
        ViewController *vc = [mainStoryboard instantiateInitialViewController];
        
        SAYCommandBarController *commandBarController = [[SAYCommandBarController alloc] init];
        
        commandBarController.contentViewController = vc;
        
        self.window.rootViewController = commandBarController;
        [self.window makeKeyAndVisible];
        
        return YES;
    }

    /* ... */
    ```

#### Classes used:
- SAYCommandBarController


## Available Commands (verbal request)
Conversant apps should let the user know what commands are usable at any given point in the app. Using SayKit, this is as straightforward as registering a response for the standard command type, `SAYStandardCommandAvailableCommands`. This predefined command is dispatched when the user speaks utterances like "What can I say?" and "Available commands".

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
- The `handleAvailableCommandsCommand` helper function simply updates the results label. In a full app, we would be able to query SayKit for the currently available commands and present them to the user as speech, a table view, or both.
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


## Search for recipes (verbal request)
In the previous step, we responded to the standard "Available Commands" command. The response, however, didn't rely on any input parameters from the user beyond the fact that they are requesting Available Commands. In this step, we'll respond to the standard "Search" command, which includes a parameter for the search query.

- Add a response to the standard Search command.
    ``` objc
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
    [commandRegistry addResponseForCommandType:SAYStandardCommandSearch responseBlock:^(SAYCommand * _Nonnull command) {
        /* ... */
    }];
    ```
- In the response block, extract the `searchQuery` parameter from the `command` input, and present it in the `resultsLabel`. In a full app, we would pass the query on to an API call. `viewDidLoad` should not look like this:
    ``` objc
    - (void)viewDidLoad {
        [super viewDidLoad];

        SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
        
        // Respond to a search query, such as "Search for Chinese food" or "I want Italian".
        [commandRegistry addResponseForCommandType:SAYStandardCommandSearch responseBlock:^(SAYCommand * _Nonnull command) {
            NSString *query = command.parameters[SAYStandardCommandSearchParameterQuery];
            
            // Calls to UIKit should be done on the main thread.
            dispatch_async(dispatch_get_main_queue(), ^{
                self.resultLabel.text = [NSString stringWithFormat:@"Received command: Search for %@", query];
            });
        }];
    }
    ```

#### Classes to go over:
- Same as in Available Commands


## Search for recipes (string request)
A `SAYStringRequest` can be used to ask the user for a string. Let's ask the user what recipe they would like to search for. In a full app, this could be triggered by a button tap, or it could be a followup request to our earlier Recipe Search Verbal Request in case the app was unable to understand a search query.
For this example, we'll trigger the string request whenever the microphone button is tapped. We start by overriding `SAYCommandBarController`'s delegate, and implementing the `SAYCommandBarDelegate` methods in `ViewController.m`.

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
    ```
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
    ```
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

#### Classes to go over:
- SAYCommandBarDelegate
- SAYVoiceRequestPresenter
- SAYStringRequest


## View Saved Recipes (select request)
We can use a `SAYSelectRequest` to prompt the user to make a selection from a list. Suppose we have a list of saved recipes from which the user can make a selection to get details on that recipe. We'll reuse the same setup we had in the previous example with the String request, so when we tap the microphone button, the user will be asked to make the selection. As before, we'll simply update the `resultsLabel` with the user's selection.
- In a full app, we would maintain a list of saved recipes for the user. Here, we'll simply call a helper/dummy function to serve us the list:
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
- There is an alternative initializer for `SAYSelectRequest` that can handle aliases for each item, `initWithOptions:promptText:completionBlock`. We'll go over that in the next example. (TODO)
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
        / * ... */
    }];
    ```

#### Classes to go over:
	- SAYSelectRequest
    - SAYSelectOption
    - SAYSelectResult


## Recipe Ingredients (using pattern match resolver)
An alternative to using SayKit Standard verbal command requests is to construct your own text resolver. Custom text resolvers are a good way to handle simple speech patterns without having to setup your own intent recognition service.
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
- In `ViewContrller.m`'s `viewDidLoad` method, we register our resolver via a helper function:
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

#### Classes to go over:
- SAYPatternTextResolver
- SAYDomain
- SAYDomainRegistry
- SAYCommandResponseRegistry
