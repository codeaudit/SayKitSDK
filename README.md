# SayKitSDK
Framework for building voice enabled applications on iOS. Currently deployed as Version 0.6.

# Roadmap

This is a private beta release of the SayKit framework, with new features and API changes being rolled out continuously in this repository.

More specifically, the planned release timeline includes:

- Version 0.6 (early-December)
  - All **foundational tools** necessary for an end-to-end conversational user interface
- Version 0.7 (mid-December)
  - **Turn-taking (back-and-forth) dialogue** management to more directly define a back-and-forth dialogue between user and application
- Version 0.8 (early-January)
  - Hierarchical application state features to support **conditional command availability** and **layered speech output** from different application contexts
  - **UIKit binding** tools for multi-modal interfaces
- Version 0.9 (mid-January)
  - Command resolution improvements, including **support for third-party intent recognition services**

# Getting Started
## 1. Get the SDK!
Download the SayKit SDK [here](https://github.com/ConversantLabs/SayKitSDK).

## 2. Setup a Project
You can follow along and create your own project, or skip to the bottom for a link to the entire example project.

### Create the project
- File -> New -> Project -> iOS Application -> Single View Application
- Assign a Product Name.
- Select your language: Objective C or Swift.

### Import SayKit SDK
- File -> Add Files to "MyProject".
- Navigate to where you downloaded the framework, and select `SayKitSDK.framework`. The framework should now appear on the left, in Xcode's Project Navigator pane.
- Select the project in the Navigator pane, select your target, and go to the Build Phases tab.
- Under "Link Binary With Libraries", make sure `SayKitSDK.framework` is in the list.
- Under "Embed Frameworks", make sure `SayKitSDK.framework` is in the list.
- If using Swift, create a bridging header that includes "SayKit.h" 		// TODO - Add details

## 3. Create a Voice Request
We're going to make a simple Magic 8 Ball app that listens to the user's yes-or-no question, and randomly replies with one of several responses that we'll define below.

### Setup the UI
We'll add a button that we can press to launch the request, as well as some labels to display visual feedback to the user.

- Open `Main.storyboard`
- Add a UIButton with the title "Start Request" to the view controller.
- Create an action outlet for the button in `ViewController.m`:
```
- (IBAction)voiceRequestButtonTapped:(id)sender
{
    /* ... */
}
```

- Add a "Results" UILabel to display the app's response to the user.
- Add an "Echo" UILabel to display what the user just said.
- Create outlets for the "Results" and "Echo" labels in `ViewController.m`:
```
@property (strong, nonatomic) IBOutlet UILabel *resultsLabel;
@property (strong, nonatomic) IBOutlet UILabel *echoLabel;
```
```
// TODO - Insert picture of storyboard setup here
```

### Prepare app logic
- Define an array where we can store our Magic 8 Ball responses:
```
@interface ViewController ()

/* ... */

@property (copy, nonatomic) NSArray *responseStrings;

@end
```

- and initialize them in `viewDidLoad`:
```
_responseStrings = @[@"It is certain",
                     @"It is decidedly so",
                     @"Without a doubt",
                     @"Yes, definitely",
                     @"You may rely on it",
                     @"As I see it, yes",
                     @"Most likely",
                     @"Outlook good",
                     @"Yes",
                     @"Signs point to yes",
                     @"Reply hazy try again",
                     @"Ask again later",
                     @"Better not tell you now",
                     @"Cannot predict now",
                     @"Concentrate and ask again",
                     @"Don't count on it",
                     @"My reply is no",
                     @"My sources say no",
                     @"Outlook not so good",
                     @"Very doubtful"];
```

- Create a helper method `getResponseString` that randomly returns one of the strings in our response list:
```
- (NSString *)getResponseString
{
    u_int32_t upperBound = (u_int32_t)self.responseStrings.count;
    NSUInteger randomIndex = arc4random_uniform(upperBound);
    
    return self.responseStrings[randomIndex];
}
```

### Instantiate the request
- In `ViewController.m`, import SayKit:
```
#import "ViewController.h"
#import <SayKit/SayKit.h>
```

- In `voiceRequestButtonTapped:`, add a call to an upcoming helper function, `beginVoiceRequest`:
```
- (IBAction)voiceRequestButtonTapped:(id)sender
{
    [self beginVoiceRequest];
}
```

- Create a helper function, `beginVoiceRequest`.

Here we create the voice request using a subclass of `SAYVoiceRequest`, `SAYStringRequest`. It takes a string, `promptText`, to speak and display to the user, as well as a completion block that contains the result of the request:
```
NSString *promptText = @"Ask me anything! The Magic 8 Ball knows all.";
SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:promptText completionBlock:^(SAYStringRequestResult *result) { /* ... */ }
```

Within the completion block, we can respond to any errors and contents of the result. In this case, we're interested in the transcript of recognized speech. Depending on the request type, a result may also contain additional parameters for your app to consume.
```
NSString *promptText = @"Ask me anything! The Magic 8 Ball knows all.";
SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:promptText completionBlock:^(SAYStringRequestResult *result) {
    if (result.error) {
        self.echoLabel.text = @"--";
        self.resultsLabel.text = result.error.localizedDescription;
    }
    else {
        self.echoLabel.text = result.transcription;
        self.resultsLabel.text = [self buildResponseString];
    }
}];
```

Finally, present the request using `SAYVoiceRequestPresenter`'s `defaultPresenter`.
```
[[SAYVoiceRequestPresenter defaultPresenter] presentRequest:request];
```

`beginVoiceRequest` should now look like this:
```
- (void)beginVoiceRequest
{
    NSString *promptText = @"Ask me anything! The Magic 8 Ball knows all.";
    SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:promptText completionBlock:^(SAYStringRequestResult * _Nonnull result) {
        if (result.error) {
            self.echoLabel.text = @"--";
            self.resultsLabel.text = result.error.localizedDescription;
        }
        else {
            self.echoLabel.text = result.transcription;
            self.resultsLabel.text = [self buildResponseString];
        }
    }];
    
    [[SAYVoiceRequestPresenter defaultPresenter] presentRequest:request];
}
```

Put it all together and you should end up with a `ViewController.m` that looks something like [this]() // TODO - Link to ViewController.m

You're done! Build and run the app. Tap the "Start Request" button and the app should speak and display the prompt, "Ask me anything! The Magic 8 Ball knows all.". Tap the microphone button and say "Will I find a lucky penny today?". The app should speak and display its response via `responseLabel`, as well as display the recognized speech text via `echoLabel`.

## 4. Next Steps
Download the full [Magic 8 Ball app]() to get you started. // TODO - Link

Check out our [tutorial series]() that walks you through the creation of a Recipe app. // TODO - Link

Learn more about SayKit's design and capabilities. // TODO - link to dev guide

Read through SayKit's [full documentation](https://github.com/ConversantLabs/SayKitSDK/tree/master/Developer%20Guide).
