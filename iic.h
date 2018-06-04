#ifndef _iic_H
#define _iic_H


/*-----------------------------´æ´¢Æ÷¿ØÖÆ---------------------*/

#define I2C_SCL_H                (P17=1)
#define I2C_SCL_L                (P17=0)

#define I2C_SDA_H 								(xP4|=0x80)
#define I2C_SDA_L 								(xP4&=~0x80)


#define I2C_SDA			              ((xP4&0x80)==0? 0:1)
#define I2C_SDA_OUT				        {xP4MDH &= 0x3F; xP4MDH |= 0x80;}
#define I2C_SDA_IN       				  {xP4MDH &= 0x3F; xP4MDH |= 0x00;}

void I2C_Init(void);

void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack();
void I2C_NAck(void);
u8   I2C_Wait_Ack(void);
void I2C_Send_Byte(u8 txd);
u8   I2C_Read_Byte(void);



#endif