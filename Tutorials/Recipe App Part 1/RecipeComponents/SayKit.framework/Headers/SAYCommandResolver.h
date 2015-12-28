//
//  SAYCommandResolver.h
//  SayKit
//
//  Created by Greg Nicholas on 11/2/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYCommandEnumerator;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYCommandResolver` protocol describes types that are able to interpret arbitrary data, turning it an collection of potential commands. For more specific types of input data, a more specific version of the protocol may be appropriate (see `SAYTextCommandResolver`).
 */
@protocol SAYCommandResolver <NSObject>

/**
 *  Resolves the given data into an enumeration of commands. If no potential commands are can be resolved, the enumeration can be empty.
 *
 *  @param data Information containing potential commands
 *
 *  @return An enumeration of resolved commands. These results should be sorted so the most likely commands are enumerated first.
 */
- (void)resolveCommandsFromData:(id)data completion:(void (^)(SAYCommandEnumerator *))completion;

@end

NS_ASSUME_NONNULL_END
