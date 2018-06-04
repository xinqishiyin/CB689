#include "system.h"
#include "BK4802.h"
#include "vco.h"
#include "lcdset.h"
#include "handler.h"

/***************************************修改记录*****************************************************
Function List：
1、BK4802_Init   		4802开启初使化
2、BK4802_RXtoTX		4802接收转发射
3、BK4802_TXtoRX		4802发射转接收
4、BK4802_Change_Freq   4802修改频率
5、BK4802_SLEEP			4802进入休眠
6、BK4802_RssiAndSnr	获取4802接收强度
7、BK4802_ASQ			获取4802静噪强度

Change Log:
 [2018/05/23 16:53 陈兴起] BK4802_TXtoRX AM模式时 发射时 4802发射出所需频率  接收时 4802发射出 （所需频率+10.7M）

****************************************************************************************************/


u8 isSecess = 1;

u8 ack;

/*-------------------------------------------------------------------------
*函数：BK_Start  存储器启动
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void BK_Start(void)
{
	SET_BK4802_SDA;
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;
	delayus(1);
	CLS_BK4802_SCK;
}
/*-------------------------------------------------------------------------
*函数：BK_Stop  存储器停止使用
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void BK_Stop(void)
{
	CLS_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
}
/*-------------------------------------------------------------------------
*函数：BK_Read_Ack  读1位存储器
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
u8 BK_Read_Ack(void)
{
	unsigned char tempTime = 0;
	CLS_BK4802_SCK;
	SET_BK4802_SDA_IN;
	SET_BK4802_SCK;
	delayus(1);
	delayus(1);
	while (BK4802_SDA_IN);
	CLS_BK4802_SCK;
	SET_BK4802_SDA_OUT;
	delayus(2);
	return 0;
}
/*-------------------------------------------------------------------------
*函数：at24c08TxAck  写1位存储器
*参数：ACK要写的字
*返回值：无
*-------------------------------------------------------------------------*/
void BK_ACK()
{
	//SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SCK;
	delayus(1);
}
void BK_NoACK()
{
	//SET_BK4802_SCK;
	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SCK;
	delayus(1);
}
/*-------------------------------------------------------------------------
*函数：at24c08I2cWriteByte  存储器写入字
*参数：value   要写的字
*返回值：无
*-------------------------------------------------------------------------*/
void BK_Write_Byte(u8 value)
{
	unsigned char i;
	CLS_BK4802_SCK;
	for (i = 0; i<8; i++)
	{
		if (value & 0x80)
		{
			SET_BK4802_SDA;
		}
		else
		{
			CLS_BK4802_SDA;
		}
		delayus(2);
		SET_BK4802_SCK;
		delayus(2);
		CLS_BK4802_SCK;

		value <<= 1;
	}
}
/*-------------------------------------------------------------------------
*函数：at24c08I2cReadByte  存储器读一字
*参数：无
*返回值：读出的字
*-------------------------------------------------------------------------*/
u8 BK_Read_Byte(void)
{
	u8 i, temp = 0;
	CLS_BK4802_SCK;
	SET_BK4802_SDA_IN;
	delayus(2);
	for (i = 0; i<8; i++)
	{
		temp <<= 1;
		if (BK4802_SDA_IN)
		{
			temp |= 0x01;
		}
		SET_BK4802_SCK;
		delayus(2);
		CLS_BK4802_SCK;
		delayus(2);
	}
	SET_BK4802_SDA_OUT;
	return temp;
}
/*-------------------------------------------------------------------------
*函数：eepromWriteByte  向存储器是写字
*参数：page 存储器页   addr 存储器地址  value 写入的值
*返回值：无
*-------------------------------------------------------------------------*/
void BK_Write_Reg(u8 addr, u16 value)
{
	BK_Start();
	BK_Write_Byte(0x90);
	BK_Read_Ack();
	BK_Write_Byte(addr);
	BK_Read_Ack();
	BK_Write_Byte(value >> 8);
	BK_Read_Ack();
	BK_Write_Byte(value & 0x00ff);
	BK_Read_Ack();
	BK_Stop();
	delayms(5);
}

/*-------------------------------------------------------------------------
*函数：eepromReadByte  读存储器
*参数：无
*返回值：所读的值
*-------------------------------------------------------------------------*/
u16 BK_Read_Reg(u8 addr)
{
	u16 value;
	u8 val1, val2;
	BK_Start();
	BK_Write_Byte(0x90);
	BK_Read_Ack();
	BK_Write_Byte(addr);
	BK_Read_Ack();
	BK_Start();
	BK_Write_Byte(0x91);
	BK_Read_Ack();
	val1 = BK_Read_Byte();
	BK_ACK();
	val2 = BK_Read_Byte();
	BK_NoACK();
	BK_Stop();
	value = val1 * 256 + val2;
	return value;
}
void BK4802_IOInit()
{
	CLS_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;

	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
}
/*-------------------------------------------------------------------------
*函数：Init_RX  初使进入接收
*参数：无
*返回值：所读的值
*-------------------------------------------------------------------------*/
void Init_RX()
{

	//BK_Write_Reg(23,0x18ff);
	//delayms(50);
	BK_Write_Reg(4, 0x0b00);       //B15： 1-关闭频率综合器； 0-打开频率综合器      RX 0x0c00  TX:0x7200
								   //B14： 1-关闭接收前端； 0-打开接收前端
								   //B13： 1-关闭接收中频； 0-打开接收中频
								   //B12： 1-关闭接收音频； 0-打开接收音频
								   //B11： 1-关闭发射前端； 0-打开发射前端
								   //B10： 1-关闭发射拼音； 0-打开发射音频
								   //B09： 1-关闭采样ADC； 0-打开采样ADC

	BK_Write_Reg(5, 0x0c04);       //锁相环相关设置，建议用默认值
	BK_Write_Reg(6, 0xf140);       //锁相环相关设置，建议用默认值
	BK_Write_Reg(7, 0xed00);       //B10：触发锁相环校准，上升沿有效
	BK_Write_Reg(8, 0x3fe0);				//锁相环相关设置，建议用默认值
	BK_Write_Reg(9, 0xe0e0);
	BK_Write_Reg(10, 0x8543);			//B15~B10：微调晶体振荡器的输出频率                RX:0x00fc  TX:0x00cc
										//B07~B06：设置采样ADC的稳压器输出电压
										//B05： 1-中频ADC时钟有效； 0-中频ADC时钟失效
										//B04： 1-采样ADC时钟有效； 0-采样ADC时钟失效
										//B03~B02：微调晶体振荡器的输出幅度
										//B01~B00：设置数字稳压器输出电压

	BK_Write_Reg(11, 0xf700);      //B15~B13：调整发射音频ADC的参考电压
								   //B12：增加发射音频VGA增益，约为3dB
								   //B06：调整麦克风输入电阻。 0-16k Ohm； 1-8k Ohm
								   //B05：调整麦克风VGA反馈电阻的大小。 0-52k Ohm；
								   //1-26k Ohm
								   //B04~B03：调整音频功放P端、 N端非交叠时间。 0-2nS；
								   //1-3nS； 2-4nS； 3-5nS

	BK_Write_Reg(12, 0xa066);      //B15~B08： 设置接收中频模数转换器参考电压
								   //B07~B05： 设置接收中频增益， 3dB/级。 0-0dB； 7-21dB
								   //B04：设置接收中频滤波器带宽。 0-200kHz； 1-1MHz
								   //B03：设置接收中频VGA电流偏置。 0-2uA； 1-10uA
								   //B02~B00：设置接收中频稳压器输出电压

	BK_Write_Reg(13, 0xffff);      //B15：收发模式控制方式。 0-寄存器控制； 1-DSP控制
								   //B14：收发模式选择。 0-接收模式； 1-发射模式
								   //B13：设置低噪声放大器增益。 0-低增益； 1-高增益
								   //B12~B10：调整低噪声放大器偏置电流
								   //B09~B07：调整混频器直流偏置
								   //B05： ASK模式使能。 0-失效； 1-使能
								   //B04~B03：设置接收前端稳压器输出电压
								   //B02~B00：调整功率放大器输出功率

	BK_Write_Reg(14, 0xffe0);      //B15~B14： 发射音频数字滤波器增益。
								   //0-0dB； 1-1dB； 2-3.5dB； 3-6dB
								   //B13~B09：发射音量控制。
								   //B08~B05：带内信号能量设置

	BK_Write_Reg(15, 0x0210);      //B12~B00：发射限幅设置
	BK_Write_Reg(16, 0x9e3c);      //B15：发射音频AGC使能。 0-无效； 1-使能
	BK_Write_Reg(17, 0x1f00);      //TX Audio AGC设置
	BK_Write_Reg(18, 0xd1d1);      //B15~B04： 发射频偏控制
	BK_Write_Reg(19, 0x200f);      //B15~B14： CIC滤波器增益。 0-0dB； 1-1dB；
								   //2-3.5dB； 3-6dB
								   //B13~B12： FM解调输出幅度设置
								   //B03~B00：音量调整

	BK_Write_Reg(20, 0x01ff);      //B15：关闭自动频率校正（AFC）。 0-打开； 1-关闭
	BK_Write_Reg(21, 0xE000);      //AFC阈值设置
	BK_Write_Reg(22, 0x0c00);      //B15： IQ上下边带选择。 0-选择上边带； 1-选择下边带
								   //B14： AFC方向选择。 0-对应上边带； 1-对应下边带
								   //B07~B00：设置静噪的接收信号强度（RSSI） 阈值
	if (mCbParam.Modu == FM)
	{
		BK_Write_Reg(2, 0xc000);
	}
	else
	{
		BK_Write_Reg(2, 0xa000);
	}

	BK_Write_Reg(1, mVcoParam.l_Fre_Rx); //写入频率
	BK_Write_Reg(0, mVcoParam.h_Fre_Rx);
	//CLS_AT_MUTE;       //

}
void BK4802_RX()
{
	Init_RX();
}


void BK4802_TX()
{
	BK4802_TRX = 1;
	delayms(50);
	BK_Write_Reg(4, 0x7c00);       //B15： 1-关闭频率综合器； 0-打开频率综合器      RX 0x0c00  TX:0x7200
								   //B14： 1-关闭接收前端； 0-打开接收前端
								   //B13： 1-关闭接收中频； 0-打开接收中频
								   //B12： 1-关闭接收音频； 0-打开接收音频
								   //B11： 1-关闭发射前端； 0-打开发射前端
								   //B10： 1-关闭发射拼音； 0-打开发射音频
								   //B09： 1-关闭采样ADC； 0-打开采样ADC

	
	if (mCbParam.Modu == AM && mMenu.isTx == 0)
	{
		BK_Write_Reg(2, 0xa000);
	}
	else
	{		
		BK_Write_Reg(2, 0xc000);			
	}
	BK_Write_Reg(1, mVcoParam.l_Fre_Tx); //写入频率
	BK_Write_Reg(0, mVcoParam.h_Fre_Tx);
}


/*-------------------------------------------------------------------------
*函数：BK_4802_Init  4802初使化
*参数： 无
*返回值：无
*-------------------------------------------------------------------------*/
void BK4802_Init()
{
	BK4802_IOInit();	
	BK4802_TRX = 0;
	BK4802_TRX = 1;
	BK4802_TRX = 0;
	delayms(50);
	Init_RX();
	LED_RED = 0;
	LED_GREEN = 1;
	LCD_RX(1);
}
void BK4802_RXtoTX()
{	
	CLS_AM_EN;
	CLS_FM_EN;
	SET_AT_MUTE;
	BK4802_TX();
	CLS_MIC_MUTE;
	LED_GREEN = 0;
	LED_RED = 1;
}

void BK4802_TXtoRX()
{
	SetModu();
	if (mCbParam.Modu == AM)
	{			
		
		BK4802_TX();		
	}
	else
	{
		SET_MIC_MUTE;
		
		//CLS_AT_MUTE;      //----------

		BK4802_TRX = 0;
		delayms(50);
		BK4802_RX();		
	}
	//CLS_AT_MUTE;
	LED_RED = 0;
	LED_GREEN = 1;
}

void BK4802_SLEEP()
{
	
}

u16 BK4802_RssiAndSnr()
{
	u16 val;
	val = BK_Read_Reg(23);  //snr=val[13-8]   rssi=val[6-0];
	return val;
}
u16 BK4802_ASQ()
{
	return BK_Read_Reg(30);
}






