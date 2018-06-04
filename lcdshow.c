#include "system.h"
#include "lcdshow.h"
#include "lcdset.h"
#include "Menu.h"


/***************************************�޸ļ�¼*****************************************************
 
 Function List��
		1��ShowChannel         ��ʾ�ŵ���Ϣ���ŵ������Ƿ���PTYӦ���ŵ����Ƿ���ASQ���Ƿ���VOX���Ƿ��Ǹ߹��ʡ��Ƿ���EU DE UK��FM��AM���ƣ�
	  2��ShowAsq             ASQ����ʱ ������˸
		3��ShowTable     			 ���ұ������ʾ
		4��ShowCountry         ���ҽ�����ʾ
		5��ShowPower       		 ���ʸߵ�������ʾ
		6��ShowButtonToneSwitch        �л���������ʾ
		7��ShowBackColor          		 �л�������ɫ��ʾ	
		8��ShowLocked          ��ʾ����
		9��ShowLockedOtherKey  ����ʱ������������˸��ʾ����
		10��ClearNum           �������
		11��ShowClear          �����ʾ
		12��ShowAll            ȫ����ʾ
 Change Log:
 

****************************************************************************************************/

extern tMenu mMenu;

void ShowChannel()
{
	LCD_NUM1(mCbParam.Channel/10);
	LCD_NUM2(mCbParam.Channel%10);
	if(mMenu.emgIndex==0) LCD_PTY(0);
	else LCD_PTY(1);
	if(mSqParam.IsAsq==1) LCD_ASQ(1);
	else 	LCD_ASQ(0);
	if(mSqParam.IsVox==1)LCD_VOX(1);
	else LCD_VOX(0);
	if((mCbParam.CountryTable==2||mCbParam.CountryTable==3)&&(mCbParam.TxPower == POWER_HIGH))
	{
		LCD_H(1);
	}
	else LCD_H(0);
	switch(mCbParam.Country)
	{
		case COUNTRY_EU:
			LCD_EU();
			break;
		case COUNTRY_UK:
			LCD_UK();
			break;
		case COUNTRY_DE:
			LCD_DE();
			break;
		default:
			LCD_OtherContry();
			break;
	}
	if(mCbParam.Modu==AM) LCD_AM();		
	else LCD_FM();
}

void ShowTable()
{
	LCD_TABLE(mCbParam.CountryTable);
}
	
void ShowCountry()
{
	LCD_COUNTRY(mCbParam.Country+mCbParam.Band);
}

void ShowPower()
{
	LCD_POWER(mCbParam.TxPower);
}
void ShowButtonToneSwitch()
{
	LCD_BUTTONTONE(mCbParam.ButtonToneSwitch);
}
void ShowReset()
{
	LCD_RESET();
}
void ShowBackColor(u8 i)
{
	if(i==1)
	{
		LCD_COLOR(mCbParam.LcdColor);
	}
	switch(mCbParam.LcdColor)
	{
		case 0:
			CLS_LIGHT_B;
			LIGHT_R=0;
			LIGHT_G=0;
			break;
		case 1:
			SET_LIGHT_B;
		  LIGHT_R=0;
			LIGHT_G=0;
			break;
		case 2:
			CLS_LIGHT_B;
		  LIGHT_R=1;
			LIGHT_G=0;
			break;
		case 3:
			CLS_LIGHT_B;
		  LIGHT_R=0;
			LIGHT_G=1;
			break;
		case 4:
			SET_LIGHT_B;
		  LIGHT_R=1;
			LIGHT_G=0;
			break;
		case 5:
			SET_LIGHT_B;
		  LIGHT_R=0;
			LIGHT_G=1;
			break;
		case 6:
			CLS_LIGHT_B;
		  LIGHT_R=1;
			LIGHT_G=1;
			break;
		case 7:
			SET_LIGHT_B;
			LIGHT_R=1;
			LIGHT_G=1;
			break;
	  default:
			break;
	}
}
void ShowLocked()
{
	LCD_LOCK(1);
}
void ShowDeLock()
{
	LCD_LOCK(0);
}
void ShowAsq()
{
	LCD_ASQ(1);
}
void ClearNum()
{
	LCD_NUM_CLEAR();
}
void ShowClear()
{
	LCD_CLEAR();
}
void ShowAll()
{
	LCD_ALL();
}

void ShowTk()
{
	if (mTimer.TkCyclTime>0)
	{
		mTimer.TkCyclTime--;
	}
	else
	{
		mTimer.TkCyclTime = TK_CYCL_TIME;
		switch (mMenu.MenuIndex)
		{
		case CHANNEL:
			if (mMenu.isTkShow==1)
			{
				if (mSqParam.IsVox==1)	LCD_VOX(1);        //VOX
				else LCD_VOX(0);
				
				if (mMenu.emgIndex>0)                      //emg
				{	
					LCD_NUM1(mCbParam.Channel / 10);
					LCD_NUM2(mCbParam.Channel % 10);				
				}
				mMenu.isTkShow=0;
			}
			else
			{
				if (mSqParam.IsVox == 1) LCD_VOX(0);		//vox

				if (mMenu.emgIndex > 0)                      //emg
				{
					LCD_NUM_CLEAR();
				}
				mMenu.isTkShow=1;
			}
			break;
			default:
				break;
		}
	}
}

