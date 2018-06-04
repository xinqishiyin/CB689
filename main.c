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
Author: ������: Date:2018-6-20 
Description: CB689��CB����iic��д24c08�洢����4802оƬ��4802��FMģʽʱ���������ͬƵ�ʣ���AMģʽʱ����Ϊ����+��Ƶ��10.7M��
Others: ����4802 35-38MΪä��ͨ������ó���ʽ��35M-42MƵ��Ƶƫ��100Hz����
History:
2018-4-13����ʼ��д
4-18��delayus ��ʱΪ 6.5us  delaymsΪ1.00ms
4-21:��Ƶ��ɣ���4802�ڷ���ʱ����дREG4
4-23:ä���������� ��25-32Mʱ  mVcoParam.NDIV_FRE=128   REG2 д0xc000   ��35-42Mʱ REG2д 0xa000   25-32M�������ṩ�Ĺ�ʽ����ó���
	 35-42M��������ó���ʽ(26.5078+((temp+IF)-38.556)*20/29.095)*mVcoParam.NDIV_FRE*8388608/21.7����40.8MʱƵƫΪ-300  ��35.8MʱƵƫΪ+300
4-25:����ͨѶ��ͨ���ɶ���ѹֵ ��ָ��Ϊ FE 01 00
4-25:LCD��ʾ  1��xSYSCFG|=0x30; //����RCTʱ������LCD   2��RTCSEL = 0x04;	RTCDATA|=0x01;  //����RCTʱ������LCD  3��xLCDPEN1 = 0xff;      
	 IO�ڸ�����LCD COM �� SEG 
4-27:����Ԥ��Ƶ�� 161.755-163.275     mVcoParam.NDIV_FRE=24  REG2д0x2000  
5-15:�˵���ȫ����ϼ���������ϼ������������ȳ���ȫ
5-17:дƵ׼��������ɣ���д�洢��������  ϸ������Ƶƫ������100Hz��
5-18:���ղ��ԣ����ϸ��ļĴ����޷����գ����˼���֧�ֲ��õ��˿ɽ��ռĴ������ã������������Ƶ��140K��ä��Ƶ�ʰ���ʽ�б䡣���µ�����
5-22:4802������ƵƵƫREG<2>b04-b00,������Ƶ����ΪREG<15>b12-b00
[2018/05/23  16:52 ������]:AMģʽʱ ����ʱ 4802���������Ƶ��  ����ʱ 4802����� ������Ƶ��+10.7M���޸����
[2018/05/31 14:48 XingqiChen]:����˵���飬1�����VOX��˸
										  2��PTYӦ���ŵ���˸
										  3��PPT+PTY�������ñ�����
										  4��P9.2 P9.3��Ϊ����Ƶ��OP1,OP2�жϽǣ�OP1=1,OP2=1ʱΪ��ͨ���ұ� �͹���   OP1=1,OP2ʱΪRUƵ�ʶο��л��ߵ͹���
											 OP1=0��OP2=1ʱΪHXƵ�ʶ�  ���л��ߵ͹���  OP1=0,OP2=0ʱΪ��ͨ���ұ� ���л��ߵ͹���
										  5��PPT+SQ�������ù��һ�Ƶ�ʶ�  ����ͨ���ұ�ʱΪ���ù���  ��RU��HX����ʱΪ����Ƶ�ʶ�
										  6����AM/FM������ ����ͨ���ұ�͹��� ������ߵ͹����л�����
										  4��PPT+VOX������λ
										  5����UK������  ����AM/FM������CE���� �ٴγ����ص�UK����  �ڵ����ƹ�����AM/FM�����ػ�ŵ����ܡ�
										  




****************************************************************************************************/



/***************************************�޸ļ�¼***************************************************** 
Function List��
	1��irq_timer1   		16ms��ʱ���ж�
	2��PowerOnShow  		������ʾ
	3��PowerOnComKey    ������ϰ����¼�
	4��main             ���������
	
Change Log:
	


****************************************************************************************************/





/*-------------------------------------------------------------------------
*������irq_timer1  16ms��ʱ�ж�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void irq_timer1(void) interrupt 3
{

   if((mReceivePackage.RecvCount!=0)||(mReceivePackage.RecvStatus!=UART0_IDLE))            //����ͨѶ��ʱ
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
	if(mSysParam.isButtonTone==1)														   //������
	{
		mTimer.ButtonToneTime--;
		if(mTimer.ButtonToneTime==0)
		{
			xPWMCN &= ~0x10;				
			mSysParam.isButtonTone=0;
		}
	}
    if (mSqParam.Scan==1&&mSqParam.ScanHould==2)                                           //ɨ��Ⱥʱ����ɨ��
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
*������PowerOnShow  ������ʾȫ������ʾ����Ȼ������ŵ�ģʽ���������
*��������
*����ֵ����
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
*������PowerOnComKey  ����������Ӧ����
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void PowerOnComKey()
{
	u16 key=	Get_AD(ADC_Key1);
	if(((KEY_AFM_VAL-15)<key)&&(key<(KEY_AFM_VAL+15))&&mCbParam.CountryTable==2)          //�� PPT ��  ASQ ��ϼ�ʱ���뷢�书��ѡ��
	{
		mMenu.MenuIndex = CHENNEL_POWER;
		ShowPower();
		mSysParam.rest=1;
		while(PPT==0);
		delayms(500);
	}
	if(PPT==0&&((KEY_VOX_VAL-15)<key)&&(key<(KEY_VOX_VAL+15)))          //�� PPT ��  VOX ��ϼ�ʱ���븴λ
	{
		ShowReset();
		mSysParam.rest=1;
		while(PPT==0);
		ResetParam();
		delayms(1000);
	}
	if(PPT==0&&((KEY_SQ_VAL-15)<key)&&(key<(KEY_SQ_VAL+15)))          //�� PPT ��  A��FM ��ϼ�ʱ������ұ�ѡ��
	{
		mMenu.MenuIndex = CHANNEL_COUNTRY;
		ShowCountry();
		mSysParam.rest=1;
		while(PPT==0);
		delayms(500);
	}
	if(PPT==0&&(((KEY_PTY_VAL-15)<key)&&(key<(KEY_PTY_VAL+15))))          //�� PPT ��  PTY ��ϼ�ʱ���뱳����ɫ��ѡ��
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
		IS_KEY1_PRESS();           //ɨ�谴��
		PPT_PRESS();
		UART_EVENT();
		SQ_Switch();
		ShowTk();
		VOX_Check();
		dat =BK4802_RssiAndSnr();
		dat =BK4802_ASQ();
	}
}
