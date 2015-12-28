//
//  ViewController.m
//  RecipeComponents
//
//  Created by Adam Larsen on 12/24/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import "ViewController.h"
#import <SayKit/SayKit.h>

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *recognizedSpeechLabel;
@property (weak, nonatomic) IBOutlet UILabel *resultLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    [self respondToAvailableCommands];
    [self respondToSearchCommand];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Private Helpers

- (void)respondToAvailableCommands
{
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
    
    // Respond to speech that asks about available commands, such as "What can I say?" and "Available Commands".
    [commandRegistry addResponseForCommandType:SAYStandardCommandAvailableCommands responseBlock:^(SAYCommand * _Nonnull command) {
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = @"Received command: Available Commands";
        });
    }];
    
    // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
}

- (void)respondToSearchCommand
{
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
    
    // Respond to a search query, such as "Search for Chinese food" or "I want Italian".
    [commandRegistry addResponseForCommandType:SAYStandardCommandSearch responseBlock:^(SAYCommand * _Nonnull command) {
        NSString *query = command.parameters[SAYStandardCommandSearchParameterQuery];
        
        // Calls to UIKit should be done on the main thread.
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"Received command: Search for %@", query];
        });
    }];
    
    // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
}

@end
