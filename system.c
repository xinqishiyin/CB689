
#include "system.h"

/***************************************�޸ļ�¼*****************************************************
Function List��
	1��systemCLK_init   		ϵͳʱ������  ���ڲ�ʱ��4MHz
	2��initTimer0  				  Timer0��ʹ��
	3��IO_Init    					IO�ڳ�ʹ��
	4��delayms             	1ms��ʱ����
	5��delayus              һ��ʱ�� 16us ��ʱ����
	6��UART0_Init           �����жϳ�ʹ��
	7��LCD_Init             LCD��ʹ��
	8��Get_AD               ��ѹ��⺯��
Change Log:



****************************************************************************************************/

xdata tCbParam mCbParam;
xdata tSqParam mSqParam;
xdata tSysParam mSysParam;
xdata tTimer   mTimer;
xdata tReceivePackage mReceivePackage;
xdata tVoltageSend mVoltageSend;
xdata tMenu mMenu;

/*���ڽ���*/
uchar mUartCmd = 0;


/*-------------------------------------------------------------------------
*������systemCLK_init  ϵͳʱ��ѡ��  �ⲿ16Mʱ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void systemCLK_init()
{
	WPKEY = 0x37;
  CLKEN |= 0x25;                  // ��RCH   P9.2 P9.3��Ϊ��ͨIO��<5>
  while((MCKSEL&0x08) != 0x08);   // �鿴RCH�ȶ���־λ�Ƿ�����
	WPKEY  = 0x37;
  MCKSEL &= 0xF8;                // �л���RCH
	WPKEY = 0x37;
	MCKDIV = 0x03;	//����Ƶ
	WPKEY = 0x37;
	xSYSCFG|=0x30;                //����RCTʱ������LCD

}
/*-------------------------------------------------------------------------
*������initTimer0  ��ʱ����ʹ��  16ms��ʱ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void initTimer0(void) //��ʱ16ms
{
	TMOD   = 0X03;					//ģʽ3,2��������8λ������
    xTIMPRS= 0X07;  		        //��ʱ����Ƶ����Ϊ256
    TH0    = 6;                  
    TCON   = 0X10;					//������ʱ��0
    EA     = 1;
    ET1=1;                          //ʹ��T1�ж�
    TR1=0;                          //������ʱʱ1
	/*
    //��ʼ����ʱ��
  	xTIMPRS |= 0x07;	//t0: MCLK/256 = 4M/256 = 15625Hz
	TMOD |= 0x01;	//t0: 16λ��ʱ��
	TH0 = (65535 - 781) / 256;	
	TL0 = (65535 - 781) % 256;	//50ms => 0.05S * 15625 = 781	
  TR0 = 1;
	ET0 = 1;
	*/
}
/*-------------------------------------------------------------------------
*������IO_Init  IO�ڳ�ʹ��  
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void IO_Init()
{
	P0MDL=0xAA;                  //LCD����
	P0MDH=0xAA;                  //LCD����
  //P0=0;

	
	
	P1MDL=0xAA;                 //0��4802TRX  1��A/F_EN  2��GREEN  3��CE  
	P1MDH=0xAA;                 //4��4W 5�� 1W  6��RED  7SCL
	P1=0x20;
	
	
	P2MDL=0xA1;                 //0��TXD/PPT��������  1:RXD/VOX  2:LIGHT_G  3:BEEP  
	P2MDH=0x82;                  //4:LIGHT_R  5..  6.. 7:MODDA


	
	P3MDH=0xAA;                 //COM0-3	
	
	xP4MDL=0xAA; 								//0:SEG8  1��LIGHT_B  2:AM_EN  3��MIC_MUTE  
	xP4MDH=0xAA;							  //4:AT_MUTE  5:FM_EN  6��4802 SCK  7:4802 24C08 SDA
	SET_AT_MUTE;

	
	
	xADCFG=0x10;                  //ADC���뷽ʽΪ  ��4λADRL ��2λADRH 
	
	xP9AEN&=0x03;									//P9.2  P9.3��ΪGPIO�˿�
	xP9AEN|=0x03;
  xP9MDL=0x00;                 //P9.2  P9.3��Ϊ����
	
	
	
	SET_BK4802_SCK;
	SET_BK4802_SDA;
	
	
}



/*-------------------------------------------------------------------------
*������delayms  ��ʱ1ms   
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void delayms(unsigned int i)
{
	unsigned int m,n;
	
	for(m=0;m<i;m++)
	{
		for(n=0;n<208;n++);
	}
}
/*-------------------------------------------------------------------------
*������delayus  ��ʱ6.5us���� 
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void delayus(u8 i)
{
    while(--i);
}
/*-------------------------------------------------------------------------
*������initBEEP  PWM  BEEP����ʹ�� 
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void initBEEP(void)
{	
	xSYSCFG |= 0x20;
	xPWMPSC|=0x16;				  //PWMԤ��Ƶ��20
	xIOMUX0 |= 0x02;//En P23 as Pwm0
	xPWMP = 0Xad;	//����
	xPWM0D = 0X50;	//ռ�ձȣ�modda
	P2MDL &= 0x3f;
	P2MDL |= 0x80;
}
/*-------------------------------------------------------------------------
*������UART0_Init  ���ڳ�ʹ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void UART0_Init()
{
	xIOMUX0 |= 0x01;        //P21/P20������UART0�˿�
	SCON0=0x50;							//����ģʽ1,8λ�첽�������ʿɵ� ��������뷢��
	BRCON0  = 0x68;         //�����ʼ��㹫ʽΪ1/32��2smod=1��,�����ʷ������������߾��Ȳ����ʿ���ʹ��
	SBUF0=0;
	BRTIM0  = 242;          //
  IE |=0X10;        //�������ж�		 
}
/*
void UART1_Init()
{
	xIOMUX2 |= 0x01;        //P24/P23������UART1�˿�
  SCON1 |= 0x50;         //����ģʽ1,8λ�첽�������ʿɵ� ʹ�ܽ���
 
  xBRCON1  = 0XE8;//0x68;         //�����ʼ��㹫ʽΪ1/16��2smod=1���������ʷ������������߾��Ȳ����ʿ���ʹ��   
  xBRTIM1  = 0x98;
  EIE2 |=0X10;                    //ʹ��ES1�ж�
}
*/

void INT1_Init(void)
{
    EA = 0;
    xIOMUX2 &= 0xDF;                  //INT��ѡP01
    IT1 = 1; 		                      //�����أ��½��أ������ж�
    EINTCS0 = 0xA0;	                  //bit5=1��INT1�ж�ʹ���ź� ,�첽�ж�ģʽ
    IE1 = 0;                          //��INT1�½����жϱ�־
    EINTCS0 &= 0xfc;                  //�����־ ��˫������Ƶ��жϣ�2�������־
    EINTCS0 &= 0xfc;                  //�����־
    
}
void LCD_Init(void)
{
	WPKEY = 0x37;
	RTCSEL = 0x04;
	RTCDATA|=0x01;
	xLCDPEN1 = 0xff;      //P00-P07����ΪLCD SEG
	xLCDPEN0 = 0x0f;			//P34-P37����ΪLCD COM
	xLCDPEN2 = 0x01;      //P40����ΪLCD SEG	
	xLCDCON  = 0x97;       //bit0 1:�ĸ�COM��   bit2:ƫ��1/3 4��ƽ  bit4 5:LCDɨ��Ƶ��Ϊ256HZ  bit7:LCDģ�鿪��

	//xTKADDR0=0;
	//TKCON=��  TKADDR=? ��˸����
	xLCDPCON=0x82;       //
}


void SystemInit()
{
	systemCLK_init();
	IO_Init();	
	initTimer0();
	UART0_Init();
	LCD_Init();
	//UART1_Init();
	initBEEP();	
	EA=1;
	//INT1_Init();
	//UART1_Init();
}

u16 Get_AD(u8 AD_IO)
{
	u16 i,j;
	u32 temp;
	u16 val[10];
	
	switch(AD_IO)	
	{		
		case ADC_ASQ:           //P30
			xP3AEN=0x01;  
			ADCON=0x08;
			break;
		case ADC_Key1:
			xP9AEN=0x01;         //P90
			ADCON=0x48;
			break;
		case ADC_VOX:					 //P91
			xP9AEN=0x02;         
			ADCON=0x58;
			break;
		case ADC_RSSI:				  //P32
			xP3AEN=0x04;  
			ADCON=0x28;
			break;
		case ADC_AGCA:					//P33
			xP3AEN=0x08;  
			ADCON=0x38;
			break;
		default:
			break;
	}
	
	delayus(10);
	for(i=0;i<10;i++)
	{
		ADGO=1;
		while(ADGO==1);
		val[i]=((ADRH<<8)|ADRL);
	}
	for(i=0;i<10;i++)   
  {
    for(j=0;j<10-i;j++)
    {
      if(val[j]>val[j+1])
      { 
        temp = val[j];			
        val[j] = val[j+1];
        val[j+1] = temp;                 
      }
    }
  }
  temp=0;
	for(i=3;i<6;i++)	
	{
		temp+=val[i];
	}
	temp=temp/3;
	return temp;
}


