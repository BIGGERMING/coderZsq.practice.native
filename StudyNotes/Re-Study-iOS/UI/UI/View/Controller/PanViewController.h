//
//  PanViewController.h
//  UI
//
//  Created by 朱双泉 on 2018/9/13.
//  Copyright © 2018 Castie!. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PanViewController : UIViewController

@property (nonatomic, weak) UIViewController * mainViewController;
@property (nonatomic, weak) UIViewController * secondaryViewController;
@property (nonatomic, weak) UIViewController * featureViewController;
@property (nonatomic, assign) CGFloat ratio;

- (void)pan;
- (void)unPan;

@end
