//
//  SAYSoundTrackCoordinator.h
//  SayKit
//
//  Created by Greg Nicholas on 7/1/15.
//  Copyright (c) 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYAudioFocusManagement.h"

@class SAYManagedSynthesizer;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYAudioTrackCoordinator` is the nerve-center for all audio operations. It manages multiple `SAYAudioTrack`s, giving each permission to present their events according to their priority.
 */
@interface SAYAudioTrackCoordinator : NSObject <SAYAudioFocusGuard>

/**
 *  The managed synthesizer controlled by this coordinator. It is available to tracks when audio focus is granted to them.
 */
@property (nonatomic, readonly) SAYManagedSynthesizer * managedSynth;

/**
 *  Returns a system-wide default coordinator available to all SayKit applications.
 *
 *  @return A system-wide default coordinator
 */
+ (SAYAudioTrackCoordinator *)defaultCoordinator;

/**
 *  Initailizes a new coordinator with the given synthesizer
 *
 *  @param managedSynth Managed synthesizer instance to coordinate  multi-agent speech synthesis
 *
 *  @return The newly-initialized `SAYAudioTrackCoordinator`
 */
- (instancetype)initWithManagedSynthesizer:(SAYManagedSynthesizer *)managedSynth NS_DESIGNATED_INITIALIZER;

/// @abstract Use initWithManagedSynthesizer: to initialize.
- (instancetype)init NS_UNAVAILABLE;

/**
 *  Suspends execution on all tracks, regardless of priority.
 */
- (void)suspendTracks;

/**
 *  Resumes execution of tracks, according to standard prioritization rules.
 */
- (void)resumeTracks;

@end

NS_ASSUME_NONNULL_END
