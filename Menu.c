#include "system.h"
#include "Menu.h"
#include "MenuEvent.h"
#include "key.h"



/***************************************修改记录*****************************************************
  Function List：
		1、MenuOperate       菜单操作程序		
 Change Log:

****************************************************************************************************/


/*-------------------------------------------------------------------------
*函数：Channel_Menu  信道菜单
*参数：无
*返回值：无
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
*函数：Scan_Menu  扫描菜单
*参数：无
*返回值：无
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
*函数：Country_Menu  国家菜单
*参数：无
*返回值：无
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
*函数：Lock_Menu  锁键状态菜单
*参数：无
*返回值：无
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
*函数：BackLight_Menu  背景颜色菜单
*参数：无
*返回值：无
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
*函数：PowerSet_Menu  发射功率菜单
*参数：无
*返回值：无
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
	if (mMenu.keyCombSQUP == 1 && key != KEY_UP) { mMenu.keyCombSQUP = 0; mKey.isKeyCombo = 0; }   //非组合键清状态值
	if (mMenu.keyCombSQDN == 1 && key != KEY_DN) { mMenu.keyCombSQDN = 0; mKey.isKeyCombo = 0; }
}


/*-------------------------------------------------------------------------
*函数：MenuOperate  菜单按键
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void MenuOperate(unsigned char key)
{
	Check_ComKey_Flag(key);
	
	switch(mMenu.MenuIndex)
	{
		case CHANNEL:																  //通道菜单
			Channel_Menu(key);
			break;		
		case CHANNEL_SCAN:															 //扫描模式界面
			Scan_Menu(key);
			break;
		case CHANNEL_COUNTRY:															//国家界面
			Country_Menu(key);
			break;
		case CHANNEL_LOCK:                                //  锁屏界面
			Lock_Menu(key);
			break;
		case CHANNEL_BACKLIGHT:														//背景灯界面
			BackLight_Menu(key);
			break;
		case CHENNEL_POWER:																//发射功率界面
			PowerSet_Menu(key);
			break;		
		default:
			break;
	}
}
