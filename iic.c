#include "system.h"
#include "iic.h"

extern u8 sisessce;

void I2C_Init(void)
{
	I2C_SDA_H;
	delayus(1);
	I2C_SCL_H;
}

//产生起始信号
void I2C_Start(void)
{	
	I2C_SDA_H;
	I2C_SCL_H;
	delayus(1);
	I2C_SDA_L;
	delayus(1);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{   
   //I2C_SCL_L;
   I2C_SDA_L;
	 delayus(1);
   I2C_SCL_H;
   delayus(1);
   I2C_SDA_H;
   delayus(1);
}


//主机产生应答信号ACK
void I2C_Ack()
{	
	 I2C_SDA_L;
   delayus(1);
   I2C_SCL_H;
   delayus(2);
   I2C_SCL_L;
}
void I2C_NAck()
{
	 I2C_SDA_H;
	 delayus(1);
   I2C_SCL_H;
   delayus(2);
   I2C_SCL_L;
} 

//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;
	I2C_SCL_L;
	I2C_SDA_IN;
	I2C_SCL_H;
	delayus(1);	
	while(I2C_SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			sisessce=0;
			I2C_Stop();
			I2C_SDA_OUT;
			return 1;
		}	 
	}
	I2C_SCL_L;
	I2C_SDA_OUT;
	delayus(2);
	return 0;
}


//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delayus(1); //发送数据
		I2C_SCL_L;
		delayus(1);
	}
}


//I2C 读取一个字节

u8 I2C_Read_Byte()
{
   u8 i,receive;
	 I2C_SCL_L;	
	delayus(2);
   I2C_SDA_IN;
	 delayus(2);
   for(i=0;i<8;i++)
   {
			receive<<=1;
		  if(I2C_SDA==1) receive|=0x01;
			I2C_SCL_H;	
			delayus(2);
			I2C_SCL_L;			
			delayus(1);	
   }
	I2C_SDA_OUT;
	return receive;
}














