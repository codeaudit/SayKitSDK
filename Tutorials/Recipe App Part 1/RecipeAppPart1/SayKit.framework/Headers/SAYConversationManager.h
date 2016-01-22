//
//  SAYConversationManager.h
//  SayKit
//
//  Created by Greg Nicholas on 1/12/16.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYAudioEventListener.h"

@protocol SAYVerbalCommandRegistry;
@protocol SAYAudioEventSource;

@class SAYAudioTrackCoordinator;

NS_ASSUME_NONNULL_BEGIN

@interface SAYConversationManager : NSObject <SAYAudioEventListener>

@property (nonatomic, strong, nonnull) SAYAudioTrackCoordinator *trackCoordinator;

@property (nonatomic, strong, nullable) id<SAYVerbalCommandRegistry> commandRegistry;

// comes with a pre-built track
+ (SAYConversationManager *)systemManager;

- (instancetype)initWithTrackCoordinator:(SAYAudioTrackCoordinator *)trackCoordinator;

- (void)addAudioSource:(id<SAYAudioEventSource>)source forTrack:(NSString *)trackIdentifier;
- (void)removeAudioSource:(id<SAYAudioEventSource>)source;

@end

FOUNDATION_EXPORT NSString * const SAYAudioTrackMainIdentifier;
FOUNDATION_EXPORT const unsigned int SAYAudioTrackMainPriority;

NS_ASSUME_NONNULL_END
