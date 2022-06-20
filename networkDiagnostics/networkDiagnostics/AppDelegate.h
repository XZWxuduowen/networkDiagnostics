//
//  AppDelegate.h
//  networkDiagnostics
//
//  Created by 许振文 on 2022/6/20.
//

#import <UIKit/UIKit.h>

#import "Reachability.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow * window;

// 当前网络状态检测对象
@property (strong, nonatomic) Reachability *networkReachability;
// 当前网络状态
@property (assign, nonatomic) NetworkStatus networkStatus;

@end

