//
//  SAYPatternMatchRequest.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/29.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequest.h"

@class SAYPatternMatchResult;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYPatternMatchRequest` describes a voice request for speech matching a particular string pattern. If user speech does not conform to the prescribed patterns provided, the user will be prompted to try again.
 */
@interface SAYPatternMatchRequest : SAYVoiceRequest

/**
 *  Message to present to the user before the application turns on the microphone.
 */
@property (nonatomic, copy) NSString *promptText;

/**
 *  Message presented before the user is asked to speak again because the first attempt failed to produce a result.
 */
@property (nonatomic, copy, null_resettable) NSString *followupPromptText;

/**
 *  Array of templates. User speech must match one of these patterns to be accepted.
 *
 *  TODO: add a reference to docs for pattern syntax
 */
@property (nonatomic, copy) NSArray<NSString *> *templates;

/**
 *  Block the interpreted result is sent to. A nil result indicates the request was cancelled.
 */
@property (nonatomic, copy) void (^completionBlock)(SAYPatternMatchResult * __nullable);

/**
 *  Create a new `SAYPatternMatchRequest` with the given templates
 *
 *  @param promptText      Message to present to the user when the prompt begins
 *  @param templates       An array of templates to use in parsing the recognized text
 *  @param completionBlock Block to deliver result to
 *
 * Entities in each template must be defined according to the following examples:
 *      "Call @recipient:String."
 *      "Ask @nameOfFriend for @cookieCount:Number cookies."
 *       "@payer gave @payee @amount:Number dollars."
 *       "@payee received @amount:Number dollars from @payer."
 *       In general, the syntax of an entity is "@entityName:EntityType", where EntityType can be either "String" or "Number". If ":EntityType" is omitted, the parser assumes the Entity is a string.
 */
- (instancetype)initWithPromptText:(NSString *)promptText
                         templates:(NSArray<NSString *> *)templates
                   completionBlock:(void (^)(SAYPatternMatchResult * __nullable))completionBlock NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService
                                 responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
