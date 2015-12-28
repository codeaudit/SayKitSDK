//
//  SAYSpeechIntent.h
//  SayKit
//
//  Created by Greg Nicholas on 10/14/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Represents a loosely structured intent suggestion returned from an external service.
 */
@interface SAYSpeechIntent : NSObject

@property (nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, copy, readonly) NSDictionary *entities;

// On initialization, `confidence` is normalized to be a value from 0.0 to 1.0, with the minimum corresponding to a raw confidence equal to `kDefaultVoiceIntentConfidenceThreshold`.
@property (nonatomic, assign, readonly) float confidence;

@property (nonatomic, copy, readonly, nullable) NSString *rawText;

+ (SAYSpeechIntent *)intentWithIdentifier:(NSString *)identifier
                                 entities:(NSDictionary *)entities
                            rawConfidence:(float)confidence
                                  rawText:(nullable NSString *)rawText;

- (instancetype)initWithIdentifier:(NSString *)identifier
                          entities:(NSDictionary *)entities
                     rawConfidence:(float)confidence
                           rawText:(nullable NSString *)rawText NS_DESIGNATED_INITIALIZER;

/// @abstract Not supported. Use designated initialize for this class instead.
- (instancetype)init NS_UNAVAILABLE;

@end

FOUNDATION_EXPORT const float kDefaultVoiceIntentConfidenceThreshold;

NS_ASSUME_NONNULL_END
