#define _UART_H
#ifdef _UART_H



#define MAGIC 0xFE

#define CMD_ASQ  30
#define CMD_KEY1 31
#define CMD_VOX  32
#define CMD_RSSI 33
#define CMD_AGCA 34
#define CMD_ACK  35



enum
{
	MSG_SYNC=5,	
	MSG_HEADER=6,	
	MSG_DATA=7	
};


	
/*-------------------------------------------------------------------------
*������sendCommand  �����ѹֵ
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void sendCommand();
/*-------------------------------------------------------------------------
*������UART_EVENT  �����ж��ⲿ�������
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void UART_EVENT(void);
#endif