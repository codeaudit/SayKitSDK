//
//  SAYSpeechRecognitionService.h
//  SayKit
//
//  Created by Greg Nicholas on 7/28/15.
//  Copyright (c) 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SAYSpeechRecognitionServiceDelegate;
@protocol SAYSpeechRecognitionServiceObserver;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYSpeechRecognitionService` protocol provides a standard for communicating with (typically off-device) speech recognition services. Classes conforming to this protocol must also guarantee to call their delegate's `SAYSpeechRecognitionServiceDelegate` methods where appropriate.
 */
@protocol SAYSpeechRecognitionService <NSObject>

/**
 *  A delegate instance to receive updates and responses from the recognition process.
 */
@property (nonatomic, weak, nullable) id<SAYSpeechRecognitionServiceDelegate> delegate;

/**
 * Starts a new recording session.
 */
- (void)start;

/**
 Stops the current recording session, if any, which should signal the backing recognizer to return a response as soon as possible.
 
 Recording sessions can also stop on their own (for example, if the service detects a pause in speech).
 */
- (void)stop;

/**
 *  Whether or not a recording session is active. This value should still be YES in the interim between the end of recording and a `SAYSpeechRecognitionServiceDelegate` response call.
 */
@property (atomic, readonly) BOOL isRecording;

/**
 *  Last measured audio level of the input audio source.
 */
@property (readonly) float audioLevel;

@end

/**
 *  The `SAYSpeechRecognitionServiceDelegate` protocol describes a set of response messages a `SAYSpeechRecognitionService` should send when recognition events occur.
 */
@protocol SAYSpeechRecognitionServiceDelegate <NSObject>

/**
 *  Sent periodically during a recording session with the current audio level
 *
 *  @param recognitionService   Service managing microphone
 *  @param newLevel             Raw decibel level of microphone input
 */
- (void)recognitionService:(id<SAYSpeechRecognitionService>)recognitionService didReceiveAudioLevelUpdate:(float)newLevel;

/**
 *  Sent when the microphone has been first activated at the beginning of a recording session.
 *
 *  @param recognitionService Service that has begun recording audio
 */
- (void)recognitionServiceDidStartRecording:(id<SAYSpeechRecognitionService>)recognitionService;

/**
 *  Sent when the microphone has deactivated at the end of a recording session.
 *
 *  @param recognitionService Service that has stopped recording audio
 */
- (void)recognitionServiceDidStopRecording:(id<SAYSpeechRecognitionService>)recognitionService;

/**
 *  Sent after an audio signal has been successfully recognized.
 *
 *  The protocol does not specify the data type of this result: it can be customized as appropriate for the underlying service. For example, a simple `NSString` can suffice for simple implementations, but more robust recognizers may be able to return an array of `SAYSpeechTranscript` instances, which pair numerical confidence values along with strings.
 *
 *  @param recognitionService   Service that has completed recognition
 *  @param result               Speech recognition result
 */
- (void)recognitionService:(id<SAYSpeechRecognitionService>)recognitionService didReceiveResult:(id)result;

/**
 *  Sent after a problem has occurred with the recognition process and no result recognition is possible.
 *
 *  @param recognitionService   Service that has completed recognition
 *  @param error                Error that prevented speech recognition
 */
- (void)recognitionService:(id<SAYSpeechRecognitionService>)recognitionService didReceiveError:(NSError *)error;

/**
 *  Some services provide preliminary text recognition results while the request is in process. This his preliminary text is sent to delegates via this method.
 *
 *  @param recognitionService   Service that recevied partial transcript
 *  @param text                 Raw string transcript contents
 */
- (void)recognitionService:(id<SAYSpeechRecognitionService>)recognitionService didReceivePartialTranscriptText:(NSString *)text;

@end

NS_ASSUME_NONNULL_END
