//
//  WitResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYSpeechIntent;

@interface WitResult : NSObject

@property (nonatomic, copy, readonly) NSString *transcription;
@property (nonatomic, copy, readonly) NSArray<SAYSpeechIntent *> *intents;

- (instancetype)initWithTranscription:(NSString *)transcription andIntents:(NSArray<SAYSpeechIntent *> *)intents;

@end
