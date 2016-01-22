//
//  SAYVoiceRequestCommonResponder.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/30.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceRequestResponder.h"

NS_ASSUME_NONNULL_BEGIN

@interface SAYVoiceRequestCommonResponder : NSObject <SAYVoiceRequestResponder>

- (void)handleSpeechRecognitionError:(NSError *)error voiceRequest:(SAYVoiceRequest *)voiceRequest;
- (void)handleIntentRecognitionError:(NSError *)error voiceRequest:(SAYVoiceRequest *)voiceRequest;
- (void)handleWitError:(NSError *)error voiceRequest:(SAYVoiceRequest *)voiceRequest;
- (void)handleConnectionError:(NSError *)error voiceRequest:(SAYVoiceRequest *)voiceRequest;
- (void)handleUnknownError:(NSError *)error voiceRequest:(SAYVoiceRequest *)voiceRequest;

- (void)voiceRequest:(SAYVoiceRequest *)voiceRequest receivedData:(nullable id)responseData error:(nullable NSError *)error;
- (void)voiceRequest:(SAYVoiceRequest *)voiceRequest receivedError:(NSError *)error;
- (void)dismissRequest:(SAYVoiceRequest *)voiceRequest completion:(void (^ __nullable)(void))completion;

// The following methods should be overwritten by a subclass.
- (void)voiceRequest:(SAYVoiceRequest *)voiceRequest receivedData:(id)responseData;
- (void)presentErrorMessage:(NSString *)errorMessage
            underlyingError:(NSError *)error
               voiceRequest:(SAYVoiceRequest *)voiceRequest
         shouldAbortRequest:(BOOL)shouldAbortRequest;

@end

NS_ASSUME_NONNULL_END
