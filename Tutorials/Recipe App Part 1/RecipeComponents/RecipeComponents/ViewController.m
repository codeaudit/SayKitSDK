//
//  ViewController.m
//  RecipeComponents
//
//  Created by Adam Larsen on 12/24/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *recognizedSpeechLabel;
@property (weak, nonatomic) IBOutlet UILabel *resultLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

//    [self respondToAvailableCommands];
//    [self respondToSearchCommand];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - SAYCommandBarDelegate Methods

- (void)commandBarDidSelectMicrophone:(SAYCommandBar *)commandBar
{
//    SAYStringRequest *request = [[SAYStringRequest alloc] initWithPromptText:@"What recipe would you like to search for?" completionBlock:^(SAYStringResult * _Nullable result) {
//        if (result.error) {
//            // Handle error
//        }
//        else {
//            NSString *query = result.transcription;
//            [self handleSearchCommandForQuery:query];
//        }
//    }];
    
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

- (void)commandBarDidSelectCommandMenu:(SAYCommandBar *)commandBar
{
    // Do nothing for now.
}

#pragma mark - Private Helpers

- (void)respondToAvailableCommands
{
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
    
    // Respond to speech that asks about available commands, such as "What can I say?" and "Available Commands".
    [commandRegistry addResponseForCommandType:SAYStandardCommandAvailableCommands responseBlock:^(SAYCommand * _Nonnull command) {
        [self handleAvailableCommandsCommand];
    }];
}

- (void)respondToSearchCommand
{
    SAYCommandResponseRegistry *commandRegistry = [SAYCommandResponseRegistry sharedInstance];
    
    // Respond to a search query, such as "Search for Chinese food" or "I want Italian".
    [commandRegistry addResponseForCommandType:SAYStandardCommandSearch responseBlock:^(SAYCommand * _Nonnull command) {
        NSString *query = command.parameters[SAYStandardCommandSearchParameterQuery];
        
        [self handleSearchCommandForQuery:query];
    }];
}

- (void)handleAvailableCommandsCommand
{
    // Calls to UIKit should be done on the main thread.
    dispatch_async(dispatch_get_main_queue(), ^{
        self.resultLabel.text = @"Received command: Available Commands";
    });
    
    // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
}

- (void)handleSearchCommandForQuery:(NSString *)query
{
    // Calls to UIKit should be done on the main thread.
    dispatch_async(dispatch_get_main_queue(), ^{
        self.resultLabel.text = [NSString stringWithFormat:@"Received command: Search for %@", query];
    });
    
    // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
}

- (NSArray<NSString *> *)retrieveSavedRecipeLabels
{
    return @[@"Chocolate Butterscotch Cookies",
             @"Beef Lasagna",
             @"Tuna Casserole"];
}

- (void)handleSelectResultWithOption:(SAYSelectOption *)selectedOption atIndex:(NSUInteger)selectedIndex
{
    NSString *recipeName = selectedOption.label;
    
    // Calls to UIKit should be done on the main thread.
    dispatch_async(dispatch_get_main_queue(), ^{
        self.resultLabel.text = [NSString stringWithFormat:@"Selected \"%@\" (Index %lu)", recipeName, selectedIndex];
    });
    
    // TODO: Update `recognizedSpeechLabel` with transcript (add observer?)
}

@end
