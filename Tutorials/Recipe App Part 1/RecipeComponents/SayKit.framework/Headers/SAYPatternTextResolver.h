//
//  SAYPatternTextResolver.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SAYTextResolver.h"

NS_ASSUME_NONNULL_BEGIN

@interface SAYPatternTextResolver : NSObject <SAYTextResolver>

@property (nonatomic, copy, readonly) SAYTextResolverBlock resolverBlock;

- (instancetype)initWithTemplates:(NSArray<NSString *> *)templates forCommandType:(NSString *)commandType;

@end

NS_ASSUME_NONNULL_END
