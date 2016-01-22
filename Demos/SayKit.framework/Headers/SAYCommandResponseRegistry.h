//
//  SAYCommandResponseRegistry.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYCommandProcessingTypes.h"
#import "SAYCommandResponder.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYCommandResponseRegistry` provides a simple interpretation of the `SAYCommandResponder` protocol. It collects block functions that are able to respond to prescribed command types. When asked to respond to a particular command instance, it looks for a block registered to handle the command's type, and executes the block if one is found.
 */
@interface SAYCommandResponseRegistry : NSObject <SAYCommandResponder>

/**
 *  Returns a shared registry guaranteed to exist in each SayKit application.
 *
 *  @return The shared registry instance
 */
+ (SAYCommandResponseRegistry *)sharedInstance;

/**
 *  Registers the block with the registry for the provided command type only. Note that only one block can be registered for a particualr command type, so this method has the potential of overwriting an existing registration.
 *
 *  @param type Command type
 *  @param block Function to respond to commands matching the provided type
 */
- (void)addResponseForCommandType:(NSString *)type responseBlock:(SAYCommandResponseBlock)block;

/**
 *  Registers a validation block with the registry.
 *
 *  Validators are often used to verify the parameters of a command are of a proper format. If the parameters do not provide enough context to respond to the command, a validator allows the registry to respond correctly to `canRespondToCommand:` inquiries made on it.
 *
 *  For example, if the registry has a registered block capable of acting on a "Call" command (representing a request to begin phone call), the block may only be able to respond if a "phoneNumber" parameters is provided with the command. If that is the case, a validator function can do this check up-front, allowing the registry to correctly inform callers that it is not able to handle these ill-formed commands.
 *
 *  @param type Command type
 *  @param block Function capable of determining whether or not the given command can be responded to
 */
- (void)addValidatorForCommandType:(NSString *)type validator:(SAYCommandValidationBlock)block;

/**
 *  Unregister the block associated with the given command type.
 *
 *  @param type Command type
 */
- (void)removeResponseForCommandType:(NSString *)type;

@end

NS_ASSUME_NONNULL_END
