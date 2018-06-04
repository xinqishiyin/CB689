#include "system.h"
#include "at24c08.h"

/***************************************�޸ļ�¼*****************************************************
 Function List��
		1��eepromWriteByte      дһ�ֽڴ洢��
		2��eepromWritePage      ����д�洢��
		3��eepromReadByte       ��һ�ֽڴ洢��
		4��eepromReadSequential �������洢��
 
 Change Log:

****************************************************************************************************/

void initAt24c08()
{
	I2C_Init();
}

/*-------------------------------------------------------------------------
*������eepromWriteByte  ��洢����д��
*������page �洢��ҳ   addr �洢����ַ  value д���ֵ 
*����ֵ����
*-------------------------------------------------------------------------*/
void eepromWriteByte(u8 page,u8 addr,u8 value)
{	
	I2C_Start();	
	I2C_Send_Byte(page);
	I2C_Wait_Ack();	
	I2C_Send_Byte(addr);
	I2C_Wait_Ack();
	I2C_Send_Byte(value);
	I2C_Wait_Ack();
	I2C_Stop();
	delayms(5);
	//I2C_Start();
	//I2C_Stop();
	
}

void eepromWritePage(u8 *p_value,u8 page, u8 addr, u8 len)
{
	u8 i;
	I2C_Start();
	I2C_Send_Byte(page);
	I2C_Wait_Ack();	
	I2C_Send_Byte(addr);
	I2C_Wait_Ack();	
	for(i=0; i<len; i++)
	{
		I2C_Send_Byte(*(p_value++));
		I2C_Wait_Ack();
	}
	I2C_Stop();
	delayms(5);
}


/*-------------------------------------------------------------------------
*������eepromReadByte  ���洢��
*��������  
*����ֵ��������ֵ
*-------------------------------------------------------------------------*/
u8 eepromReadByte(u8 page,u8 addr)
{
	u8 value;	
	I2C_Start();
	I2C_Send_Byte(page);
	I2C_Wait_Ack();	
	I2C_Send_Byte(addr);
	I2C_Wait_Ack();	
	I2C_Start();
	I2C_Send_Byte(page | 0x01);
	I2C_Wait_Ack();	
	value = I2C_Read_Byte();	
	I2C_NAck();
	I2C_Stop();
	return value;
}
void eepromReadSequential(u8 *p_data,u8 page, u8 addr, u8 length)
{
	u16 i;
	I2C_Start();
	I2C_Send_Byte(page);
	I2C_Wait_Ack();	
	I2C_Send_Byte(addr);
	I2C_Wait_Ack();	
	I2C_Start();
	I2C_Send_Byte(page | 0x01);
	I2C_Wait_Ack();
	for(i=0; i<length-1; i++)	 //���һλҪ���������Ϊ�������һλ����Ӧ���ź�
	{
		*(p_data + i) = I2C_Read_Byte();
		I2C_Ack();
	}
	*(p_data + i) = I2C_Read_Byte();
	I2C_NAck();
	I2C_Stop();
}
