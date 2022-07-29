//
//  AppDelegate.m
//  networkDiagnostics
//
//  Created by 许振文 on 2022/6/20.
//

#import "GDNetInterface.h"
#import "ViewController.h"
#import "AppDelegate.h"

@interface AppDelegate (){
    NSMutableArray *_testArr;
}

@end

@implementation AppDelegate

#pragma mark - The life cycle
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.rootViewController = [[ViewController alloc] init];
    [self.window makeKeyAndVisible];
    
    [self addNotification];
    [self handleReachability];
    
    NSLog(@"本工具会根据网络状态的变化，通过Ping、Telnet、Mtr、Dig、Curl实时更新网络信息。");
    return YES;
}

#pragma mark - Lazy
- (Reachability *)networkReachability {
    if (!_networkReachability) {
        _networkReachability = [Reachability reachabilityForInternetConnection];
    }
    return _networkReachability;
}

#pragma mark - setter - getter
- (NetworkStatus)networkStatus{
    return [self.networkReachability currentReachabilityStatus];
}

#pragma mark - Function
- (void)addNotification{
    // 网络状态变化的监听
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:kReachabilityChangedNotification object:nil];
}

- (void)handleReachability{
    [self.networkReachability startNotifier];
    [AppDelegate handleReachability:nil];
}

+ (void)handleReachability:(Reachability *)reach {
    AppDelegate *app = (AppDelegate *)[UIApplication sharedApplication].delegate;
    // 适配其它入口的Reachability
    if ([reach isKindOfClass:[Reachability class]]) {
        app.networkReachability = reach;
    }
    //
    NetworkStatus netStatus = app.networkStatus;
    switch(netStatus) {
        case NotReachable: {
            NSLog(@"没有网络...");
            break;
        }
        case ReachableViaWiFi: {
            NSLog(@"wifi网络...");
            break;
        }
        case ReachableViaWWAN: {
            NSLog(@"sim运营商网络...");
            break;
        }
    }
    [AppDelegate demoForDeveloper:netStatus];
}
+ (void)demoForDeveloper:(NetworkStatus)netStatus{
    AppDelegate *app = (AppDelegate *)[UIApplication sharedApplication].delegate;
    if (app->_testArr == nil) {
        app->_testArr = [[NSMutableArray alloc] init];
    }
    [app->_testArr removeAllObjects];
    GDLoginfo *log = [[GDLoginfo alloc] init];
    // 开始打印
    [log recordStepInfo:@"网络信息一键诊断"];
    [log recordStepInfo:[NSString stringWithFormat:@"当前本机IP: %@",[GDNetworkAddress deviceIPAddress]]];
    if (netStatus == NotReachable) {
        [log recordStepInfo:@"当前是否联网: 未联网"];
        NSLog(@"%@",[log printLoginfo]);
    }else {
        [log recordStepInfo:@"当前是否联网: 已联网"];
        NSString *tmpNetworkType = @"wifi网络";
        if (netStatus == ReachableViaWWAN) {
            tmpNetworkType = @"运营商网络";
        }
        [log recordStepInfo:[NSString stringWithFormat:@"当前联网类型: %@",tmpNetworkType]];
        
        // 本地设备网络信息获取
        if (netStatus == ReachableViaWiFi) {
            [log recordStepInfo:[NSString stringWithFormat:@"本地网关: %@",[GDNetworkAddress getGatewayIPAddress]]];
        }
        [log recordStepInfo:[NSString stringWithFormat:@"本地DNS: %@",[[GDNetworkAddress deviceServerDNS] componentsJoinedByString:@", "]]];
        
        NSString *domain = @"www.baidu.com";//@"180.101.49.42";//@"14.215.177.38";//@"originmood.com";//@"www.gamedreamer.com";//@"www.baidu.com";
        [log recordStepInfo:[NSString stringWithFormat:@"\n网络分析的远端域名: %@", domain]];
        // host地址IP列表
        long time_start = [GDNetworkAddress getMicroSeconds];
        NSArray *ipAddress = [NSArray arrayWithArray:[GDNetworkAddress getDNSWithDomain:domain]];
        long time_duration = [GDNetworkAddress computeDurationSince:time_start] / 1000;
        if (ipAddress.count == 0) {
            [log recordStepInfo:[NSString stringWithFormat:@"DNS解析结果: 解析失败"]];
        } else {
            [log
             recordStepInfo:[NSString stringWithFormat:@"DNS解析结果: %@ (%ldms)",
                             [ipAddress componentsJoinedByString:@", "],
                             time_duration]];
        }
        //TCP链接
        [log recordStepInfo:@"\n\n开始Telnet"];
        if (ipAddress.count == 0) {
            [log recordStepInfo:[NSString stringWithFormat:@"DNS解析失败: 主机地址不可达"]];
        } else {
            int tmpPort = 80; // 以知baidu的80端口是可通
            NSString *ip = [NSString stringWithFormat:@"%@",ipAddress.firstObject];
            GDNetInterface *telnet = [[GDNetInterface alloc] init];
            [app->_testArr addObject:telnet];
            [telnet telnetHost:ip port:tmpPort progressHandler:^(GDNetInterface * _Nonnull obj, BOOL isFinish) {
                if (isFinish) {
                    [log recordStepInfo:[obj.log printLoginfo]];
                    [log recordStepInfo:@"\n开始Ping"];
                    GDNetInterface *ping = [[GDNetInterface alloc] init];
                    [app->_testArr addObject:ping];
                    [ping pingHost:domain count:4 content:nil progressHandler:^(GDNetInterface *obj1, BOOL isFinish1) {
                        [log recordStepInfo:obj1.msg];
                        if (isFinish1) {
                            [log recordStepInfo:@"\n开始Mtr"];
                            GDNetInterface *mtr = [[GDNetInterface alloc] init];
                            [app->_testArr addObject:mtr];
                            [mtr mtrHost:domain needShowRemoteInfo:false progressHandler:^(GDNetInterface *obj2, BOOL isFinish2) {
                                [log recordStepInfo:obj2.msg];
                                if (isFinish2) {
                                    [log recordStepInfo:@"Mtr: end\n\n\n开始Dig"];
                                    GDNetInterface *dig = [[GDNetInterface alloc] init];
                                    [app->_testArr addObject:dig];
                                    [dig digDomain:domain progressHandler:^(GDNetInterface *obj3, BOOL isFinish3) {
                                        [log recordStepInfo:obj3.msg];
                                        if (isFinish3) {
                                            [log recordStepInfo:@"Dig: end\n\n\n开始Curl"];
                                            GDNetInterface *curl = [[GDNetInterface alloc] init];
                                            [app->_testArr addObject:curl];
                                            [curl curlAddress:@"https://www.baidu.com" port:443 progressHandler:^(GDNetInterface * _Nonnull obj4, BOOL isFinish4) {
                                                [log recordStepInfo:obj4.msg];
                                                if (isFinish4) {
                                                    [log recordStepInfo:@"\nCurl: end\n"];
                                                    NSLog(@"%@",[log printLoginfo]);
                                                }
                                            }];
                                        }
                                    }];
                                }
                            }];
                        }
                    }];
                }
            }];
        }
    }
}

#pragma mark - Notification
- (void)reachabilityChanged:(NSNotification *)sender {
    if ([[sender object] isKindOfClass:[Reachability class]]) {
        Reachability *reach = [sender object];
        [AppDelegate handleReachability:reach];
    }
}
- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(nullable UIWindow *)window {
    return UIInterfaceOrientationMaskPortrait;
}

@end
