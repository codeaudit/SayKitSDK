//
//  SAYVoiceRequest.h
//  SayKit
//
//  Created by Greg Nicholas on 11/18/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYSpeechRecognitionManager.h"
#import "SAYVoiceRequestViewController.h"

@protocol SAYSpeechRecognitionService;
@protocol SAYVoiceRequestResponder;
@class SAYVoiceRequestSoundBoard;
@class SAYVoiceRequestPresenter;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Abstract base class integrating all components necessary for a request-response cycle. This includes the underlying speech recognition service, the strategy for handling recognized speech, and the interface communicating the ongoing request's progress.
 */
@interface SAYVoiceRequest : NSObject <SAYSpeechRecognitionManagerDelegate, SAYVoiceRequestControlsDelegate>

/**
 *  Underlying service responsible for recognizing speech
 */
@property (nonatomic, strong, readonly) id<SAYSpeechRecognitionService> recognitionService;

/**
 *  An agent responsible for interpretting recognized speech and producing a response suitable for the request.
 */
@property (nonatomic, strong, readonly) id<SAYVoiceRequestResponder> responder;

/**
 *  A visual interface responsible for displaying the progress of the request session. Also includes customizable interactive components.
 */
@property (nonatomic, strong) SAYVoiceRequestViewController *viewController;

/**
 *  An audio interface to provide feedback during the request session.
 */
@property (nonatomic, strong) SAYVoiceRequestSoundBoard *soundBoard;

/**
 *  When the request is active, the instance that presented it.
 
    This property is nil when the request is no currently presented.
 */
@property (nonatomic, strong, nullable) SAYVoiceRequestPresenter *presenter;

/**
 *  When the request is active, the recognition manager that was provided to it. This manager is guaranteed to be idle and available for a new session initialization.
 
    This property is nil when the request is no currently presented.
 */
@property (nonatomic, strong, readonly, nullable) SAYSpeechRecognitionManager *recognitionManager;

/**
 *  Initiates a voice request using the given recognition service and recognized speech responder.
 *
 *  @param recognitionService Agent responsible for communicating with speech recognition service
 *  @param responder Agent responsible for responding to recognized speech (or recognition error)
 *
 *  @return The newly initialized request
 */
- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService
                                 responder:(id<SAYVoiceRequestResponder>)responder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/**
 *  Called to start a new request session.
 *
 *  Subclasses should not override this method. The `didActivate` method is available if a subclass requires additional behavior during activation.
 *
 *  @param manager Agent capable of managing the details of the speech recognition session
 *
 *  @warning The manager included in this message should be idle. If it is not, an exception is thrown because. If the manager is not idle, the application could enter an unstable state because the request assumes complete control over its recognition session.
 */
- (void)activateWithRecognitionManager:(SAYSpeechRecognitionManager *)manager;

/**
 *  Called to end a request session.
 */
- (void)deactivate;

/**
 *  Called immediately before `activateWithRecognitionManager:` returns. Provided as a customization point for subclasses.
 */
- (void)didActivate;

/**
 *  Called as soon as the `deactivate` method is called. Provided as a customization point for subclasses.
 */
- (void)willDeactivate;

@end

NS_ASSUME_NONNULL_END