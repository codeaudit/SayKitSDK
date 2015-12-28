//
//  SAYIntentRecognitionResolver.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYTextResolver.h"

@class SAYCommonServiceAdapter;

NS_ASSUME_NONNULL_BEGIN

@interface SAYIntentRecognitionResolver : NSObject <SAYTextResolver>

@property (nonatomic, copy, readonly) SAYTextResolverBlock resolverBlock;

@property (nonatomic, copy, readonly) NSString *intentId;
@property (nonatomic, copy, readonly) SAYCommonServiceAdapter *service;     // TODO - Generalize to SAYSpeechRecognitionService

- (instancetype)initWithIntentId:(NSString *)intentId;

@end

NS_ASSUME_NONNULL_END
