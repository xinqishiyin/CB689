#include "system.h"
#include "Timer.h"
#include "Menu.h"



/*-------------------------------------------------------------------------
*������irq_timer1  16ms��ʱ�ж�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void irq_timer1(void) interrupt 3
{
	/*---------------------ͨѶ��ʱ---------------------------*/
   if((mReceivePackage.RecvCount!=0)||(mReceivePackage.RecvStatus!=UART0_IDLE))
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
   /*---------------------������ֹͣ---------------------------*/
	if(mSysParam.isButtonTone==1)
	{
		mTimer.ButtonToneTime--;
		if(mTimer.ButtonToneTime==0)
		{
			xPWMCN &= ~0x10;				
			mSysParam.isButtonTone=0;
		}
	}

	/*---------------------�������˵�---------------------------*/
	if (mMenu.MenuIndex != CHANNEL&&mMenu.MenuIndex != CHANNEL_COUNTRY&&mMenu.MenuIndex != CHANNEL_TABLE)
	{
		mTimer.Back_Channel_Time--;
		if (mTimer.Back_Channel_Time == 0)
		{
			if (mMenu.isLock == 0 && mMenu.isTx == 0)
			{
				mMenu.isBackChannel = 1;				
			}
			mTimer.Back_Channel_Time = BACK_TIME;
		}
	}
	else
	{
		mTimer.Back_Channel_Time = BACK_TIME;
	}

	/*----------------------��ϼ���ʱ-----------------*/
	if (mKey.isKeyCombo == 1)
	{
		mKey.KeyComboLimit--;
		if (mKey.KeyComboLimit == 0)
		{
			mMenu.keyCombSQUP = 0;
			mMenu.keyCombSQDN = 0;
			mKey.isKeyCombo = 0;
		}
	}
	else
	{
		mKey.KeyComboLimit = KEY_COMBOlIMIT;
	}
	/*----------------------ɨ��ͣ����ʱ-----------------*/
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


