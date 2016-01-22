//
//  SAYVoiceRequestPresenter.h
//  SayKit
//
//  Created by Greg Nicholas on 11/15/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UIViewController;
@class SAYSpeechRecognitionManager;
@class SAYVoiceRequest;
@class SAYAudioTrack;

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
 *  Track to be used for presenting all audio
 */
@property (nonatomic, strong) SAYAudioTrack *outputTrack;

/**
 *  The currently presented request, if it exists
 */
@property (nonatomic, strong, readonly, nullable) SAYVoiceRequest *presentedRequest;

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
 *  @param audioTrack Track to send audio events to
 *
 *  @return The newly-initiated presenter
 */
- (instancetype)initWithSpeechRecognitionManager:(SAYSpeechRecognitionManager *)manager outputTrack:(SAYAudioTrack *)audioTrack;

/**
 *  Convenience method for `presentRequest:fromViewController:`. Uses the application's root view controller.
 *
 *  @param request Request to be presented
 *
 *  @warning Because this method presents a `UIViewController`, it must be called on the main thread.
 */
- (void)presentRequest:(SAYVoiceRequest *)request;

/**
 *  Presents and activates the given request. This includes connecting the `outputTrack` to the request's `soundBoard` and using the `UIViewController` argument to present the request's `viewController`. Only after the interfaces are connected will the request activate.
 *
 *  @param request Request to be presented
 *  @param presentingViewController View controller from which to modally present request's visual component
 *
 *  @warning Because this method presents a `UIViewController`, it must be called on the main thread.
 */
- (void)presentRequest:(SAYVoiceRequest *)request fromViewController:(nullable UIViewController *)presentingViewController;

/**
 *  Deactivates and dismisses the given request. Once the request deactivates, the view controller is dismissed, the `outputTrack` is disconnected, and any active recognition session with manager is cancelled.
 
    @param completion Block to be executed when dismissal completes
 */
- (void)dismissPresentedRequestCompletion:(void (^ __nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
