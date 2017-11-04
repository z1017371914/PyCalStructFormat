#pragma once

#pragma region
#define GETMODE			0x10000001		// 得到封装类型
#define GETLENGTH		0x10000002		// 得到封装类型的长度
#define GETCTRL			0x10000003		// 得到控制消息
#define GETJMSG			0x10000004		// 得到J消息
#define PPLI_2_2		0x10000005		// PPLI2.2
#define PPLI_2_5		0x10000006		// PPLI2.5
#define REALDISPLAY     0x10000007		// 实时消息
#define COMMONDISPLAY	0x10000008		// 普通消息
#define COUNTDISPLAY	0x10000009		// 消息统计
#define OPENCHECK		0x10000010		// 开机自检
#define HARDWARE		0x10000011		// 硬件结果
#define ADDSLOT			12				// 增加时隙延时

#pragma endregion 自定义宏

#pragma region
typedef struct HeaderAck
{
	UINT	struMsgHeader;
}HEADSCR, *pHeader;

typedef struct VerisonMsg
{
	UINT	struMsgHeader;
	UINT    uVersionMsg[5];
}*pVerisonMsg;

typedef struct SysTime			// 系统时间
{
	UCHAR		ucEpochNum;		// 时元号
	UCHAR		ucFrameNum;		// 时帧号
	USHORT		usSlotNum;		// 时隙号
}STRU_SYS_TIME, *pSysTime;

typedef struct SlotSrc			// 时隙设置
{
	UCHAR		ucSetNum;		// 组号0:A 1:B 3:C
	USHORT		ucIndex;		// 时元内时隙号
	UCHAR		ucRrn;			// 重复率
}STRU_SLOT_SRC, *pSlotSrc;

typedef struct StruTxdata					// J消息发送时隙结构
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strTxSlotSrc;		// 该消息发送时隙号
	USHORT				uiTxMsgNo;			// 发送消息序列号
	USHORT				uiTxMsgLength;		// 时隙消息所占字节数
	UCHAR				ucTxMsgData[379];	// J消息（报头+内容）
}StruRxdata, *pStTxData;

typedef struct RttInit
{
	UCHAR				ucRttItype;			// RTT模式
	USHORT				usRttIPara;			// RTTA时表示目标源航迹号，RTTB时表示时间质量
}STRU_RTTI, *pRtt;

typedef struct SysWorkTime					// 状态初始化信息
{
	UINT				struMsgHeader;
	UCHAR				ucWorkMode;			// 工作模式 0：正常模式
	UCHAR				ucNtrIndicator;		// 指示是否是NTR 1：是； 0：不是		
	STRU_RTTI			strRttI;			// RTTI配置参数结构体
	UCHAR				ucTransMode;		// 通信模式  跳频0
	UCHAR				ucFreqNum;			// 单频 0~50
	USHORT				SrcTrackNum;		// 源航迹号
	USHORT				usSduNum;			// SDU序列号
	STRU_SYS_TIME		strSysTime;			// 系统时间
	STRU_SLOT_SRC		strRttSlot;			// RTT时隙资源
	UCHAR				ucFreqSeed;			// 跳频种子
	UCHAR				ucJitterSeed;		// 跳时种子
}STRU_INIT_NET, *pInitNet;

typedef struct Juinitack						// 模拟器上报开机自检结构
{
	UINT				struMsgHeader;
	UCHAR				ucJUSelfTestRes[10];	// 模拟结果
}STRU_SELFTEST_DATA, *pSelf;

typedef struct JustateData						// 模拟器运行状态
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strNetTime;				// 网络时间
	UCHAR				ucJUState;				// 模拟器状态 0：未同步 1：以同步  2：以入网  3：重入网
	UCHAR				ucTimeQual;				// 时间质量
	UCHAR				ucMsgSpace;				// 剩余消息空间
	UINT				uiErrorCode;			// 错误代码
}STRU_JUSTATE_DATA, *pJuState;

typedef struct HwState							// 模拟器运行中硬件状态
{
	UINT				struMsgHeader;
	UCHAR				ucJUHwState[30];
}STRU_HW_STATE, *pHwState;

typedef struct StruNetMsg						// 入网状态
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strNetTime;				// 网络时间
	USHORT				uiMsgNo;				// RTT消息类型
	USHORT				usRevMsgLength;			// 消息所占字节数
	UCHAR				ucJURxMsg[379];
}STRU_JU_NET_MSG, *pNet;

typedef struct StPower							// 开关状态
{
	UINT				struMsgHeader;
	UINT				uiHwPower;				// 开关标志位	0表示关，1表示开
}STR_HW_GNFIG, *pPower;

// 信息终端->模拟器 
#define HANDSHAKEINQ		0x20000001			// PC->端机握手
#define SELFTESTCTL			0x20000007			// PC->端机自检
#define INITPARA			0x20000003			// PC->端机初始化
#define SLOTTXDATA			0x20000005			// PC->端机时隙参数
#define POWERSWITCH         0x2000000E			// PC->端机开关
#define RETURNFLAG			0x20000000			// PC退出标志位
#define RESYSTEMINFO		0x20000004          // PC重新配置系统信息
// 模拟器->信息终端
#define HANDSHAKEACK		0x60000001			// 端机->PC回复握手信息
#define SELFTESTACK			0x60000007			// 端机->PC回复自检确认
#define SELFTESTDATA		0x40000001			// 端机->PC自检结果统计
#define INITACK				0x60000003			// 端机->PC回复初始化应答
#define JUSTATE				0x60000004			// 端机->PC发送端机运行状态
#define JUMSG				0x60000005			// 端机->PC空口消息
#define HWSTATE				0x40000002			// 端机->PC上报硬件状态
#define JUNETMSG			0x6000000A			// 端机->PC上报入网过程
#define SWITCHPOWER         0x6000000E			// 端机->PC开关
#define VERSIONMSG			0x6000000B			// 端机->PCVersion版本号

#pragma endregion 通信协议

#pragma region
typedef struct main_parameter
{
	int usIndex; //封装模式
	int srcTrackNumber;//源航迹号
	int SDUnumber;//SDU序列号
	int type;//测试类型
	int mode;//封装模式
	int n;
	int m;
	int destTrackNumber;//目的源航迹号
	int RT_TM;//0为J消息 1为音频
	bool E[2];
	bool C[7];
}main_parameter;//主要参数
typedef struct PPLI2_2
{
	int time;					//4位	时间质量
	double hight;				//13位	高度
	double Latitude;			//23位  纬度
	double Longitude;			//24位	经度
	int azimuth;				//9位	航向
	int speed;					//11位  速度
}PPLI2_2;

typedef struct PPLI2_5
{
	int location;				//1位  在延长字还是继续字有位置信息
	int time;					//4位  时间质量
	double hight;				//11位 海拔
	double Latitude;			//23位 纬度
	double Longitude;			//24位 经度
	int Identity;				//6位  陆地地点身份
	int action;					//7位  陆地地点活动
}PPLI2_5;

typedef struct Message_rcv
{
	int srcTrackNumber;//源地址
	int mode;//封装模式
	int SN;//序列号
	int n;
	int m;
	int len;//长度
	int RT_TM;
	int destTrackNumber;//目的地址
	int SDUNumber;
}Message_rcv;

typedef struct Message_Send_data
{
	UCHAR * Message_Data;
}Message_Send_data;
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define		STDP 4
#define		P2SP 3
#define		P2DP 5
#define		P4SP 7
#define		STOP 6
#define     VOICE            6//音频代号
#define     HEADER_LENGTH    7//报头长度

#define     ORDINARY_TEST    1//普通测试TYPE类型
#define     REALTIME_TEST    0//实时测试TYPE类型
#define     STDP_LENGTH      52//stdp长度
#define     P2SP_LENGTH      97//P2SP长度
#define		P2DP_LENGTH      97//p2dp长度
#define     P4SP_LENGTH      187//p4sp长度
#define     WORD_LENGTH      15//字长
#define     ERROR_CODE       0 //错误码
#define     BROADCAST		 127//广播号 
#define		SENDSOLT		 20 //提前时隙	
#pragma endregion 消息解析

#pragma region
class CInputIPDlg;
class CLink16_SignalDlg;
class CSetInitSystemDlg;
class CTestRealMsg;
class CTestOrdiaryMsg;
class CSetPPLIMsg;
class JMsgRcv;
class CSocketLink16;
class VoiceProcessing;
class CStateDisplay;
class CHelp;
class CWriteLog;
class CSoundOut;
class CCountNumber;
// 保存全局变量
class CGlobalSaveVariable
{
public:
	CGlobalSaveVariable();
	virtual ~CGlobalSaveVariable();
public:
	// 全局对话框变量
	CInputIPDlg			*		pInputIPDlg;			// IP配置对话框指针
	CLink16_SignalDlg	*	    pMainDlg;				// 主对话框指针
	CSetInitSystemDlg	*		pSetInitSystem;			// 系统配置对话框指针
	CTestRealMsg		*		pTestRealMsg;			// 实时测试对话框
	CTestOrdiaryMsg     *		pTestOrdiaryMsg;		// 普通测试对话框指针
	CSetPPLIMsg			*		pPPLIMsg;				// 设置PPLI消息对话框指针
	JMsgRcv             *       JmsgRcv;				// J消息接收
	VoiceProcessing     *		pVoice;					// 语音类指针
	CStateDisplay		*		pStateDis;				// 硬件状态显示 
	CHelp				*		pHelp;					// 帮助对话框
	CWriteLog			*		pWrite;					// 保存日志
	CSoundOut           *       pSoundOut;				// 语音输出
	CCountNumber		*       pCountNumber;			// 消息统计对话框
};
extern CGlobalSaveVariable SaveDlgPoint;					// 保存对话框指针


class CGlobalUseVariable
{
public:
	CGlobalUseVariable();
	virtual ~CGlobalUseVariable();
public:
	USHORT usSrPath;					// 本机源航迹号
	USHORT g_usSduNum;					// 全局SDU
};
extern CGlobalUseVariable SaveUseVar;	// 保存对话框指针
#pragma endregion 全局变量

#pragma region
//发送数据类型定义
#define TX_NONE  0         //不发任何信息
#define TX_RTTA  1         //发送RTTA
#define TX_PPLI  2         //发送PPLI
#define TX_JMSG  3         //发送J消息
#define TX_WAVE  4         //发送语音
//3组共12台端机源航迹号定义                          
#define ST_GPA0  1         //A组端机1源航迹号
#define ST_GPA1  2         //A组端机2源航迹号
#define ST_GPA2  3         //A组端机3源航迹号
#define ST_GPA3  4         //A组端机4源航迹号
#define ST_GPB0  5         //B组端机1源航迹号
#define ST_GPB1  6         //B组端机2源航迹号
#define ST_GPB2  7         //B组端机3源航迹号
#define ST_GPB3  8         //B组端机4源航迹号
#define ST_GPC0  9         //C组端机1源航迹号
#define ST_GPC1  10        //C组端机2源航迹号
#define ST_GPC2  11        //C组端机3源航迹号
#define ST_GPC3  12        //C组端机4源航迹号
//AB组时隙分配参数定义
#define GA_STR0  0         //A组端机1起始时隙号
#define GA_STR1  4         //A组端机2起始时隙号
#define GA_STR2  8         //A组端机3起始时隙号
#define GA_STR3  11        //A组端机4起始时隙号
#define GB_STR0  1         //B组端机1起始时隙号
#define GB_STR1  9         //B组端机2起始时隙号
#define GB_STR2  15        //B组端机3起始时隙号
#define GB_STR3  19        //B组端机4起始时隙号
#define GA_GAPU  6         //A组端机时隙最小间隔
#define GB_GAPU  12        //B组端机时隙最小间隔
#define GA_SMAX  84        //A组端机最大时隙对数
#define GB_SMAX  42        //B组端机最大时隙对数
#pragma endregion 时隙发送列表