#include "system.h"
#include "uart.h"
#include "BK4802.h"
#include "at24c08.h"

/***************************************修改记录*****************************************************
 Function List：
		1、uart0SendData    发送1字节数据
		2、getVoltage       读取电压值
		3、returnData       回复存储器数据
		4、reciveData       保存接收数据
		5、UART_EVENT       串口中断外部处理程序
		6、Uart0            串口中断处理程序
 Change Log:

****************************************************************************************************/

xdata const u8 connSendCode[8]={0x02,0x50,0x52,0x4f,0x47,0x52,0x41,0x4d};  //第一次握手接收
xdata const u8 connReciveCode=0x06;
xdata const u8 connReSureCode=0x06;
xdata const u8 connSendSure=0x02;
xdata const u8 connReciveSure[8]={0x53,0x4d,0x50,0x35,0x35,0x38,0xff,0xff};
xdata const u8 readSendCode=0x52;
xdata const u8 writeSendCode=0x57;

xdata u8 uartPage=0;
xdata u8 uartAddr=0;
u8 isConn=0;
u8 eeprombuf[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void uart0SendByte(unsigned char dat)
{
	SBUF0 = dat;	
	while(TI == 0);
	TI = 0;
}
/*-------------------------------------------------------------------------
*函数：uart0SendData  发送对应长度数组
*参数：cTxLength 长度    
*返回值：无
*-------------------------------------------------------------------------*/
void uart0SendData(unsigned char *p,u8 length)
{	
	ES = 0;
	while(length--)
	{
		uart0SendByte(*p);		
		p++;
	}
	ES = 1;
}

void getVoltage()
{
	u16 val;
	mVoltageSend.ASQ_Vol=Get_AD(ADC_ASQ);
	mVoltageSend.KEY1_Vol=Get_AD(ADC_Key1);
	mVoltageSend.VOX_Vol=Get_AD(ADC_VOX);
	mVoltageSend.RSSI_Vol=Get_AD(ADC_RSSI);
	mVoltageSend.AGCA_Vol=Get_AD(ADC_AGCA);
	val= BK4802_RssiAndSnr();
	mVoltageSend.BK4802_Snr= (val&0x3f00)>>8;
	mVoltageSend.BK4802_Rssi=(val&0x007f);
	mVoltageSend.BK4802_ASQ=(val&0x00ff);
}



void sendCommand()
{
	u8 i;
	getVoltage();	
	mCbParam.UartTxBuf[1]=14;
	mCbParam.UartTxBuf[2]=mVoltageSend.ASQ_Vol/256;
	mCbParam.UartTxBuf[3]=mVoltageSend.ASQ_Vol%256;
	mCbParam.UartTxBuf[4]=mVoltageSend.KEY1_Vol/256;
	mCbParam.UartTxBuf[5]=mVoltageSend.KEY1_Vol%256;
	mCbParam.UartTxBuf[6]=mVoltageSend.VOX_Vol/256;
	mCbParam.UartTxBuf[7]=mVoltageSend.VOX_Vol%256;
	mCbParam.UartTxBuf[8]=mVoltageSend.RSSI_Vol/256;
	mCbParam.UartTxBuf[9]=mVoltageSend.RSSI_Vol%256;
	mCbParam.UartTxBuf[10]=mVoltageSend.AGCA_Vol/256;
	mCbParam.UartTxBuf[11]=mVoltageSend.AGCA_Vol%256;
	mCbParam.UartTxBuf[12]=mVoltageSend.BK4802_Snr;
	mCbParam.UartTxBuf[13]=mVoltageSend.BK4802_Rssi;
	mCbParam.UartTxBuf[14]=mVoltageSend.BK4802_ASQ;
	mCbParam.UartTxBuf[15]=0;
	for(i=2;i<15;i++)
	{
		mCbParam.UartTxBuf[15] ^=  mCbParam.UartTxBuf[i];
	}
	mCbParam.UartTxBuf[15]&=0x7f;
	uart0SendData(mCbParam.UartTxBuf,16);
}


void returnData()
{	
	u8 i;
	mCbParam.UartTxBuf[0]=writeSendCode;
	mCbParam.UartTxBuf[1]=uartPage;
	mCbParam.UartTxBuf[2]=uartAddr;
	mCbParam.UartTxBuf[3]=mReceivePackage.AdressLenth;
	eepromReadSequential(eeprombuf,uartPage,uartAddr,mReceivePackage.AdressLenth);
	for(i=0;i<8;i++)
	{
		mCbParam.UartTxBuf[4+i]=eeprombuf[i];
	}
	uart0SendData(mCbParam.UartTxBuf,mReceivePackage.AdressLenth+4);
}
void reciveData()
{
	eepromWritePage(&mReceivePackage.RecvBuf,uartPage,uartAddr,mReceivePackage.AdressLenth);
	uart0SendByte(connReciveCode);
}

void UART_EVENT(void)
{
	eepromReadSequential(eeprombuf,0xA0,0x00,8);
	if(mReceivePackage.isSendData==1)
	{
		returnData();
		mReceivePackage.isSendData=0;
	}
	if(mReceivePackage.isReciveData==1)
	{
		reciveData();
		mReceivePackage.isReciveData=0;
	}
	if(mUartCmd!=0)
	{
		sendCommand();
		mUartCmd=0;
	}
	//sendCommand();
	//getVoltage();
}

/*-------------------------------------------------------------------------
*函数：analyseCMD  发送参数
*参数：要发送的参数    
*返回值：无
*-------------------------------------------------------------------------*/
void analyseCMD(void)
{
	mUartCmd = mReceivePackage.RecvBuf[1];          //1为参数名	
}

void Uart0(void) interrupt 4
{
	uchar dat=0;
	uchar i=0;	
	if(RI==1)      //发送完毕
	{
		RI=0;
		TI = 0;
		TR1=1;              //开启定时器，用于超时检测
		mTimer.uartTimeCount=0;
		
		dat=SBUF0;
		switch(mReceivePackage.RecvStatus)
		{
			case UART0_IDLE:                       //接收8位第一次握手
				if(isConn==0&&dat==0x02)
				{
					isConn=1;
					mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					mReceivePackage.RecvCount++;
				}
				else if(isConn==1)
				{
					mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					mReceivePackage.RecvCount++;
					if(mReceivePackage.RecvCount==8)
					{
						for(i=0;i<8;i++)
						{
							if(mReceivePackage.RecvBuf[i]!=connSendCode[i])
							{
								mReceivePackage.RecvCount=0;
								return;
							}
						}
						uart0SendByte(connReciveCode);
						mReceivePackage.RecvStatus=UART0_SYN;
						mReceivePackage.RecvCount=0;
					}	
				}	
				
				break;
			case UART0_SYN:                    //接收0X02 回复确认 第二次握手
				if(dat==connSendSure)
				{		
				
					uart0SendData(connReciveSure,8);
				}
				else if(dat==connReSureCode)                          //进入数据传送  第三次握手
				{
					mReceivePackage.RecvStatus=UART0_HEAD;
					mReceivePackage.RecvCount=0;
					
					uart0SendByte(connReciveCode);
				}
				break;
			case UART0_HEAD:
				switch(mReceivePackage.RecvCount)
				{
					case 0:
						if(dat==readSendCode)
						{
							mReceivePackage.WriteOrRead=Read;	
							mReceivePackage.RecvCount++;
						}
						else if(dat==writeSendCode)
						{
							mReceivePackage.WriteOrRead=Write;	
							mReceivePackage.RecvCount=1;
						}
						else
						{
							mReceivePackage.RecvStatus=UART0_IDLE;
							mReceivePackage.RecvCount=0;
						}
						
						if(dat==MAGIC)
						{
							mReceivePackage.RecvStatus = MSG_HEADER;
						}
						break;
					case 1:
						uartPage=dat;
						mReceivePackage.RecvCount=2;
						break;
					case 2:
						uartAddr=dat;
						mReceivePackage.RecvCount=3;
						break;
					case 3:				
						mReceivePackage.AdressLenth=dat;					
						if(mReceivePackage.WriteOrRead==Write)
						{
							mReceivePackage.RecvStatus=UART0_DATA;
							mReceivePackage.RecvCount=0;
						}
						else if(mReceivePackage.WriteOrRead==Read)
						{
							mReceivePackage.isSendData=1;
							mReceivePackage.RecvCount=0;
						}
						break;
				}
				break;
			case UART0_DATA:
				if(mReceivePackage.RecvCount<mReceivePackage.AdressLenth)
				{
					mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					mReceivePackage.RecvCount++;		
					if(mReceivePackage.RecvCount==8)
					{
						mReceivePackage.isReciveData=1;
						mReceivePackage.RecvStatus=UART0_HEAD;
						mReceivePackage.RecvCount=0;
					}
				}
				else
				{					
					mReceivePackage.RecvStatus=UART0_IDLE;
					mReceivePackage.RecvCount=0;
				}
				break;
			case MSG_HEADER:                                         // 0 位为数据头
					mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					if(mReceivePackage.RecvCount == 2)
					{
						if(mReceivePackage.RecvBuf[2] == 0)	//数据长度
						{
							analyseCMD();
							mReceivePackage.RecvCount = 0;
						}
						else 
						{
							mReceivePackage.RecvStatus = MSG_DATA;
						}
					}
					mReceivePackage.RecvCount++;
					break;
				case MSG_DATA:
					mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					if(mReceivePackage.RecvCount==4)
					{
						mReceivePackage.RecvBuf[mReceivePackage.RecvCount]=dat;
					}
					if((mReceivePackage.RecvCount -2)>=mReceivePackage.RecvBuf[2]) //2为数据长度
					{
						dat=0;
						for(i=3;i<2+(mReceivePackage.RecvBuf[2]); i++)
						{
							dat^=mReceivePackage.RecvBuf[i];
						}
						dat &=0x7f;
						if(mReceivePackage.RecvBuf[i]==dat)
						{
							analyseCMD();
							mReceivePackage.RecvCount=0;
						}
					}
				
					mReceivePackage.RecvCount++;
					break;		
			default:break;
		}
	}
}
