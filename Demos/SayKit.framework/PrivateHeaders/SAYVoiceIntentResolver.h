//
//  SAYVoiceIntentResolver.h
//  SayKit
//
//  Created by Greg Nicholas on 10/28/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYCommandProcessingTypes.h"

NS_ASSUME_NONNULL_BEGIN

typedef NSArray <SAYCommand *> * _Nonnull (^SAYSpeechIntentResolverBlock)(SAYSpeechIntent *);

@interface SAYVoiceIntentResolver : NSObject

@property (nonatomic, copy, readonly) NSString *intentIdentifier;
@property (nonatomic, copy, readonly) SAYSpeechIntentResolverBlock resolutionBlock;

- (instancetype)initWithIntentIdentifier:(NSString *)identifier resolutionBlock:(SAYSpeechIntentResolverBlock)block;

@end

NS_ASSUME_NONNULL_END
