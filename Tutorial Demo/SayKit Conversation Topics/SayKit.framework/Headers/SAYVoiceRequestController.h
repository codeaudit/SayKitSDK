//
//  SAYVoiceRequestController.h
//  SayKit
//
//  Created by Greg Nicholas on 10/20/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SAYSpeechRecognitionManager.h"

@protocol SAYVoiceRequestMicrophoneDelegate;
@protocol SAYVoiceRequest;

@class SAYVoiceRequestSoundBoard;
@class SAYVoiceRequestPresenter;
@class SAYVoiceRequestView;
@class SAYInterpretation;

#import "SAYVoiceRequestResponse.h"

NS_ASSUME_NONNULL_BEGIN

@interface SAYVoiceRequestController : UIViewController <SAYSpeechRecognitionManagerDelegate>

/**
 *  Primary view displaying state of request and allowing interaction with the request flow
 */
@property (nonatomic, strong, null_unspecified) SAYVoiceRequestView *voiceRequestView;

/**
 *  An audio interface to provide feedback during the request session.
 */
@property (nonatomic, strong) SAYVoiceRequestSoundBoard *soundBoard;

/**
 *  Customizable style for the overlay underlying the request view
 */
@property (nonatomic, assign) UIBlurEffectStyle overlayBlurEffectStyle;

/**
 *  A supplemental child controller whose view is embedded in the `voiceRequestView`
 */
@property (nonatomic, strong, readonly, nullable) UIViewController *supplementalViewController;

/**
 *  When the request is active, the instance that presented it.
 
 This property is nil when the request is no currently presented.
 */
@property (nonatomic, strong, nullable) SAYVoiceRequestPresenter *presenter;

@property (nonatomic, strong, nullable) SAYSpeechRecognitionManager *recognitionManager;

@property (nonatomic, strong, nullable) id<SAYVoiceRequest> voiceRequest;

- (void)respondImmediatelyToInterpretation:(SAYInterpretation *)interpretation;
- (nullable SAYVoiceRequestResponseAction)cancelRequest;

@end

NS_ASSUME_NONNULL_END
