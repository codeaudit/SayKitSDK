//
//  SAYCommandBarPresentationController.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/18.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SAYCommandBar;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Presentation controller used to assist `SAYVoiceRequestViewController` placement for voice command requests.
 */
@interface SAYCommandBarPresentationController : UIPresentationController

/**
 *  Should be set to the height of the command bar
 */
@property (nonatomic) CGFloat commandBarHeight;

@end

NS_ASSUME_NONNULL_END
