//
//  SAYVoiceRequestPresenter.h
//  SayKit
//
//  Created by Greg Nicholas on 11/15/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SAYVoiceRequest;
@protocol SAYAudioEventListener;

@class UIViewController;
@class SAYSpeechRecognitionManager;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYVoiceRequestPresenter` is responsible for integrating all system components necessary to presenting and activate a `SAYVoiceRequest`.
 */
@interface SAYVoiceRequestPresenter : NSObject

/**
 *  Recognition manager to be provided to all presented requests. To ensure the manager is idle when presenting, no other parts of the application should interact with it.
 */
@property (nonatomic, strong) SAYSpeechRecognitionManager *recognitionManager;

/**
 *  Listener to receive and present audio events (e.g. prompt speech)
 */
@property (nonatomic, strong) id<SAYAudioEventListener> audioEventPresenter;

/**
 *  Returns a system-wide default presenter
 *
 *  @return The a system-wide default presenter
 */
+ (SAYVoiceRequestPresenter *)defaultPresenter;

/**
 *  Initiates a `SAYVoiceRequestPresenter` with the given request manager and output audio track.
 *
 *  @param manager Manager to run speech recognition sessions
 *
 *  @return The newly-initiated presenter
 */
- (instancetype)initWithSpeechRecognitionManager:(SAYSpeechRecognitionManager *)manager;

/**
 *  Connects the given request to a `SAYVoiceRequestController` and presents it, using the receiver's `presentingTrack` and `presentingViewController`.
 *
 *  @param request Request to be presented
 */
- (void)presentRequest:(id<SAYVoiceRequest>)request;

/**
 *  Presents the given request, using the provided view controller as a presenter instead of the receiver's built-in instance.
 *
 *  @param request Request to be presented
 *  @param presentingViewController View controller from which to modally present request's visual component
 */
- (void)presentRequest:(id<SAYVoiceRequest>)request fromViewController:(UIViewController *)presentingViewController;

/**
 *  Deactivates and dismisses the given request. Once the request deactivates, the view controller is dismissed, the `outputTrack` is disconnected, and any active recognition session with manager is cancelled.
 *
 *  @param completion Block to be executed when dismissal completes
 */
- (void)dismissPresentedRequestCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END