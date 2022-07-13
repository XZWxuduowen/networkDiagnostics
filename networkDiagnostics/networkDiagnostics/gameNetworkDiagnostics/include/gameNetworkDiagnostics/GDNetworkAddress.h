//
//  GDNetworkAddress.h
//  GDNetDiag
//
//  Created by 许振文 on 2022/5/31.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface GDNetworkAddress : NSObject

#pragma mark - current device info
/*!
 * 获取当前设备型号
 */
+ (NSString *)deviceModel;

/*!
 * 获取当前设备系统版本
 */
+ (NSString *)deviceSystemVersion;

#pragma mark - current device ip address
/*!
 * 获取当前设备ip地址
 */
+ (NSString *)deviceIPAddress;

#pragma mark - current device server DNS
/*!
 * 获取当前网络DNS服务器地址
 */
+ (NSArray *)deviceServerDNS;

#pragma mark - get DNS from domain
/*!
 * 通过domain获取ip列表 DNS解析地址
 */
+ (NSArray *)getDNSWithDomain:(NSString *)domain;

#pragma mark - current device gateway address
/*!
 * 获取当前设备网关地址
 */
+ (NSString *)getGatewayIPAddress;

#pragma mark - time
/**
 * Retourne un timestamp en microsecondes.
 */
+ (long)getMicroSeconds;

/**
 * Calcule une durée en millisecondes par rapport au timestamp passé en paramètre.
 */
+ (long)computeDurationSince:(long)uTime;

/**
 * Calculate timestamp. %Y年%m月%d日%H时%M分%S秒
 * The technique below is faster than using NSDateFormatter.
 */
+ (NSString *)getCTimeFormatterWithTimestamp:(NSTimeInterval)timestamp;

#pragma mark - port
/**
 * 根据地址分析端口号
 * 支持 https://www.baidu.com:443 的端口分析
 */
+ (NSDictionary *)comparePortAndDomain:(NSString *)content;

#pragma mark - valid
/**
 * 域名正则检测
 */
+ (BOOL)validDomain:(NSString *)domain;

/**
 * ip正则检测
 */
+ (BOOL)validIP:(NSString *)ip;

@end

NS_ASSUME_NONNULL_END
