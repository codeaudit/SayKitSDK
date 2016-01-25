//
//  WitServiceAdapter.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/14.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYSpeechRecognitionService.h"
#import "Wit.h"

@class WitResult;

NS_ASSUME_NONNULL_BEGIN

@interface WitServiceAdapter : NSObject <SAYSpeechRecognitionService, WitDelegate>

@property (nonatomic, weak, nullable) id<SAYSpeechRecognitionServiceDelegate> delegate;

@property (atomic, assign) float audioLevel;

- (instancetype)initWithAccessToken:(NSString *)accessToken;
- (void)setContextIdentifiers:(NSArray<NSString *> *)identifiers;

+ (WitResult * _Nullable)parseResult:(NSDictionary *)json error:(NSError * __autoreleasing *)error;

@end

FOUNDATION_EXPORT NSString * const kRecognizerContextKeyState;

NS_ASSUME_NONNULL_END
