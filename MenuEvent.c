#include "system.h"
#include "MenuEvent.h"
#include "lcdset.h"
#include "lcdshow.h"
#include "handler.h"
#include "Menu.h"
#include "BK4802.h"
#include "memory.h"
#include "vco.h"




/***************************************�޸ļ�¼*****************************************************
 Function List��
		1��checkChannel        �л��ŵ�ʱ�Թ����ŵ����ŵ���С�����ֵ�����ж�
	  2��MenuFuc             �˵�����ִ������
 Change Log:



****************************************************************************************************/

void checkChannel()
{
	mSysParam.MinChannel = 1;
	switch(mCbParam.Country)
	{
		case COUNTRY_EU: mSysParam.MaxChannel = 40;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_CE: mSysParam.MaxChannel = 40;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_UK: mSysParam.MaxChannel = 40;mCbParam.Band=0;mSysParam.isUK=1;break;
		case COUNTRY_PL: mSysParam.MaxChannel = 40;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_I0: mSysParam.MaxChannel = 40;mCbParam.Band=0;mSysParam.isUK=0;break;		
		
		case COUNTRY_RU:
			{		
				if(mCbParam.Band>9) mCbParam.Band=0;
				mSysParam.MaxChannel = 40;
				mSysParam.isUK=0;
			}
			break;
		
		case COUNTRY_I2: mSysParam.MaxChannel = 34;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_DE: mSysParam.MaxChannel = 80;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_IN: mSysParam.MaxChannel = 27;mCbParam.Band=0;mSysParam.isUK=0;break;
		case COUNTRY_HX: 
			if(mCbParam.Band>8) mCbParam.Band=0;
		  if(mCbParam.Band==8) mSysParam.MaxChannel = 20;
		  else mSysParam.MaxChannel = 40;
			mSysParam.isUK=0;
			break;
	}
	if(mCbParam.Country==COUNTRY_DE&&mCbParam.Modu==AM) 	mSysParam.MaxChannel=80;	
	else if((mCbParam.Country==COUNTRY_DE&&mCbParam.Modu==FM)) mSysParam.MaxChannel=80;
	
}
/*-------------------------------------------------------------------------
*������CHANNEL_TXPOWER_CHANGE_FUC  �����л�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_TXPOWER_CHANGE_FUC()
{
	if(mCbParam.TxPower==POWER_LOW) mCbParam.TxPower=POWER_HIGH;
	else mCbParam.TxPower=POWER_LOW;
	saveData(EEP_POWER,mCbParam.TxPower);
	ShowPower();
}


/*-------------------------------------------------------------------------
*������CHANNEL_LONG_SQ_FUC  SQ/ASQ�л�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_LONG_SQ_FUC()
{
	if(mSqParam.IsAsq==1)mSqParam.IsAsq=0;
	else 	mSqParam.IsAsq=1;	
	saveData(EEP_IS_ASQ,mSqParam.IsAsq);
	ShowChannel();
}
/*-------------------------------------------------------------------------
*������CHANNEL_UP_FUC  �ŵ���
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_UP_FUC()
{
	checkChannel();
	if(mCbParam.Channel<mSysParam.MaxChannel)
	{
		mCbParam.Channel++;
	}
	else		
	{
		
		if(mCbParam.Country==COUNTRY_DE&&mCbParam.Modu==AM)
		{
			mSysParam.MaxChannel=80;
			mCbParam.Channel=41;
			mCbParam.Modu=FM;
		}
		else
		{
//			if(mCbParam.Country==COUNTRY_RU)
//			{
//				if(mCbParam.Band<9)mCbParam.Band++;
//				else mCbParam.Band=0;
//			}			
			mCbParam.Channel=mSysParam.MinChannel;			
		}
	}
	if(mMenu.emgIndex!=0)mMenu.emgIndex=0;
	saveData(EEP_CHANNEL,mCbParam.Channel);	
	mMenu.emgIndex=0;
	mSysParam.isLastChannel=0;	
	mSysParam.LastChannel=mCbParam.Channel;	
	mSysParam.LastBand=mCbParam.Band;
	SetTxPower();
	ShowChannel();
	calculateFreq();              //����Ƶ��	
	BK4802_TXtoRX();

}
/*-------------------------------------------------------------------------
*������CHANNEL_DN_FUC  �ŵ���
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_DN_FUC()
{
	checkChannel();
	if(mCbParam.Channel>mSysParam.MinChannel)
	{
		mCbParam.Channel--;
	}
	else 
	{
		
//			if(mCbParam.Country==COUNTRY_RU)
//			{
//				if(mCbParam.Band>0)mCbParam.Band--;
//				else mCbParam.Band=9;
//				mCbParam.Channel=mSysParam.MaxChannel;
//			}
			if(mCbParam.Country==COUNTRY_DE&&mCbParam.Modu==AM)mCbParam.Modu=FM ;	
			mCbParam.Channel=mSysParam.MaxChannel;			
	}
	mMenu.emgIndex=0;
	mSysParam.isLastChannel=0;	
	mSysParam.LastChannel=mCbParam.Channel;	
	mSysParam.LastBand=mCbParam.Band;
	
	saveData(EEP_CHANNEL,mCbParam.Channel);	
	SetTxPower();
	ShowChannel();
	calculateFreq();              //����Ƶ��	
	BK4802_TXtoRX();
}
/*-------------------------------------------------------------------------
*������CHANNEL_SCAN_FUC  ɨ��ģʽ
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_SCAN_FUC()
{
	mSqParam.Scan = 1;
	LCD_SC(1);
}

/*-------------------------------------------------------------------------
*������CHANNEL_VOX_FUC  VOX�Ĺرտ���
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_VOX_FUC()
{
	if(mSqParam.IsVox==1)
	{
		mSqParam.IsVox=0;
	}
	else 
	{
		mSqParam.IsVox=1;
	}
	saveData(EEP_IS_VOX,mSqParam.IsVox);
	ShowChannel();
}
/*-------------------------------------------------------------------------
*������CHANNEL_PTY_FUC  �����ŵ�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_PTY_FUC()
{
	switch(mMenu.emgIndex)
	{
		case 0:
					
			mMenu.emgIndex++;
			mCbParam.forEMGChannel=mCbParam.Channel;
			mCbParam.Channel=9;			
			break;
		case 1:mMenu.emgIndex++;		  
			mCbParam.Channel=19;
		 
			break;
		case 2:mMenu.emgIndex=0;		
			mCbParam.Channel=mCbParam.forEMGChannel;
		break;
	}
	SetTxPower();
	ShowChannel();
	calculateFreq();              //����Ƶ��
}
/*-------------------------------------------------------------------------
*������CHANNEL_AFM_FUC  AM/FM�л�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_AFM_FUC()
{
	if(mCbParam.Country==COUNTRY_EU||               \
		 mCbParam.Country==COUNTRY_PL||               \
	   mCbParam.Country==COUNTRY_I0||               \
	   mCbParam.Country==COUNTRY_I2||               \
	   (mCbParam.Country==COUNTRY_DE&&mCbParam.Channel<41)||               \
	   mCbParam.Country==COUNTRY_IN||               \
		 mCbParam.Country==COUNTRY_RU||               \
		 mCbParam.Country==COUNTRY_HX               \	                  
	  )
	{
		if(mCbParam.Modu==FM)	mCbParam.Modu=AM;
		else mCbParam.Modu=FM;	
	}
	else
	{		
		if(mSysParam.isLastChannel==0)
		{
			if(mCbParam.Channel==mCbParam.LastChannel&&	mCbParam.Band==mCbParam.LastBand)
			{
				mCbParam.Channel=mSysParam.BackChannel;
				mCbParam.Band=mSysParam.BackBand;				
				mMenu.emgIndex=0;
				mSysParam.isLastChannel=2;	
			}
			else
			{
				mSysParam.LastChannel=mCbParam.Channel;
				mSysParam.LastBand=mCbParam.Band;	
				mCbParam.Channel=mCbParam.LastChannel;
				mCbParam.Band=mCbParam.LastBand;
				mMenu.emgIndex=0;
				mSysParam.isLastChannel=1;
			}
		}
		else if(mSysParam.isLastChannel==1)
		{
			mCbParam.Channel=mSysParam.LastChannel;
			mCbParam.Band=mSysParam.LastBand;			
			mMenu.emgIndex=0;	
			mSysParam.isLastChannel=0;		
		}
		else if(mSysParam.isLastChannel==2)
		{
			mCbParam.Channel=mCbParam.LastChannel;
			mCbParam.Band=mCbParam.LastBand;
			mMenu.emgIndex=0;
			mSysParam.isLastChannel=0;
		}
	}
	saveData(EEP_MODU,mCbParam.Modu);	
	SetModu();
	calculateFreq();	
	BK4802_TXtoRX();		
	SetTxPower();
	ShowChannel();
}

/*-------------------------------------------------------------------------
*������CHANNEL_LONG_AF_FUC  �����ص�CEƵ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_LONG_AF_FUC()
{
	u8 oldchannel=0;
	if(mCbParam.Country==COUNTRY_UK)
	{
		playButtonTone();
		mCbParam.Country=COUNTRY_CE;
		oldchannel=mCbParam.Channel;
		mCbParam.Channel=9;	
		ShowClear();
		ShowCountry();
		delayms(1000);	
		mSysParam.isUK=1;	
		calculateFreq();	
		BK4802_TXtoRX();		
		SetTxPower();
		ShowChannel();		
	}
	else if(mCbParam.Country==COUNTRY_CE&&mSysParam.isUK==1)
	{
		playButtonTone();
		mCbParam.Country=COUNTRY_UK;
		oldchannel=mCbParam.Channel;
		mCbParam.Channel=9;	
		mSysParam.isUK=0;	
		ShowClear();
		ShowCountry();
		delayms(1000);
		calculateFreq();	
		BK4802_TXtoRX();		
		SetTxPower();				
		ShowChannel();			
	}
}
/*-------------------------------------------------------------------------
*������CHANNEL_PPT_DN_FUC  ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_PPT_DN_FUC()
{
	if(mMenu.isTx==0)
	{
		mMenu.isTx=1;
		calculateFreq();
		BK4802_RXtoTX();
		//RX_P=0;
		mSysParam.isLastChannel=0;
		mSysParam.BackChannel=mCbParam.LastChannel;
		mSysParam.BackBand=mCbParam.LastBand;
		mCbParam.LastChannel=mCbParam.Channel;
		mCbParam.LastBand=mCbParam.Band;
		if(mSqParam.Scan==2) mSqParam.ScanHould=2;
		if(mCbParam.TxPower==POWER_HIGH)
		{
			LCD_STRENGTH(6);
		}
		else
		{
			LCD_STRENGTH(3);
		}
		LCD_RX(0);
		LCD_TX(1);
	}
}
/*-------------------------------------------------------------------------
*������CHANNEL_PPT_UP_FUC  ֹͣ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_PPT_UP_FUC()
{
	mMenu.isTx=0;
	calculateFreq();	
	RX_P=1;
	BK4802_TXtoRX();	
	LCD_STRENGTH(0);
	LCD_TX(0);
	LCD_RX(1);
}
	
/*-------------------------------------------------------------------------
*������CHANNEL_ASQ_FUC  ����ASQ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_ASQ_FUC()
{
	ShowAsq();
}
	/*-------------------------------------------------------------------------
*������CHANNEL_ASQ_SQ_FUC  ��ASQ���ڷ����ŵ�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_ASQ_SQ_FUC()
{
	ShowChannel();
}
	
/*-------------------------------------------------------------------------
*������CHANNEL_ASQ_UP_FUC  ASQ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_ASQ_UP_FUC()
{
	if(mSqParam.AsqLevel<5)
	{
		mSqParam.AsqLevel++;
	}
	saveData(EEP_ASQ_LEVEL,mSqParam.AsqLevel);
	ShowAsq();
}
/*-------------------------------------------------------------------------
*������CHANNEL_ASQ_DN_FUC  ASQ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_ASQ_DN_FUC()
{
	if(mSqParam.AsqLevel>1)
	{
		mSqParam.AsqLevel--;
	}
	saveData(EEP_ASQ_LEVEL,mSqParam.AsqLevel);
	ShowAsq();
}

/*-------------------------------------------------------------------------
*������CHANNEL_SCAN_LONG_PRESS_FUC  �˳�ɨ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_SCAN_LONG_PRESS_FUC()
{
	LCD_SC(0);
}
/*-------------------------------------------------------------------------
*������CHANNEL_SCAN_PPT_DN_FUC  ɨ��״̬�·���
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_SCAN_PPT_DN_FUC()
{
	
}
/*-------------------------------------------------------------------------
*������CHANNEL_SCAN_PPT_UP_FUC  ɨ״̬��ֹͣ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_SCAN_PPT_UP_FUC()
{

}	
	
/*-------------------------------------------------------------------------
*������CHANNEL_COUNTRY_UP_FUC  ���Ҽ�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_COUNTRY_UP_FUC()
{	
	if(mCbParam.Country==COUNTRY_RU)
	{
		if(mCbParam.Band<9)	mCbParam.Band++;
		else mCbParam.Band=0;
	}
  else if(mCbParam.Country==COUNTRY_HX)
	{
		if(mCbParam.Band<8)	mCbParam.Band++;
		else mCbParam.Band=0;
	}
	else
	{
		if(mCbParam.Country<7)	mCbParam.Country++;
		else mCbParam.Country=0;
	}
	saveData(EEP_COUNTRY,mCbParam.Country);
	saveData(EEP_BAND,mCbParam.Band);		
	ShowCountry();
}
/*-------------------------------------------------------------------------
*������CHANNEL_COUNTRY_DN_FUC  ���Ҽ�
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_COUNTRY_DN_FUC()
{
	if(mCbParam.Country==COUNTRY_RU)
	{
		if(mCbParam.Band>0)	mCbParam.Band--;
		else mCbParam.Band=9;
	}
  else if(mCbParam.Country==COUNTRY_HX)
	{
		if(mCbParam.Band>0)	mCbParam.Band--;
		else mCbParam.Band=8;
	}
	else
	{
		if(mCbParam.Country>0)	mCbParam.Country--;
		else mCbParam.Country=7;
	}	
	saveData(EEP_COUNTRY,mCbParam.Country);
	saveData(EEP_BAND,mCbParam.Band);		
	ShowCountry();
}
/*-------------------------------------------------------------------------
*������CHANNEL_REST_FUC  ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/	
void CHANNEL_REST_FUC()
{
	mSysParam.rest=0;
}
/*-------------------------------------------------------------------------
*������CHANNEL_SWITCH_TUTTONTONE_FUC  �л�������
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_SWITCH_TUTTONTONE_FUC()
{
	if(mCbParam.ButtonToneSwitch==0)mCbParam.ButtonToneSwitch=1;
	else mCbParam.ButtonToneSwitch=0;
	ShowButtonToneSwitch();
	saveData(EEP_TONE_SW,mCbParam.ButtonToneSwitch);
	delayms(1000);
	ShowChannel();
}

/*-------------------------------------------------------------------------
*������CHANNEL_BACKCOLOR_UP_FUC  �л�������ɫ  ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_BACKCOLOR_UP_FUC()
{
	if(mCbParam.LcdColor<7)mCbParam.LcdColor++;
	else mCbParam.LcdColor=0;
	ShowBackColor(1);
	saveData(EEP_LCD_COLOR,mCbParam.LcdColor);
}
/*-------------------------------------------------------------------------
*������CHANNEL_BACKCOLOR_DN_FUC  �л�������ɫ ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_BACKCOLOR_DN_FUC()
{
	if(mCbParam.LcdColor>0)mCbParam.LcdColor--;
	else mCbParam.LcdColor=7;
	ShowBackColor(1);
	saveData(EEP_LCD_COLOR,mCbParam.LcdColor);
}

/*-------------------------------------------------------------------------
*������CHANNEL_LOCK_FUC  ����
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_LOCK_FUC()
{
	ShowLocked();
	delayms(1000);
	ShowChannel();
}
/*-------------------------------------------------------------------------
*������CHANNEL_LOCK_OTHERKEY_FUC  ������������
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_LOCK_OTHERKEY_FUC()
{
	u8 i;
	for(i=0;i<3;i++)
	{
		ShowLocked();
		delayms(200);
		ClearNum();
		delayms(200);		
	}	
	ShowChannel();
}
/*-------------------------------------------------------------------------
*������CHANNEL_DELOCK_FUC  �������
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void CHANNEL_DELOCK_FUC()
{
	ShowDeLock();
	delayms(1000);
	ShowChannel();
}