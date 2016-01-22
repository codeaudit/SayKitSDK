//
//  SAYVoiceRequestResponder.h
//  SayKit
//
//  Created by Greg Nicholas on 11/23/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYVoiceRequest;

NS_ASSUME_NONNULL_BEGIN

/**
 *  The `SAYVoiceRequestResponder` protocol standardizes the interface for classes that can handle recognized speech.
 */
@protocol SAYVoiceRequestResponder <NSObject>

/**
 *  Handle the response (or error) from the a speech recognition service. Exactly one of the `responseData` or `error` is guaranteed to be non-nil. The data type of the `responseData` argument depends on the recognition service used by associated request object.
 *
 *  Due to this close interaction with the lifecycle and its request-specific logic, a `VoiceRequestResponder` conformer is typically bound tightly to the type of VoiceRequest it serves.
 *
 *  @warning If a request cycle ends with this message, it is the receiver's duty to end the request’s lifecycle as part of its response to this message.
 *
 *  @param voiceRequest Request that received data/error
 *  @param responseData Response data (type depends on underlying `SAYSpeechRecognitionService`). Will be nil if error occurs.
 *  @param error        If non-nil, error describing why a recognition response could not be received
 */
- (void)voiceRequest:(SAYVoiceRequest *)voiceRequest receivedData:(nullable id)responseData error:(nullable NSError *)error;

/**
 *  Handle the cancellation process of the request. This is typically triggered by the user manually canceling the request via the GUI.
 *
 *  @warning The method is responsible for triggering the actual dismissal of the request. Allowing the request's lifecycle to continue after this method is not expected behavior.
 *
 *  @param voiceRequest Request that was cancelled
 */
- (void)voiceRequestWasCancelled:(SAYVoiceRequest *)voiceRequest;

@end

NS_ASSUME_NONNULL_END
