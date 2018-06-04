#define _SYSTEM_H
#ifdef _SYSTEM_H
#include <SC51F2832.H>



#define MAX_TX_BYTES	30 	//����������ֽ���


#define uint	unsigned int
#define uchar 	unsigned char
#define ulong   unsigned long
#define u8	  	unsigned char
#define u16		unsigned int
#define u32		unsigned long


sbit ADGO = ADCON^2;
#define Channel_Start_Adress  0x03e8




/*---------------��ѹ���궨��-----------------*/

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

#define MAX_RX_BYTES	32	//�����������ֽ���


/*---------------ʱ��궨��-----------------*/
#define BACK_TIME      			   80          //����������ʱ��
#define LONGPRESSTIME         	   15         //����ʱ��
#define KEY_COMBOlIMIT             20         //x��ϰ���ʱ��
#define BUTTONTONE_TIME            5          //��������ʱ��
#define TK_CYCL_TIME               15         //��˸ʱ��
#define SCAN_HOULD_TIME            313

/***************************************
*	             ֵӳ��                *
***************************************/
//LED����ֵӳ��
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

#define TRY_TIMES 	5		//��෢��TRY_TIMES��ָ��

#define POWER_HIGH 	2
#define POWER_LOW	  1
#define POWER_1W	  0

//�����б�
#define COUNTRY_EU	0
#define COUNTRY_CE	1
#define COUNTRY_UK	2
#define COUNTRY_PL	3
#define COUNTRY_I0	4
#define COUNTRY_I2	5
#define COUNTRY_DE	6
#define COUNTRY_IN	7

//RU��
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


//HA--HI��
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

/*---------------------���ź궨��--------------------------*/

/*----------------------LCD����----------------------------*/
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


/*------------------------LCD����ɫ--------------------------*/
#define SET_LIGHT_B               (xP4|=0x02)         
#define CLS_LIGHT_B               (xP4&=~0x02) 
#define LIGHT_R                   	P24
#define LIGHT_G                     P22





#define SET_AM_EN                 (xP4|=0x04)           //AM����ʹ��
#define CLS_AM_EN                 (xP4&=~0x04)

#define SET_MIC_MUTE              (xP4|=0x08)           //��˷�ʹ��
#define CLS_MIC_MUTE              (xP4&=~0x08)
#define SET_AT_MUTE               (xP4|=0x10)           //AMģʽ��ֹ
#define CLS_AT_MUTE               (xP4&=~0x10)
#define SET_FM_EN                 (xP4|=0x20)						//FM����ʹ��
#define CLS_FM_EN                 (xP4&=~0x20)
#define AF_EN                      P11                  //AF����ʹ��

#define SET_BK4802_SCK            (xP4|=0x40)
#define CLS_BK4802_SCK            (xP4&=~0x40)
#define SET_BK4802_SDA            (xP4|=0x80)
#define CLS_BK4802_SDA            (xP4&=~0x80)
#define SET_BK4802_SDA_OUT      	{xP4MDH &= 0x3F; xP4MDH |= 0x80;}
#define SET_BK4802_SDA_IN    			{xP4MDH &= 0x3F; xP4MDH |= 0x00;}
#define BK4802_SDA_IN        			((xP4&0x80)==0? 0:1)
#define BK4802_TRX                 P10									//�շ�״̬�л����ߵ�ƽΪ���䣬�͵�ƽΪ����
#define RX_P                       P13                  //���յ�Դ



#define LED_GREEN                  P12                  //�̵ƿ��� 
#define LED_RED                    P16									//��ƿ���

#define POW_4W                     P14                  //4W���书�ʿ���
#define POW_1W                     P15									//1W���书�ʿ���


 
#define PPT                         P20                 //PPT����
#define VOX                         P21

#define OP1        			((xP9&0x04)==0? 0:1)
#define OP2        			((xP9&0x08)==0? 0:1)

#define BEEP                      	xPWM0D              //������

/*-----------------------------Ƶƫ����------------------------*/
#define MODDA                     	xPWM1D              //Ƶƫ����
#define PWM_MODDA_OPEN            	xPWMCN |=0x20       
#define PWM_MODDA_CLOSE           	xPWMCN &= ~0x10


//#define ADC_SQ_ASQ                	0x08                //SQ ASQ��ѹ�ȼ�
//#define ADC_KEY1                  	0x48								//�����ж�
//#define ADC_VOX                   	0x58								//VOX��ѹ
//#define ADC_RSSI                  	0x28                //RSSI��ѹ
//#define ADC_AGCA                  	0x38								//AGCA��ѹ



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
	unsigned char FreqCal;		//ϵͳʱ��У׼
	unsigned char CountryTable;	//�����б�
	unsigned char Country;		//����
	unsigned char Band;			//Ƶ��            //ABCDEFGHIL
	unsigned char Modu;			//����
	unsigned char TxPower;		//���书��	
	unsigned char VolLevel;		//��������
	unsigned char Channel;		//ͨ��
	unsigned char  LastChannel;  //���ʹ��ͨ��
	unsigned char LastBand;
	unsigned char forEMGChannel;
	unsigned char LcdColor;               //LCD��������ɫ
	unsigned char ButtonToneSwitch;				//����������
	unsigned char SpkerSwitch;            //�Ƿ���
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
	unsigned char KeyIndex1;	      //KEY1 ADֵ ����
	unsigned char Power_Time;	//��Դ������ʱ��
	unsigned char DoublePress_Limit;	//˫��ʱ��
	unsigned char DoublePress_Count;  //˫������
	unsigned char Press_Count;          //��������
	unsigned char MutePress_Timelimit;  //��������Դ������ʱ��
	unsigned char MuteDoublePress_Timelimit;  //��������Դ��˫��ʱ��
	unsigned char LongPress_Time;          //����SQ�л�ʱ��
	unsigned char MutePress_Count;      //��Դ��������
	unsigned char KeyComboLimit;        //��ϼ���ʱ
	unsigned char isKeyCombo;
}tKey;

typedef struct
{
	unsigned char IsAsq;			  //�Ƿ�ΪASQ
	unsigned char IsVox;
	unsigned char AsqLevel;	    //ASQ����	
	unsigned char Scan;             
	unsigned char ScanDir;
	unsigned char ScanHould ;	
	unsigned int HouldTime;
	unsigned char DisHould;	
}tSqParam;										//SQģʽ


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
}tSysParam;                             //������

typedef struct
{
	unsigned char mRssi;
	unsigned int h_Fre_Tx;            
	unsigned int l_Fre_Tx;
	unsigned int h_Fre_Rx;
	unsigned int l_Fre_Rx;
	unsigned char NDIV_FRE; 
}tVcoParam;                             //Voc����


typedef struct
{
	unsigned char RecvStatus;		//����״̬
	unsigned char RecvCount;	  //��������
	unsigned char WriteOrRead;  //��дѡ��λ
	unsigned char AdressLenth;	//��д����
	unsigned char isSendData;
	unsigned char isReciveData;
	unsigned char RecvBuf[MAX_RX_BYTES];       //0:���ձ�ʶ   1������ָ����  2���������ݳ���  3����������ֵ  4��
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

/*-------------�˵�����---------------------------*/
typedef struct
{
	unsigned char isBussy;	      //æ ���ص���
	unsigned char MenuIndex;		  //�˵�����
	unsigned char BackMenuIndex;   //���ز˵������洢
	unsigned char Back_Channel_Time;	//�������˵�ʱ��
	unsigned char isLock;			      //�Ƿ�����
	unsigned char emgIndex;		    //�����ŵ���ʶ
	unsigned char isTx;			        //����״̬
	unsigned char isBackChannel;
	unsigned char keyCombSQUP;     //��ϼ��л�������
	unsigned char keyCombSQDN;     //��ϼ��л�����ɫ

	unsigned char isTkShow;        //��˸  �����ʶ
	
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
/*----------------------vco���-----------------*/

void SystemInit(void);
/*-------------------------------------------------------------------------
*������delayms  ��ʱ1ms
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void delayms(u16 time);
/*-------------------------------------------------------------------------
*������delayus  ��ʱ6.5us����
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void delayus(u8 i);
/*-------------------------------------------------------------------------
*������UART0_Init  �����жϳ�ʹ��
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void UART0_Init();
/*-------------------------------------------------------------------------
*������IO_Init  IO�ڳ�ʹ��
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void IO_Init();
/*-------------------------------------------------------------------------
*������Get_AD  AD�ڻ�ȡֵ
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
u16 Get_AD(u8 AD_IO);
/*-------------------------------------------------------------------------
*������PowerOnShow  ������ʾ
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void PowerOnShow();
/*-------------------------------------------------------------------------
*������playButtonTone  �������ж�
*������
*����ֵ��
*-------------------------------------------------------------------------*/
void playButtonTone(void);
#endif