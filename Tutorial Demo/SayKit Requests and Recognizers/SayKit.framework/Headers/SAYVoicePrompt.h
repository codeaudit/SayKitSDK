//
//  SAYVoicePrompt.h
//  SayKit
//
//  Created by Greg Nicholas on 12/16/15.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UIViewController;
@class AVSpeechUtterance;
@class SAYVoicePromptViewController;

NS_ASSUME_NONNULL_BEGIN

@interface SAYVoicePrompt : NSObject <NSCopying>

@property (nonatomic, copy, readonly) NSAttributedString *displayMessage;
@property (nonatomic, copy, readonly) AVSpeechUtterance *spokenMessage;

@property (nonatomic, strong, nullable) UIViewController *supplementalViewController;

+ (instancetype)promptWithMessage:(NSString *)message;

- (instancetype)initWithMessage:(NSString *)message;
- (instancetype)initWithDisplayMessage:(NSAttributedString *)displayMessage spokenMessage:(AVSpeechUtterance *)spokenMessage NS_DESIGNATED_INITIALIZER;

/// @abstract Not supported. Use designated initialize for this class instead.
- (instancetype)init NS_UNAVAILABLE;

- (BOOL)isEqualToVoicePrompt:(SAYVoicePrompt *)voicePrompt;

@end

NS_ASSUME_NONNULL_END
