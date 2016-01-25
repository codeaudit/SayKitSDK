//
//  SAYCommandResponder.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SAYCommand;

/**
 *  The `SAYCommandResponder` protocol provides methods for agents that are able to respond to specific commands. In addition, it supports the concept of a "responder chain" by allowing the conformer to provide another instance capable of responding.
 */
@protocol SAYCommandResponder <NSObject>

/**
 *  Evaulates the given command and responds with whether of not the receiver is able to respond to it.
 *
 *  @param command A `SAYCommand` instance
 *
 *  @return YES if the receiver is able to respond to the command, NO otherwise.
 */
- (BOOL)canRespondToCommand:(SAYCommand *)command;

/**
 *  Performs whatever action is necessary to respond to the given command
 *
 *  @param command A `SAYCommand` instance
 */
- (void)respondToCommand:(SAYCommand *)command;

/**
 *  Returns the next responder in the chain.
 *
 *  @return The next responder in the chain, if one exists; nil otherwise.
 */
- (nullable id<SAYCommandResponder>)nextResponder;

@end

NS_ASSUME_NONNULL_END
