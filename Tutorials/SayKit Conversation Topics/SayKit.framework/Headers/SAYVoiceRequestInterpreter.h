//
//  SAYVoiceRequestInterpreter.h
//  SayKit
//
//  Created by Greg Nicholas on 12/16/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SAYSpeechRecognitionResult;
@protocol SAYVoiceRequest;
@class SAYInterpretation;

NS_ASSUME_NONNULL_BEGIN

@protocol SAYVoiceRequestInterpreter <NSObject>

- (void)voiceRequest:(id<SAYVoiceRequest>)voiceRequest interpretResult:(id<SAYSpeechRecognitionResult>)result completion:(void (^)(SAYInterpretation *))completion;

@end

NS_ASSUME_NONNULL_END
