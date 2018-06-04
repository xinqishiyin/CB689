#include "system.h"
#include "at24c08.h"

/***************************************修改记录*****************************************************
 Function List：
		1、eepromWriteByte      写一字节存储器
		2、eepromWritePage      连续写存储器
		3、eepromReadByte       读一字节存储器
		4、eepromReadSequential 连续读存储器
 
 Change Log:

****************************************************************************************************/

void initAt24c08()
{
	I2C_Init();
}

/*-------------------------------------------------------------------------
*函数：eepromWriteByte  向存储器是写字
*参数：page 存储器页   addr 存储器地址  value 写入的值 
*返回值：无
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
*函数：eepromReadByte  读存储器
*参数：无  
*返回值：所读的值
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
	for(i=0; i<length-1; i++)	 //最后一位要另外读，因为读完最后一位发非应答信号
	{
		*(p_data + i) = I2C_Read_Byte();
		I2C_Ack();
	}
	*(p_data + i) = I2C_Read_Byte();
	I2C_NAck();
	I2C_Stop();
}
