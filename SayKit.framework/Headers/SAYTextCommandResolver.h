//
//  SAYTextCommandResolver.h
//  SayKit
//
//  Created by Greg Nicholas on 11/2/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYCommandResolver.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  `SAYTextCommandResolver` is a specialization of the `SAYCommandResolver` protocol, providing functionality specific to resolving text.
 */
@protocol SAYTextCommandResolver <SAYCommandResolver>

/**
 *  Resolves the provided text into an enumeration of commands. If no potential commands are can be resolved, the enumeration can be empty.
 *
 *  @param text Text containing command content
 *
 *  @return An enumeration of resolved commands. These results should be sorted so the most likely commands are enumerated first.
 */
- (SAYCommandEnumerator *)resolveCommandsFromText:(NSString *)text;

@end

NS_ASSUME_NONNULL_END
