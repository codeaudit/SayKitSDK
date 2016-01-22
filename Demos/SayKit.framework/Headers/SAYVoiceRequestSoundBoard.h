//
//  SAYVoiceRequestSoundBoard.h
//  SayKit
//
//  Created by Greg Nicholas on 11/23/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYAudioTrack;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYVoiceRequestSoundBoard` is a simple "sound board" class that will play individual sounds on  its set audio track. While it can play arbitrary speech utterances and tones, it has particular settings for customizing the sounds used for microphone activity feedback.
 */
@interface SAYVoiceRequestSoundBoard : NSObject

/**
 *  Track to be used for presenting audio events
 */
@property (nonatomic, strong, nullable) SAYAudioTrack *audioTrack;

/**
 *  Tone to play when the microphone becomes active.
 
    When set to nil, the SayKit default tone will be used.
 */
@property (nonatomic, copy, null_resettable) NSURL *microphoneStartToneURL;

/**
 *  Tone to play when the microphone becomes inactive.
 
    When set to nil, the SayKit default tone will be used.
 */
@property (nonatomic, copy, null_resettable) NSURL *microphoneStopToneURL;

/**
 *  Speaks the given text immediately.
 *
 *  @param promptText Prompt message to speak
 */
- (void)speakPrompt:(NSString *)promptText;

/**
 *  Speaks the given text immediately. Once the speech utterance completes, the given block will be executed.
 *
 *  @param promptText Prompt message to speak
 *  @param completion Action block executed after speech completes
 */
- (void)speakPrompt:(NSString *)promptText then:(void(^)())completion;

/**
 *  Plays the given tone immediately.
 *
 *  @param url URL of sound file to play
 */
- (void)playToneWithURL:(NSURL *)url;

/**
 *  Plays the given tone immediately. Once the tone completes, the given block will be executed.
 *
 *  @param url        URL of sound file to play
 *  @param completion Action block executed after sound playback completes
 */
- (void)playToneWithURL:(NSURL *)url then:(void (^)())completion;

/**
 *  Plays the receiver's preset microphone start tone.
 */
- (void)playMicrophoneStartTone;

/**
 *  Plays the receiver's preset microphone stop tone.
 */
- (void)playMicrophoneStopTone;

@end

NS_ASSUME_NONNULL_END
