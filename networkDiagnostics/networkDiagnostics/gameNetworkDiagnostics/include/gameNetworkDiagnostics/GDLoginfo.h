//
//  GDLoginfo.h
//  GDNetDiag
//
//  Created by 许振文 on 2022/5/31.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface GDLoginfo : NSObject

- (instancetype)initWithInfo:(NSString *)stepInfo;
- (void)recordStepInfo:(NSString *)stepInfo;
- (NSString *)printLoginfo;

@end

NS_ASSUME_NONNULL_END
