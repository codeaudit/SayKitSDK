//
//  SAYTextResolutionRegistry.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYCommandProcessingTypes.h"
#import "SAYTextCommandResolver.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYTextResolutionRegistry` is a simple implementation of a `SAYTextCommandResolver`, acting as a flat registry of functions capable of interpretting raw text.
 */
@interface SAYTextResolutionRegistry : NSObject <SAYTextCommandResolver>

/**
 *  Registers a text resolution block with the registry.
 *
 *  When resolving, these blocks are processed in a linear order matching the order of registration. This means that the resulting enumeration of potential commands will be sorted according to the order their corresponding source resolver blocks are registered.
 *
 *  @param block Function capable of transforming text to potential commands
 */
- (void)registerTextResolver:(SAYTextResolverBlock)block;

/**
 *  Registers a text resolution block associated with a tag. This tag gives a handle for allowing the deregistration of the block in the future.
 *
 *  @param block Function capable of transforming text to potential commands
 *  @param tag String to associate with the block
 */
- (void)registerTextResolver:(SAYTextResolverBlock)block withTag:(NSString *)tag;

/**
 *  Removes the block from the registry asosciated with the given tag. A block must have been initially registered with `registerTextResolver:withTag:` to use this method.
 *
 *  @param tag String associated with the block
 */
- (void)deregisterTextResolverWithTag:(NSString *)tag;

/**
 *  Removes all blocks from the registry
 */
- (void)deregisterAll;

@end

NS_ASSUME_NONNULL_END
