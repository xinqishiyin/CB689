#define _SYSTEM_H
#ifdef _SYSTEM_H
#include <SC51F2832.H>



#define MAX_TX_BYTES	30 	//串口最大发送字节数


#define uint	unsigned int
#define uchar 	unsigned char
#define ulong   unsigned long
#define u8	  	unsigned char
#define u16		unsigned int
#define u32		unsigned long


sbit ADGO = ADCON^2;
#define Channel_Start_Adress  0x03e8




/*---------------电压检测宏定义-----------------*/

#define ADC_ASQ       1      //adc0
#define ADC_Key1      2      //adc4
#define ADC_VOX       3      //adc5
#define ADC_RSSI      4      //adc2
#define ADC_AGCA      5      //adc3

#define KEY_SQ_VAL        0x034c
#define KEY_UP_VAL        0x02c1
#define KEY_DN_VAL        0x0292
#define KEY_VOX_VAL       0x0267
#define KEY_PTY_VAL       0x0200
#define KEY_AFM_VAL       0x0146

#define VOX_GAIN_VAL      0x0010

#define MAX_RX_BYTES	32	//串口最大接收字节数


/*---------------时间宏定义-----------------*/
#define BACK_TIME      			   80          //返回主界面时间
#define LONGPRESSTIME         	   15         //长按时间
#define KEY_COMBOlIMIT             20         //x组合按件时限
#define BUTTONTONE_TIME            5          //按键间响时长
#define TK_CYCL_TIME               15         //闪烁时间
#define SCAN_HOULD_TIME            313

/***************************************
*	             值映射                *
***************************************/
//LED开关值映射
#define ON			  	1 
#define OFF			  	0 
#define LIGHT_ON		1
#define LIGHT_OFF		0
#define OPEN			  1 
#define CLOSE		  	0

#define FM          0
#define AM          1

#define YES         1
#define NO        	0

#define TRY_TIMES 	5		//最多发送TRY_TIMES次指令

#define POWER_HIGH 	2
#define POWER_LOW	  1
#define POWER_1W	  0

//国家列表
#define COUNTRY_EU	0
#define COUNTRY_CE	1
#define COUNTRY_UK	2
#define COUNTRY_PL	3
#define COUNTRY_I0	4
#define COUNTRY_I2	5
#define COUNTRY_DE	6
#define COUNTRY_IN	7

//RU段
#define COUNTRY_RU	8

#define COUNTRY_RA	8
#define COUNTRY_RB	9
#define COUNTRY_RC	10
#define COUNTRY_RD	11
#define COUNTRY_RE	12
#define COUNTRY_RF	13
#define COUNTRY_RG	14
#define COUNTRY_RH	15
#define COUNTRY_RI	16
#define COUNTRY_RL	17


//HA--HI段
#define COUNTRY_HX	18

#define COUNTRY_HA	18
#define COUNTRY_HB	19
#define COUNTRY_HC	20
#define COUNTRY_HD	21
#define COUNTRY_HE	22
#define COUNTRY_HF	23
#define COUNTRY_HG	24
#define COUNTRY_HH	25
#define COUNTRY_HI	26

/*---------------------引脚宏定义--------------------------*/

/*----------------------LCD驱动----------------------------*/
#define LCD_SEG0                  P00
#define LCD_SEG1                  P01
#define LCD_SEG2                  P02
#define LCD_SEG3                  P03
#define LCD_SEG4                  P04
#define LCD_SEG5                  P05
#define LCD_SEG6                  P06
#define LCD_SEG7                  P07
#define LCD_SEG8                  (xP4|=0x01)
#define LCD_COM0                  P34
#define LCD_COM1                  P35
#define LCD_COM2                  P36
#define LCD_COM3                  P37


/*------------------------LCD屏三色--------------------------*/
#define SET_LIGHT_B               (xP4|=0x02)         
#define CLS_LIGHT_B               (xP4&=~0x02) 
#define LIGHT_R                   	P24
#define LIGHT_G                     P22





#define SET_AM_EN                 (xP4|=0x04)           //AM接收使能
#define CLS_AM_EN                 (xP4&=~0x04)

#define SET_MIC_MUTE              (xP4|=0x08)           //麦克风使能
#define CLS_MIC_MUTE              (xP4&=~0x08)
#define SET_AT_MUTE               (xP4|=0x10)           //AM模式禁止
#define CLS_AT_MUTE               (xP4&=~0x10)
#define SET_FM_EN                 (xP4|=0x20)						//FM接收使能
#define CLS_FM_EN                 (xP4&=~0x20)
#define AF_EN                      P11                  //AF接收使能

#define SET_BK4802_SCK            (xP4|=0x40)
#define CLS_BK4802_SCK            (xP4&=~0x40)
#define SET_BK4802_SDA            (xP4|=0x80)
#define CLS_BK4802_SDA            (xP4&=~0x80)
#define SET_BK4802_SDA_OUT      	{xP4MDH &= 0x3F; xP4MDH |= 0x80;}
#define SET_BK4802_SDA_IN    			{xP4MDH &= 0x3F; xP4MDH |= 0x00;}
#define BK4802_SDA_IN        			((xP4&0x80)==0? 0:1)
#define BK4802_TRX                 P10									//收发状态切换，高电平为发射，低电平为接收
#define RX_P                       P13                  //接收电源



#define LED_GREEN                  P12                  //绿灯控制 
#define LED_RED                    P16									//红灯控制

#define POW_4W                     P14                  //4W发射功率控制
#define POW_1W                     P15									//1W发射功率控制


 
#define PPT                         P20                 //PPT按键
#define VOX                         P21

#define OP1        			((xP9&0x04)==0? 0:1)
#define OP2        			((xP9&0x08)==0? 0:1)

#define BEEP                      	xPWM0D              //按键音

/*-----------------------------频偏控制------------------------*/
#define MODDA                     	xPWM1D              //频偏设置
#define PWM_MODDA_OPEN            	xPWMCN |=0x20       
#define PWM_MODDA_CLOSE           	xPWMCN &= ~0x10


//#define ADC_SQ_ASQ                	0x08                //SQ ASQ电压等级
//#define ADC_KEY1                  	0x48								//按键判断
//#define ADC_VOX                   	0x58								//VOX电压
//#define ADC_RSSI                  	0x28                //RSSI电压
//#define ADC_AGCA                  	0x38								//AGCA电压



#define SetBit(VAR,Place)         ( (VAR) |= (u8)((u8)1<<(u8)(Place)) )
#define ClrBit(VAR,Place)         ( (VAR) &= (u8)((u8)((u8)1<<(u8)(Place))^(u8)255) )

enum
{
	UART0_IDLE,
	UART0_SYN,
	UART0_HEAD,
	UART0_DATA
};
enum
{
	Write,
	Read
};


typedef struct
{	 
	unsigned char FreqCal;		//系统时钟校准
	unsigned char CountryTable;	//国家列表
	unsigned char Country;		//国家
	unsigned char Band;			//频段            //ABCDEFGHIL
	unsigned char Modu;			//调制
	unsigned char TxPower;		//发射功率	
	unsigned char VolLevel;		//音量级别
	unsigned char Channel;		//通道
	unsigned char  LastChannel;  //最后使用通道
	unsigned char LastBand;
	unsigned char forEMGChannel;
	unsigned char LcdColor;               //LCD背景灯颜色
	unsigned char ButtonToneSwitch;				//按键音开关
	unsigned char SpkerSwitch;            //是否静音
	unsigned char UartTxBuf[MAX_TX_BYTES];
}tCbParam;		

typedef struct
{
	unsigned int Back_Channel_Time;
	unsigned int uartTimeCount;
	unsigned int ButtonToneTime;
	unsigned int TkCyclTime;
	unsigned int ScanHouldTime;
}tTimer;

typedef struct
{
	unsigned char KeyIndex1;	      //KEY1 AD值 索引
	unsigned char Power_Time;	//电源键长按时长
	unsigned char DoublePress_Limit;	//双击时限
	unsigned char DoublePress_Count;  //双击次数
	unsigned char Press_Count;          //按键次数
	unsigned char MutePress_Timelimit;  //静音（电源）长按时长
	unsigned char MuteDoublePress_Timelimit;  //静音（电源）双击时限
	unsigned char LongPress_Time;          //长按SQ切换时长
	unsigned char MutePress_Count;      //电源按键次数
	unsigned char KeyComboLimit;        //组合键限时
	unsigned char isKeyCombo;
}tKey;

typedef struct
{
	unsigned char IsAsq;			  //是否为ASQ
	unsigned char IsVox;
	unsigned char AsqLevel;	    //ASQ级别	
	unsigned char Scan;             
	unsigned char ScanDir;
	unsigned char ScanHould ;	
	unsigned int HouldTime;
	unsigned char DisHould;	
}tSqParam;										//SQ模式


typedef struct
{
	unsigned char Rssi;
	unsigned char Ack;
	unsigned char ActivityChannel;
	unsigned char MaxChannel;
	unsigned char MinChannel;
	unsigned char LastChannel;
	unsigned char LastBand;
	unsigned char BackChannel;
	unsigned char BackBand;
	unsigned char ThisChannel;
	unsigned char ThisBand;
	unsigned char MaxCountry;
	unsigned char MinCountry;
	unsigned char HitPower;
	unsigned char isMute;
	unsigned char isLastChannel;
	unsigned char isUK;
	unsigned char SpkOpen;
	unsigned int mAsqVoltage;
	unsigned int mRssiVoltage;
	unsigned int mAgcaVoltage;	
	unsigned char isButtonTone;
	unsigned char rest;
}tSysParam;                             //变量表

typedef struct
{
	unsigned char mRssi;
	unsigned int h_Fre_Tx;            
	unsigned int l_Fre_Tx;
	unsigned int h_Fre_Rx;
	unsigned int l_Fre_Rx;
	unsigned char NDIV_FRE; 
}tVcoParam;                             //Voc参数


typedef struct
{
	unsigned char RecvStatus;		//接收状态
	unsigned char RecvCount;	  //接收数量
	unsigned char WriteOrRead;  //读写选择位
	unsigned char AdressLenth;	//读写长度
	unsigned char isSendData;
	unsigned char isReciveData;
	unsigned char RecvBuf[MAX_RX_BYTES];       //0:接收标识   1：接收指令码  2：接收数据长度  3：接收数据值  4：
}tReceivePackage;	

typedef struct
{
	unsigned int ASQ_Vol;		
	unsigned int KEY1_Vol; 	
	unsigned int VOX_Vol;
	unsigned int RSSI_Vol; 
	unsigned int AGCA_Vol;
  unsigned int BK4802_Snr;
  unsigned int BK4802_Rssi;	
	unsigned int BK4802_ASQ;
}tVoltageSend;

/*-------------菜单参数---------------------------*/
typedef struct
{
	unsigned char isBussy;	      //忙 防重调用
	unsigned char MenuIndex;		  //菜单索引
	unsigned char BackMenuIndex;   //反回菜单索引存储
	unsigned char Back_Channel_Time;	//返回主菜单时间
	unsigned char isLock;			      //是否锁键
	unsigned char emgIndex;		    //紧急信道标识
	unsigned char isTx;			        //发射状态
	unsigned char isBackChannel;
	unsigned char keyCombSQUP;     //组合键切换按键音
	unsigned char keyCombSQDN;     //组合键切换屏颜色

	unsigned char isTkShow;        //闪烁  亮灭标识
	
}tMenu;	

extern tCbParam mCbParam;                    
extern tSqParam mSqParam;
extern tSysParam mSysParam;
extern tVcoParam mVcoParam;
extern tTimer mTimer;
extern uchar mUartCmd;
extern tReceivePackage mReceivePackage;
extern tVoltageSend mVoltageSend;
extern tMenu mMenu;
extern xdata tKey mKey;
/*----------------------vco相关-----------------*/

void SystemInit(void);
/*-------------------------------------------------------------------------
*函数：delayms  延时1ms
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void delayms(u16 time);
/*-------------------------------------------------------------------------
*函数：delayus  延时6.5us左右
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void delayus(u8 i);
/*-------------------------------------------------------------------------
*函数：UART0_Init  串口中断初使化
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void UART0_Init();
/*-------------------------------------------------------------------------
*函数：IO_Init  IO口初使化
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void IO_Init();
/*-------------------------------------------------------------------------
*函数：Get_AD  AD口获取值
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
u16 Get_AD(u8 AD_IO);
/*-------------------------------------------------------------------------
*函数：PowerOnShow  开机显示
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void PowerOnShow();
/*-------------------------------------------------------------------------
*函数：playButtonTone  按键音判断
*参数：
*返回值：
*-------------------------------------------------------------------------*/
void playButtonTone(void);
#endif