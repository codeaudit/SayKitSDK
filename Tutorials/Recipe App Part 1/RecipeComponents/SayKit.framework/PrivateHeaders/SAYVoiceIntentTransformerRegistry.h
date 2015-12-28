//
//  SAYVoiceIntentTransformerRegistry.h
//  SayKit
//
//  Created by Greg Nicholas on 10/27/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYCommandProcessingTypes.h"
#import "SAYCommandResolver.h"

@class SAYSpeechIntent;
@class SAYCommandEnumerator;
@class SAYVoiceIntentResolver;

NS_ASSUME_NONNULL_BEGIN

@interface SAYVoiceIntentTransformerRegistry : NSObject <SAYCommandResolver>

@property (nonatomic, assign) BOOL automaticallyTransformUnhandledIntents;
@property (nonatomic, assign) float confidenceThreshold;

+ (SAYVoiceIntentTransformerRegistry *)builtInRegistry;

- (void)registerVoiceIntentResolver:(SAYVoiceIntentResolver *)resolver;
- (void)unregisterVoiceIntentTransformerForIdentifier:(NSString *)intentIdentifier;

- (NSArray<SAYCommand *> *)resolveCommandsFromVoiceIntents:(NSArray <SAYSpeechIntent *> *)voiceIntents;

@end

NS_ASSUME_NONNULL_END
