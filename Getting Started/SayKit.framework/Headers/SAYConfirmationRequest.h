//
//  SAYConfirmationRequest.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/20.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequest.h"
#import "SAYConfirmationResult.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Describes a voice request used to receive yes-or-no messages from the user. The request attempts to reduce recognized speech to boolean values.
 */
@interface SAYConfirmationRequest : SAYVoiceRequest

/**
 *  Message to present to the user before the application turns on the microphone.
 */
@property (nonatomic, copy) NSString *promptText;

/**
 *  Message presented before the user is asked to speak again because the first attempt failed to produce a result.
 */
@property (nonatomic, copy, null_resettable) NSString *followupPromptText;

/**
 *  Block the interpreted result is sent to. A nil result indicates the request was cancelled.
 */
@property (nonatomic, copy) void (^completionBlock)(SAYConfirmationResult * __nullable);

/**
 *  Initializes new request
 *
 *  @param promptText      Message to present to the user when the prompt begins
 *  @param completionBlock Block to deliver result to
 *
 *  @return The newly-initialized `SAYConfirmationRequest`
 */
- (instancetype)initWithPromptText:(NSString *)promptText completionBlock:(void (^)(SAYConfirmationResult * __nullable))completionBlock NS_DESIGNATED_INITIALIZER;

// Use `SAYConfirmationRequest` initializer instead
- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService
                                 responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
