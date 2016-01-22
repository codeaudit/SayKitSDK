//
//  SAYVoiceRequest.h
//  SayKit
//
//  Created by Greg Nicholas on 12/31/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYVoicePrompt;
@protocol SAYSpeechRecognitionService;
@protocol SAYVoiceRequestInterpreter;
@protocol SAYVoiceRequestResponder;

@protocol SAYVoiceRequest <NSObject>

@property (nonatomic, copy, readonly, nullable) SAYVoicePrompt *prompt;

/**
 *  Underlying service responsible for recognizing speech
 */
@property (nonatomic, readonly, nonnull) id<SAYSpeechRecognitionService> recognitionService;

/**
 *  Delegate responsible for interpeting speech input into a usable result
 */
@property (nonatomic, readonly, nonnull) id<SAYVoiceRequestInterpreter> interpreter;

/**
 *  Delegate responsible for reacting to the interpreted result (and potentially generating the next turn).
 */
@property (nonatomic, readonly, nonnull) id<SAYVoiceRequestResponder> responder;

@end
