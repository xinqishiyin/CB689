#include "system.h"
#include "lcdset.h"

/***************************************修改记录*****************************************************
Function List：LCD对应显示
Change Log:
	



****************************************************************************************************/


//                          0    1    2    3    4    5    6    7    8    9     
code const u8 Num_Code[10]={0xaf,0x06,0x6d,0x4f,0xc6,0xcb,0xeb,0x0e,0xef,0xcf};

	
code const u8 country_ecode[27][2]=
{
	{0xe9,0xa7},//EU
	{0xa9,0xe9},//CE
	{0xa7,0xe0},//UK
	{0xec,0xa1},//PL
	{0x06,0x63},//IO
	{0x06,0x6d},//I2		
	{0x67,0xe9},//DE
	{0x06,0x62},//IN
	
	{0x60,0xee},//RA
	{0x60,0xe3},//RB
	{0x60,0xa9},//RC
	{0x60,0x67},//RD
	{0x60,0xe9},//RE
	{0x60,0xe8},//RF
	{0x60,0xcf},//RG
	{0x60,0xe6},//RH
	{0x60,0x06},//RI
	{0x60,0xa1},//RL

	
	{0xe6,0xee},//HA
	{0xe6,0xe3},//HB
	{0xe6,0xa9},//HC
	{0xe6,0x67},//HD
	{0xe6,0xe9},//HE
	{0xe6,0xe8},//HF
	{0xe6,0xcf},//HG
	{0xe6,0xe6},//HH
	{0xe6,0x06},//HI

};
code const u8 lock_ecode[2]={0xae,0xa9};
code const u8 power_ecode[2][2]={{0xa1,0x63},{0xe6,0x06}};
code const u8 buttontone_ecode[2][2]={{0xe3,0xaf},{0xe3,0xe8}};



void LCD_FM()
{
	xLCDDATA1|=0x01;
	xLCDDATA1 &= ~0x02;
}
void LCD_AM()
{
	xLCDDATA1|=0x02;
	xLCDDATA1 &= ~0x01;
}
void LCD_ASQ(u8 i)
{
	if(i)xLCDDATA1|=0x04;
	else xLCDDATA1&=~0x04;
}
void LCD_VOX(u8 i)
{
	if(i)xLCDDATA1|=0x08;
	else xLCDDATA1&=~0x08;
}
void LCD_UK()
{
	xLCDDATA2&=~0x07;
	xLCDDATA2|=0x01;

}
void LCD_EU()
{
	xLCDDATA2&=~0x07;
	xLCDDATA2|=0x02;
}
void LCD_DE()
{
	xLCDDATA2&=~0x07;
	xLCDDATA2|=0x04;
}
void LCD_OtherContry()
{
	xLCDDATA2 &= ~0x07;	
}

void LCD_PTY(u8 i)
{
	if(i)xLCDDATA2|=0x08;
	else xLCDDATA2&=~0x08;
}
void LCD_TX(u8 i)
{
	if(i)xLCDDATA3|=0x01;
	else xLCDDATA3&=~0x01;
}
void LCD_M(u8 i)
{
	if(i)xLCDDATA3|=0x02;
	else xLCDDATA3&=~0x02;
}
void LCD_SC(u8 i)
{
	if(i)xLCDDATA3|=0x04;
	else xLCDDATA3&=~0x04;
}
void LCD_WL(u8 i)
{
	if(i)xLCDDATA3|=0x08;
	else xLCDDATA3&=~0x08;
}
void LCD_RX(u8 i)
{
	if(i)xLCDDATA4|=0x01;
	else xLCDDATA4&=~0x01;
}
void LCD_R(u8 i)
{
	if(i)xLCDDATA4|=0x02;
	else xLCDDATA4&=~0x02;
}
void LCD_H(u8 i)
{
	if(i)xLCDDATA4|=0x04;
	else xLCDDATA4&=~0x04;
}
//void LCD_H(u8 i)
//{
//	if(i)xLCDDATA4|=0x04;
//	else xLCDDATA4&=~0x04;
//}
void LCD_NL(u8 i)
{
	if(i)xLCDDATA4|=0x08;
	else xLCDDATA4&=~0x08;
}
void LCD_NUM1(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(Num_Code[i]>>4);
	xLCDDATA6|=(Num_Code[i]&0x0f);	
}

void LCD_NUM2(u8 i)
{
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(Num_Code[i]>>4);
	xLCDDATA8|=(Num_Code[i]&0x0f);
}

void LCD_STRENGTH(u8 i)
{
	switch(i)
	{
		case 0:
			xLCDDATA0&=0xf0;
			xLCDDATA5&=0xfe;
			xLCDDATA7&=0xfe;
			break;
		case 1:
			xLCDDATA0&=0xf0;
		  xLCDDATA0|=0x01;
			xLCDDATA5&=0xfe;
			xLCDDATA7&=0xfe;
			break;
		case 2:
			xLCDDATA0&=0xf0;
			xLCDDATA0|=0x03;
			xLCDDATA5&=0xfe;
			xLCDDATA7&=0xfe;
			break;
		case 3:
			xLCDDATA0&=0xf0;
			xLCDDATA0|=0x07;
			xLCDDATA5&=0xfe;
			xLCDDATA7&=0xfe;
			break;
		case 4:			
			xLCDDATA0|=0x0f;
			xLCDDATA5&=0xfe;
			xLCDDATA7&=0xfe;
			break;
		case 5:
			xLCDDATA0|=0x0f;		  
			xLCDDATA5|=0x01;
		  xLCDDATA7&=0xfe;			
			break;
		case 6:
			xLCDDATA0|=0x0f;		  
			xLCDDATA5|=0x01;
		  xLCDDATA7|=0x01;	
			break;
	}
}

void LCD_BUTTONTONE(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA5|=0x0e;
	xLCDDATA6|=0x03;
	if(i==1)
	{		
		xLCDDATA7|=0x06;
		xLCDDATA8|=0x03;	
	}
	else
	{		
		xLCDDATA7|=0x0e;
		xLCDDATA8|=0x08;
	}
}

void LCD_LOCK(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	if(i==1)
	{
		xLCDDATA5|=0x0a;
		xLCDDATA6|=0x01;
		xLCDDATA7|=0x0a;
		xLCDDATA8|=0x09;	
	}
	else
	{
		xLCDDATA5|=0x0a;
		xLCDDATA6|=0x0f;
		xLCDDATA7|=0x0e;
		xLCDDATA8|=0x08;	
	}
}
void LCD_NUM_CLEAR()
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
}

void LCD_COUNTRY(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(country_ecode[i][0]>>4);
	xLCDDATA6|=(country_ecode[i][0]&0x0f);
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(country_ecode[i][1]>>4);
	xLCDDATA8|=(country_ecode[i][1]&0x0f);	
}
void LCD_TABLE(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(0x0e);
	xLCDDATA6|=(0x01);
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(Num_Code[i]>>4);
	xLCDDATA8|=(Num_Code[i]&0x0f);	
	
}
void LCD_POWER(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(power_ecode[i-1][0]>>4);
	xLCDDATA6|=(power_ecode[i-1][0]&0x0f);
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(power_ecode[i-1][1]>>4);
	xLCDDATA8|=(power_ecode[i-1][1]&0x0f);
}
void LCD_RESET()
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(0x06);
	xLCDDATA6|=(0x00);
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(0x0e);
	xLCDDATA8|=(0x01);
}
void LCD_COLOR(u8 i)
{
	xLCDDATA5&=0xf1;
	xLCDDATA6&=0xf0;
	xLCDDATA5|=(0x0a);
	xLCDDATA6|=(0x09);
	xLCDDATA7&=0xf1;
	xLCDDATA8&=0xf0;
	xLCDDATA7|=(Num_Code[i]>>4);
	xLCDDATA8|=(Num_Code[i]&0x0f);
}



void LCD_CLEAR()
{
	xLCDDATA0=0x00;
	xLCDDATA1=0x00;
	xLCDDATA2=0x00;
	xLCDDATA3=0x00;
	xLCDDATA4=0x00;
	xLCDDATA5=0x00;
	xLCDDATA6=0x00;
	xLCDDATA7=0x00;
	xLCDDATA8=0x00;
}
void LCD_ALL()
{
	xLCDDATA0=0x0f;
	xLCDDATA1=0x0f;
	xLCDDATA2=0x0f;
	xLCDDATA3=0x0f;
	xLCDDATA4=0x0f;
	xLCDDATA5=0x0f;
	xLCDDATA6=0x0f;
	xLCDDATA7=0x0f;
	xLCDDATA8=0x0f;
}
