#include "system.h"
#include "iic.h"

extern u8 sisessce;

void I2C_Init(void)
{
	I2C_SDA_H;
	delayus(1);
	I2C_SCL_H;
}

//������ʼ�ź�
void I2C_Start(void)
{	
	I2C_SDA_H;
	I2C_SCL_H;
	delayus(1);
	I2C_SDA_L;
	delayus(1);
	I2C_SCL_L;
}

//����ֹͣ�ź�
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


//��������Ӧ���ź�ACK
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

//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�
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


//I2C ����һ���ֽ�
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;
	I2C_SCL_L;//����ʱ�ӿ�ʼ���ݴ���

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delayus(1); //��������
		I2C_SCL_L;
		delayus(1);
	}
}


//I2C ��ȡһ���ֽ�

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














