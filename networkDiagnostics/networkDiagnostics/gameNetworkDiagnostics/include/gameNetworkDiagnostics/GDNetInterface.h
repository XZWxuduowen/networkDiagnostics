//
//  GDNetInterface.h
//  GDNetDiag
//
//  Created by 许振文 on 2022/6/20.
//

#import <Foundation/Foundation.h>

#import "GDLoginfo.h"
#import "GDNetworkAddress.h"

NS_ASSUME_NONNULL_BEGIN

@class GDNetInterface;

typedef void (^GDNetInterfaceCallBack)(GDNetInterface *obj, BOOL isFinish);

@interface GDNetInterface : NSObject

@property (nonatomic, copy)NSString *toolAddress;
@property (nonatomic, assign)NSUInteger toolPort;
@property (nonatomic, copy)NSString *msg;
@property (nonatomic, copy)NSDictionary *content;
@property (nonatomic, strong)GDLoginfo *log;

#pragma mark - Ping
/*
 * 使用Ping，按命令行信息输出
 * @param hostName 指定域名
 * @param count ping的次数
 * @param content ping的内容，可为空
 * @param handler ping的回调
 */
- (void)pingHost:(NSString *)hostName count:(int)count content:(NSString * _Nullable )content progressHandler:(GDNetInterfaceCallBack)handler;
- (void)stopPing;

#pragma mark - Curl
/*
 * 调用curl解析指定站点
 * @param address 指定站点
 * @param port 指定端口
 * @param handler curl的回调
 */
- (void)curlAddress:(NSString *)address port:(NSUInteger)port progressHandler:(GDNetInterfaceCallBack)handler;
- (void)stopCurl;

#pragma mark - Mtr
/*
 * 调用Mtr解析指定host
 * @param host 指定域名
 * @param handler tracerouter的回调
 */
- (void)mtrHost:(NSString *)host progressHandler:(GDNetInterfaceCallBack)handler;
- (void)stopMtr;

#pragma mark - Telnet
/*
 * 调用Telnet连接指定host
 * @param host 指定host
 * @param port 指定port
 * @param handler connect的回调
 */
- (void)telnetHost:(NSString *)host port:(NSUInteger)port progressHandler:(GDNetInterfaceCallBack)handler;
- (void)stopTelnet;

#pragma mark - Dig
/*
 * 调用Dig解析指定域名
 * @param domain 指定域名
 * @param handler lookup的回调
 */
- (void)digDomain:(NSString *)domain progressHandler:(GDNetInterfaceCallBack)handler;
- (void)stopDig;

@end

NS_ASSUME_NONNULL_END
