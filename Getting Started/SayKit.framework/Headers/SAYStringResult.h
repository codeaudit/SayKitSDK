//
//  SAYStringResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/03.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Encapsulates result data from a completed `SAYStringRequest`
 */
@interface SAYStringResult : NSObject

NS_ASSUME_NONNULL_BEGIN

/**
 *  Transcription of user speech. If nil, no speech was recognized.
 */
@property (nonatomic, copy, readonly, nullable) NSString *transcription;

/**
 *  Error that prevented the request from completing successfully.
 */
@property (nonatomic, strong, readonly, nullable) NSError *error;

/**
 *  Initializer for a new `SAYStringResult` representing a request with a successfully recognized text transcript.
 *
 *  @param transcription String representing of recognized speech
 *
 *  @return The newly-initiated `SAYStringResult`
 */
- (instancetype)initWithTranscription:(NSString *)transcription NS_DESIGNATED_INITIALIZER;

/**
 *  Initializer for a new `SAYStringResult` representing a request that failed because of an error.
 *
 *  @param error  Content of error underlying failure
 *
 *  @return The newly-initiated `SAYStringResult`
 */
- (instancetype)initWithError:(NSError *)error NS_DESIGNATED_INITIALIZER;

// Use `initWithTranscription:` or `initWithError:` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
