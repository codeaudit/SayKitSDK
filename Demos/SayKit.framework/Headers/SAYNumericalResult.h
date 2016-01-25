//
//  SAYNumericalResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/28.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Encapsulates result data from a completed `SAYNumericalRequest`
 */
@interface SAYNumericalResult : NSObject

/**
 *  Result represented as a number. If nil, no number could be interpreted from user input.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *number;

/**
 *  Error that prevented the request from completing successfully.
 */
@property (nonatomic, strong, readonly, nullable) NSError *error;

/**
 *  Initializer for a new `SAYNumericalResult` representing a request with a successful boolean result.
 *
 *  @param number Number representing user's numerical response
 *
 *  @return The newly-initiated `SAYNumericalResult`
 */
- (instancetype)initWithNumber:(NSNumber *)number NS_DESIGNATED_INITIALIZER;

/**
 *  Initializer for a new `SAYNumericalResult` representing a request that failed because of an error.
 *
 *  @param error  Content of error underlying failure
 *
 *  @return The newly-initiated `SAYNumericalResult`
 */
- (instancetype)initWithError:(NSError *)error NS_DESIGNATED_INITIALIZER;

// Use `initWithNumber:` or `initWithError:` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
