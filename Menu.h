#define _MENU_H
#ifdef _MENU_H

/*--------------�˵������궨��------------------------*/
#define CHANNEL                             0
//#define CHANNEL_ASQ													2   //����ASQ�ȼ�����
#define CHANNEL_PPTDN                       4
#define CHANNEL_SCAN 												6  //����ɨ��ģʽ
#define CHANNEL_BUTTONTONE                  10  //����˵�ģʽ PB ������
#define CHANNEL_BACKCOLOUR   								11  //�˵��л���FC LCD��ɫ�л�
#define CHANNEL_BUTTONLED 								  12  //�˵��л���FL ����������
#define CHANNEL_COUNTRY                     13  //���ù��ҽ�������
#define CHANNEL_TABLE                       14  //����л�
#define CHANNEL_LOCK                        15  //��������
#define CHANNEL_BACKLIGHT                   16	//����������
#define CHENNEL_POWER                       17  //��������

/*-------------------------------------------------------------------------
*������MenuOperate        ��ǰ�˵��°�����ѡ����������
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void MenuOperate(unsigned char key);

#endif