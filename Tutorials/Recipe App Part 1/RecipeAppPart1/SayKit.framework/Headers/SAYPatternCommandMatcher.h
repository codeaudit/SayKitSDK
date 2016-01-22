//
//  SAYPatternCommandTranslator.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SAYTextCommandMatcher.h"

NS_ASSUME_NONNULL_BEGIN

// TODO: add confidence-linked templates?

@interface SAYPatternCommandMatcher : NSObject <SAYTextCommandMatcher>

@property (nonatomic, copy, readonly) NSArray<NSString *> *templates;

- (instancetype)initWithTemplates:(NSArray<NSString *> *)templates;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END