//
//  SAYCommandDispatcher.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYCommandEnumerator;
@class SAYCommandDispatch;
@protocol SAYCommandResponder;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYCommandDispatcher` class defines a simple search strategy to match the best command with best responder for the job. It cycles through each commands from the provided CommandEnumerator and for each one, it walks down the responder chain until it finds a responder able to act on the command.
 */
@interface SAYCommandDispatcher : NSObject

/**
 *  Returns a standard system-wide dispatcher available to all SayKit applications
 *
 *  @return The system-wide dispatcher
 */
+ (SAYCommandDispatcher *)systemDispatcher;

/**
 *  The beginning of the responder chain. This instance will have the first chance to respond to a each potential command.
 */
@property (atomic, strong, nullable) id<SAYCommandResponder> firstResponder;

/**
 *  Performs the search for a responder to handle a command from a collection of potential options.
 *
 *  @param commandEnumerator An enumerator that runs through potential commands
 *
 *  @return The result of the search: an instance paired with a responder. If no responder could be found for any command, nil is returned instead.
 */
- (nullable SAYCommandDispatch *)prepareDispatchForCommands:(SAYCommandEnumerator *)commandEnumerator;

@end

NS_ASSUME_NONNULL_END
