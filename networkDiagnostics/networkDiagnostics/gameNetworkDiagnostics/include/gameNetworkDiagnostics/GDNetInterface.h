//
//  GDNetInterface.h
//  GDNetDiag
//
//  Created by 许振文 on 2022/6/20.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import "GDLoginfo.h"
#import "XZWCdnModel.h"
#import "GDNetworkAddress.h"

#define kFASTHTTPPORT 80
#define kFASTHTTPSPORT 443
#define kFASTTCPCONNECTTIMEOUT 1

static NSString * _Nullable const GDNetInterfaceDir = @"egretGame";

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
 * @param isRemoteInfo 是否显示远端服务器信息
 * @param handler tracerouter的回调
 */
- (void)mtrHost:(NSString *)host needShowRemoteInfo:(BOOL)isRemoteInfo progressHandler:(GDNetInterfaceCallBack)handler;
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

#pragma mark - Cdn
/*
 * 调用tcpCdnIp获取ip connect时间
 * @param ip host
 * @param port 端口号
 * @return delta 延迟时间(ms)，为0的情况代表连接出错
 */
+ (int)tcpCdnIp:(NSString *)ip port:(int16_t)port;

/*
 * 调用tryBestDomain获取择优的排序数据，有协议的情况会保留协议再做检测
 * @param domains 域名数据
 * @param isAsc 是否升序
 * @param tryComplete 返回择优的排序数据的结果
 */
+ (void)tryBestDomain:(NSArray <NSString *>*)domains andAsc:(BOOL)isAsc andComplete:(void (^)(NSArray <NSDictionary <NSString *, XZWCdnModel *>*>*result))tryComplete;

/*
 * 调用tryBestIp获取择优的排序数据
 * @param ips ip数据
 * @param isAsc 是否升序
 * @param tryComplete 返回择优的排序数据的结果
 */
+ (void)tryBestIp:(NSArray <NSString *>*)ips andAsc:(BOOL)isAsc andComplete:(void (^)(NSArray <NSDictionary <NSString *, XZWCdnModel *>*>*result))tryComplete;

/*
 * 调用tryBestCdn获取择优的排序数据
 * @param cdns cdn数据
 * @param isAsc 是否升序
 * @param tryComplete 返回择优的排序数据的结果
 */
+ (void)tryBestCdn:(NSDictionary <NSString *, XZWCdnModel *>*)cdns andAsc:(BOOL)isAsc andComplete:(void (^)(NSArray <NSDictionary <NSString *, XZWCdnModel *>*>*result))tryComplete;

/*
 * getNetworkCardBytes 获取手机网卡的流量信息
 *
 * @return 返回网卡下载的流量
 */
+ (NSInteger)getNetworkCardBytes;

#pragma mark - File
/**
 * getDirectoryByUrl: 根据远端地址转化为目录
 *
 *  @param urlString 远端地址
 */
+ (NSString *)getDirectoryByUrl:(NSString *)urlString;

/**
 * getFileNameByUrl: 根据远端地址转化为文件名
 *
 *  @param urlString 远端地址
 */
+ (NSString *)getFileNameByUrl:(NSString *)urlString;

/**
 *  documentFile:andDirectory:  返回Document的根路径下的文件路径
 *
 *  @param fileName 文件名
 *  @param dir 目录名或者多个目录的路径 : dir1/dir2/dir3
 *
 *  @return 文件路径
 */
+ (NSString *)documentFile:(NSString *)fileName andDirectory:(nullable NSString *)dir;

/**
 *  doesItExistDocumentDirectory 检查是否已经创建文件夹目录
 *
 * @param dir 目录名或者多个目录的路径 : dir1/dir2/dir3
 *
 *  @return YES 已经创建
 */
+ (BOOL)doesItExistDocumentDirectory:(NSString *)dir;

/**
 *  doesItExistFile:andDirectory: 检查文件是否已经创建
 *
 *  @param fileName 文件名
 *  @param dir 目录名或者多个目录的路径 : dir1/dir2/dir3
 *
 *  @return 已经创建返回YES,否则返回NO
 */
+ (BOOL)doesItExistFile:(NSString *)fileName andDirectory:(nullable NSString *)dir;

/**
 *  deleteFile:andDirectory: 删除文件
 *
 * Example：
 * 删除所有预加载目录的资源
 * fileError = [GDNetInterface deleteFile:@"" andDirectory:nil];
 * 只删除预加载目录的src资源
 * fileError = [GDNetInterface deleteFile:@"" andDirectory:GDNetInterfaceDir];
 * 只删除预加载目录的storagePath文件
 * fileError = [GDNetInterface deleteFile:storagePath andDirectory:nil];
 *
 *  @param fileName 文件名
 *  @param dir 目录名或者多个目录的路径 : dir1/dir2/dir3
 *
 *  @return 错误的情况返回NSError
 */
+ (NSError *)deleteFile:(NSString *)fileName andDirectory:(nullable NSString *)dir;

/**
 * createEgretPreResDirectory 创建预加载文件目录 GDNetInterfaceDir
 *
 * @return 错误的情况返回NSError
 */
+ (NSError *)createEgretPreResDirectory;

/**
 * createEgretPreResPath: 创建预加载资源文件
 *
 *  @param fileName 文件名
 */
+ (void)createEgretPreResFile:(NSString *)fileName;

/**
 * copyFile:toTarget: 拷贝文件到指定路径
 *
 * @param originFile 原文件url
 * @param targetFile 目标文件url
 *
 * @return 错误的情况返回NSError
 */
+ (NSError *)copyFile:(NSURL *)originFile toTarget:(NSURL *)targetFile;

/**
 * readInfoWithFile: 获取文件相关信息
 *
 *  @param path 文件完整路径
 *
 *  @return 返回文件信息
 */
+ (NSDictionary *)readInfoWithFile:(NSString *)path;

/**
 * readFilesInDirectory: 读取目录下的文件
 *
 *  @param dir 目录完整路径
 *
 *  @return 返回文件信息
 */
+ (NSArray *)readFilesInDirectory:(NSString *)dir;

/**
 * readSizeWithFile: 读取文件大小
 *
 *  @param path 文件完整路径
 *
 *  @return 返回格式化的文件大小
 */
+ (NSString *)readSizeWithFile:(NSString *)path;

/**
 * fileFormatSize: 文件大小的格式化
 *
 *  @param fileSize 文件大小
 *
 *  @return 返回文件大小的格式化
 */
+ (NSString *)fileFormatSize:(NSInteger)fileSize;

/**
 * deviceIdleSpace 获取设备空闲存储空间的大小
 *
 *
 *  @return 返回空闲存储空间的大小
 */
+ (CGFloat)deviceIdleSpace;

/**
 * md5WithFile: 获取文件的md5
 *
 *  @param path 文件完整路径
 *
 *  @return 文件的md5
 */
+ (NSString *)md5WithFile:(NSString *)path;

/**
 * handleCdnResZipFile:storageName:andUnzipPath:andServerMd5: 处理cdn资源文件
 *
 *  @param originFile 不为空 下载的临时文件
 *  @param storageName 不为空 需要存放的文件名
 *  @param unzipPath 不为空 需要解压目录的路径
 *  @param smd5 可空 服务端返回的md5
 *
 *  @return 错误的情况返回NSError
 */
+ (NSError *)handleCdnResZipFile:(NSURL *)originFile storageName:(NSString *)storageName andUnzipPath:(NSString *)unzipPath andServerMd5:(nullable NSString *)smd5;

/**
 * handleLocalZip: 分析是否需要是用本地的zip的解压文件
 *
 *  @param path 比较的文件名
 *
 *  @return 是否需要使用本地zip的解压文件
 */
+ (BOOL)handleLocalZip:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
