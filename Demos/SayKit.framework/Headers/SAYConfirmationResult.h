//
//  SAYConfirmationResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/26.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Encapsulates result data from a completed `SAYConfirmationRequest`
 */
@interface SAYConfirmationResult : NSObject

/**
*  Boolean result wrapped up as an `NSNumber`. Value will always be @0, @1, or nil.
*/
@property (nonatomic, readonly, nullable) NSNumber *confirmed;

/**
 *  Error that prevented the request from completing successfully.
 */
@property (nonatomic, strong, readonly, nullable) NSError *error;

/**
 *  Initializer for a new `SAYConfirmationResult` representing a request with a successful boolean result.
 *
 *  @param confirmed YES if user answered affirmatively, NO otherwise.
 *
 *  @return The newly-initiated `SAYConfirmationResult`
 */
- (instancetype)initWithConfirmation:(BOOL)confirmed NS_DESIGNATED_INITIALIZER;

/**
 *  Initializer for a new `SAYConfirmationResult` representing a request that failed because of an error.
 *
 *  @param error  Content of error underlying failure
 *
 *  @return The newly-initiated `SAYConfirmationResult`
 */
- (instancetype)initWithError:(NSError *)error NS_DESIGNATED_INITIALIZER;

// Use `initWithConfirmation:` or `initWithError:` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
