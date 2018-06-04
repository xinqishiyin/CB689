
#include "system.h"

/***************************************修改记录*****************************************************
Function List：
	1、systemCLK_init   		系统时钟设置  用内部时钟4MHz
	2、initTimer0  				  Timer0初使化
	3、IO_Init    					IO口初使化
	4、delayms             	1ms延时函数
	5、delayus              一个时钟 16us 延时函数
	6、UART0_Init           串口中断初使化
	7、LCD_Init             LCD初使化
	8、Get_AD               电压检测函数
Change Log:



****************************************************************************************************/

xdata tCbParam mCbParam;
xdata tSqParam mSqParam;
xdata tSysParam mSysParam;
xdata tTimer   mTimer;
xdata tReceivePackage mReceivePackage;
xdata tVoltageSend mVoltageSend;
xdata tMenu mMenu;

/*串口接收*/
uchar mUartCmd = 0;


/*-------------------------------------------------------------------------
*函数：systemCLK_init  系统时钟选择  外部16M时钟
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void systemCLK_init()
{
	WPKEY = 0x37;
  CLKEN |= 0x25;                  // 打开RCH   P9.2 P9.3作为普通IO口<5>
  while((MCKSEL&0x08) != 0x08);   // 查看RCH稳定标志位是否置起
	WPKEY  = 0x37;
  MCKSEL &= 0xF8;                // 切换到RCH
	WPKEY = 0x37;
	MCKDIV = 0x03;	//不分频
	WPKEY = 0x37;
	xSYSCFG|=0x30;                //开启RCT时钟用于LCD

}
/*-------------------------------------------------------------------------
*函数：initTimer0  定时器初使化  16ms定时器
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void initTimer0(void) //定时16ms
{
	TMOD   = 0X03;					//模式3,2个独立的8位计数器
    xTIMPRS= 0X07;  		        //定时器分频比设为256
    TH0    = 6;                  
    TCON   = 0X10;					//启动定时器0
    EA     = 1;
    ET1=1;                          //使能T1中断
    TR1=0;                          //启动定时时1
	/*
    //初始化定时器
  	xTIMPRS |= 0x07;	//t0: MCLK/256 = 4M/256 = 15625Hz
	TMOD |= 0x01;	//t0: 16位定时器
	TH0 = (65535 - 781) / 256;	
	TL0 = (65535 - 781) % 256;	//50ms => 0.05S * 15625 = 781	
  TR0 = 1;
	ET0 = 1;
	*/
}
/*-------------------------------------------------------------------------
*函数：IO_Init  IO口初使化  
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void IO_Init()
{
	P0MDL=0xAA;                  //LCD控制
	P0MDH=0xAA;                  //LCD控制
  //P0=0;

	
	
	P1MDL=0xAA;                 //0：4802TRX  1：A/F_EN  2：GREEN  3：CE  
	P1MDH=0xAA;                 //4：4W 5： 1W  6：RED  7SCL
	P1=0x20;
	
	
	P2MDL=0xA1;                 //0：TXD/PPT（上拉）  1:RXD/VOX  2:LIGHT_G  3:BEEP  
	P2MDH=0x82;                  //4:LIGHT_R  5..  6.. 7:MODDA


	
	P3MDH=0xAA;                 //COM0-3	
	
	xP4MDL=0xAA; 								//0:SEG8  1：LIGHT_B  2:AM_EN  3：MIC_MUTE  
	xP4MDH=0xAA;							  //4:AT_MUTE  5:FM_EN  6：4802 SCK  7:4802 24C08 SDA
	SET_AT_MUTE;

	
	
	xADCFG=0x10;                  //ADC对齐方式为  低4位ADRL 高2位ADRH 
	
	xP9AEN&=0x03;									//P9.2  P9.3作为GPIO端口
	xP9AEN|=0x03;
  xP9MDL=0x00;                 //P9.2  P9.3作为输入
	
	
	
	SET_BK4802_SCK;
	SET_BK4802_SDA;
	
	
}



/*-------------------------------------------------------------------------
*函数：delayms  延时1ms   
*参数：无  
*返回值：无
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
*函数：delayus  延时6.5us左右 
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void delayus(u8 i)
{
    while(--i);
}
/*-------------------------------------------------------------------------
*函数：initBEEP  PWM  BEEP音初使化 
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void initBEEP(void)
{	
	xSYSCFG |= 0x20;
	xPWMPSC|=0x16;				  //PWM预分频比20
	xIOMUX0 |= 0x02;//En P23 as Pwm0
	xPWMP = 0Xad;	//周期
	xPWM0D = 0X50;	//占空比，modda
	P2MDL &= 0x3f;
	P2MDL |= 0x80;
}
/*-------------------------------------------------------------------------
*函数：UART0_Init  串口初使化
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void UART0_Init()
{
	xIOMUX0 |= 0x01;        //P21/P20复用做UART0端口
	SCON0=0x50;							//工作模式1,8位异步，波特率可调 允许接收与发送
	BRCON0  = 0x68;         //波特率计算公式为1/32（2smod=1）,波特率发生器开启，高精度波特率控制使能
	SBUF0=0;
	BRTIM0  = 242;          //
  IE |=0X10;        //开串口中断		 
}
/*
void UART1_Init()
{
	xIOMUX2 |= 0x01;        //P24/P23复用做UART1端口
  SCON1 |= 0x50;         //工作模式1,8位异步，波特率可调 使能接收
 
  xBRCON1  = 0XE8;//0x68;         //波特率计算公式为1/16（2smod=1），波特率发生器开启，高精度波特率控制使能   
  xBRTIM1  = 0x98;
  EIE2 |=0X10;                    //使能ES1中断
}
*/

void INT1_Init(void)
{
    EA = 0;
    xIOMUX2 &= 0xDF;                  //INT脚选P01
    IT1 = 1; 		                      //负边沿（下降沿）触发中断
    EINTCS0 = 0xA0;	                  //bit5=1，INT1中断使能信号 ,异步中断模式
    IE1 = 0;                          //清INT1下降沿中断标志
    EINTCS0 &= 0xfc;                  //清除标志 ，双缓冲机制的中断，2次清除标志
    EINTCS0 &= 0xfc;                  //清除标志
    
}
void LCD_Init(void)
{
	WPKEY = 0x37;
	RTCSEL = 0x04;
	RTCDATA|=0x01;
	xLCDPEN1 = 0xff;      //P00-P07复用为LCD SEG
	xLCDPEN0 = 0x0f;			//P34-P37复用为LCD COM
	xLCDPEN2 = 0x01;      //P40复用为LCD SEG	
	xLCDCON  = 0x97;       //bit0 1:四个COM口   bit2:偏置1/3 4电平  bit4 5:LCD扫描频率为256HZ  bit7:LCD模块开启

	//xTKADDR0=0;
	//TKCON=？  TKADDR=? 闪烁控制
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


