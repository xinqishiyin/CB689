#include "system.h"
#include "memory.h"
#include "at24c08.h"
#include "vco.h"

/***************************************修改记录***************************************************** 
 Function List：
		1、saveData        		 按地址保存数据到存储器
		2、loadData            按地址从存储器读取数据
		3、setDefaultParam     初使化参数数据
		4、saveAllParam        保存所有参数数据
		5、checkAllParam       检验加载的参数数据
		6、loadAllParam        加载数据
		7、initMemory          初使读取存储器功能参数		
 Change Log:


****************************************************************************************************/

u8 sisessce=1;

/*-------------------------------------------------------------------------
*函数：saveData  保存数据
*参数：addr 地址  数据  
*返回值：无
*-------------------------------------------------------------------------*/
void saveData(u16 addr, u8 dat)
{
	u8 page;
	page = addr/256;
	switch(page)
	{
		case 0:page = AT24C08_PAGE0;break;
		case 1:page = AT24C08_PAGE1;break;
		case 2:page = AT24C08_PAGE2;break;
		case 3:page = AT24C08_PAGE3;break;
	}
	EA = 0;
	eepromWriteByte(page,addr%256,dat);
	EA = 1;	
}

/*-------------------------------------------------------------------------
*函数：loadData  读取数据
*参数：addr 地址   
*返回值：数据
*-------------------------------------------------------------------------*/
unsigned char loadData(u16 addr)
{
	u8 dat,page;
	page = addr/256;
	switch(page)
	{
		case 0:page = AT24C08_PAGE0;break;
		case 1:page = AT24C08_PAGE1;break;
		case 2:page = AT24C08_PAGE2;break;
		case 3:page = AT24C08_PAGE3;break;
	}
	EA = 0;
	dat = eepromReadByte(page,addr%256);
	EA = 1;	
	return dat;	
}

void initFlag()
{	
	//mCbParam.UartTxBuf[0] = 0xFE;
	mVcoParam.NDIV_FRE=128;
	mSysParam.isMute=0;
	mSysParam.Rssi=0;
	mSysParam.SpkOpen=0;
	mSqParam.Scan=1;
	mSqParam.ScanHould=1;
	mSysParam.MinChannel = 1;
	mSqParam.HouldTime=0;	
	mReceivePackage.RecvStatus=UART0_IDLE;
	mReceivePackage.RecvCount=0;
	mReceivePackage.isSendData=0;
	mReceivePackage.isReciveData=0;
}

/*-------------------------------------------------------------------------
*函数：setDefaultParam  默认设置
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void setDefaultParam(void)
{	
	mCbParam.FreqCal=0;
	mCbParam.CountryTable = 2;
	mCbParam.Country = COUNTRY_EU;
	mCbParam.Band = 0;
	mCbParam.Channel = 9;
	mCbParam.Modu = FM;
	mCbParam.TxPower = POWER_LOW;
	mCbParam.VolLevel = 5;
	mCbParam.LastChannel=mCbParam.Channel ;
	mSqParam.IsAsq = 0;
	mSqParam.IsVox = 0;
	mSqParam.AsqLevel = 3;	
	mSqParam.Scan=0;
	mSqParam.ScanDir=0;
	mSqParam.ScanHould=1;	
	mCbParam.SpkerSwitch = 1;
	mCbParam.LcdColor = 7;
	mCbParam.ButtonToneSwitch = 1;	
}
/*-------------------------------------------------------------------------
*函数：saveAllParam  保存功能信息
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void saveAllParam(void)
{
	saveData(EEP_BASE,0xa5);
	saveData(EEP_COUNTRY_TB,mCbParam.CountryTable);
	saveData(EEP_COUNTRY,mCbParam.Country);				
	saveData(EEP_BAND,mCbParam.Band);		
	saveData(EEP_CHANNEL,mCbParam.Channel);		
	saveData(EEP_MODU,mCbParam.Modu);		
	saveData(EEP_POWER,mCbParam.TxPower);
	saveData(EEP_VOL,mCbParam.VolLevel);
	saveData(EEP_LAST_CH,mCbParam.LastChannel);	
	saveData(EEP_LCD_COLOR,mCbParam.LcdColor);		
	saveData(EEP_TONE_SW,mCbParam.ButtonToneSwitch);
	saveData(EEP_SPK_SW,mCbParam.SpkerSwitch);	
	saveData(EEP_IS_ASQ,mSqParam.IsAsq);
	saveData(EEP_IS_VOX,mSqParam.IsVox);
	saveData(EEP_ASQ_LEVEL,mSqParam.AsqLevel);
}
/*-------------------------------------------------------------------------
*函数：checkAllParam  验证加载信息
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void checkAllParam(void)
{	
	switch(mCbParam.Country)
	{
		case COUNTRY_EU: mSysParam.MaxChannel = 40;mCbParam.Band=0;break;
		case COUNTRY_CE: mSysParam.MaxChannel = 40;mCbParam.Band=0;break;
		case COUNTRY_UK: mSysParam.MaxChannel = 40;mCbParam.Band=0;break;
		case COUNTRY_PL: mSysParam.MaxChannel = 40;mCbParam.Band=0;break;
		case COUNTRY_I0: mSysParam.MaxChannel = 40;mCbParam.Band=0;break;		
		case COUNTRY_RU:
			if(mCbParam.Band>9) mCbParam.Band=0;
			mSysParam.MaxChannel = 40;
			break;		
		case COUNTRY_I2: mSysParam.MaxChannel = 34;mCbParam.Band=0;break;
		case COUNTRY_DE: mSysParam.MaxChannel = 80;mCbParam.Band=0;break;
		case COUNTRY_IN: mSysParam.MaxChannel = 27;mCbParam.Band=0;break;
		case COUNTRY_HX:
			if(mCbParam.Band>8) mCbParam.Band=0;
		  if(mCbParam.Band==8) mSysParam.MaxChannel = 20;
		  else	mSysParam.MaxChannel = 40;
		break;		
	}	
	if(mCbParam.CountryTable > 2)mCbParam.CountryTable = 1;	
	else if (mCbParam.CountryTable==0) mCbParam.CountryTable = 1;	
	if (((mCbParam.Country > 7)&&(mCbParam.Country!=COUNTRY_RU)&&(mCbParam.Country!=COUNTRY_HX)) || (mCbParam.Country < 0))mCbParam.Country = 0;
	
	
	mSysParam.ActivityChannel = mCbParam.Channel;
	if ((mCbParam.Channel > mSysParam.MaxChannel) || (mCbParam.Channel < mSysParam.MinChannel))mCbParam.Channel = mSysParam.MinChannel;
	if ((mSysParam.LastChannel < mSysParam.MinChannel) || (mSysParam.LastChannel > mSysParam.MaxChannel))
	{
		mSysParam.LastChannel = mCbParam.Channel;
		mSysParam.ActivityChannel = mSysParam.LastChannel;
	}
	if (mCbParam.VolLevel > 9) mCbParam.VolLevel = 5;
	if (mCbParam.TxPower > POWER_HIGH)mCbParam.TxPower = POWER_HIGH;
	if ((mSqParam.IsAsq > 1))mSqParam.IsAsq = 0;
	if ((mSqParam.IsVox > 1))mSqParam.IsVox = 0;
	if (mSqParam.AsqLevel > 5) mSqParam.AsqLevel = 1;
	if (mCbParam.LcdColor > 7) mCbParam.LcdColor = 7;
	if (mSysParam.HitPower > 0) mSysParam.HitPower = 1;	
	
	mSysParam.rest=0;
}
void checkTb()
{
	if(OP1)
	{
		if(OP2) 																		//OP1=1   OP2=1
		{
			if(mCbParam.CountryTable!=1||mCbParam.Country>7||mCbParam.TxPower == POWER_HIGH)
			{
				mCbParam.TxPower=POWER_LOW;
				mCbParam.CountryTable=1;
				mCbParam.Country=COUNTRY_EU;
				mCbParam.Band=0;
				mCbParam.Channel=9;
				mCbParam.Modu=FM;		
			}
		}
		else																				//OP1=1  OP2=0
		{
			if(mCbParam.CountryTable!=2||mCbParam.Country!=COUNTRY_RU)
			{
				mCbParam.CountryTable=2;
				mCbParam.Country=COUNTRY_RU;
				mCbParam.Band=3;			
				mCbParam.Channel=9;
				mCbParam.Modu=FM;					
			}			
		}
	}
	else
	{
		if(OP2)																			//OP1=0   OP2=1
		{
			if(mCbParam.CountryTable!=2||mCbParam.Country!=COUNTRY_HX)
			{
				mCbParam.CountryTable=2;
				mCbParam.Country=COUNTRY_HX;
				mCbParam.Band=3;			
				mCbParam.Channel=9;
				mCbParam.Modu=FM;					
			}	
		}
		else																				//OP1=0   OP2=0
		{
			if(mCbParam.CountryTable!=2||mCbParam.Country>7)
			{
				mCbParam.CountryTable=2;
				mCbParam.Country=COUNTRY_EU;
				mCbParam.Band=3;			
				mCbParam.Channel=9;
				mCbParam.Modu=FM;					
			}	
		}
	}
}


/*-------------------------------------------------------------------------
*函数：loadAllParam  加载功能信息
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void loadAllParam(void)
{
	u8 dat;
	initFlag();
	dat=loadData(EEP_BASE);
	dat=loadData(EEP_BASE);
	dat=loadData(EEP_BASE);
	dat=loadData(EEP_BASE);
	if(loadData(EEP_BASE) != 0xa5)
	{
		setDefaultParam();
		saveAllParam();
	}
	else
	{		
		mCbParam.CountryTable = loadData(EEP_COUNTRY_TB);
		mCbParam.Country = loadData(EEP_COUNTRY);
		mCbParam.Band = loadData(EEP_BAND);
		mCbParam.LastBand=mCbParam.Band;		
		mCbParam.Channel = loadData(EEP_CHANNEL);		
		mSysParam.LastChannel=mCbParam.Channel;
		mCbParam.LastChannel=0x09 ;
		mCbParam.Modu = loadData(EEP_MODU);
		mCbParam.TxPower = loadData(EEP_POWER);
		mCbParam.VolLevel = loadData(EEP_VOL);
		mSqParam.IsAsq = loadData(EEP_IS_ASQ);
		mSqParam.IsVox = loadData(EEP_IS_VOX);
		mSqParam.AsqLevel = loadData(EEP_ASQ_LEVEL);	
		mCbParam.SpkerSwitch = loadData(EEP_SPK_SW);
		mCbParam.LcdColor = loadData(EEP_LCD_COLOR);		
		mCbParam.ButtonToneSwitch = loadData(EEP_TONE_SW);
		mSysParam.LastChannel = loadData(EEP_LAST_CH);	
		
	}
	checkAllParam();
	checkTb();
}
/*-------------------------------------------------------------------------
*函数：ResetParam  初使化设置
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void ResetParam()
{
	setDefaultParam();
	saveAllParam();
}

/*-------------------------------------------------------------------------
*函数：initMemory  初使加载功能信息
*参数：无   
*返回值：无
*-------------------------------------------------------------------------*/
void initMemory(void)
{
	initAt24c08();
	loadAllParam();
	calculateFreq();              //计算频率
}