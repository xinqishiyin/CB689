#include "system.h"
#include "BK4802.h"
#include "vco.h"
#include "lcdset.h"
#include "handler.h"

/***************************************�޸ļ�¼*****************************************************
Function List��
1��BK4802_Init   		4802������ʹ��
2��BK4802_RXtoTX		4802����ת����
3��BK4802_TXtoRX		4802����ת����
4��BK4802_Change_Freq   4802�޸�Ƶ��
5��BK4802_SLEEP			4802��������
6��BK4802_RssiAndSnr	��ȡ4802����ǿ��
7��BK4802_ASQ			��ȡ4802����ǿ��

Change Log:
 [2018/05/23 16:53 ������] BK4802_TXtoRX AMģʽʱ ����ʱ 4802���������Ƶ��  ����ʱ 4802����� ������Ƶ��+10.7M��

****************************************************************************************************/


u8 isSecess = 1;

u8 ack;

/*-------------------------------------------------------------------------
*������BK_Start  �洢������
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void BK_Start(void)
{
	SET_BK4802_SDA;
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;
	delayus(1);
	CLS_BK4802_SCK;
}
/*-------------------------------------------------------------------------
*������BK_Stop  �洢��ֹͣʹ��
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
void BK_Stop(void)
{
	CLS_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
}
/*-------------------------------------------------------------------------
*������BK_Read_Ack  ��1λ�洢��
*��������
*����ֵ����
*-------------------------------------------------------------------------*/
u8 BK_Read_Ack(void)
{
	unsigned char tempTime = 0;
	CLS_BK4802_SCK;
	SET_BK4802_SDA_IN;
	SET_BK4802_SCK;
	delayus(1);
	delayus(1);
	while (BK4802_SDA_IN);
	CLS_BK4802_SCK;
	SET_BK4802_SDA_OUT;
	delayus(2);
	return 0;
}
/*-------------------------------------------------------------------------
*������at24c08TxAck  д1λ�洢��
*������ACKҪд����
*����ֵ����
*-------------------------------------------------------------------------*/
void BK_ACK()
{
	//SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SCK;
	delayus(1);
}
void BK_NoACK()
{
	//SET_BK4802_SCK;
	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SCK;
	delayus(1);
}
/*-------------------------------------------------------------------------
*������at24c08I2cWriteByte  �洢��д����
*������value   Ҫд����
*����ֵ����
*-------------------------------------------------------------------------*/
void BK_Write_Byte(u8 value)
{
	unsigned char i;
	CLS_BK4802_SCK;
	for (i = 0; i<8; i++)
	{
		if (value & 0x80)
		{
			SET_BK4802_SDA;
		}
		else
		{
			CLS_BK4802_SDA;
		}
		delayus(2);
		SET_BK4802_SCK;
		delayus(2);
		CLS_BK4802_SCK;

		value <<= 1;
	}
}
/*-------------------------------------------------------------------------
*������at24c08I2cReadByte  �洢����һ��
*��������
*����ֵ����������
*-------------------------------------------------------------------------*/
u8 BK_Read_Byte(void)
{
	u8 i, temp = 0;
	CLS_BK4802_SCK;
	SET_BK4802_SDA_IN;
	delayus(2);
	for (i = 0; i<8; i++)
	{
		temp <<= 1;
		if (BK4802_SDA_IN)
		{
			temp |= 0x01;
		}
		SET_BK4802_SCK;
		delayus(2);
		CLS_BK4802_SCK;
		delayus(2);
	}
	SET_BK4802_SDA_OUT;
	return temp;
}
/*-------------------------------------------------------------------------
*������eepromWriteByte  ��洢����д��
*������page �洢��ҳ   addr �洢����ַ  value д���ֵ
*����ֵ����
*-------------------------------------------------------------------------*/
void BK_Write_Reg(u8 addr, u16 value)
{
	BK_Start();
	BK_Write_Byte(0x90);
	BK_Read_Ack();
	BK_Write_Byte(addr);
	BK_Read_Ack();
	BK_Write_Byte(value >> 8);
	BK_Read_Ack();
	BK_Write_Byte(value & 0x00ff);
	BK_Read_Ack();
	BK_Stop();
	delayms(5);
}

/*-------------------------------------------------------------------------
*������eepromReadByte  ���洢��
*��������
*����ֵ��������ֵ
*-------------------------------------------------------------------------*/
u16 BK_Read_Reg(u8 addr)
{
	u16 value;
	u8 val1, val2;
	BK_Start();
	BK_Write_Byte(0x90);
	BK_Read_Ack();
	BK_Write_Byte(addr);
	BK_Read_Ack();
	BK_Start();
	BK_Write_Byte(0x91);
	BK_Read_Ack();
	val1 = BK_Read_Byte();
	BK_ACK();
	val2 = BK_Read_Byte();
	BK_NoACK();
	BK_Stop();
	value = val1 * 256 + val2;
	return value;
}
void BK4802_IOInit()
{
	CLS_BK4802_SCK;
	delayus(1);
	CLS_BK4802_SDA;

	delayus(1);
	SET_BK4802_SDA;
	delayus(1);
	SET_BK4802_SCK;
}
/*-------------------------------------------------------------------------
*������Init_RX  ��ʹ�������
*��������
*����ֵ��������ֵ
*-------------------------------------------------------------------------*/
void Init_RX()
{

	//BK_Write_Reg(23,0x18ff);
	//delayms(50);
	BK_Write_Reg(4, 0x0b00);       //B15�� 1-�ر�Ƶ���ۺ����� 0-��Ƶ���ۺ���      RX 0x0c00  TX:0x7200
								   //B14�� 1-�رս���ǰ�ˣ� 0-�򿪽���ǰ��
								   //B13�� 1-�رս�����Ƶ�� 0-�򿪽�����Ƶ
								   //B12�� 1-�رս�����Ƶ�� 0-�򿪽�����Ƶ
								   //B11�� 1-�رշ���ǰ�ˣ� 0-�򿪷���ǰ��
								   //B10�� 1-�رշ���ƴ���� 0-�򿪷�����Ƶ
								   //B09�� 1-�رղ���ADC�� 0-�򿪲���ADC

	BK_Write_Reg(5, 0x0c04);       //���໷������ã�������Ĭ��ֵ
	BK_Write_Reg(6, 0xf140);       //���໷������ã�������Ĭ��ֵ
	BK_Write_Reg(7, 0xed00);       //B10���������໷У׼����������Ч
	BK_Write_Reg(8, 0x3fe0);				//���໷������ã�������Ĭ��ֵ
	BK_Write_Reg(9, 0xe0e0);
	BK_Write_Reg(10, 0x8543);			//B15~B10��΢���������������Ƶ��                RX:0x00fc  TX:0x00cc
										//B07~B06�����ò���ADC����ѹ�������ѹ
										//B05�� 1-��ƵADCʱ����Ч�� 0-��ƵADCʱ��ʧЧ
										//B04�� 1-����ADCʱ����Ч�� 0-����ADCʱ��ʧЧ
										//B03~B02��΢�������������������
										//B01~B00������������ѹ�������ѹ

	BK_Write_Reg(11, 0xf700);      //B15~B13������������ƵADC�Ĳο���ѹ
								   //B12�����ӷ�����ƵVGA���棬ԼΪ3dB
								   //B06��������˷�������衣 0-16k Ohm�� 1-8k Ohm
								   //B05��������˷�VGA��������Ĵ�С�� 0-52k Ohm��
								   //1-26k Ohm
								   //B04~B03��������Ƶ����P�ˡ� N�˷ǽ���ʱ�䡣 0-2nS��
								   //1-3nS�� 2-4nS�� 3-5nS

	BK_Write_Reg(12, 0xa066);      //B15~B08�� ���ý�����Ƶģ��ת�����ο���ѹ
								   //B07~B05�� ���ý�����Ƶ���棬 3dB/���� 0-0dB�� 7-21dB
								   //B04�����ý�����Ƶ�˲������� 0-200kHz�� 1-1MHz
								   //B03�����ý�����ƵVGA����ƫ�á� 0-2uA�� 1-10uA
								   //B02~B00�����ý�����Ƶ��ѹ�������ѹ

	BK_Write_Reg(13, 0xffff);      //B15���շ�ģʽ���Ʒ�ʽ�� 0-�Ĵ������ƣ� 1-DSP����
								   //B14���շ�ģʽѡ�� 0-����ģʽ�� 1-����ģʽ
								   //B13�����õ������Ŵ������档 0-�����棻 1-������
								   //B12~B10�������������Ŵ���ƫ�õ���
								   //B09~B07��������Ƶ��ֱ��ƫ��
								   //B05�� ASKģʽʹ�ܡ� 0-ʧЧ�� 1-ʹ��
								   //B04~B03�����ý���ǰ����ѹ�������ѹ
								   //B02~B00���������ʷŴ����������

	BK_Write_Reg(14, 0xffe0);      //B15~B14�� ������Ƶ�����˲������档
								   //0-0dB�� 1-1dB�� 2-3.5dB�� 3-6dB
								   //B13~B09�������������ơ�
								   //B08~B05�������ź���������

	BK_Write_Reg(15, 0x0210);      //B12~B00�������޷�����
	BK_Write_Reg(16, 0x9e3c);      //B15��������ƵAGCʹ�ܡ� 0-��Ч�� 1-ʹ��
	BK_Write_Reg(17, 0x1f00);      //TX Audio AGC����
	BK_Write_Reg(18, 0xd1d1);      //B15~B04�� ����Ƶƫ����
	BK_Write_Reg(19, 0x200f);      //B15~B14�� CIC�˲������档 0-0dB�� 1-1dB��
								   //2-3.5dB�� 3-6dB
								   //B13~B12�� FM��������������
								   //B03~B00����������

	BK_Write_Reg(20, 0x01ff);      //B15���ر��Զ�Ƶ��У����AFC���� 0-�򿪣� 1-�ر�
	BK_Write_Reg(21, 0xE000);      //AFC��ֵ����
	BK_Write_Reg(22, 0x0c00);      //B15�� IQ���±ߴ�ѡ�� 0-ѡ���ϱߴ��� 1-ѡ���±ߴ�
								   //B14�� AFC����ѡ�� 0-��Ӧ�ϱߴ��� 1-��Ӧ�±ߴ�
								   //B07~B00�����þ���Ľ����ź�ǿ�ȣ�RSSI�� ��ֵ
	if (mCbParam.Modu == FM)
	{
		BK_Write_Reg(2, 0xc000);
	}
	else
	{
		BK_Write_Reg(2, 0xa000);
	}

	BK_Write_Reg(1, mVcoParam.l_Fre_Rx); //д��Ƶ��
	BK_Write_Reg(0, mVcoParam.h_Fre_Rx);
	//CLS_AT_MUTE;       //

}
void BK4802_RX()
{
	Init_RX();
}


void BK4802_TX()
{
	BK4802_TRX = 1;
	delayms(50);
	BK_Write_Reg(4, 0x7c00);       //B15�� 1-�ر�Ƶ���ۺ����� 0-��Ƶ���ۺ���      RX 0x0c00  TX:0x7200
								   //B14�� 1-�رս���ǰ�ˣ� 0-�򿪽���ǰ��
								   //B13�� 1-�رս�����Ƶ�� 0-�򿪽�����Ƶ
								   //B12�� 1-�رս�����Ƶ�� 0-�򿪽�����Ƶ
								   //B11�� 1-�رշ���ǰ�ˣ� 0-�򿪷���ǰ��
								   //B10�� 1-�رշ���ƴ���� 0-�򿪷�����Ƶ
								   //B09�� 1-�رղ���ADC�� 0-�򿪲���ADC

	
	if (mCbParam.Modu == AM && mMenu.isTx == 0)
	{
		BK_Write_Reg(2, 0xa000);
	}
	else
	{		
		BK_Write_Reg(2, 0xc000);			
	}
	BK_Write_Reg(1, mVcoParam.l_Fre_Tx); //д��Ƶ��
	BK_Write_Reg(0, mVcoParam.h_Fre_Tx);
}


/*-------------------------------------------------------------------------
*������BK_4802_Init  4802��ʹ��
*������ ��
*����ֵ����
*-------------------------------------------------------------------------*/
void BK4802_Init()
{
	BK4802_IOInit();	
	BK4802_TRX = 0;
	BK4802_TRX = 1;
	BK4802_TRX = 0;
	delayms(50);
	Init_RX();
	LED_RED = 0;
	LED_GREEN = 1;
	LCD_RX(1);
}
void BK4802_RXtoTX()
{	
	CLS_AM_EN;
	CLS_FM_EN;
	SET_AT_MUTE;
	BK4802_TX();
	CLS_MIC_MUTE;
	LED_GREEN = 0;
	LED_RED = 1;
}

void BK4802_TXtoRX()
{
	SetModu();
	if (mCbParam.Modu == AM)
	{			
		
		BK4802_TX();		
	}
	else
	{
		SET_MIC_MUTE;
		
		//CLS_AT_MUTE;      //----------

		BK4802_TRX = 0;
		delayms(50);
		BK4802_RX();		
	}
	//CLS_AT_MUTE;
	LED_RED = 0;
	LED_GREEN = 1;
}

void BK4802_SLEEP()
{
	
}

u16 BK4802_RssiAndSnr()
{
	u16 val;
	val = BK_Read_Reg(23);  //snr=val[13-8]   rssi=val[6-0];
	return val;
}
u16 BK4802_ASQ()
{
	return BK_Read_Reg(30);
}






