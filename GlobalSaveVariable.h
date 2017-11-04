#pragma once

#pragma region
#define GETMODE			0x10000001		// �õ���װ����
#define GETLENGTH		0x10000002		// �õ���װ���͵ĳ���
#define GETCTRL			0x10000003		// �õ�������Ϣ
#define GETJMSG			0x10000004		// �õ�J��Ϣ
#define PPLI_2_2		0x10000005		// PPLI2.2
#define PPLI_2_5		0x10000006		// PPLI2.5
#define REALDISPLAY     0x10000007		// ʵʱ��Ϣ
#define COMMONDISPLAY	0x10000008		// ��ͨ��Ϣ
#define COUNTDISPLAY	0x10000009		// ��Ϣͳ��
#define OPENCHECK		0x10000010		// �����Լ�
#define HARDWARE		0x10000011		// Ӳ�����
#define ADDSLOT			12				// ����ʱ϶��ʱ

#pragma endregion �Զ����

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

typedef struct SysTime			// ϵͳʱ��
{
	UCHAR		ucEpochNum;		// ʱԪ��
	UCHAR		ucFrameNum;		// ʱ֡��
	USHORT		usSlotNum;		// ʱ϶��
}STRU_SYS_TIME, *pSysTime;

typedef struct SlotSrc			// ʱ϶����
{
	UCHAR		ucSetNum;		// ���0:A 1:B 3:C
	USHORT		ucIndex;		// ʱԪ��ʱ϶��
	UCHAR		ucRrn;			// �ظ���
}STRU_SLOT_SRC, *pSlotSrc;

typedef struct StruTxdata					// J��Ϣ����ʱ϶�ṹ
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strTxSlotSrc;		// ����Ϣ����ʱ϶��
	USHORT				uiTxMsgNo;			// ������Ϣ���к�
	USHORT				uiTxMsgLength;		// ʱ϶��Ϣ��ռ�ֽ���
	UCHAR				ucTxMsgData[379];	// J��Ϣ����ͷ+���ݣ�
}StruRxdata, *pStTxData;

typedef struct RttInit
{
	UCHAR				ucRttItype;			// RTTģʽ
	USHORT				usRttIPara;			// RTTAʱ��ʾĿ��Դ�����ţ�RTTBʱ��ʾʱ������
}STRU_RTTI, *pRtt;

typedef struct SysWorkTime					// ״̬��ʼ����Ϣ
{
	UINT				struMsgHeader;
	UCHAR				ucWorkMode;			// ����ģʽ 0������ģʽ
	UCHAR				ucNtrIndicator;		// ָʾ�Ƿ���NTR 1���ǣ� 0������		
	STRU_RTTI			strRttI;			// RTTI���ò����ṹ��
	UCHAR				ucTransMode;		// ͨ��ģʽ  ��Ƶ0
	UCHAR				ucFreqNum;			// ��Ƶ 0~50
	USHORT				SrcTrackNum;		// Դ������
	USHORT				usSduNum;			// SDU���к�
	STRU_SYS_TIME		strSysTime;			// ϵͳʱ��
	STRU_SLOT_SRC		strRttSlot;			// RTTʱ϶��Դ
	UCHAR				ucFreqSeed;			// ��Ƶ����
	UCHAR				ucJitterSeed;		// ��ʱ����
}STRU_INIT_NET, *pInitNet;

typedef struct Juinitack						// ģ�����ϱ������Լ�ṹ
{
	UINT				struMsgHeader;
	UCHAR				ucJUSelfTestRes[10];	// ģ����
}STRU_SELFTEST_DATA, *pSelf;

typedef struct JustateData						// ģ��������״̬
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strNetTime;				// ����ʱ��
	UCHAR				ucJUState;				// ģ����״̬ 0��δͬ�� 1����ͬ��  2��������  3��������
	UCHAR				ucTimeQual;				// ʱ������
	UCHAR				ucMsgSpace;				// ʣ����Ϣ�ռ�
	UINT				uiErrorCode;			// �������
}STRU_JUSTATE_DATA, *pJuState;

typedef struct HwState							// ģ����������Ӳ��״̬
{
	UINT				struMsgHeader;
	UCHAR				ucJUHwState[30];
}STRU_HW_STATE, *pHwState;

typedef struct StruNetMsg						// ����״̬
{
	UINT				struMsgHeader;
	STRU_SYS_TIME		strNetTime;				// ����ʱ��
	USHORT				uiMsgNo;				// RTT��Ϣ����
	USHORT				usRevMsgLength;			// ��Ϣ��ռ�ֽ���
	UCHAR				ucJURxMsg[379];
}STRU_JU_NET_MSG, *pNet;

typedef struct StPower							// ����״̬
{
	UINT				struMsgHeader;
	UINT				uiHwPower;				// ���ر�־λ	0��ʾ�أ�1��ʾ��
}STR_HW_GNFIG, *pPower;

// ��Ϣ�ն�->ģ���� 
#define HANDSHAKEINQ		0x20000001			// PC->�˻�����
#define SELFTESTCTL			0x20000007			// PC->�˻��Լ�
#define INITPARA			0x20000003			// PC->�˻���ʼ��
#define SLOTTXDATA			0x20000005			// PC->�˻�ʱ϶����
#define POWERSWITCH         0x2000000E			// PC->�˻�����
#define RETURNFLAG			0x20000000			// PC�˳���־λ
#define RESYSTEMINFO		0x20000004          // PC��������ϵͳ��Ϣ
// ģ����->��Ϣ�ն�
#define HANDSHAKEACK		0x60000001			// �˻�->PC�ظ�������Ϣ
#define SELFTESTACK			0x60000007			// �˻�->PC�ظ��Լ�ȷ��
#define SELFTESTDATA		0x40000001			// �˻�->PC�Լ���ͳ��
#define INITACK				0x60000003			// �˻�->PC�ظ���ʼ��Ӧ��
#define JUSTATE				0x60000004			// �˻�->PC���Ͷ˻�����״̬
#define JUMSG				0x60000005			// �˻�->PC�տ���Ϣ
#define HWSTATE				0x40000002			// �˻�->PC�ϱ�Ӳ��״̬
#define JUNETMSG			0x6000000A			// �˻�->PC�ϱ���������
#define SWITCHPOWER         0x6000000E			// �˻�->PC����
#define VERSIONMSG			0x6000000B			// �˻�->PCVersion�汾��

#pragma endregion ͨ��Э��

#pragma region
typedef struct main_parameter
{
	int usIndex; //��װģʽ
	int srcTrackNumber;//Դ������
	int SDUnumber;//SDU���к�
	int type;//��������
	int mode;//��װģʽ
	int n;
	int m;
	int destTrackNumber;//Ŀ��Դ������
	int RT_TM;//0ΪJ��Ϣ 1Ϊ��Ƶ
	bool E[2];
	bool C[7];
}main_parameter;//��Ҫ����
typedef struct PPLI2_2
{
	int time;					//4λ	ʱ������
	double hight;				//13λ	�߶�
	double Latitude;			//23λ  γ��
	double Longitude;			//24λ	����
	int azimuth;				//9λ	����
	int speed;					//11λ  �ٶ�
}PPLI2_2;

typedef struct PPLI2_5
{
	int location;				//1λ  ���ӳ��ֻ��Ǽ�������λ����Ϣ
	int time;					//4λ  ʱ������
	double hight;				//11λ ����
	double Latitude;			//23λ γ��
	double Longitude;			//24λ ����
	int Identity;				//6λ  ½�صص����
	int action;					//7λ  ½�صص�
}PPLI2_5;

typedef struct Message_rcv
{
	int srcTrackNumber;//Դ��ַ
	int mode;//��װģʽ
	int SN;//���к�
	int n;
	int m;
	int len;//����
	int RT_TM;
	int destTrackNumber;//Ŀ�ĵ�ַ
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
#define     VOICE            6//��Ƶ����
#define     HEADER_LENGTH    7//��ͷ����

#define     ORDINARY_TEST    1//��ͨ����TYPE����
#define     REALTIME_TEST    0//ʵʱ����TYPE����
#define     STDP_LENGTH      52//stdp����
#define     P2SP_LENGTH      97//P2SP����
#define		P2DP_LENGTH      97//p2dp����
#define     P4SP_LENGTH      187//p4sp����
#define     WORD_LENGTH      15//�ֳ�
#define     ERROR_CODE       0 //������
#define     BROADCAST		 127//�㲥�� 
#define		SENDSOLT		 20 //��ǰʱ϶	
#pragma endregion ��Ϣ����

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
// ����ȫ�ֱ���
class CGlobalSaveVariable
{
public:
	CGlobalSaveVariable();
	virtual ~CGlobalSaveVariable();
public:
	// ȫ�ֶԻ������
	CInputIPDlg			*		pInputIPDlg;			// IP���öԻ���ָ��
	CLink16_SignalDlg	*	    pMainDlg;				// ���Ի���ָ��
	CSetInitSystemDlg	*		pSetInitSystem;			// ϵͳ���öԻ���ָ��
	CTestRealMsg		*		pTestRealMsg;			// ʵʱ���ԶԻ���
	CTestOrdiaryMsg     *		pTestOrdiaryMsg;		// ��ͨ���ԶԻ���ָ��
	CSetPPLIMsg			*		pPPLIMsg;				// ����PPLI��Ϣ�Ի���ָ��
	JMsgRcv             *       JmsgRcv;				// J��Ϣ����
	VoiceProcessing     *		pVoice;					// ������ָ��
	CStateDisplay		*		pStateDis;				// Ӳ��״̬��ʾ 
	CHelp				*		pHelp;					// �����Ի���
	CWriteLog			*		pWrite;					// ������־
	CSoundOut           *       pSoundOut;				// �������
	CCountNumber		*       pCountNumber;			// ��Ϣͳ�ƶԻ���
};
extern CGlobalSaveVariable SaveDlgPoint;					// ����Ի���ָ��


class CGlobalUseVariable
{
public:
	CGlobalUseVariable();
	virtual ~CGlobalUseVariable();
public:
	USHORT usSrPath;					// ����Դ������
	USHORT g_usSduNum;					// ȫ��SDU
};
extern CGlobalUseVariable SaveUseVar;	// ����Ի���ָ��
#pragma endregion ȫ�ֱ���

#pragma region
//�����������Ͷ���
#define TX_NONE  0         //�����κ���Ϣ
#define TX_RTTA  1         //����RTTA
#define TX_PPLI  2         //����PPLI
#define TX_JMSG  3         //����J��Ϣ
#define TX_WAVE  4         //��������
//3�鹲12̨�˻�Դ�����Ŷ���                          
#define ST_GPA0  1         //A��˻�1Դ������
#define ST_GPA1  2         //A��˻�2Դ������
#define ST_GPA2  3         //A��˻�3Դ������
#define ST_GPA3  4         //A��˻�4Դ������
#define ST_GPB0  5         //B��˻�1Դ������
#define ST_GPB1  6         //B��˻�2Դ������
#define ST_GPB2  7         //B��˻�3Դ������
#define ST_GPB3  8         //B��˻�4Դ������
#define ST_GPC0  9         //C��˻�1Դ������
#define ST_GPC1  10        //C��˻�2Դ������
#define ST_GPC2  11        //C��˻�3Դ������
#define ST_GPC3  12        //C��˻�4Դ������
//AB��ʱ϶�����������
#define GA_STR0  0         //A��˻�1��ʼʱ϶��
#define GA_STR1  4         //A��˻�2��ʼʱ϶��
#define GA_STR2  8         //A��˻�3��ʼʱ϶��
#define GA_STR3  11        //A��˻�4��ʼʱ϶��
#define GB_STR0  1         //B��˻�1��ʼʱ϶��
#define GB_STR1  9         //B��˻�2��ʼʱ϶��
#define GB_STR2  15        //B��˻�3��ʼʱ϶��
#define GB_STR3  19        //B��˻�4��ʼʱ϶��
#define GA_GAPU  6         //A��˻�ʱ϶��С���
#define GB_GAPU  12        //B��˻�ʱ϶��С���
#define GA_SMAX  84        //A��˻����ʱ϶����
#define GB_SMAX  42        //B��˻����ʱ϶����
#pragma endregion ʱ϶�����б�