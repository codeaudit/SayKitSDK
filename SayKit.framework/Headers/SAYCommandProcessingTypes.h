//
//  SAYCommandProcessingTypes.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYCommand;
@class SAYSpeechIntent;

NS_ASSUME_NONNULL_BEGIN

/// Type describing a function that maps a string to a collection of commands
typedef NSArray <SAYCommand *> * _Nonnull (^SAYTextResolverBlock)(NSString *);

/// General type describing a function that is able to process a command
typedef void (^SAYCommandResponseBlock)(SAYCommand *);

/// Type describing functions that map a command to a Boolean. Used by `SAYCommandResponder` classes as a way to validate it can handle a given command.
typedef BOOL (^SAYCommandValidationBlock)(SAYCommand *);

NS_ASSUME_NONNULL_END
