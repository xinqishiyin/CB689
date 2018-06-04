#define _MENU_H
#ifdef _MENU_H

/*--------------菜单索引宏定义------------------------*/
#define CHANNEL                             0
//#define CHANNEL_ASQ													2   //进入ASQ等级设置
#define CHANNEL_PPTDN                       4
#define CHANNEL_SCAN 												6  //进入扫描模式
#define CHANNEL_BUTTONTONE                  10  //进入菜单模式 PB 按键音
#define CHANNEL_BACKCOLOUR   								11  //菜单切换到FC LCD颜色切换
#define CHANNEL_BUTTONLED 								  12  //菜单切换到FL 按键灯设置
#define CHANNEL_COUNTRY                     13  //设置国家界面索引
#define CHANNEL_TABLE                       14  //表格切换
#define CHANNEL_LOCK                        15  //锁屏界面
#define CHANNEL_BACKLIGHT                   16	//背景灯设置
#define CHENNEL_POWER                       17  //功率设置

/*-------------------------------------------------------------------------
*函数：MenuOperate        当前菜单下按按键选择运行内容
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void MenuOperate(unsigned char key);

#endif