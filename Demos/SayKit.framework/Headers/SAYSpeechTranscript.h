//
//  SAYSpeechTranscript.h
//  SayKit
//
//  Created by Greg Nicholas on 10/14/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  A `SAYSpeechTranscript` combines a text string with a confidence value. Useful in responses from speech recognition services that are capable of incorporating uncertainty with their  transcriptions.
 */
@interface SAYSpeechTranscript : NSObject

/**
 *  A potential string of recognized text
 */
@property (nonatomic, copy, readonly) NSString *text;

/**
 *  The confidence associated with the recognized text
 */
@property (nonatomic, assign, readonly) float confidence;

+ (SAYSpeechTranscript *)transcriptWithText:(NSString *)text;
+ (SAYSpeechTranscript *)transcriptWithText:(NSString *)text confidence:(float)confidence;

- (instancetype)initWithText:(NSString *)text;
- (instancetype)initWithText:(NSString *)text confidence:(float)confidence NS_DESIGNATED_INITIALIZER;

/// @abstract Not supported. Use designated initialize for this class instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
