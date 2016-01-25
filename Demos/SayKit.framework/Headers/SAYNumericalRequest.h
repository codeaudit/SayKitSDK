//
//  SAYNumericalRequest.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/28.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequest.h"

@class SAYNumericalResult;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Describes a voice request used to receive speech input that contains numerical content.
 */
@interface SAYNumericalRequest : SAYVoiceRequest

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
@property (nonatomic, copy) void (^completionBlock)(SAYNumericalResult * __nullable);

/**
 *  Initializes new request
 *
 *  @param prompt Message to present to the user when the prompt begins
 *  @param completionBlock Block to deliver result to
 *
 *  @return The newly-initialized `SAYNumericalRequest`
 */
- (instancetype)initWithPromptText:(NSString *)prompt completionBlock:(void (^)(SAYNumericalResult * __nullable))completionBlock NS_DESIGNATED_INITIALIZER;

// Use `SAYNumericalRequest` initializer instead
- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
