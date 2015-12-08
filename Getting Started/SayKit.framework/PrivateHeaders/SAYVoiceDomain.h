//
//  SAYVoiceDomain
//  SayKit
//
//  Created by Adam Larsen on 2015/10/23.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYCommandProcessingTypes.h"

@class SAYCommand;
@class SAYSpeechIntent;
@class SAYVoiceIntentResolver;
@protocol SAYSpeechRecognitionService;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * __nullable (^SAYReviewTextGenerator)(SAYCommand *);

@protocol SAYVoiceDomain <NSObject>

@property (nonatomic, strong, readonly) id<SAYSpeechRecognitionService> service;

+ (NSArray<SAYVoiceIntentResolver *> *)voiceIntentResolvers;

@optional

@property (nonatomic, copy, readonly) NSArray<SAYTextResolverBlock> *rawTextResolvers;
+ (SAYReviewTextGenerator) reviewTextGenerator;

@end

NS_ASSUME_NONNULL_END
