//
//  SAYSelectRequest.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/27.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequest.h"
#import "SAYSelectResult.h"

NS_ASSUME_NONNULL_BEGIN

@class SAYSelectOption;

/**
 *  This request prompts the a user to make a choice between a pre-defined list of options. It includes an optional visual component to allow the user to tap an option directly.
 */
@interface SAYSelectRequest : SAYVoiceRequest

/**
 *  Array of options the user must choose between
 */
@property (nonatomic, copy) NSArray<SAYSelectOption *> *options;

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
@property (nonatomic, copy) void (^completionBlock)(SAYSelectResult * __nullable);

/**
 *  Convenience initializer to create a new request with basic string options (i.e. no aliases)
 *
 *  @param itemLabels      String values for the user to choose
 *  @param promptText      Message to present to the user when the prompt begins
 *  @param completionBlock Block to deliver result to
 *
 *  @return The newly-initialized `SAYSelectResult`
 */
- (instancetype)initWithItemLabels:(NSArray<NSString *> *)itemLabels
                        promptText:(NSString *)promptText
                   completionBlock:(void (^)(SAYSelectResult * __nullable))completionBlock;

/**
 *  Initializes new request with full options
 *
 *  @param options         String values for the user to choose
 *  @param promptText      Message to present to the user when the prompt begins
 *  @param completionBlock Block to deliver result to
 *
 *  @return The newly-initialized `SAYSelectResult`
 */
- (instancetype)initWithOptions:(NSArray<SAYSelectOption *> *)options
                     promptText:(NSString *)promptText
                completionBlock:(void (^)(SAYSelectResult * __nullable))completionBlock NS_DESIGNATED_INITIALIZER;

// Use `SAYSelectRequest` initializer instead
- (instancetype)initWithRecognitionService:(id<SAYSpeechRecognitionService>)recognitionService
                                 responder:(id<SAYVoiceRequestResponder>)responder NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
