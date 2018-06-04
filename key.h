#define _KEY_H
#ifdef _KEY_H

#define KEY_NULL      0
#define KEY_SQ        10
#define KEY_LONG_SQ   11
#define KEY_UP        12
#define KEY_LONG_UP   13
#define KEY_DN        14
#define KEY_LONG_DN   15
#define KEY_VOX       16
#define KEY_LONG_VOX  17
#define KEY_PTY       18
#define KEY_AFM       19
#define KEY_LONG_AFM  20
#define KEY_PPT_DN    21
#define KEY_PPT_UP    22




typedef struct
{
	unsigned char KeyIndex1;	      //KEY1 AD值 索引
	unsigned char Power_Time;	//电源键长按时长
	unsigned char DoublePress_Limit;	//双击时限
	unsigned char DoublePress_Count;  //双击次数
	unsigned char Press_Count;          //按键次数
	unsigned char MutePress_Timelimit;  //静音（电源）长按时长
	unsigned char MuteDoublePress_Timelimit;  //静音（电源）双击时限
	unsigned char LongPress_Time;          //长按SQ切换时长
	unsigned char MutePress_Count;      //电源按键次数
	unsigned char KeyComboLimit;        //组合键限时
	unsigned char isKeyCombo;
}tKey;
extern xdata tKey mKey;

extern u8 ButtonToneTime;
extern u8 isButtonTone;
/*-------------------------------------------------------------------------
*函数：InitKey  按键参数初使化
*参数：无  
*返回值：无
*-------------------------------------------------------------------------*/
void InitKey();
/*-------------------------------------------------------------------------
*函数：IS_KEY1_PRESS 6In1按键判断
*参数：
*返回值：
*-------------------------------------------------------------------------*/
void IS_KEY1_PRESS(void);
/*-------------------------------------------------------------------------
*函数：PPT_PRESS  PPT按键判断
*参数：
*返回值：
*-------------------------------------------------------------------------*/
void PPT_PRESS(void);

#endif