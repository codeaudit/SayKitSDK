//
//  SAYVerbalCommandRequestManager.h
//  SayKit
//
//  Created by Greg Nicholas on 11/2/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYVerbalCommandRequest.h"

@protocol SAYTextCommandResolver;
@class SAYCommandDispatcher;
@class SAYVoiceRequestViewController;
@class SAYVerbalCommandRequest;

NS_ASSUME_NONNULL_BEGIN

/**
 *  A `SAYVerbalCommandRequestManager` integrates the various components required by a `SAYVerbalCommandRequest`. It is most commonly used as a centralized source for housing and accessing these components, which often must be manipulated in separate areas of an application.
 
    The manager uses a two-phase command resolution process, first consulting a built-in resolver that looks for a fixed set of SayKit library commands, then consulting custom logic provided by the `customCommandResolver`.
 */
@interface SAYVerbalCommandRequestManager : NSObject

/**
 *  A special `SAYCommandResolver` instance capable of resolving raw text into potential commands.
 *
 *  Its default value is an empty `SAYTextResolutionRegistry` instance, but it can be set to any conforming type.
 */
@property (nonatomic, strong) id<SAYTextCommandResolver> customCommandResolver;

/**
 *  An instance which will attempt to dispatch resolved commands
 */
@property (nonatomic, strong) SAYCommandDispatcher *commandDispatcher;

/**
 *  Returns the system-wide default manager. Most applications will have no need for a different instance.
 *
 *  @return The system-wide default manager
 */
+ (SAYVerbalCommandRequestManager *)defaultManager;

/**
 *  Initializes a request manager with the given resolver and dispatcher agents
 *
 *  @param textResolver Command resolver to process text
 *  @param dispatcher   Command dispatcher
 *
 *  @return The newly-initialized request manager.
 */
- (instancetype)initWithTextResolver:(id<SAYTextCommandResolver>)textResolver dispatcher:(SAYCommandDispatcher *)dispatcher NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/**
 *  Spawns a new request using the receiver's command pipeline configuration
 *
 *  @return A new request
 */
- (SAYVerbalCommandRequest *)newRequest;

@end

NS_ASSUME_NONNULL_END
