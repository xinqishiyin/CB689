#define _MENUEVENT_H
#ifdef _MENUEVENT_H

/*-------------------------------------------------------------------------�����˵�--------------------------*/

void CHANNEL_REST_FUC();          		//����

/*-------------�����л�---------------*/	
void CHANNEL_TXPOWER_CHANGE_FUC();    //�����л�

/*-------------�����л�---------------*/	
void CHANNEL_COUNTRY_UP_FUC();        //���Ҽ�	
void CHANNEL_COUNTRY_DN_FUC();				//���Ҽ�

/*-------------�������л�---------------*/	
void CHANNEL_BACKCOLOR_UP_FUC();      //������ɫ��
void CHANNEL_BACKCOLOR_DN_FUC();			//������ɫ��

/*-------------------------------------------------------------------------ͨ���˵�--------------------------*/
 
void CHANNEL_LONG_SQ_FUC();           //�л�SQ/ASQ	

/*-------------�ŵ��л�---------------*/	
void CHANNEL_UP_FUC();                //�ŵ���		
void CHANNEL_DN_FUC();								//�ŵ���
void CHANNEL_PTY_FUC();               //�����ŵ�

void CHANNEL_SCAN_FUC();              //����ɨ��ģʽ	
void CHANNEL_VOX_FUC();								//VOX�����ر�		

void CHANNEL_AFM_FUC();								//�л�AM/FM	
void CHANNEL_LONG_AF_FUC();           //����
/*-------------�������---------------*/	
void CHANNEL_PPT_DN_FUC();            //����	
void CHANNEL_PPT_UP_FUC();						//ֹͣ����

void CHANNEL_ASQ_FUC();               //����ASQ����

/*------------------------------------------------------------------------ASQ���ò˵�------------------------*/

void CHANNEL_ASQ_SQ_FUC();            //�˳�ASQ����
	
void CHANNEL_ASQ_UP_FUC();						//ASQ��	
void CHANNEL_ASQ_DN_FUC();						//ASQ��


/*-------------------------------------------------------------------------ɨ��ģʽ---------------------------*/
	
void CHANNEL_SCAN_LONG_PRESS_FUC();   //�˳�ɨ��ģʽ
	
void CHANNEL_SCAN_PPT_DN_FUC();				//ɨ��ģʽ�еķ���	
void CHANNEL_SCAN_PPT_UP_FUC();				//ɨ��ģʽ�е�ֹͣ����

	

	
/*---------------------------------------------------------------------------��������------------------------*/	

void CHANNEL_SWITCH_TUTTONTONE_FUC(); //�л�������



void CHANNEL_LOCK_FUC();              //����
void CHANNEL_DELOCK_FUC();						//�������
void CHANNEL_COUNTRY_PPT_DN_FUC();
void CHANNEL_LOCK_OTHERKEY_FUC();
#endif