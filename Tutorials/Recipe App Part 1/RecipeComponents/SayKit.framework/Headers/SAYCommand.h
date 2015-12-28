//
//  SAYCommand.h
//  SayKit
//
//  Created by Greg Nicholas on 7/29/15.
//  Copyright (c) 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  The `SAYCommand` class lays out a general representation for commands in the SayKit command processing pipeline.
 */
@interface SAYCommand : NSObject

/**
 *  The command type. This is the primary value used for identifying a command's purpose.
 */
@property (nonatomic, copy, readonly, nonnull) NSString *type;

/**
 *  Additional parameters associated with the command.
 */
@property (nonatomic, copy, readonly, nonnull) NSDictionary *parameters;

/**
 *  Confidence (between 0.0 and 1.0) assigned to the command by an external service or local resolver.
 */
@property (nonatomic, readonly) float confidence;

/**
 *  Factory initializer for commands with no parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *
 *  @return A newly-initialized `SAYCommand`
 */
+ (SAYCommand * __nonnull)commandWithType:(NSString * __nonnull)type;

/**
 *  Factory initializer for commands with parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *  @param parameters Values associated with this particular command
 *
 *  @return A newly-initialized `SAYCommand`
 */
+ (SAYCommand * __nonnull)commandWithType:(NSString * __nonnull)type parameters:(NSDictionary * __nonnull)parameters;

/**
 *  Factory initializer for commands with parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *  @param parameters Values associated with this particular command
 *  @param confidence Measurement of likelihood that this command was interpreted successfully
 *
 *  @return A newly-initialized `SAYCommand`
 */
+ (SAYCommand * __nonnull)commandWithType:(NSString * __nonnull)type parameters:(NSDictionary * __nonnull)parameters confidence:(float)confidence;

/**
 *  Initialize a command with the given type and parameters. An empty dictionary should be provided for commands without parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *  @param parameters Values associated with this particular command
 *  @param confidence Measurement of likelihood that this command was interpreted successfully
 *
 *  @return The newly-initialized command
 */
- (nonnull instancetype)initWithType:(NSString * __nonnull)type parameters:(NSDictionary * __nonnull)parameters confidence:(float)confidence NS_DESIGNATED_INITIALIZER;

/**
 *  Initialize a command with the given type and parameters. An empty dictionary should be provided for commands without parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *  @param parameters Values associated with this particular command
 *
 *  @return The newly-initialized command
 */
- (nonnull instancetype)initWithType:(NSString * __nonnull)type parameters:(NSDictionary * __nonnull)parameters;

/**
 *  Convenience initializer for commands with no parameters.
 *
 *  @param type Identifier that uniquely defines this type of command
 *
 *  @return The newly-initialized command
 */
- (nonnull instancetype)initWithType:(NSString * __nonnull)type;

/// @abstract Use initWithType: to initialize.
- (nonnull instancetype)init NS_UNAVAILABLE;

@end
