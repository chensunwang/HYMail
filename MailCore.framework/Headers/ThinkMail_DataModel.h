//
//
//  Modify by wangjiangchao on 16-12-22.
//  Copyright (c) 2014年 Richinfo. All rights reserved.
//

/* 发送邮件类型 */
typedef enum
{
    ThinkMailSendNewMail = 0,       // 发送新建邮件
    ThinkMailSendReplyMail,         // 发送回复邮件
    ThinkMailSendForwardMail,       // 转发邮件
    ThinkMailFirstSaveMail,         // 首次存草稿
    ThinkMailEditSaveMail,          // 修改保存草稿
    ThinkMailSendSaveMail           // 发送草稿邮件
}ThinkMailSendMailType;


/** 发送邮件类型 */
typedef enum
{
    TKCreateNewMail = 0,        // 新建写信
    TKDraftMail,                // 编辑发送草稿邮件
    TKReplyMail,                // 回复
    TKForwardMail,              // 转发
    
}TKMailCreateType;

/**邮件文件夹标签类型 */
typedef enum
{
    TKMailFolderTypeAll = 0,        /*全部*/
    TKMailFolderTypeOfSystem,       /**< 系统文件夹 location[1, 4999]*/
    TKMailFolderTypeOfManager,      /**< 管理文件夹 location[5000, 9999]*/
    TKMailFolderTypeOfUser,         /**< 用户自定义文件夹 location[10000, 29999]*/
    TKMailFolderTypeOfLabel = 5     /**< 标签文件夹 location[30000, 49999]*/
}TKMailFolderType;

typedef enum ThinkMail_RequestState
{
    ThinkMail_RequestStateOfSuccess = 0,            //请求成功
    ThinkMail_RequestStateOfFail,                   //请求失败
    ThinkMail_RequestStateOfLoginFailed,            //登录鉴定失败
    ThinkMail_RequestStateOfDataAnalysisFailed      //服务器返回数据格式有误
    
}ThinkMail_RequestState;

typedef enum SearchMailFieldType
{
    SearchMailFieldTypeOfAttachName = -1,      /**< 搜索匹配附件名 */
    SearchMailFieldTypeOfAll,                  /**< 搜索匹配发件人、收件人、邮件主题和邮件内容 */
    SearchMailFieldTypeOfFrom,                 /**< 搜索匹配发件人 */
    SearchMailFieldTypeOfTO,                   /**< 搜索匹配收件人 */
    SearchMailFieldTypeOfSubject,              /**< 搜索匹配邮件主题 */
    SearchMailFieldTypeOfContent,              /**< 搜索匹配邮件内容 */
}SearchMailFieldType;


//往来邮件类型
typedef enum ContactMailType{
    
    ContactMailTypeAll = 0, //全部
    ContactMailTypeReceive, //我收到的
    ContactMailTypeSend, //我发送的

}ContactMailType;


//筛选收件箱邮件类型
typedef enum FilterMailType
{
    
    FilterMailTypeOfNone = 0,
    FilterMailTypeOfStarFlag = 1<<0,                /**< 筛选星标邮件 */
    FilterMailTypeOfUnRead = 1<<1,                  /**< 筛选未读邮件 */
    FilterMailTypeOfHasAttachment = 1<<2,           /**< 筛选含附件邮件 */
    FilterMailTypeOfMainDelivery = 1<<3,             /**< 筛选主送我邮件 */
    FilterMailTypeOfLabelMail = 1<<4,             /**< 筛选标签邮件 */

}FilterMailType;



#import <Foundation/Foundation.h>
@class ThinkMail_GDataXMLElement;

extern NSString * const KInboxFolder;       //收件箱
extern NSString * const KDeleteboxFolder;   //以删除
extern NSString * const KOutboxFolder;      //已发送
extern NSString * const KDraftsFolder;      //草稿箱
extern NSString * const KSendFolder;        //发件箱
extern NSString * const KSpamFolder;        //垃圾邮件

#pragma mark - 上下文数据定义
/**
 *  请求的上下文信息
 */
@interface TKMContextModel : NSObject<NSCopying>

/**
 *    @brief    //帐号信息
 */
@property (nonatomic, copy) NSString * contextAccount;

@property (nonatomic, copy) NSString * encryptedAccount;

/**
 *    @brief    文件夹信息    KInboxFolder;       //收件箱
 KDeleteboxFolder;   //以删除
 KOutboxFolder;      //已发送
 KDraftsFolder;      //草稿箱
 KSendFolder;        //发件箱
 KSpamFolder         垃圾邮件
 */
@property (nonatomic, copy) NSString * contextFolder;

/**
 *    url
 */
@property (nonatomic, copy) NSString * contextUrl;

@property (nonatomic, assign) NSInteger contextTag;

@property (nonatomic, copy) NSString * contextLoginHost;

@property (nonatomic, copy) NSString *userAgentMark;

/**
 *    @brief    // 2016.12.12
 *    Created by jiangchaowang 因为封装接口统一block返回，对之前回调的接口修改，通过context传入block进行返回
 */
@property (nonatomic, copy) void(^blockFinish)(NSError *error, id response);

@end


#pragma mark - 通用的返回数据类型
/**
 *    @brief  返回数据: requestContex：请求时传入的上下文信息，respondModel：完成请求后post到外部的通用数据。
 *
 *    Created by gao on 2014-04-17 15:08
 */
@interface TKMResponsedModel : NSObject <NSCopying>

@property (nonatomic, strong) TKMContextModel * requestContex;

@property (nonatomic, strong) id requestObject;

/**
 *    @brief    返回的数据类型
 */
@property (nonatomic, strong) id respondModel;

/**
 *    @brief    请求状态
 */
@property (nonatomic) ThinkMail_RequestState requestState;

/**
 *    @brief    请求响应代码
 */
@property (nonatomic)int statusCode;

/**
 *    @brief    请求响应信息
 */
@property (nonatomic, copy) NSString *statusMsg;

- (id)parseResponsedata:(NSDictionary*)dict;

@end

#pragma mark - 返回数据中用的数据类。

/**
 *    @brief     邮件标志对象(flags object)
 *
 *    Created by gao on 2014-04-17 15:14
 */
@interface TKRequestModel_flagsObject : NSObject

/**
 *    @brief    int        0/1    1:未读
 *
 *    Created by gao on 2014-04-17 15:14
 */
@property (nonatomic, assign) NSInteger   read;

/**
 *    @brief    int        0/1    定时邮件
 *
 *    Created by gao on 2014-04-17 15:14
 */
@property (nonatomic, assign) NSInteger   fixedtime;

/**
 *    @brief    int        0/1    1有附件
 *
 *    Created by gao on 2014-04-17 15:14
 */
@property (nonatomic, assign) NSInteger   attached;

/**
 *    @brief    int        0/1    1敏感词邮件
 *
 *    Created by gao on 2014-04-17 15:15
 */
@property (nonatomic, assign) NSInteger   signedInt;

/**
 *    @brief    int        0/1    1加密邮件
 *
 *    Created by gao on 2014-04-17 15:15
 */
@property (nonatomic, assign) NSInteger   encrypted;


/**
 *    @brief int        0/1/2    1天数到后自毁 2阅读后自毁
 *
 *    Created by gao on 2014-04-17 15:15
 */
@property (nonatomic, assign) NSInteger   selfdestruct;

/**
 *    @brief      int        0/1    1已回复
 *
 *    Created by gao on 2014-04-17 15:15
 */
@property (nonatomic, assign) NSInteger   replied;

/**
 *    @brief    int        0/1    1已转发
 *
 *    Created by gao on 2014-04-17 15:16
 */
@property (nonatomic, assign) NSInteger   forwarded;

/**
 *    @brief    int        0/1    已deprecated 容量超过Soft Quota的警告信
 *
 *    Created by gao on 2014-04-17 15:16
 */
@property (nonatomic, assign) NSInteger   squotaWarning;

/**
 *    @brief    int        0/1    已deprecated 容量超过Hard Quota的警告信
 *
 *    Created by gao on 2014-04-17 15:16
 */
@property (nonatomic, assign) NSInteger   hquotaWarning;

/**
 *    @brief    int        0/1    草稿邮件
 *
 *    Created by gao on 2014-04-17 15:18
 */
@property (nonatomic, assign) NSInteger   draft;

/**
 *    @brief    int        0/1    语音邮件
 *
 *    Created by gao on 2014-04-17 15:19
 */
@property (nonatomic, assign) NSInteger   voice;

/**
 *    @brief    int        0/1    传真邮件
 *
 *    Created by gao on 2014-04-17 15:19
 */
@property (nonatomic, assign) NSInteger   fax;

/**
 *    @brief    int        0/1    已逻辑删除邮件
 *
 *    Created by gao on 2014-04-17 15:19
 */
@property (nonatomic, assign) NSInteger   deleted;

/**
 *    @brief    int        0/1    系统邮件
 *
 *    Created by gao on 2014-04-17 15:19
 */
@property (nonatomic, assign) NSInteger   system;

/**
 *    @brief    int        0/1    置顶邮件
 *
 *    Created by gao on 2014-04-17 15:19
 */
@property (nonatomic, assign) NSInteger   top;

/**
 *    @brief    int        0/1    支持召回邮件
 *
 *    Created by gao on 2014-04-17 15:20
 */
@property (nonatomic, assign) NSInteger   recall;

/**
 *    @brief    int        0/1    发送成功邮件
 *
 *    Created by gao on 2014-04-17 15:20
 */
@property (nonatomic, assign) NSInteger   successed;

/**
 *    @brief    int        0/1    召回成功邮件
 *
 *    Created by gao on 2014-04-17 15:20
 */
@property (nonatomic, assign) NSInteger   recallok;

/**
 *    @brief    int        0/1    星标邮件
 *
 *    Created by gao on 2014-04-17 15:20
 */
@property (nonatomic, assign) NSInteger   starFlag;

/**
 *    @brief    int        0/1    邮件备注标志位（1表示有备注）
 *
 *    Created by gao on 2014-04-17 15:21
 */
@property (nonatomic, assign) NSInteger   memoFlag;

/**
 *    @brief    int        0/1    是否紧急邮件
 *
 *    Created by gao on 2014-04-17 15:21
 */
@property (nonatomic, assign) NSInteger   urgencyFlag;

/**
 *    @brief    int        0-20        0、正常邮件的默认状态
 1、发信监控
 2、收信监控
 3、发信审核 待审核
 4、收信审核 待审核
 5、审核 审核通过
 6、审核 审核不通过
 7、审核 超时
 16、所有(发信和收信）待审核
 *
 *    Created by gao on 2014-04-17 15:21
 */
@property (nonatomic, assign) NSInteger   auditStatus;

/**
 *    @brief    int        0-2    任务邮件，0不是，1待办中2已完成
 *
 *    Created by gao on 2014-04-17 15:21
 */
@property (nonatomic, assign) NSInteger        taskFlag;

/**
 *    @brief    int        0/1    是否是帐单邮件 1是 0不是
 *
 *    Created by gao on 2014-04-17 15:22
 */
@property (nonatomic, assign) NSInteger        billFlag;


/**
 *    @brief    int        0/1    是否是订阅邮件 1是 0不是
 *
 *    Created by gao on 2014-04-17 15:22
 */
@property (nonatomic, assign) NSInteger        subscriptionFlag;
@end



/**
 *    @brief 返回邮件内容对象 (MIME message info Object)
 *
 *    Created by gao on 2014-04-17 15:29
 */
@interface TKResponseModel_MessageData : NSObject


@property (nonatomic, strong) NSString*         mid;
/**
 *    @brief    邮件所在文件夹的id
 *
 *    Created by gao on 2014-04-17 15:29
 */
@property (nonatomic, assign) NSInteger         fid;

/**
 *    @brief     邮件会话号
 *
 *    Created by gao on 2014-04-17 15:30
 */
@property (nonatomic, assign) NSInteger         mailSession;

/**
 *    @brief    邮件大小(byte)
 *
 *    Created by gao on 2014-04-17 15:30
 */
@property (nonatomic, assign) NSInteger         size;

/**
 *    @brief    邮件发送时间 1970年1月1日距今秒数
 *
 *    Created by gao on 2014-04-17 15:30
 */
@property (nonatomic, assign) NSInteger         sendDate;


/**
 *    @brief    邮件接收时间 1970年1月1日距今秒数
 *
 *    Created by gao on 2014-04-17 15:30
 */
@property (nonatomic, assign) NSInteger         receiveDate;

/**
 *    @brief    邮件最后修改日期，如果对邮件进行了标记、转移等操作，会更新这个时间。 1970年1月1日距今秒数
 *
 *    Created by gao on 2014-04-17 15:31
 */
@property (nonatomic, assign) NSInteger         modifyDate;

/**
 *    @brief    任务邮件的处理时间，默认为0 1970年1月1日距今秒数
 *
 *    Created by gao on 2014-04-17 15:31
 */
@property (nonatomic, assign) NSInteger         taskDate;

/**
 *    @brief    //邮件优先级 [1,2:high 3:normal 4,5:low]
 *              //priority的值等于high时为紧急邮件
 *
 *    Created by gao on 2014-04-17 15:31
 */
@property (nonatomic, assign) NSInteger         priority;

/**
 *    @brief    邮件主题颜色
 *
 *    Created by gao on 2014-04-17 15:31
 */
@property (nonatomic, assign) NSInteger         color;


@property (nonatomic, assign) NSInteger         denyForward;
/**
 *    @brief     0：unscaned  邮件未扫描
 1：novirus   邮件没有病毒
 2:cleaned   发现并清除了病毒
 3：infected  邮件包含未清除的病毒
 4：undetermined 不确定是否有病毒
 *
 *    Created by gao on 2014-04-17 15:31
 */
@property (nonatomic, assign) NSInteger         antivirusStatus;

/**
 *    @brief     信件投递状态跟踪
 0：进入队列
 1：投递成功
 2：对方已读
 3：部分投递成功（有>=1个收件人投递失败）
 4：投递失败
 *
 *    Created by gao on 2014-04-17 15:32
 */
@property (nonatomic, assign) NSInteger         rcptFlag;

@property (nonatomic, assign) NSInteger         attachmentNum;
@property (nonatomic, assign) NSInteger         mailNum;

/**
 *    @brief    0 非会议邮件 1 会议邮件
 *
 *    Created by gao on 2014-04-17 15:32
 */
@property (nonatomic, assign) NSInteger         meetingFlag;

/**
 *    @brief    邮件类型
 0 系统邮件
 1 客户端邮件
 2 webmail邮件
 3 mta邮件
 4 运营群发邮件
 *
 *    Created by gao on 2014-04-17 15:32
 */
@property (nonatomic, assign) NSInteger         mailFlag;

/**
 *    @brief    7种类型的星标邮件，值在SetValue的低三位
 *
 *    Created by gao on 2014-04-17 15:33
 */
@property (nonatomic, assign) NSInteger         starType;

/**
 *    @brief    0-6位：logotype 发件人logo类型，取值：0..128， 0表示没有logo
 *
 *    Created by gao on 2014-04-17 15:33
 */
@property (nonatomic, assign) NSInteger         logoType;

/**
 *    @brief    0为默认，（1－9为系统内部保留，不可用），10-255 各种账单类型邮件
 *
 *    Created by gao on 2014-04-17 15:33
 */
@property (nonatomic, assign) NSInteger         billType;


/**
 *    @brief    0普通邮件 1账单邮件
 *
 *    Created by gao on 2014-04-17 15:34
 */
@property (nonatomic, assign) NSInteger         billFlag;

@property (nonatomic, assign) NSInteger         securityLevel;

@property (nonatomic, strong) TKRequestModel_flagsObject      *flagObject;
@property (nonatomic, strong) NSMutableArray      *label;
@property (nonatomic, strong) NSString*         from;

@property (nonatomic, strong) NSString*         to;
@property (nonatomic, strong) NSString*         subject;
@property (nonatomic, strong) NSString*         summary;

/**
 *    @brief    //0 正常邮件
 1 发信监控
 2 收信监控
 3 发信审核
 4 收信审核
 5 审核通过
 6 审核不通过
 7 审核超时
 *
 *    Created by gao on 2014-04-17 15:34
 */
@property (nonatomic, assign) NSInteger         auditStatus;

/**
 *    @brief    包含的会话邮件数
 *
 *    Created by Mark on 2014-05-20 14:03
 */
@property (nonatomic, assign) NSInteger         conversationCount;

/**
 *    @brief    包含的会话邮件id集合
 *
 *    Created by mac on 2014-07-01 15:27
 */
@property (nonatomic, strong) NSArray *conversationMailIds;

/**
 *    @brief    附件（array of TKAttachInfoObject）
 *
 *    Created by mac on 2014-08-22 09:16
 */
@property (nonatomic, strong)NSMutableArray *attachmentArray;

/**
 *    @brief 是否是主送邮件
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, assign) BOOL isMainDelivery;

@end

/**
 *    @brief    附件下载状态
 *
 *    Created by mac on 2014-05-07 11:01
 */
typedef enum TKAttachDownloadState
{
    TKAttachDownloadStateOfUnDownload = 0, /** 未下载 */
    TKAttachDownloadStateOfPrepareToDownload, /** 准备下载 */
    TKAttachDownloadStateOfDownloading, /** 下载中*/
    TKAttachDownloadStateOfStopDownload, /** 暂停下载*/
    TKAttachDownloadStateOfDownloaded /** 已下载到本地 */
}TKAttachDownloadState;

/**
 *    @brief 附件信息对象(attach info object)
 *
 *    Created by gao on 2014-04-17 15:43
 */
@interface TKAttachInfoObject:NSObject

/**
 *    @brief    int    4        附件所在邮件的id
 *
 *    Created by gao on 2014-04-17 15:43
 */
@property (nonatomic, strong) NSString* mid;

/**
 *    @brief    附件id
 *
 *    Created by mac on 2014-05-08 15:24
 */
@property (nonatomic, strong) NSString* attachId;


/**
 *    @brief    int    2        附件所在的文件id
 *
 *    Created by gao on 2014-04-17 15:43
 */
@property (nonatomic, assign) NSInteger fid;

/**
 *    @brief    date    --    --    邮件发送时间 1970年1月1日距今秒数
 *
 *    Created by gao on 2014-04-17 15:43
 */
@property (nonatomic, assign) NSInteger sendDate;

/**
 *    @brief    date    --    --    邮件接收时间
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, assign) NSInteger receiveDate;

/**
 *    @brief    string    --        发件人
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, strong) NSString* from;

/**
 *    @brief    string    --        收件人
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, strong) NSString* to;

/**
 *    @brief    string    --        主题
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, strong) NSString* subject;

/**
 *    @brief    int            附近头偏移
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, assign) NSInteger attachHeadOffset;

/**
 *    @brief    int            附件内容偏移量
 *
 *    Created by gao on 2014-04-17 15:44
 */
@property (nonatomic, assign) NSInteger attachOffset;

/**
 *    @brief    string    --        附件分类
 *
 *    Created by gao on 2014-04-17 15:45
 */
@property (nonatomic, strong) NSString* attachType;

/**
 *    @brief    string            附件名称
 *
 *    Created by gao on 2014-04-17 15:45
 */
@property (nonatomic, strong) NSString* attachName;

/**
 *    @brief    int            附件大小
 *
 *    Created by gao on 2014-04-17 15:47
 */
@property (nonatomic, assign) NSInteger attachSize;

/**
 *    @brief    int            附件原始大小
 *
 *    Created by gao on 2014-04-17 15:47
 */
@property (nonatomic, assign) NSInteger attachRealSize;

/**
 *    @brief    string            附件的Content-Type
 *
 *    Created by gao on 2014-04-17 15:47
 */
@property (nonatomic, strong) NSString* attachContentType;

/**
 *    @brief    string            附件正文编码
 *
 *    Created by gao on 2014-04-17 15:48
 */
@property (nonatomic, strong) NSString* encode;

/**
 *    @brief    附件下载状态
 *
 *    Created by mac on 2014-05-07 10:48
 */
@property (nonatomic)TKAttachDownloadState attachDownloadState;


@end



/**
 *    @brief    时间过滤数据结构
 *
 *    Created by gao on 2014-04-17 15:49
 */
@interface FilterRecvTimeObject : NSObject

/**
 *    @brief    否    int    4    起始时间
 *
 *    Created by gao on 2014-04-17 15:49
 */
@property (nonatomic, assign) NSInteger  endTime;

/**
 *    @brief    否    int    4    结束时间
 *
 *    Created by gao on 2014-04-17 15:49
 */
@property (nonatomic, assign) NSInteger  startTime;

@end


/**
 *    @brief    附件大小过滤
 *
 *    Created by gao on 2014-04-17 15:49
 */
@interface FilterSizeObject : NSObject

/**
 *    @brief    否    int    4    最小字节
 *
 *    Created by gao on 2014-04-17 15:49
 */
@property (nonatomic, assign) NSInteger  minSize;

/**
 *    @brief    否    int    4    最大字节
 *
 *    Created by gao on 2014-04-17 15:50
 */
@property (nonatomic, assign) NSInteger  maxSize;

@end



/**
 *    @brief    //过滤条件。
 *
 *    Created by gao on 2014-04-17 15:50
 */
@interface FilterSearchObject : NSObject

/**
 *    @brief    否    object    --    按时间过滤
 *
 *    Created by gao on 2014-04-17 15:50
 */
@property (nonatomic, strong) FilterRecvTimeObject* recvTime;


/**
 *    @brief    否    string    --    按附件名称过滤
 *
 *    Created by gao on 2014-04-17 15:50
 */
@property (nonatomic, strong) NSString* attachName;

/**
 *    @brief    否    int    1    收件人和发件人过滤关系：2.表示或，1.表示与，0.默认
 *
 *    Created by gao on 2014-04-17 15:51
 */
@property (nonatomic, assign) NSInteger relation;

/**
 *    @brief    否    string    --    按发件人过滤
 *
 *    Created by gao on 2014-04-17 15:51
 */
@property (nonatomic, strong) NSString* from;

/**
 *    @brief    否    string    --    按收件人过滤
 *
 *    Created by gao on 2014-04-17 15:51
 */
@property (nonatomic, strong) NSString* to;

/**
 *    @brief    否    int    --    按附件类型过滤
 *
 *    Created by gao on 2014-04-17 15:51
 */
@property (nonatomic, assign) NSInteger attachType;

/**
 *    @brief    否    string    --    按邮件主题过滤
 *
 *    Created by gao on 2014-04-17 15:51
 */
@property (nonatomic, strong) NSString* subject;

/**
 *    @brief    否    object    --    按附件大小过滤
 *
 *    Created by gao on 2014-04-17 15:52
 */
@property (nonatomic, strong) FilterSizeObject* size;

/**
 *    @brief    否    int    2    已读未读 0 已读，1 未读
 *
 *    Created by gao on 2014-04-17 15:52
 */
@property (nonatomic, assign) NSInteger read;

@end



/**
 *    @brief    //邮件统计状态
 *
 *    Created by gao on 2014-04-17 16:12
 */
@interface TKResponseDModel_StatsData : NSObject

@property (nonatomic, assign) NSInteger       attachmentNum;
@property (nonatomic, assign) NSInteger       messageCount;
@property (nonatomic, assign) NSInteger       messageSize;
@property (nonatomic, assign) NSInteger       unreadMessageCount;
@property (nonatomic, assign) NSInteger       unreadMessageSize;
@end

/**
 *    @brief    文件夹数据结构
 *
 *    Created by gao on 2014-04-17 16:07
 */
@interface TKResponseDModel_FolderData: NSObject

/**
 *    @brief    邮箱文件夹名称
 *
 *    Created by gao on 2014-04-17 16:07
 */
@property (nonatomic, strong) NSString*       name;

/**
 *    @brief    邮件文件夹ID
 系统邮件文件夹ID说明如下：
 1：收件箱
 2：草稿箱
 3：已发送
 4：已删除
 5：垃圾邮件
 6：病毒邮件
 7：邮箱容量
 *
 *    Created by gao on 2014-04-17 16:07
 */
@property (nonatomic, assign) NSInteger       fid;

/**
 *    @brief    标签颜色，当type=5时有效
 *
 *    Created by gao on 2014-04-17 16:08
 */
@property (nonatomic, assign) NSInteger       folderColor;

/**
 *    @brief    该文件夹是否加密 1: 加密，0:没有加密
 *
 *    Created by gao on 2014-04-17 16:08
 */
@property (nonatomic, assign) NSInteger       folderPassFlag;

@property (nonatomic, assign) NSInteger       hideFlag;

/**
 *    @brief    文件夹自动清理日期，以天为单位，0表示关闭自动清理
 *
 *    Created by gao on 2014-04-17 16:08
 */
@property (nonatomic, assign) NSInteger       keepPeriod;

/**
 *    @brief    文件夹位置，主要用于排序，本接口返回的文件夹列表数据必须按照location进行正序排序。
 系统: 1-4999；
 管理: 5000-9999
 用户: 10000-29999
 标签: 30000-49999
 *
 *    Created by gao on 2014-04-17 16:11
 */
@property (nonatomic, assign) NSInteger       location;

/**
 *    @brief    父文件夹id 客户端进行文件夹树形结构组装
 *
 *    Created by gao on 2014-04-17 16:12
 */
@property (nonatomic, assign) NSInteger       parentId;

/**
 *    @brief    是否能被pop代收邮件
 *
 *    Created by gao on 2014-04-17 16:12
 */
@property (nonatomic, assign) NSInteger       pop3Flag;

/**
 *    @brief    //保留
 *
 *    Created by gao on 2014-04-17 16:12
 */
@property (nonatomic, assign) NSInteger       reserve;


//11-15
/**
 *    @brief    1.系统文件夹 2.管理文件夹 3.用户文件夹 5.标签文件夹
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, assign) NSInteger       type;

@property (nonatomic, assign) NSInteger       vipFlag;
/**
 *    @brief    邮件总数
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, assign) NSInteger       messageCount;

/**
 *    @brief    0-long64    所有邮件大小(字节)
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, assign) NSInteger       messageSize;

/**
 *    @brief    新邮件数
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, assign) NSInteger       unreadMessageCount;


//16-20
/**
 *    @brief    新邮件大小(字节)
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, assign) NSInteger       unreadMessageSize;

/**
 *    @brief    TKResponseDModel_StatsData 邮件统计状态，请求中stats值为1时才返回
 *
 *    Created by gao on 2014-04-17 16:13
 */
@property (nonatomic, strong) TKResponseDModel_StatsData* stats;

/**
 *    @brief    文件夹是否可见（保存在本地）
 *
 *    Created by mac on 2014-05-13 15:30
 */
@property (nonatomic) BOOL isShow;

/**
 *    @brief    邮箱的未读数据
 *
 *    Created by chenling on 2014-06-28 12:27
 */
@property (nonatomic, assign) NSInteger unseenMailCount;


@end


/**
 *    @brief    condiction对象说明
 *
 *    Created by gao on 2014-04-17 16:19
 */
@interface TKRequestModel_SearchCondiction : NSObject

/**
 *    @brief    必选    搜索属性名
 可操作的字段值：
 sendId  服务邮件的发件人ID
 logotype  邮件标志(0-127)
 from:            发件人
 (from包含多个邮件地址时,请用英文分号分隔,多个地址之间是或的关系, 前端界面支持通信录名字搜索时，一定要转换成对应的邮件地址）
 to               收件人
 (to包含多个邮件地址时,请用英文分号分隔,多个地址之间是或的关系, 前端界面支持通信录名字搜索时，一定要转换成对应的邮件地址）
 subject           邮件主题
 size              邮件大小
 priority           优先级
 antiVirusStatus     杀毒结果
 backgroundColor   背景色
 sentDate          信件发送时间
 receivedDate      信件接收时间
 memo            邮件备注
 content      邮件正文(触发全文检索)
 attachName  邮件附件名称(触发全文检索
 
 *
 *
 *    Created by gao on 2014-04-17 16:19
 */
@property (nonatomic, strong) NSString*       field;

/**
 *    @brief    否    比较操作符，详细参见以下比较操作符定义  目前系统 GT LT GE LE EQ
 *
 *    Created by gao on 2014-04-17 16:20
 */
@property (nonatomic,strong) NSString*       operatorStr;

/**
 *    @brief    可操作的值 nsinter 类型。日期使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换） 邮件大小（size）使用字节为单位
 *    value 字段 可能是  string OR int 类型。定义两个变量，组装请求数据时 首先使用string 类型value 如 nil 或者 长度<=0 则使用value nsinteger 类型 组装。
 *    Created by gao on 2014-04-17 16:20
 */
@property (nonatomic, assign) NSInteger       valueInt;


/**
 *    @brief    可操作的值 部分搜索关键测 例如：subject  需要 sting 类型的 value
 *    value 字段 可能是  string OR int 类型。定义两个变量valueInt/valueStr 组装请求数据时 首先使用string 类型value 如 nil 或者 长度<=0 则使用value nsinteger 类型 组装。
 *    Created by gao on 2014-04-28 10:36
 */
@property (nonatomic,strong) NSString*       valueStr;



@end

/**
 *    @brief approachSearch逼近式搜索条件对象
 *
 *    Created by gao on 2014-04-17 16:20
 */
@interface TKRequestModel_SearchApproachSearch : NSObject

/**
 *    @brief    可选    int    1    0:不限 1:未读 2:已读
 *
 *    Created by gao on 2014-04-17 16:21
 */
@property (nonatomic, assign) NSInteger  read;

/**
 *    @brief    可选    int    1    0:不限 1：有附件 2：无附件
 *
 *    Created by gao on 2014-04-17 16:21
 */
@property (nonatomic, assign) NSInteger  attached;

/**
 *    @brief    可选    int    4    比如要取一个月内的邮件，就将该值设置为一个月前的时间的秒数，单位秒
 *
 *    Created by gao on 2014-04-17 16:21
 */
@property (nonatomic, assign) NSInteger  during;

/**
 *    @brief    可选    int    2    文件夹id，要逼近式搜索的文件夹
 *
 *    Created by gao on 2014-04-17 16:21
 */
@property (nonatomic, assign) NSInteger  fid;

/**
 *    @brief    可选    string    80    发件人的地址，最大长度80
 *
 *    Created by gao on 2014-04-17 16:21
 */
@property (nonatomic, strong) NSString*  from;

@end


/**
 *    @brief     *邮件正文text信息对象(part object)//邮件正文html信息对象 (part object)
 *
 *    Created by gao on 2014-04-17 16:33
 */
@interface TKResponsedModel_partObject : NSObject

/**
 *    @brief    正文在邮件原文中的contentId
 *
 *    Created by gao on 2014-04-17 16:33
 */
@property (nonatomic, strong) NSString  *contentId;

/**
 *    @brief    正文类型，缺省值为text/plain
 ContentType为 "text/plain", "text/html"
 read的参数控制是否返回
 或 mime message info object
 或 null (read level之外)
 (ContentType 为"message/rfc822")
 *
 *    Created by gao on 2014-04-17 16:33
 */
@property (nonatomic, strong) NSString  *contentType;

/**
 *    @brief    正文长度，base64 encode之后的大小
 *
 *    Created by gao on 2014-04-17 16:34
 */
@property (nonatomic, assign) NSInteger contentLength;

/**
 *    @brief    编码： 7bit|8bit. quoted-printable  . base64
 *
 *    Created by gao on 2014-04-17 16:34
 */
@property (nonatomic, strong) NSString  *encoding;

/**
 *    @brief    正文部分在邮件原文中的偏移量
 *
 *    Created by gao on 2014-04-17 16:34
 */
@property (nonatomic, assign) NSInteger contentOffset;

/**
 *    @brief    正文长度估算值, base64 decode之后的大小
 *
 *    Created by gao on 2014-04-17 16:34
 */
@property (nonatomic, assign) NSInteger estimateSize;

/**
 *    @brief    邮件正文内容
 *
 *    Created by gao on 2014-04-17 16:34
 */
@property (nonatomic, strong) NSString* content;

/**
 *    @brief    返回指定的信头，具体返回哪些信头在请求参数returnHeaders中指定，
 既可以返回from,sender这些标准信头，也可以返回自定义的扩展信息。
 headers:{
 From:”aaa@a.com”,
 Sender:bbb@b.com,
 x-richinfo:1,
 x-compose:”color=1&sms=1”
 }
 *
 *    Created by gao on 2014-04-17 16:35
 */
@property (nonatomic, strong) NSDictionary* headers;

@end

/**
 *    @brief    上封邮件信息/下封邮件信息
 *
 *    Created by gao on 2014-04-17 16:35
 */
@interface TKResponsedModel_NextMailInfo: NSObject


/**
 *    @brief        邮件mid
 *
 *    Created by gao on 2014-04-17 16:35
 */
@property (nonatomic, strong) NSString* mid;

/**
 *    @brief    主题
 *
 *    Created by gao on 2014-04-17 16:35
 */
@property (nonatomic, strong) NSString* subject;

/**
 *    @brief    会话ID
 *
 *    Created by gao on 2014-04-17 16:35
 */
@property (nonatomic, assign) NSInteger sessionId;

/**
 *    @brief    会话邮件数量
 *
 *    Created by gao on 2014-04-17 16:36
 */
@property (nonatomic, assign) NSInteger  mailNum;

/**
 *    @brief    发件人地址
 *
 *    Created by gao on 2014-04-17 16:36
 */
@property (nonatomic, strong) NSString*  account;

/**
 *    @brief    邮件所在文件夹
 *
 *    Created by gao on 2014-04-17 16:36
 */
@property (nonatomic, assign) NSInteger fid;

@end


/**
 *    @brief     *  读信回执对象，有回执时返回，发送回执时把该对象以xml格式传给邮件回执回执发送接口
 *
 *    Created by gao on 2014-04-17 16:36
 */
@interface TKResponsedModel_ReadReceipt: NSObject


/**
 *    @brief    原信的id
 *
 *    Created by gao on 2014-04-17 16:36
 */
@property (nonatomic, strong) NSString* messageId;

/**
 *    @brief    原信的发送时间
 *
 *    Created by gao on 2014-04-17 16:36
 */
@property (nonatomic, assign) NSInteger sendDate;

/**
 *    @brief    发件人
 *
 *    Created by gao on 2014-04-17 16:37
 */
@property (nonatomic, strong) NSString* account;

/**
 *    @brief    收件人
 *
 *    Created by gao on 2014-04-17 16:37
 */
@property (nonatomic, strong) NSString* to;

/**
 *    @brief    主题
 *
 *    Created by gao on 2014-04-17 16:37
 */
@property (nonatomic, strong) NSString* subject;


@end

/**
 *    @brief    //邮件内容对象 (MIME message info Object)
 *
 *    Created by gao on 2014-04-17 16:38
 */
@interface TKResponsedModel_MessageInfo : NSObject

/**
 *    @brief    获取邮件状态：1 获取概要，2 获取成功
 *
 *    Created by gao on 2014-04-17 16:38
 */
@property (nonatomic)int getMailStatus;

/**
 *    @brief    发件人地址数组
 *
 *    Created by gao on 2014-04-17 16:38
 */
@property (nonatomic, strong) NSString*  account;

/**
 *    @brief    邮件id
 *
 *    Created by gao on 2014-04-18 15:51
 */
@property (nonatomic, strong) NSString*  mid;

/**
 *    @brief    收信人，unicode 名称/地址 string类型，多个用,分隔
 *
 *    Created by gao on 2014-04-17 16:38
 */
@property (nonatomic, strong) NSString*  to;

/**
 *    @brief    抄送人，unicode 名称/地址 string类型，多个用,分隔
 *
 *    Created by gao on 2014-04-17 16:38
 */
@property (nonatomic, strong) NSString*  cc;

/**
 *    @brief    密送人，unicode 名称/地址 string类型，多个用,分隔
 *
 *    Created by mac on 2014-05-16 17:12
 */
@property (nonatomic, strong) NSString*  bcc;


/**
 *    @brief    是否需要已读回执
 *
 *    Created by gao on 2014-04-17 16:38
 */
@property (nonatomic, assign) NSInteger  requestReadReceipt;

/**
 *    @brief    邮件主题
 *
 *    Created by gao on 2014-04-17 16:39
 */
@property (nonatomic, strong) NSString*  subject;

/**
 *    @brief    邮件发送日期
 *
 *    Created by gao on 2014-04-17 16:39
 */
@property (nonatomic, strong) NSString*  sendDate;

/**
 *    @brief    优先级： 1, 2: 高优先级 3 : 普通优先级 4, 5: 低优先级
 *
 *    Created by gao on 2014-04-17 16:39
 */
@property (nonatomic, assign) NSInteger  priority;

/**
 *    @brief    1：html邮件  0：文本邮件
 *
 *    Created by gao on 2014-04-17 16:39
 */
@property (nonatomic, assign) NSInteger  isHtml;

/**
 *    @brief    邮件正文text信息对象(part object)
 *
 *    Created by gao on 2014-04-17 16:39
 */
@property (nonatomic, strong) TKResponsedModel_partObject*  text;

/**
 *    @brief    邮件正文html信息对象 (part object)
 *
 *    Created by gao on 2014-04-17 16:40
 */
@property (nonatomic, strong) TKResponsedModel_partObject*  html;


/**
 *    @brief    array //附件对象的数组(attach Object)
 *
 *    Created by gao on 2014-04-17 16:40
 */
@property (nonatomic, strong) NSMutableArray*  arrAttachments;

/**
 *    @brief    object   //邮件标记状态,参考(flags object对象)
 *
 *    Created by gao on 2014-04-17 16:40
 */
@property (nonatomic, strong) TKRequestModel_flagsObject *flagObject;

/// 标签数据
@property (nonatomic, strong) NSMutableArray*  label;

/**
 *    @brief    0 不禁止转发，1禁止转发
 *
 *    Created by gao on 2014-04-17 16:40
 */
@property (nonatomic, assign) NSInteger  denyForward;

/**
 *    @brief     0 默认值，正常的发送方式
 1 以eml附件方式发送
 2 压缩加密发送（国电用）
 3 压缩加密发送（通用压缩）
 4 以会议邀请方式发送的
 5 答复会议邀请邮件的
 *
 *    Created by gao on 2014-04-17 16:40
 */
@property (nonatomic, assign) NSInteger  sendWay;

/**
 *    @brief    头信息字符串 只在请求参数header=1是返回
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) NSString*  headerRaw;

/**
 *    @brief    returnHeaders请求参数中，指明返回的头信息对象
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) NSDictionary*  headersDic;

/**
 *    @brief    object
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) NSDictionary*  antispamInfoDIc;


/**
 *    @brief    读信回执对象，有回执时返回，发送回执时把该对象以xml格式传给邮件回执回执发送接口
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) TKResponsedModel_ReadReceipt*  readReceipt;

/**
 *    @brief    上封邮件信息 object
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) TKResponsedModel_NextMailInfo*  prev;

/**
 *    @brief    下封邮件信息
 *
 *    Created by gao on 2014-04-17 16:41
 */
@property (nonatomic, strong) TKResponsedModel_NextMailInfo*  next;

/**
 *    @brief    下封邮件信息
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, strong) TKResponsedModel_NextMailInfo*  PrevNew;

@property (nonatomic, strong) TKResponsedModel_NextMailInfo*  NextNew;

/**
 *    @brief    //邮件体对象(msg info object)，同邮件列表
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, strong) NSString*  sessionMails;

/**
 *    @brief
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, strong) NSDictionary*  meetingInfo;


/**
 *    @brief 是否是主送邮件
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, assign) BOOL isMainDelivery;


@end

@interface TKFolderIdAndParentIdData : NSObject

/**
 *    @brief  文件夹id
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, assign) NSInteger fid;

/**
 *    @brief  文件夹父id  仅当修改文件夹父节点时才返回
 *
 *    Created by gao on 2014-04-17 16:42
 */
@property (nonatomic, assign) NSInteger  parentId;


@end






#pragma mark -
#pragma mark - 请求的父类
@interface TKMRequestBase : NSObject
@property (nonatomic, assign) NSOperationQueuePriority       requestPriority;
-(NSData*)getRequestData;
@end

#pragma mark - 返回数据的父类
//返回的基本信息。
@interface TKMResponsedBase : NSObject
@property (nonatomic, strong) NSString*       code;
@property (nonatomic, assign) NSInteger       errorCode;
@property (nonatomic, strong) NSString*       summary;
@end

#pragma mark - 请求 && 返回
/**
 *    @brief 登录请求数据结构。
 *
 *    Created by gao on 2014-04-17 15:11
 */
@interface TKRequestModel_LoginMail : TKMRequestBase


//1-5
@property (nonatomic,strong)                    NSString *userId;
@property (nonatomic,strong)                    NSString *password;
@property (nonatomic,strong)                    NSString *authType;
@property (nonatomic,strong)                    NSString *passType;
@property (nonatomic,strong)                    NSString *verifyCode;

//6-10
@property                                       BOOL     ipCheck;
@property                                       BOOL     cookieCheck;
@property (nonatomic,strong)                    NSString *locale;
@property (nonatomic,strong)                    NSString *style;
@property (nonatomic,strong)                    NSString *attrs;
@property (nonatomic) BOOL isNeedMD5;
@end

/**
 *    @brief    登录返回信息对外不暴露 仅返回code  errcode 判断是否成功。
 *
 *    Created by gao on 2014-04-17 15:12
 */
@interface TKResponseDModel_LoginMail : TKMResponsedBase
/**
 *    @brief    设置某用户邮件会话模式是否成功
 *
 *    Created by mac on 2014-05-09 15:21
 */
@property (nonatomic, assign)BOOL setSessionModeSeccess;
/**
 *    @brief    用户名(139邮箱 邮箱帐号)
 *
 *    Created by mac on 2014-06-13 17:09
 */
@property (nonatomic, strong)NSString *mailAccount;

/**
 *    @brief    用户名(139邮箱 手机帐号)
 *
 *    Created by mac on 2014-06-13 17:09
 */
@property (nonatomic, strong)NSString *mobileAccount;

/**
 *    @brief    用户名(139邮箱 通行证帐号)
 *
 *    Created by mac on 2014-06-13 17:09
 */
@property (nonatomic, strong)NSString *passAccount;

@property (nonatomic, copy)NSString *trueName;

@end

/**
 *    @brief    获取邮件参数请求结构
 *
 *    Created by mac on 2014-11-24 09:56
 */
@interface TKRequestModel_GetAttrs : TKMRequestBase

/**
 *    @brief    需要获取属性key值的字符串数组（key：preference_letters、
 preference_reply、
 preference_reply_title、
 preference_receipt、
 smtpsavesend、
 auto_replay_status、
 auto_replay_content、
 auto_forward_status、
 auto_forward_addr、
 auto_forward_bakup、
 apam_level、
 apam_deal、
 virus_status、
 virus_sucess、
 virus_fail、
 virus_doubt、
 virus_notify_me、
 virus_notify_send、
 sms_notify、
 language、
 timezone、
 faces、
 readmailmode、
 createtime
 ）
 *
 *    Created by mac on 2014-11-24 09:55
 */
@property (nonatomic, strong)NSArray *getAttrsKeyArray;

@end

@class TKGetInitDataConfigUserAttrs;
/**
 *    @brief    获取邮件参数返回结构
 *
 *    Created by mac on 2014-11-24 09:57
 */
@interface TKResponseDModel_GetAttrs : TKMResponsedBase
@property (nonatomic, assign)NSInteger preference_letters;//    否    int    0/1    每页显示的邮件数
@property (nonatomic, assign)NSInteger preference_reply;//    否    int    0/1    回复时，是否加入原信1: 加入原邮件2:不加入原邮件
@property (nonatomic, copy)NSString *preference_reply_title;//    否    string    0/1    回复时显示的前缀1、Re:(推荐)2、>3、Reply:
@property (nonatomic, assign)NSInteger preference_receipt;//    否    int    0/1    对方要求发送已读回执处理方法0：提示我1：不发回执2：发送回执
@property (nonatomic, assign)NSInteger smtpsavesend;//    否    int    0/1    是否开启客户端发信保存1：开启，0不开启
@property (nonatomic, assign)NSInteger auto_forward_status;//    否    int    0/1    自动转发使用状态：1：使用，0：不使用
@property (nonatomic, copy)NSString *auto_forward_addr;    //否    string    280    自动转发的地址
@property (nonatomic, assign)NSInteger auto_forward_bakup;    //否    int    0/1    转发后，是否在本地保留备份1：保存，0：不保存
@property (nonatomic, assign)NSInteger auto_replay_status;//    否    int    0/1    自动回复使用状态：1：使用，0：不使用
@property (nonatomic, copy)NSString *auto_replay_content;//    否    string    4000    自动回复内容自动回复内容,支持HTML格式
@property (nonatomic, assign)NSInteger auto_replay_starttime;//    否        int    4        自动回复的开始时间使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换）
@property (nonatomic, assign)NSInteger auto_replay_endtime;//    否    int    4            自动回复的结束时间使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换）
@property (nonatomic, assign)NSInteger spam_level;//    否    int    0/1    反垃圾邮件等级：1、低级2、中级3、高级
@property (nonatomic, assign)NSInteger spam_deal;//    否    int    1/2    反垃圾邮件的处理方法1、转移到 “垃圾邮件” 文件夹（文件夹里的邮件会被定期自动删除）2、直接拒收
@property (nonatomic, assign)NSInteger virus_status;//    否    int    0/1    反病毒状态：1:对邮件杀毒0:对邮件不做检查
@property (nonatomic, assign)NSInteger virus_sucess;//    否    int    1/2/3    对病毒邮件，当杀毒成功时：1：清除病毒，标志成功杀毒2：原邮件不做处理，放入病毒文件夹3：直接删除
@property (nonatomic, assign)NSInteger virus_fail;//    否    int    1/2/3    对病毒邮件，当杀毒失败时：1:原邮件作为EML附件，发送到收件箱2:原邮件不做处理，放入：病毒文件夹3:直接删除
@property (nonatomic, assign)NSInteger virus_doubt;//    否    int    1/2/3    对病毒邮件，当无法判断是否病毒邮件时：1:原邮件作为EML附件，发送到收件箱2:原邮件不做处理，放入病毒文件夹3:直接删除
@property (nonatomic, assign)NSInteger virus_notify_me;//    否    int    0/1    是否设置邮件通知我：病毒邮件的处理结果1：是 0：否
@property (nonatomic, assign)NSInteger virus_notify_send;//    否    int    0/1    是否设置：邮件通知发件人：发出的邮件含有病毒，可能无法接收1：是 0：否
@property (nonatomic, assign)NSInteger sms_notify;//    否    int    0/1    是否开户邮件到达通知1:开通 0：不开通
@property (nonatomic, copy)NSString *language;//    否    string    5    使用的语言zh_CN，en_US格式
@property (nonatomic, copy)NSString *timezone;//    否    string    5    时区, 默认为+8
@property (nonatomic, copy)NSString *faces;//    否    string    60    风格，标志版本皮肤该字段暂时保留，
@property (nonatomic, assign)NSInteger readmailmode;//    否    2    0/1/2    邮件阅读方式0：标签阅读（默认）1：分栏阅读2：保留，后续扩展
@property (nonatomic, assign)NSInteger _custom_SmsNotify;//    否    1    0/1    是否开启邮件代收短信到达通知，前提是sms_notify为启用状态下设置才会生效。1表示开启0 表示关闭
@property (nonatomic, assign)BOOL custom_phone_permission;
@property (nonatomic, assign)BOOL custom_auto_forward_veritfy;


- (TKResponseDModel_GetAttrs *)initWithData:(NSDictionary *)dicData;
@end

@interface TKRequestModel_IsOpenLogData: TKMRequestBase

- (NSData *)getRequestData:(TKMContextModel*)context;

@end

@interface TKRequestModel_GetUserGuide: TKMRequestBase

/* userGuide **/
@property (nonatomic, strong) NSNumber * userGuide;

- (NSData *)getRequestData:(TKMContextModel*)context;

@end

@interface TKRequestModel_PostMailLogData: TKMRequestBase

@property(nonatomic, copy) NSString *BOUNDARY;

@property(nonatomic, strong) NSData *logData;
@property(nonatomic, copy) NSString *logDataName;

- (NSData *)getRequestData:(TKMContextModel*)context;

@end

@interface TKRequestModel_GetInitData: TKMRequestBase

- (NSData *)getRequestData;

@end

@interface TKRequestModel_GetComposeId: TKMRequestBase


@end

/**
 *    @brief    请求返回用户信息（文件夹及基本信息,基本配置信息）用于登录流程
 *
 *    Created by mac on 2014-11-19 14:55
 */
@interface TKRequestModel_GetInitDataConfig : TKMRequestBase

/**
 *    @brief    返回文件夹列表的类型：
 1.系统文件夹
 2.管理文件夹
 3.用户文件夹
 5.标签文件夹
 0.全部文件夹
 *
 *    Created by mac on 2014-11-19 14:56
 */
@property (nonatomic)NSInteger type;

/**
 *    @brief    文件夹密码，如果密码校验失败，则加密文件夹将不返回给用户
 *
 *    Created by mac on 2014-11-19 14:56
 */
@property (nonatomic, copy)NSString *folderPass;

@end

@class TKGetInitDataConfigFolderList;
@class TKGetInitDataConfigUserConfig;
@class TKGetInitDataConfigSignList;
@class TKGetInitDataConfigPOPList;
@class TKGetInitDataConfigMessageInfo;
@class TKGetInitDataConfigUserAttrs;
@interface TKResponsedModel_GetInitDataConfig : TKMResponsedBase
@property (nonatomic, copy)NSString *result;//    是    array        通用返回结果的数组单指令调用时返回值无意义
@property (nonatomic)NSInteger passFlag;//    否    int    1    是否开通了文件夹加密功能1：已经开户文件夹加密功能，并且密码校验成功0：没能开通文件夹加密功能2：已开通文件夹加密功能，密码校验失败
@property (nonatomic)NSInteger totalStarCount    ;//是    int    4    星标邮件总数
@property (nonatomic)NSInteger unreadStarCount;//    是    int    4    未读星标邮件总数
@property (nonatomic, strong)TKGetInitDataConfigUserAttrs *userAttrs;//    是    object        详见用户属性对象(userAttrs)
@property (nonatomic, strong)TKGetInitDataConfigMessageInfo *messageInfo;//    是    object        详见邮箱信息对象(messageInfo)
@property (nonatomic, strong)TKGetInitDataConfigSignList *signList;//    是    object        详见用户签名对象(signList object)
@property (nonatomic, strong)TKGetInitDataConfigPOPList *popList;//    是    object        详见代收列表对象(popList object)
@property (nonatomic, strong)TKGetInitDataConfigFolderList *folderList;//    是    object        详见文件夹对象（folder object）
@property (nonatomic, strong)TKGetInitDataConfigUserConfig *userConfig;//    是    object        详见用户属性对象(userConfig object)

- (TKResponsedModel_GetInitDataConfig *)initWithData:(NSDictionary *)dataDict;
@end

@interface TKGetInitDataConfigUserAttrs : NSObject
@property (nonatomic, copy)NSString *uid;//邮箱账号
@property (nonatomic, copy)NSString *trueName;//真实姓名
@property (nonatomic, assign)NSInteger replyWithQuote;//回复时是否加入原信0不
@property (nonatomic, assign)NSInteger defaultPageSize;//每页显示的邮件数
@property (nonatomic, assign)NSInteger replyPrefix;//回复时显示的标题 0不
@property (nonatomic, assign)NSInteger promptForReceipt;//回执处理方式
@property (nonatomic, assign)NSInteger isShowSize;//是否显示邮件大小  0不显示，1显示
@property (nonatomic, assign)NSInteger isShowContent;//是否显示正文摘要，0不显示 1显示
@property (nonatomic, assign)NSInteger fts_flag;//是否开启全文检索 0否
@property (nonatomic, assign)NSInteger userCosId;//用户角色id
@property (nonatomic, assign)NSInteger sessionMode;//是否开启会话模式0否
@property (nonatomic, assign)NSInteger unallow_pop3_delete_mail;//1:不允许pop3删除邮件; 0: 允许删除
@property (nonatomic, assign)NSInteger unallow_pop3_change_mail_state;//1:不允许pop把未读邮件状态变为已读状态; 0: 允许
@property (nonatomic, assign)NSInteger custom_auto_forward_veritfy;//10已认证，1未认证， 没有这项配置时默认为已认证
@property (nonatomic, assign)NSInteger custom_phone_permission;//0-手机端不可访问，1-手机端可以访问。默认为1。

- (TKGetInitDataConfigUserAttrs *)initWithData:(NSDictionary *)dataDict;
@end

@interface TKGetInitDataConfigMessageInfo : NSObject
@property (nonatomic, assign)NSInteger limitMessageSize;    //int    4        邮箱容量 大小KB
@property (nonatomic, assign)NSInteger messageSize;    //int    4        邮件已使用大小KB
@property (nonatomic, assign)NSInteger messageCount;    //int    4        当前邮件数量
@property (nonatomic, assign)NSInteger unreadMessageCount;    //int    4        未读邮件数量
@end

@interface TKGetInitDataConfigSignList : NSObject
@property (nonatomic, assign)NSInteger id;     //int    4        签名id
@property (nonatomic, assign)NSInteger title;    //int    64        签名标题
@property (nonatomic, assign)NSInteger type;    //int    2        签名的类型0：不限制 1：写新邮件时出现 2：回复邮件时出现 3：转发邮件时出现
@property (nonatomic, assign)NSInteger isHtml;    //int    4        是否是HTML格式 1.是 0.不是
@property (nonatomic, assign)NSInteger isDefault;    //int    1    0、1    是否默认签名：1：是，0不是
@property (nonatomic, assign)NSInteger isAutoDate;    //int    1    0、1    否自动加入写信日期：1：是，0不是
@property (nonatomic, assign)NSInteger isSMTP;    //int    1    0、1    是否支持在SMTP信件中追加签名：1：是； 0：不支持
@property (nonatomic, copy)NSString *content;    //string    2    65535    签名的内容
@end

@interface TKGetInitDataConfigPOPList : NSObject
@property (nonatomic, assign)NSInteger popId;    //int    4        代收邮箱的id
@property (nonatomic, copy)NSString *email;    //string    64        代收邮箱地址
@property (nonatomic, assign)NSInteger fid;    //int    2        代收邮件存放到指定的文件夹id
@property (nonatomic, assign)NSInteger location;    /*int    4        文件夹位置，主要用于排序，本接口返回的文件夹列表数据必须按照location进行正序排序。
                                                     系统: 1-4999；
                                                     管理: 5000-9999
                                                     用户: 10000-29999
                                                     标签: 30000-49999*/
@end

@interface TKGetInitDataConfigFolderList : NSObject

@end

@interface TKGetInitDataConfigUserConfig : NSObject

@property (nonatomic, copy)NSString *auto_replay_content;    //否    string        自动回复内容
@property (nonatomic, assign)NSInteger preference_letters;    //否    int    0/1    每页显示的邮件数
@property (nonatomic, assign)NSInteger preference_reply;    //否    int    0/1    回复时，是否加入原信1: 加入原邮件2:不加入原邮件
@property (nonatomic, copy)NSString *preference_reply_title;    //否    string    0/1    回复时显示的前缀1、Re:(推荐)2、>3、Reply:
@property (nonatomic, assign)NSInteger preference_receipt;    //否    int    0/1    对方要求发送已读回执处理方法0：提示我1：不发回执2：发送回执
@property (nonatomic, assign)NSInteger smtpsavesend;    //否    int    0/1    是否开启客户端发信保存1：开启，0不开启
@property (nonatomic, assign)NSInteger auto_forward_status;    //否    int    0/1    自动转发使用状态：1：使用，0：不使用
@property (nonatomic, copy)NSString *auto_forward_addr;    //否    string    280    自动转发的地址
@property (nonatomic, assign)NSInteger auto_forward_bakup;    //否    int    0/1    转发后，是否在本地保留备份1：保存，0：不保存
@property (nonatomic, assign)NSInteger auto_replay_status;    //否    int    0/1    自动回复使用状态：1：使用，0：不使用

@property (nonatomic, assign)NSInteger auto_replay_starttime;        //否        int    4        自动回复的开始时间使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换）
@property (nonatomic, assign)NSInteger auto_replay_endttime;    //否    int    4            自动回复的结束时间使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换）
@property (nonatomic, assign)NSInteger spam_level;    //否    int    0/1    反垃圾邮件等级：1、低级2、中级3、高级
@property (nonatomic, assign)NSInteger spam_deal;    //否    int    1/2    反垃圾邮件的处理方法1、转移到 “垃圾邮件” 文件夹（文件夹里的邮件会被定期自动删除）2、直接拒收
@property (nonatomic, assign)NSInteger virus_status;    //否    int    0/1    反病毒状态：1:对邮件杀毒0:对邮件不做检查
@property (nonatomic, assign)NSInteger virus_sucess;    //否    int    1/2/3    对病毒邮件，当杀毒成功时：1：清除病毒，标志成功杀毒2：原邮件不做处理，放入病毒文件夹3：直接删除
@property (nonatomic, assign)NSInteger virus_fail;//否    int    1/2/3    对病毒邮件，当杀毒失败时：1:原邮件作为EML附件，发送到收件箱2:原邮件不做处理，放入：病毒文件夹3:直接删除
@property (nonatomic, assign)NSInteger virus_doubt;    //否    int    1/2/3    对病毒邮件，当无法判断是否病毒邮件时：1:原邮件作为EML附件，发送到收件箱2:原邮件不做处理，放入病毒文件夹3:直接删除
@property (nonatomic, assign)NSInteger virus_notify_me;//    否    int    0/1    是否设置邮件通知我：病毒邮件的处理结果1：是 0：否
@property (nonatomic, assign)NSInteger virus_notify_send;//    否    int    0/1    是否设置：邮件通知发件人：发出的邮件含有病毒，可能无法接收1：是 0：否
@property (nonatomic, assign)NSInteger sms_notify;//    否    int    0/1    是否开户邮件到达通知1:开通 0：不开通
@property (nonatomic, copy)NSString *language;//    否    string    5    使用的语言zh_CN，en_US格式
@property (nonatomic, copy)NSString *timezone;//    否    string    5    时区, 默认为+8
@property (nonatomic, copy)NSString *faces;//    否    string    60    风格，标志版本皮肤该字段暂时保留，
@property (nonatomic, assign)NSInteger readmailmode;//    否    2    0/1/2    邮件阅读方式0：标签阅读（默认）1：分栏阅读2：保留，后续扩展
@property (nonatomic, assign)NSInteger custom_SmsNotify;//    否    1    0/1    是否开启邮件代收短信到达通知，前提是sms_notify为启用状态下设置才会生效。1表示开启0 表示关闭
@end


@interface TKRequestModel_SetSessionMode : TKMRequestBase
@property (nonatomic)BOOL flag;
@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    //11.1.1    接口功能
 模块ID:  mbox:getAllFolders
 *
 *    Created by gao on 2014-04-17 16:05
 */
@interface TKRequestModel_GetAllFolders : TKMRequestBase

/**
 *    @brief    int    1    返回文件夹列表的类型：
 1.系统文件夹
 2.管理文件夹
 3.用户文件夹
 5.标签文件夹
 0.全部文件夹
 *
 *    Created by gao on 2014-04-17 16:05
 */
@property (nonatomic, assign) NSInteger type;

/**
 *    @brief    0/1表示使用旧的统计接口(Ｖ1.5.12前) 2 表示要用新的统计接口(Ｖ1.5.12)
 *
 *    Created by gao on 2014-04-17 16:06
 */
@property (nonatomic, assign) NSInteger stats;

/**
 *    @brief    string    16    文件夹密码，如果密码校验失败，则加密文件夹将不返回给用户
 *
 *    Created by gao on 2014-04-17 16:06
 */
@property (nonatomic, strong) NSString* folderPass;


@end


//返回数据
@interface TKResponseDModel_GetAllFolders : TKMResponsedBase

/**
 *    @brief    是否开通了文件夹加密功能
 1：已经开户文件夹加密功能，并且密码校验成功
 0：没能开通文件夹加密功能
 2：已开通文件夹加密功能，密码校验失败
 *
 *    Created by gao on 2014-04-17 16:15
 */
@property (nonatomic, assign) NSInteger       passFlag;

/**
 *    @brief    星标邮件总数
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       totalStarCount;

/**
 *    @brief    未读星标邮件总数
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       unreadStarCount;

/**
 *    @brief    任务邮件总数 v1.4.5
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       totalTaskCount;

/**
 *    @brief    待办任务邮件数v1.4.5
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       todoTaskCount;

/**
 *    @brief    总帐单邮件 V1.5.12
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       totalBillCount;

/**
 *    @brief    未读帐单邮件 V1.5.12
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       unreadBillCount;

/**
 *    @brief    总订阅邮件 V1.5.12
 *
 *    Created by gao on 2014-04-17 16:16
 */
@property (nonatomic, assign) NSInteger       totalSubscriptionCount;

/**
 *    @brief    未读订阅邮件 V1.5.12
 *
 *    Created by gao on 2014-04-17 16:17
 */
@property (nonatomic, assign) NSInteger       unreadSubscriptionCount;

/**
 *    @brief    TKResponseDModel_FolderData 文件夹对象数组(folder object)
 *
 *    Created by gao on 2014-04-17 16:17
 */
@property (nonatomic, strong) NSMutableArray* arrVar;


+(TKResponseDModel_GetAllFolders*)parseResponseData:(NSDictionary*)dict;
@end



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    11.2    新建文件夹
 11.2.1    接口功能
 请求新建文件夹操作
 模块ID:  mbox: createUserFolder
 *
 *    Created by gao on 2014-04-18 10:32
 */

@interface TKRequestModel_MBoxCreateUserFolder : TKMRequestBase

/**
 *    @brief    是    string    64    文件夹名称，应避免文件夹名称重复
 *
 *    Created by gao on 2014-04-18 10:34
 */
@property (nonatomic, strong)  NSString* name;

/**
 *    @brief  是    int    1    1.系统文件夹
 2.管理文件夹
 3.用户文件夹
 5.标签文件夹
 6.代收文件夹，文件夹不能删除
 *
 *    Created by gao on 2014-04-18 10:34
 */
@property (nonatomic, assign)  NSInteger type;


/**
 *    @brief    是    int    2    父文件夹ID，为0创建到根目录
 *
 *    Created by gao on 2014-04-18 10:35
 */
@property (nonatomic, assign)  NSInteger parentId;

/**
 *    @brief    是    int    1    能否被pop3收取
 *
 *    Created by gao on 2014-04-18 10:35
 */
@property (nonatomic, assign)  NSInteger pop3Flag ;


/**
 *    @brief    是    int    0/1    是否设置文件夹密码 注：如果设置为1，则前提是用户已经开通了文件夹密码功能，否则设置自动失效
 *
 *    Created by gao on 2014-04-18 10:35
 */
@property (nonatomic, assign)  NSInteger folderPassFlag;

/**
 *    @brief        否    int    1    保留值
 *
 *    Created by gao on 2014-04-18 10:35
 */
@property (nonatomic, assign)  NSInteger reserve;

/**
 *    @brief    是    int    2    文件夹位置
 系统：（1－4999）
 管理：（5000－9999）
 用户：（10000－29999）
 标签：（30000-49999）
 *
 *    Created by gao on 2014-04-18 10:36
 */
@property (nonatomic, assign)  NSInteger location;

/**
 *    @brief        否    int    1    标签的颜色值，新建标签时有用
 *
 *    Created by gao on 2014-04-18 10:39
 */
@property (nonatomic, assign) NSInteger  folderColor;

@end

@interface TKResponsedModel_MBoxCreateUserFolder : TKMResponsedBase
/**
 *    @brief    新建文件夹id  出错时该值不返回
 *
 *    Created by gao on 2014-04-17 16:48
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponsedModel_MBoxCreateUserFolder*)parseResponseData:(NSDictionary*)dict;
@end



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    11.3    删除文件夹
 11.3.1    接口功能
 请求删除文件夹操作
 模块ID:  mbox: deleteFolders
 *
 *    Created by gao on 2014-04-18 10:32
 */

@interface TKRequestModel_MBoxDeleteFolders : TKMRequestBase


/**
 *    @brief        否    string    16    加密文件夹的密码
 *
 *    Created by gao on 2014-04-18 11:11
 */
@property (nonatomic, strong) NSString*  folderPass;
/**
 *    @brief        是    int    2    文件夹id
 *
 *    Created by gao on 2014-04-18 11:11
 */
@property (nonatomic, assign) NSInteger  fid;

/**
 *    @brief        是    int    2    表示如果文件夹里面有邮件，自动转移到这个文件夹下面; 该值如果为空，或者跟fid一样，则表示不转移，按原有流程进行删除文件夹。
 *
 *    Created by gao on 2014-04-18 11:12
 */
@property (nonatomic, assign) NSInteger  moveToFid;

/**
 *    @brief        是    int    1    文件夹类型3：用户文件夹 5：标签文件夹  当type=5时表示删除标签，删除标签时需要清理掉该标签所有关联的信息。 (1)删除标签的同时，需要找到引用标签的所有邮件移除相应的标签。 (2) 移除标签可调用mbox:updateMessagesAll (type=deleteLabel)内部接口实现。 (3) 删除标签后，需要自动禁用（或删除）含有这个标签的过滤器。
 *
 *    Created by gao on 2014-04-18 11:12
 */
@property (nonatomic, assign) NSInteger  type;

@end

@interface TKResponsedModel_MBoxDeleteFolders : TKMResponsedBase

/**
 *    @brief        是    array        通用返回结果的数组
 单指令调用时返回值无意义
 *
 *    Created by gao on 2014-04-18 11:14
 */
@property (nonatomic, strong) NSMutableArray*  resultArr;
/**
 *    @brief    否    array    --    出错时返回，数组类型。 与请求中的items数组对应，表示items中每一项操作的结果。 0表示成功，其它表示失败
 *
 *    Created by gao on 2014-04-18 11:14
 */
@property (nonatomic, strong) NSMutableArray* varArr;

+(TKResponsedModel_MBoxDeleteFolders*)parseResponseData:(NSDictionary*)dict;

@end



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    11.4    修改文件夹信息
 11.4.1    接口功能
 请求修改文件夹信息
 模块ID:  mbox: updateFolders
 *
 *    Created by gao on 2014-04-18 10:32
 */

@interface TKRequestModel_MBoxUpdateFolders : TKMRequestBase

/**
 *    @brief        是    array   文件夹id数组，目前仅支持下面的参数type=4,5,6,7时，才支持多个fid的array元素批量操作，其他的只支持一个int的元素（就算传array也只会接受第一个）
 *
 *    Created by gao on 2014-04-18 11:29
 */
@property (nonatomic, strong) NSMutableArray*  fid;
/**
 *    @brief        是    int    1    表示是否隐藏; 1隐藏 0不隐藏
 *
 *    Created by gao on 2014-04-18 11:29
 */
@property (nonatomic, assign) NSInteger  hideFlag;

/**
 *    @brief        是    int    1     1:修改文件夹名称
 2:修改文件夹位置
 3:修改文件夹父节点
 4:修改是否可pop
 5:修改标签的颜色值
 6.修改自销毁有效日期
 7:设置文件夹是否隐藏
 *
 *    Created by gao on 2014-04-18 11:30
 */
@property (nonatomic, assign) NSInteger  type;

/**
 *    @brief        否    int    2    父文件夹id，为0表示根节点
 *
 *    Created by gao on 2014-04-18 11:30
 */
@property (nonatomic, assign) NSInteger  parentId;

/**
 *    @brief        否    string    64    文件夹名称
 *
 *    Created by gao on 2014-04-18 11:30
 */
@property (nonatomic, strong) NSString*  name;

/**
 *    @brief        否    string    16    文件夹密码
 修改加密文件夹名称时，必须传递
 *
 *    Created by gao on 2014-04-18 11:30
 */
@property (nonatomic, strong) NSString* folderPass;

/**
 *    @brief    否    int    2    1-49999修改文件夹位置
 系统：（1－4999）
 管理：（5000－9999）
 用户：（10000－29999）
 标签：（30000-49999）
 *
 *    Created by gao on 2014-04-18 11:31
 */
@property (nonatomic, assign) NSInteger  location;

/**
 *    @brief        否    int    1    0表示不能pop收取，1为可pop收取
 *
 *    Created by gao on 2014-04-18 11:31
 */
@property (nonatomic, assign) NSInteger pop3Flag;

/**
 *    @brief        否    int    1    标签的颜色值
 *
 *    Created by gao on 2014-04-18 11:31
 */
@property (nonatomic, assign) NSInteger  folderColor;

/**
 *    @brief        否    int    1    自销毁功能的自动清理日期，以天为单位，必须是大于0的值。设置自动清理时间后，每次登录将会扫描这些文件夹，删除超过清理时间的邮件。文件夹的自动清理和单封邮件的自销毁需要采用相同的机制处理。如果为0表示不销毁。
 *
 *    Created by gao on 2014-04-18 11:31
 */

@property (nonatomic, assign) NSInteger keepPeriod;

@end

@interface TKResponsedModel_MBoxUpdateFolders : TKMResponsedBase

/************
 *    @brief        是    array        通用返回结果的数组
 单指令调用时返回值无意义
 *
 *    Created by gao on 2014-04-18 11:14
 */
@property (nonatomic, strong) NSMutableArray*  resultArr;
/**
 *    @brief    否    array    --    文件夹id && 文件夹父id  仅当修改文件夹父节点时才返回
 *
 *    Created by gao on 2014-04-18 11:14
 */
@property (nonatomic, strong) NSMutableArray* varArr;

+(TKResponsedModel_MBoxUpdateFolders*)parseResponseData:(NSDictionary*)dict;

@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************
 *    @brief
 * 客户端数据获取接口
 * 统计
 *    用户启动次数请求
 *    模块ID:  data?func=client: statistics
 *
 *    Created by gao on 2016-04-21 13:19
 */

typedef NS_ENUM(NSInteger, DataFromClientType) {
    DataFromClientTypeStart = 0,
    DataFromClientTypeSendMail,
    DataFromClientTypeReceiverMail,
    DataFromClientTypeAddress,
    DataFromClientTypeCalendar,
    DataFromClientTypeDrive,
    DataFromClientTypeCalendarCreateActivities,
    DataFromClientTypeDriveSaveFiles,
    DataFromClientTypeDriveUploadFiles,
    DataFromClientTypeDriveFilesSend,
};

@interface TKRequestModel_DataFromClient : TKMRequestBase

@property (nonatomic, copy) NSString *  userId;//用户ID:

@property (nonatomic, assign) DataFromClientType dataType;//上报类型:

-(NSData*)getRequestData:(TKMContextModel*)context;

@end



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************
 *    @brief
 *  12.1    用户邮件列表
 *    12.1.1    接口功能
 *    请求返回邮件索引信息
 *    模块ID:  mbox:listMessages
 *
 *    Created by gao on 2014-04-17 15:12
 */
@interface TKRequestModel_MBoxListMessage : TKMRequestBase


/**
 *    @brief     //sendDate: 按发送日期, receiveDate:按接收日期, from: 按发件人, to: 按收件人, size: 按大小, subject:  按主题 默认按接收日期
 *
 *    Created by gao on 2014-04-17 15:02
 */
@property (nonatomic, strong)    NSString*  order;//排序字段:

/**
 *    @brief    //是否逆序排列，desc=1时表示按逆序，desc=0表示正序，此规则对所有排序字段生效，默认为1
 *
 *    Created by gao on 2014-04-17 15:04
 */
@property (nonatomic, assign)  NSInteger desc;

/**
 *    @brief 0普通列表模式  1会话列表模式＋聚合模式 2普通列表模式＋聚合模式
 *
 *    Created by gao on 2014-04-17 15:04
 */
@property (nonatomic, assign)  NSInteger sessionEnable;

/**
 *    @brief     //文件夹id
 *
 *    Created by gao on 2014-04-17 15:05
 */
@property (nonatomic, assign)  NSInteger fid;

/**
 *    @brief    //从第几条记录开始读取，从1开始
 *
 *    Created by gao on 2014-04-17 15:05
 */
@property (nonatomic, assign)  NSInteger start;

/**
 *    @brief    //取的条数（如果不够条数，则返回实条数）合法值为1-200
 *
 *    Created by gao on 2014-04-17 15:05
 */
@property (nonatomic, assign)  NSInteger total;

/**
 *    @brief    否    string        要求返回的字段，mid是固定要返回的字段，其他都可选。企邮手机邮箱需求。如要求只返回mid和flags/字段则为:mid,flags 用逗号分隔
 *
 *    Created by gao on 2014-04-17 16:23
 */
@property (nonatomic, strong) NSString*        filterFields;


@property (nonatomic)BOOL isVip;

@end

/**
 *    @brief  用户邮件列表 返回数据 模块ID:  mbox:listMessages
 *    Created by gao on 2014-04-17 15:06
 */
@interface TKResponseModel_MBoxListMessage : TKMResponsedBase

@property (nonatomic, assign) NSInteger       time;

/**
 *    @brief 本文件夹下的会话邮件数量。 特别注明: 只有开通会话，按照会话模式显示时，这个会话数量才有效。
 *
 *    Created by gao on 2014-04-17 15:36
 */
@property (nonatomic, assign) NSInteger       sessionCount;

/**
 *    @brief      array of TKResponseModel_MessageData
 *
 *    Created by gao on 2014-04-17 15:37
 */
@property (nonatomic, strong) NSMutableArray* arrVar;
+(TKResponseModel_MBoxListMessage*)parseResponseData:(NSDictionary*)dict;

@end



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief     12.11       邮件查询
 12.11.1    接口功能
 邮件搜索功能实现
 模块ID:  mbox:searchMessages
 *
 *  邮件搜索请求数据接口。
 *
 *    Created by gao on 2014-04-17 16:17
 */
@interface TKRequestModel_MBoxSearchMessages : TKMRequestBase

@property (nonatomic,assign) BOOL isTopPullRefresh;

/**
 *    @brief    否    string    16    文件夹密码，如果密码校验失败，则加密文件夹的搜索结果将不返回给用户
 *
 *    Created by gao on 2014-04-17 16:22
 */
@property (nonatomic, strong) NSString*       folderPass;

/**
 *    @brief    否    int    2    邮件文件夹的id 为0搜索所有文件夹, 如果没通过密码验证，fid=0是不搜索加锁文件夹的，通过验证后则会搜索加锁文件夹。
 *
 *    Created by gao on 2014-04-17 16:22
 */
@property (nonatomic, assign) NSInteger       fid;

/**
 *    @brief    //    否    array        Int类型的数组，可以传递多个标签id。传递此参数时，可以支持按邮件标签搜索邮件。报文示例，标签之间是 or 的关系
 <array name=”label”>
 <int>1</int>
 <int>1</int>
 </array>
 *
 *    Created by gao on 2014-04-17 16:22
 */
@property (nonatomic, strong) NSMutableArray*       labelArr;

/**
 *    @brief    否    int    1    0、不高亮命中搜索关键字 1、高亮命中搜索关键字 默认不传为1
 *
 *    Created by gao on 2014-04-17 16:23
 */
@property (nonatomic, assign) NSInteger       highLight;

/**
 *    @brief    否    string        要求返回的字段，mid是固定要返回的字段，其他都可选。企邮手机邮箱需求。如要求只返回mid和flags/字段则为:mid,flags 用逗号分隔
 *
 *    Created by gao on 2014-04-17 16:23
 */
@property (nonatomic, strong) NSString*        filterFields;

/**
 期望过滤掉指定文件夹邮件
 */
@property (nonatomic, strong) NSArray*        exceptFids;

/**
 *    @brief        否    string        排序字段，可选值为：
 date: 按日期 (发送日期)
 receivedDate:按接收日期
 from: 按发件人
 to: 按收件人
 size: 按大小
 subject:按主题
 *
 *    Created by gao on 2014-04-17 16:23
 */
@property (nonatomic, strong) NSString*       order;

/**
 *    @brief    否    int    0/1    是否降序 1: 降序 0: 升序
 *
 *    Created by gao on 2014-04-17 16:24
 */
@property (nonatomic, assign) NSInteger       desc;

/**
 *    @brief    否    int    0/1    是否进行二次排序
 *
 *    Created by gao on 2014-04-17 16:24
 */
@property (nonatomic, assign) NSInteger       secondOrder;

/**
 *    @brief    否    string    16    二次排序的字段
 1(unread)、未读置前
 2(hasAttach)、有附件置前
 3(replied)、已回复置前
 4(forwarded)、已转发置前
 5(voice)、语音邮件置前
 6(fax)、传真邮件置前
 7(recall)、已召回置前
 *
 *    Created by gao on 2014-04-17 16:24
 */
@property (nonatomic, strong) NSString*       secondOrderField;

/**
 *    @brief    否            邮件列表中的邮件起始序号，邮件序号从1开始(int32的十进制格式)。
 *
 *    Created by gao on 2014-04-17 16:24
 */
@property (nonatomic, assign) NSInteger       start;

/**
 *    @brief    否    int    2    每页显示邮件的数量，默认为20
 *
 *    Created by gao on 2014-04-17 16:25
 */
@property (nonatomic, assign) NSInteger       total;

/**
 *    @brief    否    int    1    1 新的搜索条件 0 已经处于搜索状态，将从上次搜索结果集中查询指定记录。 此时，搜索条件字段将无效
 *
 *    Created by gao on 2014-04-17 16:25
 */
@property (nonatomic, assign) NSInteger       isSearch;

/**
 *    @brief    是    int    0/1    是否递归处理子文件夹 默认不处理子文件夹
 *
 *    Created by gao on 2014-04-17 16:25
 */
@property (nonatomic, assign) NSInteger       recursive;


/**
 *    @brief 否 条件对象(condiction object)数组 可以搜索信头中的任意字段，支持多个条件进行组合以满足扩展性要求。 具体参见下文condiction对象说明
 *
 *    Created by Mark on 2014-04-17 14:17
 */
@property (nonatomic, strong) NSMutableArray*       condictionsArr;

/**
 *    @brief    @brief 否 条件对象(condiction object)数组 可以搜索信头中的任意字段，支持多个条件进行组合以满足扩展性要求。 具体参见下文condiction对象说明
 *
 *    Created by mac on 2014-08-25 09:55
 */
@property (nonatomic, strong) NSMutableArray*       flagCondictionsArr;


/**
 *    @brief 否 检测flags object指定的属性是否存在 值为1表示有该标记，为0表示没有该标记
 *
 *    Created by Mark on 2014-04-17 14:15
 */

@property (nonatomic, strong) TKRequestModel_flagsObject*       flagObject;

/**
 *    @brief    否    int    0,10-255    0为默认，（1-9为系统内部保留不可用），10-255 各种账单类型邮件
 *
 *    Created by gao on 2014-04-17 16:26
 */
@property (nonatomic, assign) NSInteger       billType;

/**
 *    @brief    是    int    0/1/2    0表示高级搜索（精确，多个搜索条件是AND关系）
 1表示全文检索（模糊，多个搜索条件是OR关系）
 2表示模糊搜索（供未开通全文检索功能的用户调用的搜索接口，多搜索条件是OR关系）
 *
 *    Created by gao on 2014-04-17 16:26
 */
@property (nonatomic, assign) NSInteger       isFullSearch;

/**
 *    @brief    否    int    0/1    0: 忽略大小写，缺省为忽略。1: 不忽略大小写
 *
 *    Created by gao on 2014-04-17 16:26
 */
@property (nonatomic, assign) NSInteger       ignoreCase;

/**
 *    @brief    否    int    0/1    0:表示不返回逼近式搜索的统计信息 1:返回逼近式搜索的统计信息
 *
 *    Created by gao on 2014-04-17 16:26
 */
@property (nonatomic, assign) NSInteger       statType;

@property (nonatomic, assign) NSInteger limit;

@property (nonatomic, strong) TKRequestModel_SearchApproachSearch *approachSearch;

@property (nonatomic)BOOL isVip;
@property (nonatomic)BOOL sessionEnable;


/**
 *    @brief    是否获取所有信息，默认为NO， 如果是YES，查询到的邮件列表信息会匹配数据库，把没有的邮件请求getMessageInfo 接口获取所有信息
 *
 *    Created by mac on 2014-06-18 10:18
 */
@property (nonatomic)BOOL isAll;

@property (nonatomic)BOOL isUnreadMail;//收索未读邮件

@end

/**
 *  邮件搜索返回数据结构。
 */
@interface TKResponsedModel_MBoxSearchMessages : TKMResponsedBase
/**
 *    @brief    所有邮件大小(字节)
 *
 *    Created by gao on 2014-04-17 16:26
 */
@property (nonatomic, assign) NSInteger       messageCount;

/**
 *    @brief    //新邮件数量
 *
 *    Created by gao on 2014-04-17 16:27
 */
@property (nonatomic, assign) NSInteger       unreadMessageCount;

/**
 *    @brief    TKResponseModel_MessageData
 *
 *    Created by gao on 2014-04-17 16:27
 */
@property (nonatomic, strong) NSMutableArray* arrVar;

/**
 *    @brief    是否完成获取邮件所有字段信息
 *
 *    Created by mac on 2014-06-20 15:44
 */
@property (nonatomic)BOOL isAll;

/**
 *    @brief    新添加到本地的邮件id列表
 *
 *    Created by mac on 2014-06-20 15:45
 */
@property (nonatomic, strong) NSMutableArray* m_newMailIdArr;



+(TKResponsedModel_MBoxSearchMessages *)parseResponseData:(NSDictionary*)dict;
+ (NSMutableArray *)parseResponseUsefulData:(NSDictionary*)dict;

@end






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief     12.13.1    接口功能 邮件内容查询
 模块ID:  mbox:readMessage
 *
 *    Created by gao on 2014-04-17 16:45
 */
@interface TKRequestModel_MBoxReadMessage : TKMRequestBase

/**
 *    @brief    //阅读正文的方式:
 没有此参数 - 不返回正文part的content属性的内容
 "text"   只返回text的content值
 "html"  返回html的content的值，如果没有html则返回text的content值
 "both"   text,html的content的值都返回
 "rmhtml"  返回魔法邮件html的content的值，如果没有则返回普通html
 "rmboth"   text,rmhtml的content的值都返回
 "mobile" 表示是手机版访问，有特殊多模板的账单邮件，在无法适配UA的情况下，优先返回手机模板内容。
 另: html part的content属性返回
 的内容将经过filter过滤
 *
 *    Created by gao on 2014-04-17 16:29
 */
@property (nonatomic, strong) NSString*       mode;

/**
 *    @brief    是否过滤Style块，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       filterStylesheets;

/**
 *    @brief    是否过滤Image，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       filterImages;

/**
 *    @brief    是否过滤Link，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       filterLinks;

@property (nonatomic, assign) NSInteger       supportTNEF;

/**
 *    @brief    是否过滤脚本，缺省为过滤普通邮件，不过滤运营邮件
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       fileterScripts;

/**
 *    @brief    是否过滤｀，缺省为过滤
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       filterFrames;

/**
 *    @brief    是否过滤Object，缺省为过滤
 *
 *    Created by gao on 2014-04-17 16:30
 */
@property (nonatomic, assign) NSInteger       filterObjects;

/**
 *    @brief    是否置已读标记, 缺省1(已读，包括全部将会话里的所有其他邮件设置为已读）, 0(不设置）， 2（只针对单封邮件设置已读，会话邮件里只会对第一封设置已读）
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, assign) NSInteger       markRead;

/**
 *    @brief    邮件id
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, strong) NSString*       mid;

/**
 *    @brief    当前邮件所在的文件夹id 为0表示搜索
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, assign) NSInteger       fid;

/**
 *    @brief    是否返回headerRaw 缺省为 0, 不返回
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, assign) NSInteger       header;

@end


/**
 *  返回的数据
 *
 */
@interface TKResponsedModel_MBoxReadMessage : TKMResponsedBase
/**
 *    @brief    / TKResponseModel_MessageData  返回邮件内容对象 (MIME message info Object)
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, strong) TKResponsedModel_MessageInfo* mesageObj;


+(TKResponsedModel_MBoxReadMessage *)parseResponseData:(NSDictionary*)dict;

//未读邮件
+ (TKResponsedModel_MBoxReadMessage *)unReadParaersData:(NSDictionary *)dict;
@end


@interface TKResponsedModel_MBoxUnReadMessage : TKMResponsedBase
/**
 *    @brief    / TKResponseModel_MessageData  返回邮件内容对象 (MIME message info Object)
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, strong) NSMutableArray * unReadMails;
@property (nonatomic, strong) NSDictionary * unReadstats;
//未读邮件
+ (TKResponsedModel_MBoxUnReadMessage *)unReadParaersData:(NSDictionary *)dict;
@end


#pragma mark - 恢复草稿请求及返回数据结构

/**
 *    @brief    请求数据结构
 *
 *    Created by mac on 2015-04-13 18:02
 */
@interface TKRequestModel_MBoxRestoreDraft : TKMRequestBase
@property (nonatomic, copy)NSString *mid;
@end

/**
 *  返回的数据
 *
 */
@interface TKResponsedModel_MBoxRestoreDraft : TKMResponsedBase
/**
 *    @brief    / TKResponseModel_MessageData  返回邮件内容对象 (MIME message info Object)
 *
 *    Created by gao on 2014-04-17 16:31
 */
@property (nonatomic, strong) TKResponsedModel_MessageInfo* mesageObj;
+(TKResponsedModel_MBoxRestoreDraft *)parseResponseData:(NSDictionary*)dict;
@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief        12.2    获取邮件索引信息
 12.2.1    接口功能
 请求返回指定邮件mid的索引信息
 模块ID:  mbox:getMessageInfo
 *    Created by gao on 2014-04-17 16:45
 */
@interface TKRequestModel_MBoxGetMessageInfo : TKMRequestBase


/**
 *    @brief    //Mid数组
 *
 *    Created by gao on 2014-04-17 16:46
 */
@property (nonatomic, strong) NSMutableArray *arrMids;

/**
 *    @brief    //Mid数组
 *
 *    Created by gao on 2014-04-17 16:46
 */
@property (nonatomic, strong) NSMutableArray *filterFields;

@end

@interface TKResponseModel_MBoxGetMessageInfo : TKMResponsedBase
/**
 *    @brief    本文件夹下的会话邮件数量。 特别注明: 只有开通会话，按照会话模式显示时，这个会话数量才有效。
 *
 *    Created by gao on 2014-04-17 16:47
 */
@property (nonatomic, assign) NSInteger       sessionCount;

/**
 *    @brief    TKResponseModel_MessageData
 *
 *    Created by gao on 2014-04-17 16:47
 */
@property (nonatomic, strong) NSMutableArray* arrVar;

+(TKResponseModel_MBoxGetMessageInfo*)parseResponseData:(NSDictionary*)dict;
@end



@interface TKResponsedModel_CutUpgradeState : TKMResponsedBase

@property (nonatomic, assign) NSInteger status;//0: 系统正常 1:系统故障 2:升级割接
@property (nonatomic, copy) NSString * cnText; //页面提示语（中文）

@property (nonatomic, copy) NSString * enText; //页面提示语(英文)

+(TKResponsedModel_CutUpgradeState*)parseResponseData:(NSDictionary*)dict;

@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    12.3    修改邮件所属的文件夹
 12.3.1    接口功能//
 修改邮件所属的文件夹
 模块ID:  mbox:moveMessages
 *
 *    Created by gao on 2014-04-17 16:47
 */
@interface TKRequestModel_MBoxMoveMessages : TKMRequestBase

/**
 *    @brief    是 新文件夹id。 当新的文件夹ID为“已删除邮件”文件夹ID时，表示该邮件为逻辑删除
 *
 *    Created by gao on 2014-04-17 16:47
 */
@property (nonatomic, assign) NSInteger        newFid;

/**
 *    @brief    否 0/1    1表示针对所有的聚合邮件，会忽略掉sendIds参数
 *
 *    Created by gao on 2014-04-17 16:47
 */
@property (nonatomic, assign) NSInteger        sendFlag;

/**
 *    @brief    否 -    聚合邮件id数组，如果是移动聚合邮件，则传入该个参数 {0, 1, 2,3}
 *
 *    Created by gao on 2014-04-17 16:47
 */
@property (nonatomic, strong) NSMutableArray*  arrSendIds;

/**
 *    @brief    否 -    邮件会话id数组，如果是移动会话邮件，则传入该个参数 ） {0, 1, 2, 3}
 *
 *    Created by gao on 2014-04-17 16:48
 */
@property (nonatomic, strong) NSMutableArray*  arrSessionIds;

/**
 *    @brief    否 -    mid 数组，如果移动普通邮件，则传该mid数组） {mid, mid, mid, mid}
 *
 *    Created by gao on 2014-04-17 16:48
 */
@property (nonatomic, strong) NSMutableArray*  arrIds;

@end


@interface TKResponseModel_MBoxMoveMessages : TKMResponsedBase
/**
 *    @brief    // 处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:48
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxMoveMessages*)parseResponseData:(NSDictionary*)dict;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief        12.4    修改邮件的状态
 12.4.1    接口功能
 修改邮件状态信息
 模块ID:  mbox:updateMessagesStatus
 *
 *    Created by gao on 2014-04-17 16:53
 */
@interface TKRequestModel_MBoxUpDateMessageStatus : TKMRequestBase


/**
 *    @brief     设置的的属性类型：
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
 starType: 7种类型的星标邮件，值在SetValue的低三位，如为0，表示取消星标邮件
 *
 *    Created by gao on 2014-04-17 16:53
 */
@property (nonatomic, strong) NSString*         type;

/**
 *    @brief    设置值，
 *
 *    Created by gao on 2014-04-17 16:53
 */
@property (nonatomic, assign) NSInteger         value;

/**
 *    @brief    mid 数组
 *
 *    Created by gao on 2014-04-17 16:53
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;

/**
 *    @brief    Sessionids 会话id数组，如果使用会话
 *
 *    Created by gao on 2014-04-17 16:54
 */
@property (nonatomic, strong) NSMutableArray*   arrSessionIds;

/**
 *    @brief    聚合邮件的id数组
 *
 *    Created by gao on 2014-04-17 16:54
 */
@property (nonatomic, strong) NSMutableArray*   arrSendIds;

@end


@interface TKResponseModel_MBoxUpDateMessageStatus : TKMResponsedBase
/**
 *    @brief    处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:54
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxUpDateMessageStatus*)parseResponseData:(NSDictionary*)dict;
@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    12.5    设置任务邮件状态(139)
 12.5.1    接口功能
 修改和设置任务提醒邮件状态和提醒时间
 模块ID:  mbox:setTaskMessages
 *
 *    Created by gao on 2014-04-17 16:54
 */
@interface TKRequestModel_MBoxSetTaskMessages : TKMRequestBase


/**
 *    @brief     设置的的属性类型：
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
 starType: 7种类型的星标邮件，值在SetValue的低三位，如为0，表示取消星标邮件
 taskFlag:添加提醒
 *
 *    Created by gao on 2014-04-17 16:54
 */
@property (nonatomic, strong) NSString*         type;//taskFlag:标记任务、添加提醒、标记完成、取消标记，type均使用taskFlag

/**
 *    @brief        设置值，
 0 表示不是任务邮件，
 1 标志为待办的任务邮件。
 2 标志为完成的任务邮件
 *
 *    Created by gao on 2014-04-17 16:55
 */
@property (nonatomic, assign) NSInteger         value;

/**
 *    @brief    表示设置要提醒的时间。
 *
 *    Created by gao on 2014-04-17 16:55
 */
// Modify by Mark 2014-07-07
//@property (nonatomic, assign) NSInteger         time;
@property (nonatomic, assign) NSTimeInterval     time;

/**
 *    @brief    mid 数组
 *
 *    Created by gao on 2014-04-17 16:55
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;


@end


@interface TKResponseModel_MBoxSetTaskMessages : TKMResponsedBase
/**
 *    @brief    处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:55
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxSetTaskMessages*)parseResponseData:(NSDictionary*)dict;
@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    12.6    修改邮件的属性
 12.6.1    接口功能
 修改邮件状态信息，例如修改邮件备注信息
 模块ID:  mbox:updateMessagesInfo
 *
 *    Created by gao on 2014-04-17 16:56
 */
@interface TKRequestModel_MBoxUpDateMessageInfo : TKMRequestBase


/**
 *    @brief    设置的的属性类型：
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
 starType: 7种类型的星标邮件，值在SetValue的低三位，如为0，表示取消星标邮件
 *
 *    Created by gao on 2014-04-17 16:56
 */
@property (nonatomic, strong) NSString*         type;

/**
 *    @brief    设置值，
 *
 *    Created by gao on 2014-04-17 16:56
 */
@property (nonatomic, assign) NSInteger         value;

/**
 *    @brief    mid 数组
 *
 *    Created by gao on 2014-04-17 16:56
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;

@end


@interface TKResponseModel_MBoxUpDateMessageInfo : TKMResponsedBase
/**
 *    @brief     处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:56
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxUpDateMessageInfo*)parseResponseData:(NSDictionary*)dict;

@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    /12.7    邮件标签
 12.7.1    接口功能
 修改邮件状态信息
 模块ID:  mbox:updateMessagesLabel
 *
 *    Created by gao on 2014-04-17 16:57
 */
@interface TKRequestModel_MBoxUpDateMessageLabel : TKMRequestBase


/**
 *    @brief    设置的的属性类型：
 label操作类型
 add:   1 增加标签
 delete:  2 删除标签
 empty:  3 清空所有标签
 *
 *    Created by gao on 2014-04-17 16:57
 */
@property (nonatomic, strong) NSString*         type;

/**
 *    @brief    增加或删除标签的id 当type为add,delete时有效
 *
 *    Created by gao on 2014-04-17 16:57
 */
@property (nonatomic, assign) NSInteger         labelId;

/**
 *    @brief    mid 数组
 *
 *    Created by gao on 2014-04-17 16:57
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;

@end


@interface TKResponseModel_MBoxUpDateMessageLabel : TKMResponsedBase
/**
 *    @brief    处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:58
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxUpDateMessageLabel*)parseResponseData:(NSDictionary*)dict;
@end






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief        12.8    修改文件夹下所有邮件状态
 12.8.1    接口功能
 请求返回邮件索引信息
 模块ID:  mbox:updateMessagesAll
 *
 *    Created by gao on 2014-04-17 16:58
 */
@interface TKRequestModel_MBoxUpDateMessageAll : TKMRequestBase


/**
 *    @brief    设置的的属性类型：
 设置的的属性类型：
 move: 1移动所有邮件
 delete: 2物理删除邮件
 empty: 3清空标签下所有的邮件
 backGroundColor:6设置邮件的新背景色
 priority:7 设置邮件的新优先级(1-5)
 read: （4/5）已读状态(0:已读，1:未读)
 addLabel:  增加标签
 deleteLabel: 删除标签
 *
 *    Created by gao on 2014-04-17 16:58
 */
@property (nonatomic, strong) NSString*         type;

/**
 *    @brief    当前文件夹id
 *
 *    Created by gao on 2014-04-17 16:58
 */
@property (nonatomic, assign) NSInteger         fid;

/**
 *    @brief    新文件夹id,移动操作时有效
 *
 *    Created by gao on 2014-04-17 16:58
 */
@property (nonatomic, assign) NSInteger         newFid;

/**
 *    @brief    设置值（取值范围参见type定义）
 *
 *    Created by gao on 2014-04-17 16:59
 */
@property (nonatomic, assign) NSInteger         value;

/**
 *    @brief    移动oa邮箱要求填写该值，如果是公共帐号操作，则填写当前真实操作个人的邮箱帐号
 *
 *    Created by gao on 2014-04-17 16:59
 */
@property (nonatomic, strong) NSString*         opUser;

/**
 *    @brief    mid 数组
 *
 *    Created by gao on 2014-04-17 16:59
 */
@property (nonatomic, strong) NSMutableArray*   arrFlags;

@end


@interface TKResponseModel_MBoxUpDateMessageAll : TKMResponsedBase
/**
 *    @brief    处理成功的记录。
 *
 *    Created by gao on 2014-04-17 16:59
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxUpDateMessageLabel*)parseResponseData:(NSDictionary*)dict;

@end

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief       12.9    物理删除邮件
 12.9.1    接口功能/
 物理删除指定的邮件(物理删除的前提条件是该邮件已经被逻辑删除)
 模块ID:  mbox:deleteMessages
 *
 *    Created by gao on 2014-04-17 17:00
 */
@interface TKRequestModel_MBoxDeleteMessages : TKMRequestBase

/**
 *    @brief    否    string    64    移动oa邮箱要求填写该值，如果是公共帐号操作，则填写当前真实操作个人的邮箱帐号
 *
 *    Created by gao on 2014-04-17 17:00
 */
@property (nonatomic, strong) NSString*         opUser;

/**
 *    @brief    否    int    0/1    1表示删除所有的聚合邮件，会忽略掉sendIds参数
 *
 *    Created by gao on 2014-04-17 17:00
 */
@property (nonatomic, assign) NSInteger         sendFlag;

/**
 *    @brief    否    array    --    聚合邮件id数组，如果是删除聚合邮件，则传入该个参数
 *
 *    Created by gao on 2014-04-17 17:00
 */
@property (nonatomic, strong) NSMutableArray*   arrSendIds;

/**
 *    @brief    否    int    4    邮件会话id数组 （此参数与ids参数为二选一,必须要有一个，如果是移动会话邮件，则传入该个参数 ）
 *
 *    Created by gao on 2014-04-17 17:00
 */
@property (nonatomic, strong) NSMutableArray*   arrSessionIds;

/**
 *    @brief    否    array    --    mid 数组（此参数 与sessionId参数为二选 一，如果是非会话邮件，则传该mid数组）
 *
 *    Created by gao on 2014-04-17 17:01
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;

@end

@interface TKResponseModel_MBoxDeleteMessages : TKMResponsedBase

/**
 *    @brief     处理成功的记录。
 *
 *    Created by gao on 2014-04-17 17:01
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxDeleteMessages*)parseResponseData:(NSDictionary*)dict;

@end



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 *    @brief  12.19    查询可撤回邮件
 12.19.1    接口功能
 应用层系统向基础平台层发起邮件撤回的请求，基础层将尝试撤回发送给指定收件人的邮件，并将撤回结果返回给应用层。
 *
 *    Created by gao on 2014-04-17 17:03
 */
@interface TKRequestModel_MBoxQuaryRecallMessage: TKMRequestBase

/**
 *    @brief    信件的标识: msid + ':' + mid
 *
 *    Created by gao on 2014-04-17 17:03
 */
@property (nonatomic, strong) NSString*         mid;

@end

/**
 *  返回的数据
 */
@interface TKResponseModel_MBoxQuaryRecallMessage : TKMResponsedBase

/**
 *    @brief    查询可撤回邮件的邮箱结果对象的数组
 *
 *    Created by gao on 2014-04-17 17:04
 */
@property (nonatomic, strong) NSMutableDictionary*       var;

+(TKResponseModel_MBoxQuaryRecallMessage*)parseResponseData:(NSDictionary*)dict;

@end



/**
 *    @brief  12.19    邮件撤回
 12.19.1    接口功能
 应用层系统向基础平台层发起邮件撤回的请求，基础层将尝试撤回发送给指定收件人的邮件，并将撤回结果返回给应用层。
 用户登录邮箱之后，应用层Web Server同步加载AJAX组件。在邮件撤回的事件触发之后，AJAX脚本异步向基础层提供的URL发起HTTP POST请求，基础层作为HTTP服务器返回应答。
 *
 *    Created by gao on 2014-04-17 17:03
 */
@interface TKRequestModel_MBoxRecallMessage: TKMRequestBase


/**
 *    @brief    信件的标识: msid + ':' + mid
 *
 *    Created by gao on 2014-04-17 17:03
 */
@property (nonatomic, strong) NSString*         mid;

/**
 *    @brief    移动oa邮箱要求填写该值，如果是公共帐号操作，则填写当前真实操作个人的邮箱帐号
 *
 *    Created by gao on 2014-04-17 17:03
 */
@property (nonatomic, strong) NSString*         opUser;

/**
 *    @brief    0:不发撤回提示邮件给被撤回的人。1:发,默认不加此参数时，则为1，表示要发撤回提示邮件给被撤回的人
 *
 *    Created by gao on 2014-04-17 17:03
 */
@property (nonatomic, assign) NSInteger         replyFlag;

/**
 *    @brief    否    array    收件人（包括抄送密送）邮件地址的数组。 如果不传递此参数则表示撤回所有接收人的邮件。
 *
 *    Created by gao on 2014-04-17 17:03
 */
@property (nonatomic, strong) NSMutableArray*   arrIds;


@end

/**
 *  返回的数据
 */
@interface TKResponseModel_MBoxRecallMessage : TKMResponsedBase

/**
 *    @brief    邮件撤回结果对象的数组
 *
 *    Created by gao on 2014-04-17 17:04
 */
@property (nonatomic, strong) NSMutableArray*       arrVar;

+(TKResponseModel_MBoxRecallMessage*)parseResponseData:(NSDictionary*)dict;

@end





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief    12.21    邮件归档
 12.21.1    接口功能
 当用户邮件超过10000封时，引导用户对邮件归档，保持收件箱的快速
 模块ID:  mbox:mailFile
 *
 *    Created by gao on 2014-04-17 17:04
 */
@interface TKRequestModel_MBoxMailFile: TKMRequestBase

/**
 *    @brief    是    int    1    1、查询 2、即时归档
 *
 *    Created by gao on 2014-04-17 17:05
 */
@property (nonatomic, assign) NSInteger          type;

/**
 *    @brief    是    int     1    归档类型：0、按时间 1、按封数
 *
 *    Created by gao on 2014-04-17 17:05
 */
@property (nonatomic, assign) NSInteger          archiveType;

/**
 *    @brief    是    int    2    欲归档的文件夹ID
 *
 *    Created by gao on 2014-04-17 17:05
 */
@property (nonatomic, assign) NSInteger          srcFolderId;

/**
 *    @brief    是    int    2    归档到指定的文件夹ID（默认10为系统默认的归档文件夹）
 *
 *    Created by gao on 2014-04-17 17:05
 */
@property (nonatomic, assign) NSInteger          desFolderId;

/**
 *    @brief    是    int    4    较旧的N封邮件 （当archiveType=1是，该值有效）
 *
 *    Created by gao on 2014-04-17 17:05
 */
@property (nonatomic, assign) NSInteger          olderNum;

/**
 *    @brief        是    int    4    邮件的开始时间（秒） 可以默认为0，表示从一开始到指定endDate时间段内。（当archiveType=0时，该值有效）
 *
 *    Created by gao on 2014-04-17 17:06
 */
@property (nonatomic, assign) NSInteger          startDate;

/**
 *    @brief    是    int    4    邮件的结束时间（秒）（当archiveType=0时，该值有效）
 *
 *    Created by gao on 2014-04-17 17:06
 */
@property (nonatomic, assign) NSInteger          endDate;

/**
 *    @brief    是    int    4    此文件夹至少保留的邮件数
 *
 *    Created by gao on 2014-04-17 17:06
 */
@property (nonatomic, assign) NSInteger          keepNum;

@end

/**
 *  返回的数据
 */
@interface TKResponseModel_MBoxMailFile : TKMResponsedBase

/**
 *    @brief    通用返回结果的数组 单指令调用时返回值无意义
 *
 *    Created by gao on 2014-04-17 17:06
 */
@property (nonatomic, strong) NSDictionary*        resultDic;

/**
 *    @brief    通用返回结果的数组 单指令调用时返回值无意义
 ├TotalNum    是    int    4    符合条件的总数
 ├TotalNewNum    是    int    4    符合条件的新邮件总数
 *
 *    Created by gao on 2014-04-17 17:07
 */
@property (nonatomic, strong) NSDictionary*        varDic;

+(TKResponseModel_MBoxMailFile*)parseResponseData:(NSDictionary*)dict;

@end



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief       12.23    获取会话邮件内容
 12.23.1    接口功能
 邮件内容查询
 模块ID:  mbox:readSessionMessage
 *
 *    Created by gao on 2014-04-17 17:07
 */
@interface TKRequestModel_MBoxReadSessionMessage : TKMRequestBase


/**
 *    @brief    是    int    4    当前邮件所在的文件夹id 为0表示搜索
 *
 *    Created by gao on 2014-04-17 17:22
 */
@property (nonatomic, assign) NSInteger fid;

/**
 *    @brief    是    int    4    区别于fid, 该参数表示为当前打开的文件夹的id
 *
 *    Created by gao on 2014-04-17 17:22
 */
@property (nonatomic, assign) NSInteger currFid;

/**
 *    @brief    否    string    0-4    阅读正文的方式:
 没有此参数 - 不返回正文part的content属性的内容
 "text"   只返回text的content值
 "html"  返回html的content的值，如果没有html则返回text的content值
 "both"   text,html的content的值都返回
 另: html part的content属性返回
 的内容将经过filter过滤
 *
 *    Created by gao on 2014-04-17 17:22
 */
@property (nonatomic, strong) NSString* mode;

/**
 *    @brief    否    string    10    强制使用此字符集解读信头及内容 如"gb2312" "big5" "GBK" "UTF-8" 等 用于纠正不正确的信头 默认使用utf-8字符集
 *
 *    Created by gao on 2014-04-17 17:22
 */
@property (nonatomic, strong) NSString* encoding;

/**
 *    @brief    否    int    0/1    是否返回headerRaw 缺省为 0, 不返回
 *
 *    Created by gao on 2014-04-17 17:23
 */
@property (nonatomic, assign) NSInteger header;



/**
 *    @brief    否    int    0/1    是否返回antispamInfo缺省为0 不返回
 *
 *    Created by gao on 2014-04-17 17:23
 */
@property (nonatomic, assign) NSInteger returnAntispamInfo;

/**
 *    @brief        否    int    0/1    是否过滤脚本，缺省为过滤
 *
 *    Created by gao on 2014-04-17 17:23
 */
@property (nonatomic, assign) NSInteger filterScripts;

/**
 *    @brief    否    int    0/1    是否过滤Style块，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 17:23
 */
@property (nonatomic, assign) NSInteger filterStylesheets;

/**
 *    @brief    否    int    0/1    是否过滤Object，缺省为过滤
 *
 *    Created by gao on 2014-04-17 17:23
 */
@property (nonatomic, assign) NSInteger filterObjects;

/**
 *    @brief    否    int    0/1    是否过滤Frame，缺省为过滤
 *
 *    Created by gao on 2014-04-17 17:24
 */
@property (nonatomic, assign) NSInteger filterFrames;


/**
 *    @brief    否    int    0/1    是否过滤Link，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 17:24
 */
@property (nonatomic, assign) NSInteger filterLinks;

/**
 *    @brief    否    int    0/1    是否过滤Image，缺省为不过滤
 *
 *    Created by gao on 2014-04-17 17:24
 */
@property (nonatomic, assign) NSInteger filterImages;

/**
 *    @brief    否    int    0/1    是否置已读标记, 缺省不传0 不标志 1所有的邮件都标记已 2 只标记会话中的第一封邮件
 *
 *    Created by gao on 2014-04-17 17:24
 */
@property (nonatomic, assign) NSInteger markRead;

/**
 *    @brief    否    int    0/1    1 默认值  表示返回html块内容 0 不返回html块内容
 *
 *    Created by gao on 2014-04-17 17:24
 */
@property (nonatomic, assign) NSInteger showhtml;

/**
 *    @brief    否    object        数组类型，指定返回哪些信头，指定的信头将在应签数据的headers字段中返回，示例
 <array name=”returnHeaders”/>
 <string name=”from”/>
 <string name=”sender”/>
 <string name=”x-richinfo”/>
 <string name=”x-compose”/>
 </array>
 *
 *    Created by gao on 2014-04-17 17:25
 */
@property (nonatomic, strong) NSDictionary* returnHeaders;
/**
 *    @brief        是    int    4    邮件会话ID值
 *
 *    Created by gao on 2014-04-17 17:25
 */
@property (nonatomic, assign) NSInteger sessionId;

/**
 *    @brief    是    int    1    邮件读标志（0、取所有 1、只取未读 2、只取已读）
 *
 *    Created by gao on 2014-04-17 17:25
 */
@property (nonatomic, assign) NSInteger readFlag;

/**
 *    @brief        是    int    4    从第几条记录开始读取
 *
 *    Created by gao on 2014-04-17 17:25
 */
@property (nonatomic, assign) NSInteger start;

/**
 *    @brief        是    int    4    取的条数（如果不够条数，则返回实际条数）合法数值为（1－200之间
 *
 *    Created by gao on 2014-04-17 17:26
 */
@property (nonatomic, assign) NSInteger total;


/**
 *    @brief     处理成功的记录。
 *
 *    Created by gao on 2014-04-17 17:22
 */
@property (nonatomic, strong) NSString* folderPass;

@end


/**
 *  返回的数据
 */
@interface TKResponseModel_MBoxReadSessionMessage : TKMResponsedBase

/**
 *    @brief     处理成功的记录。
 *
 *    Created by gao on 2014-04-17 17:21
 */
@property (nonatomic, strong) NSMutableArray*       arrVar;

+(TKResponseModel_MBoxReadSessionMessage*)parseResponseData:(NSDictionary*)dict;

@end



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief     12.25    删除会话中的邮件
 12.25.1    接口功能
 将N封邮件从某会话删除
 模块ID:  mbox:deleteSessionMessages
 
 *
 *    Created by gao on 2014-04-17 17:21
 */
@interface TKRequestModel_MBoxDeleteSessionMessage : TKMRequestBase

/**
 *    @brief    是    int    4    邮件会话ID
 *
 *    Created by gao on 2014-04-17 17:21
 */
@property (nonatomic, assign) NSInteger sessionId;


/**
 *    @brief    是    int    1    请求类型
 0、删除会话ID，
 1、将N封邮件从会话ID中删除
 默认 0删除会话ID
 *
 *    Created by gao on 2014-04-17 17:21
 */
@property (nonatomic, assign) NSInteger requestType;

/**
 *    @brief    是    int    1    0、允许与新邮件重新组成会话
 1、不允许与任何邮件再组成会话
 默认 0允许与新邮件重新组成会话
 *
 *    Created by gao on 2014-04-17 17:20
 */
@property (nonatomic, assign) NSInteger flag;


/**
 *    @brief    是    array    --    mid 数组 requestType为1时有效
 *
 *    Created by gao on 2014-04-17 17:20
 */
@property (nonatomic, strong) NSMutableArray* arrIds;

@end

@interface TKResponseModel_MBoxDeleteSessionMessage : TKMResponsedBase

/**
 *    @brief    处理成功的记录。
 *
 *    Created by gao on 2014-04-17 17:20
 */
@property (nonatomic, assign) NSInteger       var;

+(TKResponseModel_MBoxDeleteSessionMessage*)parseResponseData:(NSDictionary*)dict;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *    @brief 单附件下载
 *
 *    Created by gao on 2014-04-23 15:10
 */
@interface TKRequestModel_AttachDownload: TKMRequestBase

/**
 *    @brief        是    string    24    邮件的mid
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, strong) NSString* mid;

/**
 *    @brief        是    int    4    附件的偏移量
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, assign) NSInteger offset;

/**
 *    @brief        是    int    4    附件大小 ，字节为单位
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, assign) NSInteger size;

/**
 *    @brief        是    string    --    附件的名称，进行encodeURIComponent
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, strong) NSString* name;

/**
 *    @brief        是    String        用于区分winmail.dat的问*题
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, strong) NSString* type;

/**
 *    @brief        否    int    0/1    1表示需要断点下载或临时文件下载 默认为0
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, assign) NSInteger isRange;

/**
 *    @brief        是    int    1    0、无编码；
 1、base64；
 2、quoted-printable；
 3、7bit；
 4、8bit；
 5、Binary；
 6、uuencode
 
 *
 *    Created by gao on 2014-04-23 15:07
 */
@property (nonatomic, assign) NSInteger encoding;

@end

@interface TKResponseModel_AttachDownload : TKMResponsedBase

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *    @brief    根据邮件id（mid）数组获取邮件附件列表请求结构
 *
 *    Created by mac on 2014-06-03 11:26
 */
@interface TKRequestModel_AttachRefresh : TKMRequestBase

@property (nonatomic, strong) NSMutableArray *mids;

@end


/**
 *    @brief    根据邮件id（mid）数组获取邮件附件列表返回数据结构
 *
 *    Created by mac on 2014-06-03 11:32
 */
@interface TKResponseModel_AttachRefresh : TKMResponsedBase

@property (nonatomic, strong) NSMutableArray* attachs;

+ (TKResponseModel_AttachRefresh *)parseResponseData:(NSDictionary*)dict;
@end




/**
 *    @brief       14.5    附件列表-扩展
 14.5.1    附件列表功能
 14.5.1.1    接口功能
 请求返回邮件索引信息
 模块ID:  attach: listAttachments
 *
 *    Created by gao on 2014-04-17 17:20
 */
@interface TKRequestModel_AttachListAttachments : TKMRequestBase


/**
 *    @brief    否    string    1-16    排序字段
 sendDate:      按发送日期
 receiveDate:   按接收日期
 from:          按发件人
 to:            按收件人
 size:          按邮件大小
 subject:       按邮件主题
 name:          按附件名称
 attachSuffix:  按附件名后缀
 attachSize:    按附件大小
 默认按接收日期
 *
 *    Created by gao on 2014-04-17 17:19
 */
@property (nonatomic, strong) NSString*  order;

/**
 *    @brief    否    int    0/1    是否逆序排列，默认为1，desc时表示按逆序排列，对所有排序字段生效。
 *
 *    Created by gao on 2014-04-17 17:19
 */
@property (nonatomic, assign) NSInteger  desc;


/**
 *    @brief    是    int    4 文件夹id，为0或者不传该值表示所有邮件夹， 服务器端需要校验下面folderPass是否正确，如果正确则返回加密的文件夹，否则不返回加密的文件夹），fid=0是不搜索加锁文件夹的，通过验证后则会搜索加锁文件夹
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, assign) NSInteger  fid;

/**
 *    @brief    否    string    16    文件夹密码，如果密码校验失败，则加密文件夹下的附件不返回
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, strong) NSString*  folderPass;


/**
 *    @brief    是    int    4    从第几条记录开始读取
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, assign) NSInteger  start;


/**
 *    @brief    是    int     4    取的条数（如果不够条数，则返回实 条数）合法值为1-200
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, assign) NSInteger  total;


/**
 *    @brief        是    int    1    查询内容（1、按新的条件查询　0、从上一次的查询结果集中查取）。 注：如果该值为0,filter条件参数将被忽略
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, assign) NSInteger  isSearch;

/**
 *    @brief    是    int    1    0为忽略大小写 1为区分大小写 默认为0，忽略大小写
 *
 *    Created by gao on 2014-04-17 17:18
 */
@property (nonatomic, assign) NSInteger  ignoreCase;


/**
 *    @brief    否    object    1    过滤条件(filter search object) 当isSearch为1时，该参数不传，表示不进行附件过滤，直接返回附件列表
 *
 *    Created by gao on 2014-04-17 17:17
 */
@property (nonatomic, strong) FilterSearchObject*  filter;         //

/**
 *    @brief    是    int    4    是否返回附件统计摘要 stat为1时，返回的HHJSON数据包含邮件统计信息，stat为0时，不返回统计信息
 *
 *    Created by gao on 2014-04-17 17:17
 */
@property (nonatomic, assign) NSInteger  stat;                     //

@end



/**
 *  返回的数据
 */
@interface TKResponseModel_AttachListAttachments  : TKMResponsedBase
/**
 *    @brief    // 附件总数
 *
 *    Created by gao on 2014-04-17 17:17
 */
@property (nonatomic, assign) NSInteger       total;

/**
 *    @brief    返回的数据attach info object数组
 *
 *    Created by gao on 2014-04-17 17:16
 */
@property (nonatomic, strong) NSDictionary*   statDic;

/**
 *    @brief    // 附件统计信息对象(attache stat object) 当stat为1时返回该对象
 *
 *    Created by gao on 2014-04-17 17:16
 */
@property (nonatomic, strong) NSMutableArray* arrVar;

+(TKResponseModel_AttachListAttachments*)parseResponseData:(NSDictionary*)dict;

@end

/**
 *    @brief    上传附件文件来源类型
 *
 *    Created by mac on 2014-04-17 17:43
 */
typedef enum TKPrepareUploadAttachSourceFrom
{
    TKPrepareUploadAttachFromSkyDriver = 0, /**< 网盘文件作为附件 */
    TKPrepareUploadAttachFromLocation, /**< 本地文件作为附件 */
    TKPrepareUploadAttachFromInternal, /**< 内部附件 */
    TKPrepareUploadAttachFromUrl, /**< URL资源作为附件 */
    TKPrepareUploadAttachFromMMC, /**< 多媒体内容作为附件 */
    TKPrepareUploadAttachFromTransferStation, /**< 中转站文件作为附件 */
    TKPrepareUploadAttachFromOtherMail /**< 其它邮件附件作为附件 */
}TKPrepareUploadAttachSourceFrom;


/**
 *    @brief    上传的附件文件对象
 *
 *    Created by mac on 2014-04-21 11:51
 */
@interface TKPrepareUploadAttachObject : NSObject


/**
 *    @brief    附件来源
 *
 *    Created by mac on 2014-04-17 17:45
 */
@property (nonatomic)TKPrepareUploadAttachSourceFrom sourceFrom;

/**
 *    @brief    是否作为内联图片
 *
 *    Created by mac on 2014-04-17 17:46
 */
@property (nonatomic)BOOL isForInlineImage;

/**
 *    @brief    附件文件Id，回复或转发时，携带原始邮件附件时使用。
 *
 *    Created by gao on 2014-04-17 17:26
 */
@property (nonatomic, strong) NSString *fileId;

/**
 *    @brief    //附件所属的原始邮件Id，回复或转发时，携带原始邮件附件时使用。
 *
 *    Created by gao on 2014-04-17 17:26
 */
@property (nonatomic, strong) NSString *fileOriginalMailId;

/**
 *    @brief    会话Id。
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic, strong) NSString *fileComposeId;

/**
 *    @brief    附件文件路径，当上传本地文件作为附件时使用
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic, strong) NSString *filePath;

/**
 *    @brief    音视频邮件 首帧图片地址
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic, strong) NSString *imageFilePath;

/**
 *    @brief    附件文件名称
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic, strong) NSString *fileName;

/**
 *    @brief    附件来源类型
 *
 *    Created by mac on 2014-04-22 17:51
 */
@property (nonatomic, strong) NSString *fileType;


/**
 *    @brief    附件文件大小
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic) unsigned long long fileSize;

/**
 *    @brief    附件文件实际大小
 *
 *    Created by mac on 2014-04-22 16:59
 */
@property (nonatomic) unsigned long long fileRealSize;

/**
 *    @brief
 *
 *    Created by mac on 2014-04-23 14:35
 */
@property (nonatomic) unsigned long long fileHeadOffSet;


/**
 *    @brief    附件偏移量
 *
 *    Created by mac on 2014-04-23 14:35
 */
@property (nonatomic) unsigned long long fileOffSet;


/**
 *    @brief    取附件列表返回的encode值， 一般是
 1为base64
 *
 *    Created by mac on 2014-04-23 14:38
 */
@property (nonatomic) int fileEncoding;


@property (nonatomic) int fileFetchType;

@property (nonatomic) int fileClassId;

@property (nonatomic, strong) NSString *fileTempPath;

@property (nonatomic, strong) NSArray *oldFileIds;

/**
 *    @brief    附件文件url，当上传网盘文件作为附件时使用，为附件下载的url
 *
 *    Created by gao on 2014-04-17 17:27
 */
@property (nonatomic, strong) NSString *fileOriginalUrl;

/**
 *    @brief    初始化一个网盘附件
 *
 *    @param     fileId     fileId
 *    @param     name     名称
 *    @param     size     大小
 *    @param     bl     是否作为内联图
 *
 *    @return    需要上传的附件对象
 *
 *    Created by mac on 2014-04-17 17:48
 */
+ (TKPrepareUploadAttachObject *)skyDriverAttachObjectWith:(NSString *)fileId fileName:(NSString *)name fileSize:(unsigned long long)size isForInlineImage:(BOOL)bl;

/**
 *    @brief    初始化一个本地文件附件
 *
 *    @param     filePath     文件路径
 *    @param     bl     是否作为内联图
 *
 *    @return    需要上传的附件对象
 *
 *    Created by mac on 2014-04-17 17:48
 */
+ (TKPrepareUploadAttachObject *)locationFileAttachObjectWith:(NSString *)filePath isForInlineImage:(BOOL)bl;

/**
 *    @brief    初始化一个其它邮件附件
 *
 *    @param     omid     原始邮件id
 *    @param     fid     附件id
 *    @param     name     附件名称
 *    @param     type     附件类型
 *    @param     size     附件大小
 *    @param     url     附件url地址
 *    @param     range     文件分块的范围
 *    @param     bl     是否作为内联图
 *
 *    @return    需要上传的附件对象
 *
 *    Created by mac on 2014-04-17 17:49
 */
+ (TKPrepareUploadAttachObject *)originaMailAttachObjectWith:(NSString *)omid fileId:(NSString *)fid fileName:(NSString *)name fileType:(NSString *)type fileSize:(unsigned long long)size fileRealSize:(unsigned long long)realSize fileUrl:(NSString *)url fileOffSet:(unsigned long long)range isForInlineImage:(BOOL)bl;

/**
 *    @brief    初始化一个其它邮件附件
 *
 *    @param     data     附件信息
 *    @param     bl     是否作为内联图
 *
 *    @return    需要上传的附件对象
 *
 *    Created by mac on 2014-04-23 14:34
 */
+ (TKPrepareUploadAttachObject *)originaMailAttachObjectWithServerData:(NSDictionary *)data isForInlineImage:(BOOL)bl;

- (void)loadAttachWithOriginaMailAttachServerData:(NSDictionary *)data;
- (TKPrepareUploadAttachObject *)initWithDict:(NSDictionary *)dict;
- (NSDictionary *)getDictionary;
@end


/**
 *    @brief    发邮件，对邮件处理的类型
 *
 *    Created by mac on 2014-04-17 17:59
 */
typedef enum TKMailOperationType
{
    TKMailOperation_GetCompose = 1, /**< 重启一封新邮件，获取会话id */
    TKMailOperation_ForwardMail, /**< 转发邮件 */
    TKMailOperation_ReplyMail, /**< 回复邮件 */
    TKMailOperation_EditDraft, /**< 编辑草稿 */
    TKMailOperation_DeleteAttach, /**< 删除附件 */
    TKMailOperation_UploadAttach, /**< 添加上传附件 */
    TKMailOperation_SendMail, /**< 发送邮件 */
    TKMailOperation_SaveMail /**< 存草稿 */
    
    
}TKMailOperationType;

/**
 *    @brief    准备发送邮件对象
 *
 *    Created by mac on 2014-04-17 18:02
 */
@interface ThinkMail_MailSendObject : NSObject

@property (nonatomic, strong)TKMContextModel *m_context;
/**
 *    @brief    //发件人地址数组
 *
 *    Created by mac on 2014-04-18 13:49
 */
@property (nonatomic, strong) NSString*  account;

/**
 *    @brief    邮件标题
 *
 *    Created by mac on 2014-04-18 13:50
 */
@property (nonatomic, strong)NSString *mailSubject;

/**
 *    @brief    正文
 *
 *    Created by mac on 2014-04-18 13:50
 */
@property (nonatomic, strong)NSString *mailBodyStr;

/**
 *    @brief    收件人、抄送、密送人
 *
 *    Created by mac on 2014-04-18 13:52
 */
@property (nonatomic, strong)NSMutableArray *mailSendToContactArray;
@property (nonatomic, strong)NSMutableArray *mailSendCCContactArray;
@property (nonatomic, strong)NSMutableArray *mailBCCContactArray;

/**
 *    @brief    附件
 *
 *    Created by mac on 2014-04-18 13:50
 */
@property (nonatomic, strong)NSMutableArray *mailAttachmentArray;

/**
 *    @brief    原始邮件id
 *
 *    Created by mac on 2014-04-18 13:50
 */
@property (nonatomic, strong)NSString *m_omidString;

/**
 *    @brief    邮件会话id
 *
 *    Created by mac on 2014-04-18 13:51
 */
@property (nonatomic, strong)NSString *m_composeId;

/**
 *    @brief    邮件id
 *
 *    Created by mac on 2014-04-18 13:51
 */
@property (nonatomic, strong)NSString *m_mailId;

/**
 *    @brief    创建邮件的方式
 *
 *    Created by mac on 2014-04-18 13:51
 */
@property (nonatomic) TKMailCreateType m_type;

/**
 *    @brief    是否需要已读回执
 *
 *    Created by mac on 2014-04-18 13:52
 */
@property (nonatomic, assign) NSInteger  requestReadReceipt;

/**
 *    @brief    --会议邮件专用--
 <object name="meetingAttr">
 <string name="location">会议召开的地点</string>
 <int name="meetingStart">会议开始时间秒数</int>
 <int name="meetingEnd">会议结束时间秒数</int>
 <int name="partStat">发会议邀请呢就可以忽略此参数或只传0。0默认值1参加会议2不参加会议3暂定参加会议,只有在参会人在对收到的会议邀请邮件进行回应是否参加的时候才需要此参数。</int>
 </object>
 *
 *    Created by mac on 2015-03-12 15:51
 */
@property (nonatomic, strong) NSDictionary*  meetingAttr;


@property (nonatomic, strong) NSString*  references;
@property (nonatomic, strong) NSString*  replyTo;     //回复到某人
@property (nonatomic, strong) NSString*  messageId;
@property (nonatomic, assign) NSInteger  receiveDate;     //邮件接收时间 格式为：日期使用1970年1月1日午夜距今的秒数表示（JavaScript默认使用毫秒数，需要进行转换）下同
@property (nonatomic, assign) NSInteger  scheduleDate;     //定时发信时间, 用于定时发信操作
@property (nonatomic, assign) NSInteger  saveSentCopy;     //发送后保存副本到发件箱, 缺省为保存(1)
@property (nonatomic, assign) NSInteger  showOneRcpt;     //群发单显标记
@property (nonatomic, assign) NSInteger  inlineResources;     //是否有内联图标记
@property (nonatomic, assign) NSInteger  sendDate;      //邮件发送日期
@property (nonatomic, assign) NSInteger  priority;      //优先级： 1, 2: 高优先级 3 : 普通优先级 4, 5: 低优先级
@property (nonatomic, assign) NSInteger  isHtml;    //1：html邮件  0：文本邮件
@property (nonatomic, strong) NSDictionary*  headers;    ////returnHeaders请求参数中，指明返回的头信息对象
@property (nonatomic, strong) NSString*  sessionMails;     //邮件体对象(msg info object)，同邮件列表
@property (nonatomic, strong) NSString*  contentSummary;
@property (nonatomic, assign) NSInteger  denyForward;
@property (nonatomic, assign) NSInteger  emailOffSize;
@property (nonatomic, assign) NSInteger  keepDay;
@property (nonatomic, assign) NSInteger  keepFlag;
@property (nonatomic, assign) NSInteger  sendWay;
@property (nonatomic, strong) NSString*  sender;
@property (nonatomic, assign) NSInteger  normalizeRfc822;
@property (nonatomic, assign) NSInteger  isCommonUser;
@property (nonatomic, assign) NSInteger  returnInfo;


/**
 *
 *    @param     mailInfo     服务器返回的邮件详细信息
 *    @param     ctype     发送邮件类型
 *
 *    @return    准备发送邮件对象
 *
 *    Created by mac on 2014-04-18 11:49
 */
+ (ThinkMail_MailSendObject *)getMailSendObjectWithMailInfo:(NSDictionary *)mailInfo andMailCreateType:(TKMailCreateType)ctype;


- (NSString *)getMailSendXMLStr:(TKMailOperationType)type context:(TKMContextModel *)context;

@end


/**
 *    @brief    创建邮件返回对象
 *
 *    Created by mac on 2014-04-18 15:36
 */
@interface TKMCreateSendMailRespone : TKMResponsedBase
@property (nonatomic, strong)ThinkMail_MailSendObject *mailSendObject;
@end


/**
 *    @brief    删除附件返回对象
 *
 *    Created by mac on 2014-04-18 15:37
 */
@interface TKMDeleteAttachRespone : TKMResponsedBase
@property (nonatomic, strong)TKPrepareUploadAttachObject *deleteAttach;
@end


/**
 *    @brief    发邮件返回对象
 *
 *    Created by mac on 2014-04-18 15:37
 */
@interface TKMSendMailRespone : TKMResponsedBase
@property (nonatomic, strong)NSString *tid;
@end


/**
 *    @brief    保存草稿返回对象
 *
 *    Created by mac on 2014-04-18 15:37
 */
@interface TKMSaveDraftRespone : TKMResponsedBase
@property (nonatomic, strong)NSString *mid;
@end


/**
 *    @brief    附加下载返回对象
 *
 *    Created by mac on 2014-05-07 14:35
 */
@interface TKAttachDownloadRespone : NSObject
@property (nonatomic, strong)TKAttachInfoObject *attachInfo;
/**
 *    @brief    已下载大小
 *
 *    Created by mac on 2014-05-07 14:36
 *
 *  修改数据类型符合底层转换
 *  Modify by Mark 2014-07-31
 */
@property (nonatomic, assign) unsigned long long downloadedSize;


/**
 *    @brief    下载进度
 *
 *    Created by mac on 2014-05-07 14:44
 */
@property (nonatomic)float downloadedProgress;


/**
 *    @brief    附件存放位置
 *
 *    Created by mac on 2014-05-07 14:37
 */
@property (nonatomic, strong)NSString *attachPath;

/**
 *    @brief    附件下载状态
 *
 *    Created by mac on 2014-05-07 14:37
 */
@property (nonatomic)TKAttachDownloadState downloadState;

/**
 *    @brief    附件下载提示
 *
 *    Created by mac on 2014-05-07 14:37
 */
@property (nonatomic, strong)NSString *noteMessage;

@end

#pragma mark - 日历操作相关

@interface TKMRequestModel_AddMailCalendar : TKMRequestBase
@property (nonatomic) int comeFrom;
@property (nonatomic) int recMySms;
@property (nonatomic, strong)NSString *startTime;//范例：0900
@property (nonatomic, strong)NSString *endTime;//范例：0900
@property (nonatomic, strong)NSString *content;//范例："请处理来自幽默笑话的邮件：男女经典趣语"
@property (nonatomic, strong)NSString *title;//范例："请处理来自幽默笑话的邮件：男女经典趣语"
@property (nonatomic, strong)NSString *dateFlag;  //范例：2014-06-04
@property (nonatomic, strong)NSString *endDateFlag;//范例：2014-06-04
@property (nonatomic, strong)NSString *recMobile;//范例：13977245678
@property (nonatomic, strong)NSString *dateDesc;//范例：2014年06月04日 09:00
@property (nonatomic, strong)NSString *mid;
@property (nonatomic) int enable;
@property (nonatomic) int beforeTime;
@property (nonatomic) int beforeType;
@property (nonatomic) int recMyEmail;
@end

@interface TKMResponeModel_AddMailCalendar : TKMResponsedBase
@property (nonatomic) int awardFlag;

+ (TKMResponeModel_AddMailCalendar *)parseResponseData:(NSDictionary*)dict;
@end

@interface TKMRequestModel_DeleteMailCalendar : TKMRequestBase
@property (nonatomic) int comeFrom;
@property (nonatomic) int actionType;
@property (nonatomic, strong)NSString *mid;
@end

@interface TKMResponeModel_DeleteMailCalendar : TKMResponsedBase
@property (nonatomic) int awardFlag;

+ (TKMResponeModel_DeleteMailCalendar *)parseResponseData:(NSDictionary*)dict;
@end

@interface TKMResponeModel_GetInitData : TKMResponsedBase
@property (nonatomic) NSInteger limitMessageSize;//邮箱容量大小KB
@property (nonatomic) NSInteger messageSize;//邮件已使用大小KB
@property (nonatomic) NSInteger messageCount;//当前邮件数量
@property (nonatomic) NSInteger unreadMessageCount;//未读邮件数量

+ (TKMResponeModel_GetInitData *)parseResponseData:(NSDictionary*)dict;
@end


@interface TKMRequestModel_APPGetBalance : TKMRequestBase

@property (nonatomic, strong)NSString *account;//账户

@end

//To Do 4

//------------------------add-----------------------

@interface THinkMail_SetUserInfoRequst : TKMRequestBase
@property(nonatomic,strong)NSString *trueName;//邮箱别名
@property(nonatomic,strong)NSString *mobileNumber;//手机号码
@property(nonatomic,strong)NSString *roleId; //角色id
@property(nonatomic,strong)NSString *securityLevel;//邮件密级-0普通1秘密2机密

@end

@interface THinkMail_MailFolderSortRequst : TKMRequestBase
@property (nonatomic, strong) NSMutableArray * lastFolderLocation;//上一次的位置

- (NSData *)getRequestData;

@end

@interface TKMResponeModel_MailFolderSortRespone : TKMResponsedBase

@property (nonatomic,strong) NSMutableDictionary  *varDic;//返回数据
@property (nonatomic,strong) NSArray  *resultArr;//返回数据

+ (TKMResponeModel_MailFolderSortRespone *)parseResponseData:(NSDictionary*)dict;
@end


@interface THinkMail_UpdateLabelRequst : TKMRequestBase
@property (nonatomic, strong) NSString* fid;//标签id
@property (nonatomic, strong) NSString* labelName;//标签名字

- (NSData *)getRequestData;

@end

@interface THinkMail_UpdateLabelNameWithColorRequest : TKMRequestBase
@property (nonatomic, strong) NSString *fid; //标签id
@property (nonatomic, strong) NSString *labelName; //标签名字
@property (nonatomic, assign) NSInteger folderColor; //标签颜色(这里是色值序号)

- (NSData *)getRequestData;

@end

@interface THinkMail_UpdateLabelNameWithColorRespone : TKMResponsedBase
@property (nonatomic,strong) NSMutableDictionary  *varDic;//返回数据
@property (nonatomic,strong) NSArray  *resultArr;//返回数据
+ (THinkMail_UpdateLabelNameWithColorRespone *)parseResponseData:(NSDictionary*)dict;
@end

@interface TKMResponeModel_GetUserUnReadCount : TKMResponsedBase

@property (nonatomic) NSInteger unreadMessageCount;//未读邮件数

+ (TKMResponeModel_GetUserUnReadCount *)parseResponseData:(NSDictionary*)dict;
@end


#pragma mark - 企业通讯录

@interface ThinkMail_DeptListModel : NSObject
@property (nonatomic, strong) NSMutableArray *deptListArray;

@property (nonatomic, strong) NSDate *lastFetchListDate;//最后一次拉取时间，预留字段，以后可能会用到

@end
@interface ThinkMail_CorpDeptModel : NSObject
@property (nonatomic, assign) NSInteger default_dept_flag;
@property (nonatomic, strong) NSMutableArray *deptList; //此list里面存放的应该是corpdeptmodel
@property (nonatomic, strong) NSString *dept_address;
@property (nonatomic, assign) NSInteger dept_count;
@property (nonatomic, assign) NSInteger dept_id;// ---id
@property (nonatomic, strong) NSString *leader_email;
@property (nonatomic, strong) NSString *leader_first_name;
@property (nonatomic, assign) NSInteger leader_id;
@property (nonatomic, strong) NSString *leader_second_name;
@property (nonatomic, assign) NSInteger level;
@property (nonatomic, strong) NSString *mail_group_id;
@property (nonatomic, strong) NSString *mail_group_name;
@property (nonatomic, strong) NSString *memo;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *nameFirstChar;
@property (nonatomic, strong) NSString *nameFullChar;
@property (nonatomic, assign) NSInteger parent_id;
@property (nonatomic, assign) NSInteger permission;
@property (nonatomic, assign) NSInteger popedom;
@property (nonatomic, assign) NSInteger sort_seq;
@property (nonatomic, assign) NSInteger user_count;
@property (nonatomic, strong) NSString *zip;//这个是干嘛的呢？
@property (nonatomic, strong) NSMutableArray *userList; // ---存储用户的信息CorpContactModel

@end
@interface ThinkMail_CorpContactModel : NSObject
@property (nonatomic, strong) NSString *email; //邮箱地址
@property (nonatomic, strong) NSString *firstName;
@property (nonatomic, assign) NSInteger contactId; // id
@property (nonatomic, strong) NSString *imagePath; // imagePath
/*
 |--mobile_number_desc    是        手机号码对象列表
 |--mobile_number    是        手机号码
 |--city_desc    是        城市
 |--province_desc    是        省份
 |--tel_code    是        号段
 */
@property (nonatomic, strong) NSArray *mobile_number_desc; //---这个描述，目前没有去解析
@property (nonatomic, strong) NSString *nameFirstChar;
@property (nonatomic, strong) NSString *nameFullChar;
@property (nonatomic, strong) NSString *position;
@property (nonatomic, strong) NSString *rm_userid;//这个不理解---
@property (nonatomic, strong) NSString *secondName;
@property (nonatomic, assign) NSInteger sort_seq;
@property (nonatomic, strong) NSDictionary *status; //这个是不是字典，需要验证
@property (nonatomic, strong) NSString *telephone;
@property (nonatomic, strong) NSString *uin;

// Add by Mark 2013-11-05
@property (nonatomic, strong) NSMutableString *strCharIndex;

// Add by Mark 2013-12-03
@property (nonatomic, assign) BOOL isSelected;
@end
typedef enum {
    EContactsList,
    EContactsListUpdate,
    EContactsRemove,
    EContactsDepartUpdate,
    EContactsDepart,
    EPrivateContactsList,
    EPrivateContactGroupList
    
}EContactsType;


@interface THinkMail_ContactResponse : TKMResponsedBase
@property(nonatomic, strong) ThinkMail_DeptListModel *deptListModel;
- (NSMutableArray *)parserContactDictionary:(id)dict;
@end

@interface THinkMail_ContactUserModel : NSObject
@property (nonatomic, assign) NSInteger intID;//本地sqlid
@property (nonatomic, strong) NSString *strID;//服务端存的iD
@property (nonatomic, strong) NSString *strUIN;//
@property (nonatomic, strong) NSString *strRM_UserID;//
@property (nonatomic, strong) NSString *strSort_Seq;//
@property (nonatomic, strong) NSString *strFirstName;//全名
@property (nonatomic, strong) NSString *strSecondName;//
@property (nonatomic, strong) NSString *strNameFirstChar;//全拼首字母
@property (nonatomic, strong) NSString *strNameFullChar;//全拼
@property (nonatomic, strong) NSString *strEmail;//邮箱
@property (nonatomic, strong) NSString *strTelephone;//个人手机
@property (nonatomic, strong) NSString *strPosition;//职务
@property (nonatomic, strong) NSString *strStatus_Mail;//开通？
@property (nonatomic, strong) NSString *strStatus_Disk;//开通？
@property (nonatomic, strong) NSString *strImagePath;//头像
@property (nonatomic, strong) NSString *strDept_ID;//部门ids
@property (nonatomic, strong) NSString *strModify_Seq;//修改标志量，通过这个标志来更新
@property (nonatomic, strong) NSString *strCreate_Time;//
@property (nonatomic, strong) NSString *strModify_Time;//
@property (nonatomic, strong) NSString *strHostMail;//
@property (nonatomic, strong) NSString *strFirstChar;//
@property (nonatomic, strong) NSString *strbusinessPhone;//商务手机
@property (nonatomic, strong) NSString *strbusinessEmail;//商务邮箱
@property (nonatomic, strong) NSString *strBirthday;//生日
@property (nonatomic, strong) NSString *strbusinessCallPhone;//公司固话
@property (nonatomic, strong) NSString *strCompanyName;//公司名称
@property (nonatomic, strong) NSString *strCorpID;
@property (nonatomic, strong) NSArray *strDept_name_list;
@property (nonatomic, strong) NSString *strUser_type;
@property (nonatomic, strong) NSString *strPrerogative_type;
@property (nonatomic, strong) NSString *strMobileNumber;
@property (nonatomic, strong) NSString *strSex;//性别
@property (nonatomic, strong) NSString *strHome_address;
@property (nonatomic, strong) NSString *strCompanyAddress;
@property (nonatomic, strong) NSString *strRm_userid;
@property (nonatomic, strong) NSString *mobile_number_desc;//
// For Contact Selected Flag
// Add by Mark 2014-01-06
@property (nonatomic, assign) BOOL isSelected;
// For Address Frequency
// Add by Mark 2014-01-06
@property (nonatomic, assign) NSInteger intFrequency;

// Add by lt 2014-05-15
@property (nonatomic, assign) BOOL b139;

// Add by lt 2014-05-27
@property (nonatomic, assign) BOOL bVIP;

// Add by Tujie 2014-09-24
@property (nonatomic, assign)NSInteger recordId;

/**
 *    @brief    解析单个地址
 *
 *    @param     sValue     1.0：字符串
 *                  2.0：...
 *
 *    @return    单个mail model,如果没有name则 name =  mail
 *
 *    Created by darktm on 2014-05-16 16:28
 */
-(id)initWithValue:(id)sValue;

/**
 *    @brief    解析多个抄送人
 *
 *    @param     sValue     1.0：数据库给的单独CC字符串
 *                  2.0：.....
 *
 *    @return    ContactUserModel model的array，如果没有则为空
 *
 *    Created by darktm on 2014-05-16 16:27
 */
+(NSMutableArray *)parseCCWithValue:(id)sValue;

/**
 *    @brief    解析多个收件人
 *
 *    @param     sValue     1.0：数据库给的单独CC字符串
 *                  2.0：.....
 *
 *    @return    ContactUserModel model的array，如果没有则为空
 *
 *    Created by darktm on 2014-05-16 16:42
 */
+(NSMutableArray *)parseTOWithValue:(id)sValue;

/**
 *    @brief    解析多密送人
 *
 *    @param     sValue     1.0：数据库给的单独CC字符串
 *                  2.0：.....
 *
 *    @return    ContactUserModel model的array，如果没有则为空
 *
 *    Created by darktm on 2014-05-16 16:42
 */
+(NSMutableArray *)parseBCCWithValue:(id)sValue;
@end


@interface THinkMail_DepartmentModel : NSObject
@property (nonatomic, assign) NSInteger intID;

@property (nonatomic, strong) NSString *strID;
@property (nonatomic, strong) NSString *strParent_ID;
@property (nonatomic, strong) NSString *strName;
@property (nonatomic, strong) NSString *strDefault_Dept_Flag;
@property (nonatomic, strong) NSString *strPopedom;
@property (nonatomic, strong) NSString *strLeader_ID;
@property (nonatomic, strong) NSString *strLeader_First_Name;
@property (nonatomic, strong) NSString *strLeader_Second_Name;
@property (nonatomic, strong) NSString *strLeader_Email;
@property (nonatomic, strong) NSString *strNameFirstChar;
@property (nonatomic, strong) NSString *strNameFullChar;

@property (nonatomic, assign) NSInteger intLevel;

@property (nonatomic, strong) NSString *strSort_Seq;
@property (nonatomic, strong) NSString *strPermission;
@property (nonatomic, strong) NSString *strMail_Group_ID;
@property (nonatomic, strong) NSString *strMail_Group_Name;
@property (nonatomic, strong) NSString *strDept_Address;
@property (nonatomic, strong) NSString *strZIP;
@property (nonatomic, strong) NSString *strMemo;

@property (nonatomic, assign) NSInteger intDept_Count;
@property (nonatomic, assign) NSInteger intUser_Count;

@property (nonatomic, strong) NSString *strDeptList;
@property (nonatomic, strong) NSString *strUserList;
@property (nonatomic, strong) NSString *strHostMail;
@property (nonatomic, strong) NSString *strFirstChar;
// For Show
@property (nonatomic, strong) NSMutableArray *arrSubUser;
@property (nonatomic, strong) NSMutableArray *arrSubDept;
@end

@interface THinkMail_VIPContact : NSObject
@property (nonatomic, strong) NSArray *groups;//THinkMail_VIPContactGroup
@property (nonatomic, strong) NSArray *contacts;//THinkMail_VIPContactModel
@end

//个邮通讯录数据
@interface THinkMail_VIPContactGroup : NSObject
@property (nonatomic, copy) NSString *strCN;//
@property (nonatomic, copy) NSString *strGD;//id
@property (nonatomic, copy) NSString *strGN;//名称
@property (nonatomic, copy) NSString *strSDS;//sds
@end

@interface THinkMail_VIPContactModel : NSObject

@property (nonatomic, copy) NSString *strA; //UserType
@property (nonatomic, copy) NSString *strA0;//公司地址城市
@property (nonatomic, copy) NSString *strA2;//公司邮编
@property (nonatomic, copy) NSString *strA3;//公司地址街道
@property (nonatomic, copy) NSString *strA4;//公司名
@property (nonatomic, copy) NSString *strA6;//备注
@property (nonatomic, copy) NSString *strA7;//ContactCount
@property (nonatomic, copy) NSString *strA8;//ContactType
@property (nonatomic, copy) NSString *strA9;//ContactFlag

@property (nonatomic, copy) NSString *strB; //SourceType
@property (nonatomic, copy) NSString *strB0; //SynFlag
@property (nonatomic, copy) NSString *strB1; //SynId
@property (nonatomic, copy) NSString *strB2; //RecordSeq
@property (nonatomic, copy) NSString *strB3;//FirstNameword
@property (nonatomic, copy) NSString *strB8;//头像
@property (nonatomic, copy) NSString *strC;//名称
@property (nonatomic, copy) NSString *strC1;//职位
@property (nonatomic, copy) NSString *strC8;//飞信号
@property (nonatomic, copy) NSString *strD0;//公司地址省份
@property (nonatomic, copy) NSString *strD2;//全拼
@property (nonatomic, copy) NSString *strD3;//全拼首字母
@property (nonatomic, copy) NSString *strH;//家庭地址省
@property (nonatomic, copy) NSString *strJ;//家庭地址市
@property (nonatomic, copy) NSString *strM;//家庭地址详细
@property (nonatomic, copy) NSString *strO;//生日
@property (nonatomic, copy) NSString *strP;//电话号码
@property (nonatomic, copy) NSString *strQ;//商务手机
@property (nonatomic, copy) NSString *strR;//公司固话
@property (nonatomic, copy) NSString *strS;//常用固话
@property (nonatomic, copy) NSString *strSD;//id
@property (nonatomic, copy) NSString *strU;//公司固话
@property (nonatomic, copy) NSString *strY;//个人邮箱
@property (nonatomic, copy) NSString *strZ;//商务邮箱
@property (nonatomic, copy) NSString *strF;//性别0男，1女，
@property (nonatomic, copy) NSString *strUN;//用户名
@property (nonatomic, copy) NSString *strUIN;//用户标识
@property (nonatomic, copy) NSString *strCTE;//CreateTime
@property (nonatomic, copy) NSString *strMTE;//ModifyTime
@property (nonatomic, copy) NSString *strGD;//分组id
@property (nonatomic, assign) BOOL isVIP;//vip
@property (nonatomic, assign) BOOL isSelected;

+ (THinkMail_VIPContactModel *)parserContactString:(NSString *)srcString;
@end

typedef enum {
    EVIPContactsList,
    EVIPContactsNewModify,
    EVIPContactsAddOrModify,
    EVIPContactsDelete,
    EVIPContactsIncrement,
    EVIPContactsDepartment,
    EVIPContactsVipContacts,
    EVIPContactsQueryUserInfo
}EVIPContactsType;


@interface THinkMail_VIPContactResponse : TKMResponsedBase
@property(nonatomic, strong) THinkMail_VIPContact *contactsObj;
- (THinkMail_VIPContact *)parserContactString:(NSString *)srcString;
@end

@interface THinkMail_addGroupContactRequst : TKMRequestBase
@property(nonatomic, strong) NSString *mobileNumber;
@property(nonatomic, strong) NSString *groupID;
@property(nonatomic, strong) NSString *groupType;
@property(nonatomic, strong) NSString *serialIds;
@end

@interface THinkMail_delGroupContactRequst : TKMRequestBase
@property(nonatomic, strong) NSString *mobileNumber;
@property(nonatomic, strong) NSString *groupID;
@property(nonatomic, strong) NSString *groupType;
@property(nonatomic, strong) NSString *serialIds;
@end

@interface THinkMail_139ContactDetailRequst : TKMRequestBase
@property(nonatomic, strong) NSString *mobileNumber;
@property(nonatomic, strong) NSString *serialId;
@end

@interface THinkMail_ContactDetailRequst : TKMRequestBase
@property(nonatomic, strong) NSString *corpID;
@property(nonatomic, strong) NSString *serialId;
@end

@interface THinkMail_UploadUserImageRequst : TKMRequestBase
@property(nonatomic, strong) NSString *filename;
@property(nonatomic, strong) NSString *serialId;
@property(nonatomic, strong) NSData *imageData;
@property(nonatomic, strong) NSString *BOUNDARY;
@property(nonatomic)NSInteger fileSize;
@end



#pragma mark 个人通讯录

@interface THinkMail_PrivateContactGroupListRequst : TKMRequestBase
@property(nonatomic, strong) NSString *opType;//操作类型

@end

@interface  TKMResponseModel_PrivateContactData : NSObject
@property (nonatomic,strong) NSString *groupId;//组id
@property (nonatomic,strong) NSString *groupName;//组名
@property (nonatomic,assign) NSInteger linkManCount;//组里的联系人个数
@end

@interface TKMResponeModel_PrivateContactGroupList: TKMResponsedBase
@property (nonatomic,assign) NSInteger linkManTotalCount;//联系人总数
@property (nonatomic,strong) NSMutableArray *groupList;//组列表

+ (TKMResponeModel_PrivateContactGroupList *)parseResponseData:(NSDictionary*)dict;

@end


@interface THinkMail_PrivateContactListRequst : TKMRequestBase
@property(nonatomic, strong) NSString *invalid_linkman_flag;//是否查询有效的联系人
@property(nonatomic, strong) NSString*groupId;//组id
@end

@interface TKMResponeModel_PrivateContactPersonData :NSObject

@property(nonatomic,strong)NSString *contactPersonId; //联系人id
@property(nonatomic,strong)NSString *uin;//联系人邮箱id
@property(nonatomic,assign)NSInteger type;
@property(nonatomic,assign)BOOL isVip;//是否vip
@property(nonatomic,strong)NSArray*emails;//邮件
@property(nonatomic,copy)NSString*email;//邮件
@property(nonatomic,strong)NSArray*mobiles;//手机
@property(nonatomic,strong)NSArray*groupId;//组id
@property(nonatomic,strong)NSString*lastContactTime;//上次联系时间
@property(nonatomic,strong)NSString*firstName;//名称

@end


@interface TKMResponeModel_PrivateContactList: TKMResponsedBase

@property (nonatomic,strong) NSMutableArray *contactPersonList;//联系人列表

+ (TKMResponeModel_PrivateContactList *)parseResponseData:(NSDictionary*)dict;

@end

@interface THinkMail_PrivateContactPersonDetailRequst : TKMRequestBase
@property(nonatomic, strong) NSString *data_type;
@property(nonatomic, strong) NSString *linkman_id;//联系人id
@property(nonatomic, strong) NSString *invalid_linkman_flag;//是否查询有效的联系人

@end

@interface TKMResponeModel_PrivateContactPersonDetail: TKMResponsedBase

@property (nonatomic,strong) TKMResponeModel_PrivateContactPersonData*personData;//联系人详情模型

+ (TKMResponeModel_PrivateContactPersonDetail *)parseResponseData:(NSDictionary*)dict;

@end

@interface THinkMail_PrivateContactGroupAdminRequst : TKMRequestBase
@property(nonatomic, strong) NSString *opType;//操作类型 add update delete
@property(nonatomic, strong) NSString *group_name;//分组名称
@property(nonatomic, strong) NSString *group_id;//分组id

@end

@interface THinkMail_PrivateContactPersonAdminRequst : TKMRequestBase
@property(nonatomic, strong) NSString *opType;//操作类型 add update delete
@property(nonatomic, strong) NSString *group_id;//分组id

@property(nonatomic, strong) NSString *firstName;//姓名

@property(nonatomic, strong) NSString *email;//邮箱

@property(nonatomic, strong) NSString *mobile_number;//手机号

@property(nonatomic, strong) NSString *contactId;//联系人id

@end


@interface THinkMail_DeletePersonContactsAdminRequst : TKMRequestBase

@property(nonatomic, strong) NSString *opType;//操作类型 add update delete
/* 联系人id arr **/
@property (nonatomic, strong) NSMutableArray * strIDDataArr;
@end

@interface TKMResponeModel_DeletePersonContactsData: NSObject

@property(nonatomic,assign)NSInteger client_seq;
@property(nonatomic,copy)NSString *linkman_id;
@property(nonatomic,copy)NSString *retsult_msg;
@end

@interface TKMResponeModel_DeletePersonContactsRseponse: TKMResponsedBase

@property (nonatomic,strong) NSMutableArray *resultList;//删除返回信息

+ (TKMResponeModel_DeletePersonContactsRseponse *)parseResponseData:(NSDictionary*)dict;

@end



@interface THinkMail_PrivateContactPersonMoveRequest : TKMRequestBase
@property (nonatomic, strong) NSMutableDictionary * userIDAndGroup;//联系人id
@property (nonatomic, copy) NSString * theNewGroupID;//新的分组id

@end

@interface THinkMail_PrivateContactSearchRequst : TKMRequestBase

@property(nonatomic,strong) NSString *cropId;//公司id
@property(nonatomic,assign) NSInteger dataType;
@property(nonatomic,assign) NSInteger total; //搜索条数
@property(nonatomic,strong) NSString *content;//搜索关键字
@property(nonatomic,strong) NSString *userId;

@end

@interface TKMResponeModel_PrivateContactSearchList: TKMResponsedBase

@property (nonatomic,strong) NSMutableArray *resultList;//搜索结果列表

+ (TKMResponeModel_PrivateContactSearchList *)parseResponseData:(NSDictionary*)dict;

@end


@interface THinkMail_getContactOnSendMailSearchRequst : TKMRequestBase

@property(nonatomic,strong) NSString *cropId;//公司id
@property(nonatomic,assign) NSInteger dataType;//搜索范围/类型
@property(nonatomic,assign) NSInteger total; //搜索条数
@property(nonatomic,assign) NSInteger start; //分页
@property(nonatomic,assign) NSInteger is_mix_search; //是否混合搜索
@property(nonatomic,strong) NSString *content;//搜索关键字
//@property(nonatomic,strong) NSString *userId;

@end






