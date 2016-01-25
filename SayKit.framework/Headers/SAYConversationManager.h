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
@protocol SAYVoiceRequest;
@class SAYAudioTrackCoordinator;
@class SAYVoiceRequestPresenter;
@class UIWindow;
@class UIViewController;

NS_ASSUME_NONNULL_BEGIN

@interface SAYConversationManager : NSObject <SAYAudioEventListener>

@property (nonatomic, strong, readonly, nonnull) SAYAudioTrackCoordinator *trackCoordinator;
@property (nonatomic, strong, readonly, nonnull) UIWindow *window;

@property (nonatomic, strong, readonly, nonnull) SAYVoiceRequestPresenter *voiceRequestPresenter;

@property (nonatomic, strong, nullable) id<SAYVerbalCommandRegistry> commandRegistry;

// comes with a pre-built track
+ (SAYConversationManager *)systemManager;

- (instancetype)initWithTrackCoordinator:(SAYAudioTrackCoordinator *)trackCoordinator window:(UIWindow *)window;

- (void)addAudioSource:(id<SAYAudioEventSource>)source forTrack:(NSString *)trackIdentifier;
- (void)removeAudioSource:(id<SAYAudioEventSource>)source;

- (void)presentVoiceRequest:(id<SAYVoiceRequest>)voiceRequest;
- (void)presentVoiceRequest:(id<SAYVoiceRequest>)voiceRequest fromViewController:(UIViewController *)viewController;

@end

FOUNDATION_EXPORT NSString * const SAYAudioTrackMainIdentifier;
FOUNDATION_EXPORT const unsigned int SAYAudioTrackMainPriority;

FOUNDATION_EXPORT NSString * const SAYAudioTrackVoiceRequestIdentifier;
FOUNDATION_EXPORT const unsigned int SAYAudioTrackVoiceRequestPriority;


NS_ASSUME_NONNULL_END
