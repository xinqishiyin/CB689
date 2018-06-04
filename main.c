#include "SC51F2832.H"
#include "system.h"
#include "key.h"
#include "memory.h"
#include "BK4802.h"
#include "handler.h"
#include "lcdshow.h"
#include "Menu.h"
#include "uart.h"
#include "vco.h"

/***************************************************************************************************
 
Copyright (C), 2018.CB689: 
Author: 陈兴起: Date:2018-6-20 
Description: CB689，CB机用iic读写24c08存储器和4802芯片。4802在FM模式时发射与接收同频率，在AM模式时接收为发射+中频（10.7M）
Others: 由于4802 35-38M为盲区通过试验得出公式，35M-42M频段频偏在100Hz以内
History:
2018-4-13：开始编写
4-18：delayus 延时为 6.5us  delayms为1.00ms
4-21:锁频完成，但4802在发射时不能写REG4
4-23:盲区问题解决， 在25-32M时  mVcoParam.NDIV_FRE=128   REG2 写0xc000   在35-42M时 REG2写 0xa000   25-32M按资料提供的公式计算得出，
	 35-42M经过试验得出公式(26.5078+((temp+IF)-38.556)*20/29.095)*mVcoParam.NDIV_FRE*8388608/21.7，在40.8M时频偏为-300  在35.8M时频偏为+300
4-25:串口通讯已通，可读电压值 读指令为 FE 01 00
4-25:LCD显示  1、xSYSCFG|=0x30; //开启RCT时钟用于LCD   2、RTCSEL = 0x04;	RTCDATA|=0x01;  //开启RCT时钟用于LCD  3、xLCDPEN1 = 0xff;      
	 IO口复用于LCD COM 和 SEG 
4-27:天气预报频段 161.755-163.275     mVcoParam.NDIV_FRE=24  REG2写0x2000  
5-15:菜单补全，组合键、开机组合键、开机重启等程序补全
5-17:写频准备工作完成，读写存储器正常。  细化接收频偏控制在100Hz内
5-18:接收测试，资料给的寄存器无法接收，问了技术支持并得到了可接收寄存器配置，但发射与接收频差140K，盲区频率按公式有变。重新调整。
5-22:4802发射音频频偏REG<2>b04-b00,发射音频限制为REG<15>b12-b00
[2018/05/23  16:52 陈兴起]:AM模式时 发射时 4802发射出所需频率  接收时 4802发射出 （所需频率+10.7M）修改完成
[2018/05/31 14:48 XingqiChen]:根据说明书，1、添加VOX闪烁
										  2、PTY应急信道闪烁
										  3、PPT+PTY开机设置背景灯
										  4、P9.2 P9.3作为国家频率OP1,OP2判断角，OP1=1,OP2=1时为普通国家表 低功率   OP1=1,OP2时为RU频率段可切换高低功率
											 OP1=0，OP2=1时为HX频率段  可切换高低功率  OP1=0,OP2=0时为普通国家表 可切换高低功率
										  5、PPT+SQ开机设置国家或频率段  在普通国家表时为设置国家  在RU或HX国家时为设置频率段
										  6、按AM/FM键开机 除普通国家表低功率 外会进入高低功率切换设置
										  4、PPT+VOX开机复位
										  5、在UK国家中  长按AM/FM键进入CE国家 再次长按回到UK国家  在单调制国家中AM/FM键返回活动信道功能。
										  




****************************************************************************************************/



/***************************************修改记录***************************************************** 
Function List：
	1、irq_timer1   		16ms定时器中断
	2、PowerOnShow  		开机显示
	3、PowerOnComKey    开机组合按键事件
	4、main             主程序入口
	
Change Log:
	


****************************************************************************************************/





/*-------------------------------------------------------------------------
*函数：irq_timer1  16ms定时中断
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void irq_timer1(void) interrupt 3
{

   if((mReceivePackage.RecvCount!=0)||(mReceivePackage.RecvStatus!=UART0_IDLE))            //串口通讯超时
	{
		mTimer.uartTimeCount++;
		if (mTimer.uartTimeCount == 20)
		{
			mReceivePackage.RecvCount = 0;
			mReceivePackage.RecvStatus = UART0_IDLE;
			TR1 = 0;
			mTimer.uartTimeCount = 0;
		}
	}
	if(mSysParam.isButtonTone==1)														   //按键音
	{
		mTimer.ButtonToneTime--;
		if(mTimer.ButtonToneTime==0)
		{
			xPWMCN &= ~0x10;				
			mSysParam.isButtonTone=0;
		}
	}
    if (mSqParam.Scan==1&&mSqParam.ScanHould==2)                                           //扫描等侯超时继续扫描
    {
		mTimer.ScanHouldTime--;
		if (mTimer.ScanHouldTime==0)
		{
			mSqParam.ScanHould = 1;
			mTimer.ScanHouldTime = SCAN_HOULD_TIME;
		}		
    }    
}
/*-------------------------------------------------------------------------
*函数：PowerOnShow  开机显示全屏后显示国家然后进入信道模式并进入接收
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void PowerOnShow()
{		
	ShowAll();	
	delayms(500);
	ShowClear();
	ShowCountry();
	delayms(1000);
	ShowClear();
	ShowChannel();	
	SetTxPower();
	SetModu();		
	BK4802_Init();	
}
/*-------------------------------------------------------------------------
*函数：PowerOnComKey  按键开机对应设置
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void PowerOnComKey()
{
	u16 key=	Get_AD(ADC_Key1);
	if(((KEY_AFM_VAL-15)<key)&&(key<(KEY_AFM_VAL+15))&&mCbParam.CountryTable==2)          //按 PPT 和  ASQ 组合键时进入发射功率选择
	{
		mMenu.MenuIndex = CHENNEL_POWER;
		ShowPower();
		mSysParam.rest=1;
		while(PPT==0);
		delayms(500);
	}
	if(PPT==0&&((KEY_VOX_VAL-15)<key)&&(key<(KEY_VOX_VAL+15)))          //按 PPT 和  VOX 组合键时进入复位
	{
		ShowReset();
		mSysParam.rest=1;
		while(PPT==0);
		ResetParam();
		delayms(1000);
	}
	if(PPT==0&&((KEY_SQ_VAL-15)<key)&&(key<(KEY_SQ_VAL+15)))          //按 PPT 和  A、FM 组合键时进入国家表选择
	{
		mMenu.MenuIndex = CHANNEL_COUNTRY;
		ShowCountry();
		mSysParam.rest=1;
		while(PPT==0);
		delayms(500);
	}
	if(PPT==0&&(((KEY_PTY_VAL-15)<key)&&(key<(KEY_PTY_VAL+15))))          //按 PPT 和  PTY 组合键时进入背景颜色灯选择
	{		
			mMenu.MenuIndex = CHANNEL_BACKLIGHT;
			ShowBackColor(1);
			while (PPT == 0);
			delayms(500);
			mSysParam.rest=1;
			//PowerOnShow();
	}
}




void main()
{
	u16 dat;
	SystemInit();
	SET_AT_MUTE;
	initMemory();
	ShowBackColor(0);
	InitKey();
	RX_P=1;
	PowerOnComKey();
	SET_AT_MUTE;
	mTimer.TkCyclTime = TK_CYCL_TIME;
  while(1)
	{
		if (mSysParam.rest == 0)
		{			
			PowerOnShow();
			mSysParam.rest=1;
		}
		IS_KEY1_PRESS();           //扫描按键
		PPT_PRESS();
		UART_EVENT();
		SQ_Switch();
		ShowTk();
		VOX_Check();
		dat =BK4802_RssiAndSnr();
		dat =BK4802_ASQ();
	}
}
