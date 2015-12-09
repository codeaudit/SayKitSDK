//
//  SAYVerbalCommandRequest.h
//  SayKit
//
//  Created by Greg Nicholas on 10/20/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SAYVoiceRequest.h"

@class SAYCommandDispatcher;
@protocol SAYCommandResolver;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYVerbalCommandRequest` is a `SAYVoiceRequest` tailored towards allowing users to speak commands. The recognized speech is sent into the SayKit command processing pipeline, being resolved as potenetial commands and then dispatched to the application.
 
    In the current version of SayKit, the speech recognizer underlying this command cannot be cusotmized.
 */
@interface SAYVerbalCommandRequest : SAYVoiceRequest

/**
 *  Initialize a new request with the given command pipeline components
 *
 *  @param commandResolver   Command resolver capable of processing speech recognition results
 *  @param commandDispatcher Agent to dispatch resolved potential commands
 *
 *  @return The newly-initialized request
 */
- (instancetype)initWithCommandResolver:(id<SAYCommandResolver>)commandResolver
                             dispatcher:(SAYCommandDispatcher *)commandDispatcher NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
