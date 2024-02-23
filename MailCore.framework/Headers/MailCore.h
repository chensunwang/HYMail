//
//  MailCore.h
//  MailCore
//
//  Created by 王江潮 on 16/12/14.
//  Copyright © 2016年 Richinfo. All rights reserved.
//

/**
 *  版本
 *  V3.7.0
 */

/**
 *  使用注意事项
 *  1、使用SDK需添加依赖libz.1.dylib、libsqlite.dylib、libxml.dylib
 *  2、使用SDK工程中target－－Build Setting－－Linking－－Other Linker Flags 添加：-all_load （为了静态库使用类别)
 */

#import <Foundation/Foundation.h>
#import "ThinkMail_DataModel.h"

@interface MailCore : NSObject

/**
 *  邮箱登录接口
 *
 *  @param account         帐号
 *  @param password       密码
 *  @param host                帐号对应的域名
 *  @param block           block回调
 */
+ (void)loginWithAccount:(NSString *)account password:(NSString *)password host:(NSString*)host finish:(void(^)(NSError *error, id response))block;

/**
 *  邮箱单点登录接口（旧接口，samp下线就会跟随下线）
 *
 *  @param account         帐号
 *  @param host                帐号对应的域名
 *  @param sessionData     sessionData
 *  @param block           block回调
 */
+ (void)unifyLoginWithAccount:(NSString *)account host:(NSString *)host sessionData:(NSString *)sessionData finish:(void(^)(NSError *error, id response))block;

/**
 *  统一用户邮箱单点登录接口 （新接口，替换旧的邮箱单点登录接口 unifyLoginWithAccount:）
 *
 *  @param account        帐号
 *  @param host               帐号对应的域名   
 *  @param ticket          登录票据
 *  @param block            block回调
 */

+ (void)unifiedUserLoginWithAccount:(NSString *)account host:(NSString *)host
 ticket:(NSString *)ticket finish:(void(^)(NSError *error, id response))block;



/**
 *  文件夹列表接口
 *
 *  @param type            0：为全部；1.系统文件夹；2.管理文件夹；3.用户文件夹；5.标签文件夹
 *  @param block           block回调
 */
+ (void)folderListWithType:(TKMailFolderType)type finish:(void(^)(NSError *error, id response))block;

/**
 *  邮件列表接口（PS：邮件列表也可以用邮件搜索接口实现）
 *
 *  @param desc            是否逆序排列，desc=1时表示按逆序，desc=0表示正序
 *  @param order           sendDate: 按发送日期, receiveDate:按接收日期, from: 按发件人, to: 按收件人, size: 按大小, subject:  按主题 默认按接收日期
 *  @param sessionEnable   0：普通列表模式，1：会话列表模式＋聚合模式，2：普通列表模式＋聚合模式
 *  @param folderFid       文件夹id《参考文件夹列表返回接口id》
 *  @param start           从第几条记录开始读取（最新倒序为从1开始）
 *  @param total           取的条数（如果不够条数，则返回实条数）合法值为1-200
 *  @param block           block回调
 */
+ (void)mailListWithDesc:(NSInteger)desc order:(NSString *)order sessionEnable:(NSInteger)sessionEnable folderFid:(NSInteger)folderFid start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *  获取未读邮件列表
 *
 *  @param desc            是否逆序排列，desc=1时表示按逆序，desc=0表示正序
 *  @param order           sendDate: 按发送日期, receiveDate:按接收日期, from: 按发件人, to: 按收件人, size: 按大小, subject:  按主题 默认按接收日期
 *  @param sessionEnable   0：普通列表模式，1：会话列表模式＋聚合模式，2：普通列表模式＋聚合模式
 *  @param folderFid       文件夹id《参考文件夹列表返回接口id》
 *  @param start           从第几条记录开始读取（最新倒序为从1开始）
 *  @param total           取的条数（如果不够条数，则返回实条数）合法值为1-200
 *  @param block           block回调
 */

+ (void)unreadMailWithDesc:(NSInteger)desc order:(NSString *)order sessionEnable:(NSInteger)sessionEnable folderFid:(NSInteger)folderFid start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *  邮件索引信息接口
 *
 *  @param midArr          邮件mid集合数组
 *  @param block           block回调
 */
+ (void)getMailInfoWithMidArr:(NSArray *)midArr finish:(void(^)(NSError *error, id response))block;

/**
 *  修改邮件文件属性(修改邮件所属文件夹)接口
 *
 *  @param fid             邮件新文件夹fid集合数组
 *  @param midArr          邮件mid集合数组（PS:会话邮件将其中每个mid传入数组即可）
 *  @param block           block回调
 */
+ (void)moveMailWithNewFid:(NSInteger)fid midArr:(NSArray *)midArr finish:(void(^)(NSError *error, id response))block;

/**
 *  修改邮件状态接口
 *
 *  @param type             设置的的属性类型：
 backGroundColor:设置邮件的新背景色
 priority:设置邮件的新优先级(1-5)
 antiVirusStatus: 杀毒结果
 rcptFlag:信件投递状态跟踪
 replied:回复标志(0、未回复 1、已回复)
 forwarded:转发标志(0、未转发 1、已转发)
 top:置顶标志(0、未置顶 1、已置顶)
 successed:发送状态(0未发送1已发送成功)
 recall:召回状态（0、未召回　1、已召回）
 read:已读状态(0:已读，1:未读)
 autoDelete:自销毁标记　（0：不销毁　1：自销毁）
 starFlag:星标邮件(0: 非星标邮件  1: 星标邮件)
 starType:7种类型的星标邮件，值在SetValue的低三位，如为0，表示取消星标邮件
 *  @param value           type参数下对应的value
 *  @param midArr          邮件mid集合数组（PS:会话邮件将其中每个mid传入数组即可）
 *  @param block           block回调
 */
+ (void)updateMailStatusWithType:(NSString *)type value:(NSInteger)value midArr:(NSArray *)midArr finish:(void(^)(NSError *error, id response))block;

/**
 *  修改邮件标签接口
 *
 *  @param type            设置的的属性类型：add:增加,delete:删除,empty:清空所有标签
 *  @param labelId         增加或删除标签的id 当type为add,delete时有效
 *  @param midArr          邮件mid集合数组
 *  @param block           block回调
 */
+ (void)updateMailLabelWithType:(NSString *)type labelId:(NSInteger)labelId midArr:(NSArray *)midArr finish:(void(^)(NSError *error, id response))block;

/**
 *  物理删除邮件接口
 *
 *  @param midArr          邮件mid集合数组
 *  @param block           block回调
 */
+ (void)deleteMailWithMidArr:(NSArray *)midArr finish:(void(^)(NSError *error, id response))block;

/**
 *  获取邮件内容接口
 *
 *  @param mid             邮件mid
 *  @param block           block回调
 */
+ (void)readMailWithMid:(NSString *)mid finish:(void(^)(NSError *error, id response))block;


/**
 *  查询邮件是否可撤回接口
 *
 *  @param mid             邮件mid
 *  @param block           block回调
 */

+(void)queryMBoxRecallAddressWithMid:(NSString *)mid finish:(void(^)(NSError *error, id response))block;
/**
 *  邮件撤回接口
 *
 *  @param mid             邮件mid
 *  @param addressee       邮件收件人地址数组
 *  @param block           block回调
 邮件撤回结果对象的数组：@"var" array,撤回状态：
 "1": "稍后执行",
 "2": "成功撤回",
 "3": "已撤回（重复操作）",
 "4": "撤回失败，邮件可能已被删除、自动转发，或其它未知原因",
 "5": "撤回失败，邮件已读",
 "6": "撤回失败，邮件已被POP过",
 "8": "撤回失败，邮已过期
 */
+ (void)recallMailWithMid:(NSString *)mid addressee:(NSArray *)addressee finish:(void(^)(NSError *error, id response))block;

/**
 *  附件列表接口
 *
 *  @param order           sendDate:按发送日期，receiveDate:按接收日期，from:按发件人，to:按      收件人，size:按邮件大小，subject:按邮件主题，name:按附件名称，attachSuffix:按附件名后缀，attachSize:按附件大小
 *  @param start           从第几条记录开始读取
 *  @param total           取的条数（如果不够条数，则返回实 条数）合法值为1-200
 *  @param block           block回调
 */
+ (void)attachmentlistWithOrder:(NSString *)order start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *  获取发送邮件的ComposeId接口---------------发送邮件会自动调用此接口
 *  ---发件前获取ComposeId
 *  @param block           block回调  返回字典 -- @[@"var"]获取
 */
+ (void)getComposeIdFinish:(void(^)(NSError *error, id response))block;

/**
 *  发送邮件接口
 *
 *  @param account         发送人账号
 *  @param messageId       nil
 *  @param omid            转发时的原始邮件mid
 *  @param subject         邮件主题
 *  @param body            邮件内容（htmlStr 普通str也行，但没有邮件格式）
 *  @param toArr           收件人账号数组
 *  @param ccArr           抄送人账号数组
 *  @param bccArr          密送人账号数组
 *  @param attachmentArr   附件数组---数组中必须以字典的形式传送，字典中需包含如下key：
 sourceFrom ： 来源（本地图片或者网盘附件url，参考枚举TKPrepareUploadAttachSourceFrom）
 fileId   ：文件Id
 fileName ：文件名;
 fileSize ：文件大小;
 fileOffSet ：fileOffSet（网盘附件url需要）;
 fileOriginalUrl ：图片本地路径/网盘url;
 *  @param mailCreateType  发送邮件类型
 *  @param delegate        delegate
 *  @param action          action回调方法
 */
+ (void)sendMailWithAccount:(NSString *)account messageId:(NSString *)messageId originalMailId:(NSString *)omid subject:(NSString *)subject body:(NSString *)body to:(NSArray *)toArr cc:(NSArray *)ccArr bcc:(NSArray *)bccArr attachments:(NSArray *)attachmentArr mailCreateType:(TKMailCreateType)mailCreateType delegate:(id)delegate responeAction:(SEL)action;

/**
 *  更新文件夹接口--------目前此接口只用于修改文件夹名称
 *
 *  @param type            type（1:修改文件夹名称，2:修改文件夹位置，3:修改文件夹父节点，4:修改是否可pop，5:修改标签的颜色值，6.修改自销毁有效日期，7:设置文件夹是否隐藏）
 *  @param name            文件夹新名称
 *  @param fidArr          文件夹id数组或单个int的文件夹id，目前仅支持下面的参数type=4,5,6,7时，才支持多个fid的array元素批量操作，其他的只支持一个int的元素（就算传array也只会接受第一个）
 *  @param block           block回调
 */
+ (void)updateFolderWithType:(NSInteger)type name:(NSString *)name fidArr:(NSArray *)fidArr finish:(void(^)(NSError *error, id response))block;


/**
 *  更新标签名称和颜色（可同时修改名称和颜色，也可单个修改）
 *
 *  @param name            文件夹新名称（为空，说明不需要修改）
 *  @param fid             需要修改的标签fid
 *  @param folderColor     标签颜色序号（一一对应），为-1说明不需要修改
 *  @param block           block回调
 *  注意：此接口需要用到的type，已经固定写好分别是修改名称type=1,修改颜色type=5
 */
+ (void)updateLableNameColorWithFid:(NSString *)fid
                               name:(NSString *)name
                        folderColor:(NSInteger )folderColor
                             finish:(void(^)(NSError *error, id response))block;
 

/**
*  创建文件夹（标签）接口
*
*  @param type            type（1.系统文件夹，2.管理文件夹，3.用户文件夹，5.标签文件夹，6.代收文件夹，文件夹不能删除）
*  @param name            文件夹名称
*  @param parentId        父文件夹ID，为0创建到根目录
*  @param block           block回调
*/
+ (void)createFolderWithType:(NSInteger)type name:(NSString *)name parentId:(NSInteger)parentId finish:(void(^)(NSError *error, id response))block;


/**
 *  创建文件夹（标签）接口, 带标签颜色（type=5时候用）
 *
 *  @param type            type（1.系统文件夹，2.管理文件夹，3.用户文件夹，5.标签文件夹，6.代收文件夹，文件夹不能删除）
 *  @param name            文件夹名称
 *  @param parentId        父文件夹ID，为0创建到根目录
 *  @param folderColor     folderColor标签颜色（type=5时候有用）
 *  @param location        location文件夹的位置(标签：30000-49999)
 *  @param block           block回调
 */
+ (void)createLabelFolderWithType:(NSInteger)type name:(NSString *)name parentId:(NSInteger)parentId folderColor:(NSInteger)folderColor location:(NSInteger )location finish:(void(^)(NSError *error, id response))block;

/**
 *  删除文件夹（标签）接口
 *
 *  @param type            type（文件夹类型3：用户文件夹 5：标签文件夹）
 PS:当type=5时表示删除标签，删除标签时需要清理掉该标签所有关联的信息。
 (1)删除标签的同时，需要找到引用标签的所有邮件移除相应的标签。
 (2) 移除标签可调用mbox:updateMessagesAll (type=deleteLabel)内部接口实现。
 (3) 删除标签后，需要自动禁用（或删除）含有这个标签的过滤器。
 *  @param fid             文件夹id
 *  @param moveToFid       父文件夹ID，表示如果文件夹里面有邮件，自动转移到这个文件夹下面; 该值如果为空，或者跟fid一样，则表示不转移，按原有流程进行删除文件夹。
 *  @param block           block回调
 */
+ (void)deleteFolderWithType:(NSInteger)type fid:(NSInteger)fid moveToFid:(NSInteger)moveToFid finish:(void(^)(NSError *error, id response))block;

/**
 *  更新文件夹下邮件状态
 *
    设置的的属性类型：
    move: 1移动所有邮件
    delete: 2物理删除邮件
    empty: 3清空标签下所有的邮件
    backGroundColor:6设置邮件的新背景色
    priority:7 设置邮件的新优先级(1-5)
    read: （4/5）已读状态(0:已读，1:未读)
    addLabel:  增加标签
    deleteLabel: 删除标签
 *  @param type            设置的属性类型
 *  @param fid             当前文件夹id
 *  @param newFid          新文件夹id,移动操作时有效
 *  @param value           设置值（取值范围参见type定义）
 *  @param opUser          移动oa邮箱要求填写该值，如果是公共帐号操作，则填写当前真实操作个人的邮箱帐号
 *  @param midsArr         mid 数组
 *  @param block           block回调
 */
+ (void)updateMessagesAllInFolderType:(NSString *)type fid:(NSInteger)fid newFid:(NSInteger)newFid value:(NSInteger)value opUser:(NSString *)opUser midsArr:(NSArray *)midsArr finish:(void(^)(NSError *error, id response))block;

/**
 *  获取附件信息接口
 *  ----------------------（参数参考获取附件内容详情接口）
 *  @param midsArr                邮件mid数组
 *  @param block                  block回调
 */
+ (void)getAttachInfoWithMidsArr:(NSArray *)midsArr finish:(void(^)(NSError *error, id response))block;

/**
 *  附件下载接口
 *  ----------------------（参数参考获取附件内容详情接口）
 *  @param mid                    邮件mid
 *  @param attachName             附件名称
 *  @param attachOffset           附件的偏移量
 *  @param attachSize             附件大小
 *  @param encode                 附件编码方式（1、base64；2、quoted-printable；3、7bit；4、8bit；5、Binary；6、uuencode）
 *  @param downloadDelegate       回调代理设置
 *  @param progressAction         进度回调方法
 *  @param finishedAction         完成回调方法
 */
+ (void)attachDownloadWithMid:(NSString *)mid attachName:(NSString *)attachName attachOffset:(NSInteger)attachOffset attachSize:(NSInteger)attachSize encode:(NSInteger)encode downloadDelegate:(id)downloadDelegate progressAction:(SEL)progressAction finishedAction:(SEL)finishedAction;

/**
 *  恢复编辑草稿邮件接口
 *
 *  @param mid             会话邮件mid
 *  @param block           block回调
 */
+ (void)restoreDraftWithMid:(NSString *)mid finish:(void(^)(NSError *error, id response))block;

/**
 *  邮件搜索接口
 *
 *  @param fid             文件夹fid
 *  @param isSubscribe     是否在订阅文件夹搜索
 *  @param type            搜索区域类型，参考SearchMailFieldType枚举
 *  @param searchKey       搜索关键字（nil时不带条件搜索）
 *  @param start           从第几条开始搜索
 *  @param total           搜索条数
 *  @param block           block回调
 *
 */
+ (void)searchMailWithFid:(NSInteger)fid isSubscribe:(BOOL)isSubscribe type:(SearchMailFieldType)type searchKey:(NSString *)searchKey start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *  用户基本信息接口          这里获取取用户邮箱容量@2016-12-21
 *  @param block           block回调
 */
+ (void)getUserInitDataInfoFinish:(void(^)(NSError *error, id response))block;


// ------------------------Add-----------------------------

/**
 *  发送定时邮件接口
 *
 *  @param account         发送人账号
 *  @param messageId       nil
 *  @param omid            转发时的原始邮件mid
 *  @param subject         邮件主题
 *  @param schedule        定时发送时间的时间戳
 *  @param body            邮件内容（htmlStr 普通str也行，但没有邮件格式）
 *  @param toArr           收件人账号数组
 *  @param ccArr           抄送人账号数组
 *  @param bccArr          密送人账号数组
 *  @param attachmentArr   附件数组---数组中必须以字典的形式传送，字典中需包含如下key：
 sourceFrom ： 来源（本地图片或者网盘附件url，参考枚举TKPrepareUploadAttachSourceFrom）
 fileName ：文件名;
 fileSize ：文件大小;
 fileOffSet ：fileOffSet（网盘附件url需要）;
 fileOriginalUrl ：图片本地路径/网盘url;
 *  @param mailCreateType  发送邮件类型
 *  @param delegate        delegate
 *  @param action          action回调方法
 */

+ (void)sendTimingMailWithAccount:(NSString *)account messageId:(NSString *)messageId originalMailId:(NSString *)omid subject:(NSString *)subject schedule:(NSInteger)schedule body:(NSString *)body to:(NSArray *)toArr cc:(NSArray *)ccArr bcc:(NSArray *)bccArr attachments:(NSArray *)attachmentArr mailCreateType:(TKMailCreateType)mailCreateType delegate:(id)delegate responeAction:(SEL)action;


/**
 *
 * 保存草稿接口
 *
 * @param messageId         草稿邮件ID，传了的话会删除对应的的草稿邮件
 * @param subject           邮件主题
 * @param schedule          定时时间戳
 * @param body              邮件内容（htmlStr 普通str也行，但没有邮件格式）
 * @param toArr             收件人数组
 * @param ccArr             抄送人数组
 * @param bccArr            密送人数组
 * @param attachmentArr     附件数组---数组中必须以字典的形式传送，字典中需包含如下key：
 sourceFrom ： 来源（本地图片或者网盘附件url，参考枚举TKPrepareUploadAttachSourceFrom）
 fileName ：文件名;
 fileSize ：文件大小;
 fileOffSet ：fileOffSet（网盘附件url需要）;
 fileOriginalUrl ：图片本地路径/网盘url;
 * @param delegate          delegate
 * @Param action            action回调方法
 *
 **/

+ (void)saveDraftWithDraftMessageId:(NSString *)messageId subject:(NSString *)subject schedule:(NSInteger)schedule body:(NSString *)body to:(NSArray *)toArr cc:(NSArray *)ccArr bcc:(NSArray *)bccArr attachments:(NSArray *)attachmentArr  delegate:(id)delegate responeAction:(SEL)action;

/**
 * 获取未读邮件数接口
 * @param block  block回调
 * 返回的数据结构 TKMResponeModel_GetUserUnReadCount
 *
 */
+(void)unReadMailCountFinish:(void(^)(NSError *error, id response))block;

/**
 *
 * 查看往来邮件接口
 * @param type   ContactMailType枚举值
 * @param userName 邮箱地址
 * @param start  从第几条记录开始读取（最新倒序为从1开始）
 * @param total  取的条数（如果不够条数，则返回实条数）合法值为1-200
 * @param block  block回调
 * 返回的数据结构 TKResponsedModel_MBoxSearchMessages
 *
 */
+(void)contactsMailListWithType:(ContactMailType)type userName:(NSString*)userName start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *  修改用户名接口
 *  @param userName        用户名
 *  @param block           block回调
 */
+(void)modifyUserName:(NSString *)userName finish:(void(^)(NSError *error, id response))block;
/**
 *  邮件夹排序接口      只支持排类型为TKMailFolderTypeOfUser的邮件夹
 *  @param sortArray 邮件夹fid排序数组
 *  @param block     block回调
 */
+(void)mailFoldersSortWithSortArray:(NSArray*)sortArray finish:(void(^)(NSError *error, id response))block;

/**
 *
 * 修改标签名称接口
 * @param labelId        标签id
 * @param labelName      新的标签名称
 * @param block          block回调
 *
 */
+(void)updateLabelWithLabelId:(NSString*)labelId labelName:(NSString*)labelName finish:(void(^)(NSError *error, id response))block;

/**
 *
 * 级割接与系统故障功能查询接口
 *
 */

+(void)getCutUpgradeStateFinish:(void(^)(NSError *error, id response))block;

/**
 *
 *筛选主送我、星标、含附件、未读邮件接口
 *@param type           筛选邮件类型，参考FilterMailType枚举
 *@param desc            是否逆序排列，desc=1时表示按逆序，desc=0表示正序
 *@param order           sendDate: 按发送日期, receiveDate:按接收日期, from: 按发件人, to: 按收件人, size: 按大小, subject:  按主题 默认按接收日期
 *@param folderFid       文件夹id《参考文件夹列表返回接口id》
 *@param start           从第几条记录开始读取（最新倒序为从1开始）
 *@param total           取的条数（如果不够条数，则返回实条数）合法值为1-200
 *@param block           block回调
 *
 */
+(void)filterMailListWithType:(FilterMailType)type desc:(NSInteger)desc order:(NSString *)order folderFid:(NSInteger)folderFid start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;


/**
 *
 *筛选主送我、星标、含附件、未读邮件、标签邮件接口
 *@param type           筛选邮件类型，参考FilterMailType枚举
 *@param desc            是否逆序排列，desc=1时表示按逆序，desc=0表示正序
 *@param order           sendDate: 按发送日期, receiveDate:按接收日期, from: 按发件人, to: 按收件人, size: 按大小, subject:  按主题 默认按接收日期
 *@param folderFid       文件夹id《参考文件夹列表返回接口id》
 *@param labels          标签，数组类型中标签对象类型为NSString
 *@param start           从第几条记录开始读取（最新倒序为从1开始）
 *@param total           取的条数（如果不够条数，则返回实条数）合法值为1-200
 *@param block           block回调
 *
 */
+(void)filterMailListWithType:(FilterMailType)type desc:(NSInteger)desc order:(NSString *)order folderFid:(NSInteger)folderFid labels:(NSMutableArray *)labels start:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;

/**
 *
 *获取星标邮件接口
 *@param start           从第几条记录开始读取（最新倒序为从1开始）
 *@param total           取的条数（如果不够条数，则返回实条数）合法值为1-200
 *@param block           block回调
 */

+(void)getStarFlagMailListWithStart:(NSInteger)start total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;


/**
 *
 *登出接口
 *
 */

+(void)logoutWithFinish:(void(^)(NSError *error, id response))block;

//----------------------- 通讯录---------------------------

/**
 *  个人通讯分组列表接口
 *  @param block           block回调
 *  返回的数据结构  TKMResponeModel_PrivateContactGroupList
 */
+(void)privateContactGroupListFinish:(void(^)(NSError *error, id response))block;


/**
 *
 *  个人通讯录联系人列表接口
 *  @param groupId           分组id
 *  @param block             block回调
 *  返回的数据结构 TKMResponeModel_PrivateContactList
 *
 */
+(void)privateContactListWithGroupId:(NSString*)groupId finish:(void(^)(NSError *error, id response))block;

/**
 *  新增分组接口
 *  @param groupName        分组名称
 *  @param block            block回调
 */

+(void)privateContactGroupAddWithGroupName:(NSString *)groupName  finish:(void(^)(NSError *error, id response))block;


/**
 *   分组重命名接口
 *  @param groupId          分组Id
 *  @param groupName        分组名称
 *  @param block            block回调
 */

+(void)privateContactGroupReNameWithGroupId:(NSString *)groupId groupName:(NSString *)groupName  finish:(void(^)(NSError *error, id response))block;

/**
 *   删除分组接口
 *  @param groupId          分组Id
 *  @param block            block回调
 */
+(void)privateContactGroupDelWithGroupId:(NSString *)groupId finish:(void(^)(NSError *error, id response))block;


/**
 *  个人通讯录联系人详情接口
 *  @param contactId        联系人id
 *  @param block            block回调
 *  返回的数据结构  TKMResponeModel_PrivateContactPersonDetail
 *
 */

+(void)privateContactPersonDetailWithContactId:(NSString *)contactId  finish:(void(^)(NSError *error, id response))block;

/**
 *  新增联系人接口
 *  @param name            联系人名称
 *  @param email           联系人邮箱
 *  @param phoneNumber     联系人电话
 *  @param groupId         分组id
 *  @param block           block回调
 */

+(void)privateContactPersonAddWithPersonName:(NSString *)name email:(NSString *)email phoneNumber:(NSString*)phoneNumber groupId:(NSString *)groupId finish:(void(^)(NSError *error, id response))block;

/**
 * 删除联系人接口
 * @param contactId        联系人id
 * @param block            block回调
 */

+(void)privateContactPersonDelWithContactId:(NSString *)contactId finish:(void(^)(NSError *error, id response))block;

/**
 * 多选删除个人通讯录联系人
 * @param contactIds        联系人ids
 * @param block            block回调
 */

+(void)deletePrivateContactsWithContactIds:(NSMutableArray *)contactIds finish:(void(^)(NSError *error, id response))block;

/**
 *  修改联系人接口
 *  @param name            联系人名称
 *  @param email           联系人邮箱
 *  @param phoneNumber     联系人电话
 *  @param contactId       联系人id
 *  @param block           block回调
 */

+(void)privateContactPersonModifyWithPersonName:(NSString *)name email:(NSString *)email phoneNumber:(NSString*)phoneNumber contactId:(NSString *)contactId finish:(void(^)(NSError *error, id response))block;


/**
 *  移动联系人接口
 *  @param oldUserAndGroupDict 装着将要移动联系人的信息字典 字典的格式为@{@"分组id":@(@"联系人id",@"联系人id",...),@"分组id":@(@"联系人id",@"联系人id",...)}
 *  @param newGroupID      新的分组的id
 *  @param block           block回调
 */

+(void)privateContactPersonMoveWithOldUserAndGroupDict:(NSMutableDictionary *)oldUserAndGroupDict newGroupID:(NSString *)newGroupID finish:(void(^)(NSError *error, id response))block;

/**
 *  搜索联系人接口
 *  @param userId          账号信息
 *  @param cropId          公司id
 *  @param keyWord         搜索关键字
 *  @param total           搜索条数
 *  @param block           block回调
 *  返回的数据结构  TKMResponeModel_PrivateContactSearchLists
 *
 */
+(void)privateContactSearchWithUserId:(NSString*)userId cropId:(NSString*)cropId keyWord:(NSString *)keyWord total:(NSInteger)total finish:(void(^)(NSError *error, id response))block;


/**
 *  写信邮箱联想接口
 *  @param cropId          公司id，设置了企业id，就会按指定企业联想
 *  @param is_mix_search         搜索关键字 是否混合搜索
 *  @param content 根据content内容搜索
 *  @param start 分页参数，开始下标
 *  @param total 返回数量
 *  @param dataType          搜索范围/类型 0搜索全部(个人通讯录、企业通讯录、邮件组) 默认，
 1个人通讯录，
 2只搜索企业通讯录、邮件组
 */
+(void)getContactOnSendMailWithContent:(NSString *)content is_mix_search:(NSInteger)is_mix_search corpId:(NSString*)cropId start:(NSInteger)start total:(NSInteger)total dataType:(NSInteger)dataType finish:(void(^)(NSError *error, id response))block;


/**
 获取登录账户的用户信息
 @param account 邮箱地址
 @param NSDictionary 返回用户信息字典
 account 用户信息
 croupId 企业id
 mailAccount 邮箱地址
 trueName 真是姓名
 mobileNumber 手机号码
 */
+(NSMutableDictionary *)getMailAccountInfoWithAccount:(NSString *)account;

//删除邮箱账户
+(BOOL)logOutDeleteAccount;

//设置是否允许设置代理 YES 允许 NO 不允许
+(void)setProxyStatus:(BOOL)proxyStatus;


@end

