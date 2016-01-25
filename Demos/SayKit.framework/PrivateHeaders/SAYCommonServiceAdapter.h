//
//  SAYCommonServiceAdapter.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/12.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYSpeechRecognitionService.h"
#import "Wit.h"

NS_ASSUME_NONNULL_BEGIN

@interface SAYCommonServiceAdapter : NSObject <SAYSpeechRecognitionService, WitDelegate>

@property (nonatomic, weak, nullable) id<SAYSpeechRecognitionServiceDelegate> delegate;
@property (atomic, assign) float audioLevel;

+ (SAYCommonServiceAdapter *)sharedBuiltinInstance;
+ (SAYCommonServiceAdapter *)sharedConfirmationInstance;
+ (SAYCommonServiceAdapter *)sharedNumberInstance;
+ (SAYCommonServiceAdapter *)sharedSelectInstance;
+ (SAYCommonServiceAdapter *)sharedRecognitionOnlyInstance;

- (instancetype)initWithSpeechRecognitionAccessToken:(NSString *)witAccessToken
                 withIntentRecognitionServiceAppIDs:(NSArray<NSString *> *)luisAppIDs
        withIntentRecognitionServiceSubscriptionKey:(NSString *)luisSubscriptionKey;

@end

FOUNDATION_EXPORT NSString * const SAYWitErrorDomain;

FOUNDATION_EXPORT NSString * const SAYWitErrorLabelKey;
FOUNDATION_EXPORT NSString * const SAYWitErrorLabelNoAuth;
FOUNDATION_EXPORT NSString * const SAYWitErrorLabelAuth;
FOUNDATION_EXPORT NSString * const SAYWitErrorLabelTimeout;
FOUNDATION_EXPORT NSString * const SAYWitErrorLabelSpeechRec;

FOUNDATION_EXPORT NSString * const SAYWitErrorDescriptionNoOutcome;

NS_ASSUME_NONNULL_END
