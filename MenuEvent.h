#define _MENUEVENT_H
#ifdef _MENUEVENT_H

/*-------------------------------------------------------------------------开机菜单--------------------------*/

void CHANNEL_REST_FUC();          		//重启

/*-------------功率切换---------------*/	
void CHANNEL_TXPOWER_CHANGE_FUC();    //功率切换

/*-------------国家切换---------------*/	
void CHANNEL_COUNTRY_UP_FUC();        //国家加	
void CHANNEL_COUNTRY_DN_FUC();				//国家减

/*-------------背景灯切换---------------*/	
void CHANNEL_BACKCOLOR_UP_FUC();      //背景颜色加
void CHANNEL_BACKCOLOR_DN_FUC();			//背景颜色减

/*-------------------------------------------------------------------------通道菜单--------------------------*/
 
void CHANNEL_LONG_SQ_FUC();           //切换SQ/ASQ	

/*-------------信道切换---------------*/	
void CHANNEL_UP_FUC();                //信道加		
void CHANNEL_DN_FUC();								//信道减
void CHANNEL_PTY_FUC();               //紧急信道

void CHANNEL_SCAN_FUC();              //进入扫描模式	
void CHANNEL_VOX_FUC();								//VOX开启关闭		

void CHANNEL_AFM_FUC();								//切换AM/FM	
void CHANNEL_LONG_AF_FUC();           //长按
/*-------------发射接收---------------*/	
void CHANNEL_PPT_DN_FUC();            //发射	
void CHANNEL_PPT_UP_FUC();						//停止发射

void CHANNEL_ASQ_FUC();               //进入ASQ设置

/*------------------------------------------------------------------------ASQ设置菜单------------------------*/

void CHANNEL_ASQ_SQ_FUC();            //退出ASQ设置
	
void CHANNEL_ASQ_UP_FUC();						//ASQ加	
void CHANNEL_ASQ_DN_FUC();						//ASQ减


/*-------------------------------------------------------------------------扫描模式---------------------------*/
	
void CHANNEL_SCAN_LONG_PRESS_FUC();   //退出扫描模式
	
void CHANNEL_SCAN_PPT_DN_FUC();				//扫描模式中的发射	
void CHANNEL_SCAN_PPT_UP_FUC();				//扫描模式中的停止发射

	

	
/*---------------------------------------------------------------------------其他设置------------------------*/	

void CHANNEL_SWITCH_TUTTONTONE_FUC(); //切换按键音



void CHANNEL_LOCK_FUC();              //锁屏
void CHANNEL_DELOCK_FUC();						//解除锁屏
void CHANNEL_COUNTRY_PPT_DN_FUC();
void CHANNEL_LOCK_OTHERKEY_FUC();
#endif