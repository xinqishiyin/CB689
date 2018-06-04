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






extern u8 ButtonToneTime;
extern u8 isButtonTone;
/*-------------------------------------------------------------------------
*������InitKey  ����������ʹ��
*��������  
*����ֵ����
*-------------------------------------------------------------------------*/
void InitKey();
/*-------------------------------------------------------------------------
*������IS_KEY1_PRESS 6In1�����ж�
*������
*����ֵ��
*-------------------------------------------------------------------------*/
void IS_KEY1_PRESS(void);
/*-------------------------------------------------------------------------
*������PPT_PRESS  PPT�����ж�
*������
*����ֵ��
*-------------------------------------------------------------------------*/
void PPT_PRESS(void);

#endif