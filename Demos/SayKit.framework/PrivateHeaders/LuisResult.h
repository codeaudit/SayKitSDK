//
//  LuisResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/16.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SAYSpeechIntent;

NS_ASSUME_NONNULL_BEGIN

@interface LuisResult : NSObject

@property (nonatomic, copy, readonly) NSString *transcription;
@property (nonatomic, copy, readonly) NSArray<SAYSpeechIntent *> *intents;
@property (nonatomic, copy, readonly) NSDictionary *entities;

- (instancetype)initWithTranscription:(NSString *)transcription withIntents:(NSArray<SAYSpeechIntent *> *)intents withEntities:(NSDictionary *)entities;

- (LuisResult * __nullable)mergeWithResult:(LuisResult * __nullable)other error:(NSError * __autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
