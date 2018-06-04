#include "system.h"
#include "Menu.h"
#include "MenuEvent.h"
#include "key.h"



/***************************************�޸ļ�¼*****************************************************
  Function List��
		1��MenuOperate       �˵���������		
 Change Log:

****************************************************************************************************/


/*-------------------------------------------------------------------------
*������Channel_Menu  �ŵ��˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void Channel_Menu(unsigned char key)
{
	switch (key)
	{
	case KEY_SQ:
		playButtonTone();
		mMenu.keyCombSQUP = 1;
		mKey.isKeyCombo = 1;		
		break;
	case KEY_LONG_SQ:
		playButtonTone();
		CHANNEL_LONG_SQ_FUC();
		break;
	case KEY_UP:
		playButtonTone();
		if (mMenu.keyCombSQUP == 1)
		{
			CHANNEL_SWITCH_TUTTONTONE_FUC();
			mMenu.keyCombSQUP = 0;
			mMenu.keyCombSQDN = 0;
			mKey.isKeyCombo = 0;
		}
		else  CHANNEL_UP_FUC();

		break;
	case KEY_LONG_UP:
		playButtonTone();
		mSqParam.ScanDir = 1;
		mMenu.MenuIndex = CHANNEL_SCAN;
		CHANNEL_SCAN_FUC();
		break;
	case KEY_DN:
		playButtonTone();
		CHANNEL_DN_FUC();
		break;
	case KEY_LONG_DN:
		playButtonTone();
		mSqParam.ScanDir = 1;
		mMenu.MenuIndex = CHANNEL_SCAN;
		CHANNEL_SCAN_FUC();
		break;
	case KEY_VOX:
		playButtonTone();
		CHANNEL_VOX_FUC();
		break;
	case KEY_LONG_VOX:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL_LOCK;
		CHANNEL_LOCK_FUC();
		break;
	case KEY_PTY:
		playButtonTone();
		CHANNEL_PTY_FUC();
		break;
	case KEY_AFM:
		playButtonTone();
		CHANNEL_AFM_FUC();
		break;
	case KEY_LONG_AFM:
		playButtonTone();		
		CHANNEL_LONG_AF_FUC();
		break;
	case KEY_PPT_DN:
		playButtonTone();
		CHANNEL_PPT_DN_FUC();
		break;
	case KEY_PPT_UP:
		playButtonTone();
		CHANNEL_PPT_UP_FUC();
		break;
	default:
		break;
	}
}

/*-------------------------------------------------------------------------
*������Scan_Menu  ɨ��˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void Scan_Menu(unsigned char key)
{
	switch (key)
	{
	case KEY_LONG_UP:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_SCAN_LONG_PRESS_FUC();
		break;
	case KEY_UP:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_SCAN_LONG_PRESS_FUC();
		break;
	case KEY_DN:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_SCAN_LONG_PRESS_FUC();
		break;
	case KEY_LONG_DN:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_SCAN_LONG_PRESS_FUC();
		break;
	case KEY_PPT_DN:
		playButtonTone();
		CHANNEL_SCAN_PPT_DN_FUC();
		break;
	case KEY_PPT_UP:
		playButtonTone();
		CHANNEL_SCAN_PPT_UP_FUC();
		break;
	default:
		break;
	}
}

/*-------------------------------------------------------------------------
*������Country_Menu  ���Ҳ˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void Country_Menu(unsigned char key)
{
	switch (key)
	{
	case KEY_UP:
		playButtonTone();
		CHANNEL_COUNTRY_UP_FUC();
		break;
	case KEY_DN:
		playButtonTone();
		CHANNEL_COUNTRY_DN_FUC();
		break;
	case KEY_PPT_DN:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_REST_FUC();
		break;
	default:
		break;
	}
}
/*-------------------------------------------------------------------------
*������Lock_Menu  ����״̬�˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void Lock_Menu(unsigned char key)
{
	switch (key)
	{
	case KEY_SQ:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_LONG_SQ:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_UP:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_LONG_UP:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_DN:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_LONG_DN:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_VOX:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_PTY:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_AFM:
		playButtonTone();
		CHANNEL_LOCK_OTHERKEY_FUC();
		break;
	case KEY_LONG_VOX:
		playButtonTone();
		mMenu.MenuIndex = CHANNEL;
		CHANNEL_DELOCK_FUC();
		break;
	case KEY_PPT_DN:
		playButtonTone();
		CHANNEL_PPT_DN_FUC();
		break;
	case KEY_PPT_UP:
		playButtonTone();
		CHANNEL_PPT_UP_FUC();
		break;
	default:
		break;
	}
}
/*-------------------------------------------------------------------------
*������BackLight_Menu  ������ɫ�˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void BackLight_Menu(unsigned char key)
{
	switch (key)
	{		
		case KEY_UP:
			playButtonTone();
			CHANNEL_BACKCOLOR_UP_FUC();
			break;		
		case KEY_DN:
			playButtonTone();
			CHANNEL_BACKCOLOR_DN_FUC();
		break;		
		case KEY_PPT_DN:
			playButtonTone();
			mMenu.MenuIndex = CHANNEL;
			CHANNEL_REST_FUC();
		  while(PPT==0);
			break;
		default:
			break;
	}
}
/*-------------------------------------------------------------------------
*������PowerSet_Menu  ���书�ʲ˵�
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void PowerSet_Menu(unsigned char key)
{
	switch (key)
	{		
		case KEY_UP:
			playButtonTone();
			CHANNEL_TXPOWER_CHANGE_FUC();
			break;		
		case KEY_DN:
			playButtonTone();
			CHANNEL_TXPOWER_CHANGE_FUC();
		break;		
		case KEY_PPT_DN:
			playButtonTone();
			mMenu.MenuIndex = CHANNEL;
			CHANNEL_REST_FUC();
		  while(PPT==0);
			break;
		default:
			break;
	}
}

void Check_ComKey_Flag(unsigned char key)
{
	if (mMenu.keyCombSQUP == 1 && key != KEY_UP) { mMenu.keyCombSQUP = 0; mKey.isKeyCombo = 0; }   //����ϼ���״ֵ̬
	if (mMenu.keyCombSQDN == 1 && key != KEY_DN) { mMenu.keyCombSQDN = 0; mKey.isKeyCombo = 0; }
}


/*-------------------------------------------------------------------------
*������MenuOperate  �˵�����
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void MenuOperate(unsigned char key)
{
	Check_ComKey_Flag(key);
	
	switch(mMenu.MenuIndex)
	{
		case CHANNEL:																  //ͨ���˵�
			Channel_Menu(key);
			break;		
		case CHANNEL_SCAN:															 //ɨ��ģʽ����
			Scan_Menu(key);
			break;
		case CHANNEL_COUNTRY:															//���ҽ���
			Country_Menu(key);
			break;
		case CHANNEL_LOCK:                                //  ��������
			Lock_Menu(key);
			break;
		case CHANNEL_BACKLIGHT:														//�����ƽ���
			BackLight_Menu(key);
			break;
		case CHENNEL_POWER:																//���书�ʽ���
			PowerSet_Menu(key);
			break;		
		default:
			break;
	}
}
