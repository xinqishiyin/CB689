#include "system.h"
#include "key.h"
#include "Menu.h"
#include "lcdset.h"
#include "lcdshow.h"
#include "memory.h"

/***************************************�޸ļ�¼***************************************************** 
 Function List��
		1��IS_KEY1_PRESS       6in1 �����ж�
		2��PPT_PRESS           PPT���ж�
		3��InitKey             ����״̬��ʹ��
		4��playButtonTone      ������
 Change Log:


****************************************************************************************************/


xdata tKey mKey;
u8 inDex1=KEY_NULL;

void IS_KEY1_PRESS(void)
{
	u16 vae=0;
	vae=Get_AD(ADC_Key1);
	if(vae<0x0360)
	{
		delayms(50);                     //���󶶶������ܼ�
		vae=Get_AD(ADC_Key1);
		if(((KEY_SQ_VAL-15)<vae)&&(vae<(KEY_SQ_VAL+15))) mKey.KeyIndex1=KEY_SQ;
		else if(((KEY_UP_VAL-15)<vae)&&(vae<(KEY_UP_VAL+15))) mKey.KeyIndex1=KEY_UP;	
		else if(((KEY_DN_VAL-15)<vae)&&(vae<(KEY_DN_VAL+15))) mKey.KeyIndex1=KEY_DN;	
		else if(((KEY_VOX_VAL-15)<vae)&&(vae<(KEY_VOX_VAL+15))) mKey.KeyIndex1=KEY_VOX;
		else if(((KEY_PTY_VAL-15)<vae)&&(vae<(KEY_PTY_VAL+15))) mKey.KeyIndex1=KEY_PTY;
		else if(((KEY_AFM_VAL-15)<vae)&&(vae<(KEY_AFM_VAL+15))) mKey.KeyIndex1=KEY_AFM;
		else mKey.KeyIndex1=KEY_NULL;
	}
	else
	{
		mKey.KeyIndex1=KEY_NULL;
	}
	
	
	
	
	/*---------------------�������˵�---------------------------*/
	if(mMenu.MenuIndex!=CHANNEL&&mMenu.MenuIndex!=CHANNEL_COUNTRY)            
	{
		mMenu.Back_Channel_Time--;
		if(mMenu.Back_Channel_Time==0)
		{
			if(mMenu.isLock==0&&mMenu.isTx==0)
			{
				mMenu.MenuIndex=CHANNEL;              //����				
				ShowChannel();				
				saveAllParam();				
			}
			mMenu.Back_Channel_Time=BACK_TIME;
		}
	}
	else
	{
		mMenu.Back_Channel_Time=BACK_TIME;
	}
	
	/*----------------------��ϼ���ʱ-----------------*/
	if(mKey.isKeyCombo==1)
	{
		mKey.KeyComboLimit--;
		if(mKey.KeyComboLimit==0)
		{
			mMenu.keyCombSQUP=0;
			mMenu.keyCombSQDN=0;
			mKey.isKeyCombo=0;
		}
	}
	else 
	{
		mKey.KeyComboLimit=KEY_COMBOlIMIT;
	}
	
	switch(mKey.KeyIndex1)
	{
		case KEY_SQ:			
			inDex1=KEY_SQ;
			if(mKey.LongPress_Time>0) mKey.LongPress_Time--;
			if(mKey.LongPress_Time==0)          //����3��
			{
				MenuOperate(KEY_LONG_SQ);
				inDex1=KEY_NULL;
				mKey.LongPress_Time=LONGPRESSTIME;
				while(((KEY_SQ_VAL-50)<vae)&&(vae<(KEY_SQ_VAL+50)))
				{
					vae=Get_AD(ADC_Key1);
				}
			}
			break;
		case KEY_UP:
			inDex1=KEY_UP;
			if(mKey.LongPress_Time>0) mKey.LongPress_Time--;
			if(mKey.LongPress_Time==0)          //����3��
			{
				MenuOperate(KEY_LONG_UP);
				inDex1=KEY_NULL;
				mKey.LongPress_Time=LONGPRESSTIME;
				
				while(((KEY_UP_VAL-50)<vae)&&(vae<(KEY_UP_VAL+50)))
				{
					vae=Get_AD(ADC_Key1);
				}
			}			
			break;
		case KEY_DN:
			inDex1=KEY_DN;
			if(mKey.LongPress_Time>0) mKey.LongPress_Time--;
			if(mKey.LongPress_Time==0)          //����3��
			{
				MenuOperate(KEY_LONG_DN);
				inDex1=KEY_NULL;
				mKey.LongPress_Time=LONGPRESSTIME;		
				while(((KEY_DN_VAL-50)<vae)&&(vae<(KEY_DN_VAL+50)))
				{
					vae=Get_AD(ADC_Key1);
				}
			}	
			break;
		case KEY_VOX:
			inDex1=KEY_VOX;		
			if(mKey.LongPress_Time>0) mKey.LongPress_Time--;
			if(mKey.LongPress_Time==0)          //����3��
			{
				MenuOperate(KEY_LONG_VOX);
				inDex1=KEY_NULL;
				mKey.LongPress_Time=LONGPRESSTIME;
				while(((KEY_VOX_VAL-50)<vae)&&(vae<(KEY_VOX_VAL+50)))
				{
					vae=Get_AD(ADC_Key1);
				}
			}			
			break;
		case KEY_PTY:
			inDex1=KEY_PTY;
			MenuOperate(KEY_PTY);		  
			while(((KEY_PTY_VAL-50)<vae)&&(vae<(KEY_PTY_VAL+50)))
			{
				vae=Get_AD(ADC_Key1);
			}
			break;
		case KEY_AFM:
			inDex1=KEY_AFM;
			if(mKey.LongPress_Time>0) mKey.LongPress_Time--;
			if(mKey.LongPress_Time==0)          //����3��
			{
				MenuOperate(KEY_LONG_AFM);
				inDex1=KEY_NULL;
				mKey.LongPress_Time=LONGPRESSTIME;
				while(((KEY_AFM_VAL-50)<vae)&&(vae<(KEY_AFM_VAL+50)))
				{
					vae=Get_AD(ADC_Key1);
				}
			}			
			break;
		default:
			switch(inDex1)
			{
				case KEY_SQ:
					MenuOperate(KEY_SQ);
					break;
				case KEY_UP:
					MenuOperate(KEY_UP);
					break;
				case KEY_DN:
					MenuOperate(KEY_DN);
					break;
				case KEY_AFM:
					MenuOperate(KEY_AFM);
					break;
				case KEY_VOX:
					MenuOperate(KEY_VOX);	
					break;
			}
			inDex1=KEY_NULL;
			mKey.LongPress_Time=LONGPRESSTIME;
			break;
		
	}
}

void PPT_PRESS(void)
{
	if(PPT==0)
	{		
		if(mMenu.isTx==0)
		{
			MenuOperate(KEY_PPT_DN);
		}
		while(PPT==0);
	}
	else
	{ 
		if(mMenu.isTx==1)
		{
			MenuOperate(KEY_PPT_UP);
		}
	}
}
/*-------------------------------------------------------------------------
*������InitKey  ����������ʹ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void InitKey()
{
	mKey.KeyIndex1=0;
	mKey.Power_Time=20;
	mKey.DoublePress_Limit=3;
	mKey.DoublePress_Count=0;
	mKey.Press_Count=0;	
	mKey.MutePress_Timelimit=20;
	mKey.LongPress_Time=LONGPRESSTIME;
	mKey.MutePress_Count=0;
	mKey.MuteDoublePress_Timelimit=20;
	mMenu.Back_Channel_Time=BACK_TIME;
	mMenu.MenuIndex=0;
	mMenu.MenuIndex=0;	
	mMenu.emgIndex=0;
	mMenu.isTx=0;	
	mSqParam.Scan = 0;
	mSqParam.ScanHould = 1;
	mTimer.ScanHouldTime = SCAN_HOULD_TIME;
}
/*-------------------------------------------------------------------------
*������playButtonTone  ������
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void playButtonTone(void)
{

	if(mSysParam.SpkOpen ==1)return;
	if(mCbParam.ButtonToneSwitch) 
	{	
		xPWMCN |= 0x10;
		//SPK_EN=1;
		mSysParam.isButtonTone=1;
		mTimer.ButtonToneTime=BUTTONTONE_TIME;
	}
}



