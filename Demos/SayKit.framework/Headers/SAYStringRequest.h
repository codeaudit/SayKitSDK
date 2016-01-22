//
//  SAYStringRequest.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/03.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequest.h"

@class SAYStringResult;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Describes a voice request used to receive arbitrary speech input. The recognized speech transcript is delivered directly with no additional interpretation.
 */
@interface SAYStringRequest : SAYVoiceRequest

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
@property (nonatomic, copy) void (^completionBlock)(SAYStringResult * __nullable);

/**
 *  Initializes new request
 *
 *  @param promptText      Message to present to the user when the prompt begins
 *  @param completionBlock Block to deliver result to
 *
 *  @return The newly-initialized `SAYStringRequest`
 */
- (instancetype)initWithPromptText:(NSString *)promptText completionBlock:(void (^)(SAYStringResult * __nullable))completionBlock NS_DESIGNATED_INITIALIZER;

// Use `SAYStringRequest` initializer instead
- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService
                                 responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
