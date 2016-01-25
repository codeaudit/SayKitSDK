//
//  SAYVoiceRequestViewController.h
//  SayKit
//
//  Created by Greg Nicholas on 10/20/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SAYVoiceRequestControlsDelegate;

/**
 *  The `SAYVoiceRequestViewController` provides a visual interface that communicates to the user the request’s purpose, gives feedback about the ongoing microphone activity, and provides interactive control over the session.
 
    In addition to displaying these basics, the `SAYVoiceRequestViewController` can contain a supplemental view controller to add a more robust visual interface for the corresponding request. This supplemental view controller can be used to provide touch based interaction to a request.
 */
@interface SAYVoiceRequestViewController : UIViewController

/**
 *  Displays the current prompt text
 */
@property (nonatomic, strong, readonly) UILabel *promptLabel;

/**
 *  Button to immediately cancel the request
 */
@property (nonatomic, strong, readonly) UIButton *cancelButton;

/**
 *  Button to control microphone activity
 */
@property (nonatomic, strong, readonly) UIButton *microphoneButton;

/**
 *  Displays a partial transcript received from the speech recognition service
 */
@property (nonatomic, strong, readonly) UILabel *partialTranscriptLabel;

/**
 *  View containing the `contentViewContainer`
 */
@property (nonatomic, strong, readonly) UIView *contentViewContainer;

/**
 *  Customizable style for the overlay underlying the request view
 */
@property (nonatomic, assign) UIBlurEffectStyle overlayBlurEffectStyle;

/**
 *  An optional supplemental view controller
 */
@property (nonatomic, strong, nullable) UIViewController *contentViewController;

/**
 *  Delegate to receive messages from control interaction (i.e. microphone tap)
 */
@property (weak, nullable) id<SAYVoiceRequestControlsDelegate> controlsDelegate;

// higher-level helpers to manipulate subviews

/**
 *  Displays the given string as a prompt
 *
 *  @param string Prompt text to display
 */
- (void)displayPromptText:(NSString *)string;

/**
 *  Displays the given attributed string as a prompt
 *
 *  @param attributedString Attributed prompt text to display
 */
- (void)displayPromptAttributedText:(NSAttributedString *)attributedString;

/**
 *  Enables the microphone button
 */
- (void)enableMicrophoneInteraction;

/**
 *  Disables the microphone button
 */
- (void)disableMicrophoneInteraction;

/**
 *  Called to inform the receiver that the microphone is active and audio updates will begin streaming in
 */
- (void)microphoneLevelUpdatesWillStart;

/**
 *  Called to inform the receiver that the microphone is inactive and audio updates have stopped
 */
- (void)microphoneLevelUpdatesDidStop;

/**
 *  Update the microphone visualization with the given level
 *
 *  @param audioLevel Raw decibel level of microphone input
 */
- (void)displayMicrophoneLevel:(float)audioLevel;

/**
 *  Displays a partial transcript during the recognition process
 *
 *  @param text Partial transcript string to display
 */
- (void)displayPartialTranscript:(NSString *)text;

/**
 *  Displays the given error message
 *
 *  @param errorMessage Error string to display
 */
- (void)displayErrorMessage:(NSString *)errorMessage;

@end

/**
 *  The `SAYVoiceRequestControlsDelegate` protocol prescribes an interface for communicating control events from a `SAYVoiceRequestViewController`.
 */
@protocol SAYVoiceRequestControlsDelegate <NSObject>

/**
 *  Called when the view controller's microphone button is tapped
 *
 *  @param viewController View controller containing microphone control
 */
- (void)controllerMicrophoneWasTapped:(SAYVoiceRequestViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
