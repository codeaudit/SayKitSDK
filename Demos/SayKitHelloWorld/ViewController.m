//
//  ViewController.m
//  SayKitHelloWorld
//
//  Created by Adam Larsen on 2015/12/07.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import "ViewController.h"
#import <SayKit/SayKit.h>

@interface ViewController ()

@property (strong, nonatomic) IBOutlet UILabel *resultsLabel;
@property (strong, nonatomic) IBOutlet UILabel *echoLabel;

@property (copy, nonatomic) NSArray *responseStrings;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
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
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)voiceRequestButtonTapped:(id)sender
{
    [self beginVoiceRequest];
}

- (void)beginVoiceRequest
{
    NSString *promptText = @"Ask me anything! The Magic 8 Ball knows all.";
    SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:promptText completionBlock:^(SAYStringResult * _Nonnull result) {
        if (result == nil) {
            self.echoLabel.text = @"--";
            self.resultsLabel.text = @"User cancelled the request";
        }
        if (result.error) {
            self.echoLabel.text = @"--";
            self.resultsLabel.text = result.error.localizedDescription;
        }
        else {
            self.echoLabel.text = result.transcription;
            self.resultsLabel.text = [self getResponseString];
        }
    }];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [[SAYVoiceRequestPresenter defaultPresenter] presentRequest:request];
    });
}

// Return a random string from `self.responseStrings`.
- (NSString *)getResponseString
{
    u_int32_t upperBound = (u_int32_t)self.responseStrings.count;
    NSUInteger randomIndex = arc4random_uniform(upperBound);
    
    return self.responseStrings[randomIndex];
}

@end
