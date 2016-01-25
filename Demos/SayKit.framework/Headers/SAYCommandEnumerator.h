//
//  SAYCommandGenerator.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYCommand;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYCommandEnumerator` is a specialized `NSEnumerator` for handling only `SAYCommand` instances.
 */
@interface SAYCommandEnumerator : NSEnumerator

/**
 *  Convenience initializer that creates a `SAYCommandEnumerator` backed by an existing array of commands.
 *
 *  @param array Array of `SAYCommand` instance
 *
 *  @return The array of commands exposed as an enumeration
 */
+ (SAYCommandEnumerator *)enumeratorFromArray:(NSArray<SAYCommand *> *)array;

/**
 *  Convenience initializer to transform an existing `NSEnumerator` for `SAYCommand` instances into an official `SAYCommandEnumerator`. Useful for transforming arbitrary collections into enumerations.
 *
 *  @param enumerator Underlying `NSEnumerator` providing the values
 *
 *  @return The newly-initialized and populated `SAYCommandEnumerator`
 */
+ (SAYCommandEnumerator *)enumeratorFromEnumerator:(NSEnumerator<SAYCommand *> *)enumerator;

/**
 *  Convenience initializer to create an enumerator with no values. All `nextCommand` messages sent to the resulting instance will return nil.
 *
 *  @return An empty `SAYCommandEnumerator`
 */
+ (SAYCommandEnumerator *)emptyEnumerator;

/**
 *  Type-specific way to access the next `SAYCommand` in the enumeration. Implementation calls `nextObject` on itself.
 *
 *  @return The next command in the enumeration, or nil if no more commands exist.
 */
- (nullable SAYCommand *)nextCommand;

/**
 *  Creates a new initializer by "appending" the given enumerator onto the end of the current enumerator. 
 *
 *  The resulting enumerator will behave identical to the receiver until the receiver's last command is enumerated. At that point, future requests for commands will come from the appended enumerator.
 *
 *  @param enumerator Enumerator to be appended to the end of the receiver
 *
 *  @warning While this method does not change the receiver or argument, it does not create a new copies of them either. This means that calls to the result's `nextCommand` method will have the same effect on the two component enumerators because the result enumerator is just encapsulating its two components.
 *
 *  @return A new enumerator constructed by concatenating two enumerators
 */
- (SAYCommandEnumerator *)enumeratorByAppendingEnumerator:(SAYCommandEnumerator *)enumerator;

@end

NS_ASSUME_NONNULL_END
