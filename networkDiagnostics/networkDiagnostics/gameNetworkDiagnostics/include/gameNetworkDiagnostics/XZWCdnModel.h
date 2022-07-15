//
//  XZWCdnModel.h
//  gameNetworkDiagnostics
//
//  Created by 许振文 on 2022/7/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XZWCdnModel : NSObject

/// host
@property (nonatomic,copy)NSString *host;
/// port
@property (nonatomic,assign)int port;
/// 延迟时间
@property (nonatomic,assign)int delta;
/// 状态  0:未使用  1:成功  2:失败
@property (nonatomic,assign)int state;

@end

NS_ASSUME_NONNULL_END
