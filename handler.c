#include "system.h"
#include "handler.h"
#include "uart.h"

/***************************************修改记录*****************************************************
 
 Function List：
 1、setRfg   		Rfg引脚电压值控制 0-200
 2、SetTxPower      功率对应引脚控制
 3、checkRssi       SQ值
 4、SQ_Switch       SQ旋钮电压值
 5、SetModu         模式对应引脚控制
 Change Log:

****************************************************************************************************/

uint asq_open_table[] =   
{ 
	ASQ_OPEN_LEVEL_127DB,	ASQ_OPEN_LEVEL_126DB,	ASQ_OPEN_LEVEL_125DB,	ASQ_OPEN_LEVEL_124DB,	ASQ_OPEN_LEVEL_123DB,	ASQ_OPEN_LEVEL_122DB,  //                 3
	ASQ_OPEN_LEVEL_121DB,	ASQ_OPEN_LEVEL_120DB,	ASQ_OPEN_LEVEL_119DB,	ASQ_OPEN_LEVEL_118DB,	ASQ_OPEN_LEVEL_117DB,  
	ASQ_OPEN_LEVEL_116DB,	ASQ_OPEN_LEVEL_115DB,	ASQ_OPEN_LEVEL_114DB,	ASQ_OPEN_LEVEL_113DB,	ASQ_OPEN_LEVEL_112DB,  
	ASQ_OPEN_LEVEL_111DB,	ASQ_OPEN_LEVEL_110DB,	ASQ_OPEN_LEVEL_109DB                                       
};
uint asq_close_table[] = 
{ 
	ASQ_CLOSE_LEVEL_127DB,	ASQ_CLOSE_LEVEL_126DB,	ASQ_CLOSE_LEVEL_125DB,	ASQ_CLOSE_LEVEL_124DB,	ASQ_CLOSE_LEVEL_123DB,	ASQ_CLOSE_LEVEL_122DB,  //                 3
	ASQ_CLOSE_LEVEL_121DB,	ASQ_CLOSE_LEVEL_120DB,	ASQ_CLOSE_LEVEL_119DB,	ASQ_CLOSE_LEVEL_118DB,	ASQ_CLOSE_LEVEL_117DB,  
	ASQ_CLOSE_LEVEL_116DB,	ASQ_CLOSE_LEVEL_115DB,	ASQ_CLOSE_LEVEL_114DB,	ASQ_CLOSE_LEVEL_113DB,	ASQ_CLOSE_LEVEL_112DB,  
	ASQ_CLOSE_LEVEL_111DB,	ASQ_CLOSE_LEVEL_110DB,	ASQ_CLOSE_LEVEL_109DB                                       
};
/*
code uint asq_table[] = {	ASQ_LEVEL_121DB,	ASQ_LEVEL_119DB,	ASQ_LEVEL_117DB,	ASQ_LEVEL_115DB,	ASQ_LEVEL_113DB};
*/

uint sq_open_table[] = 
{
	SQ_OPEN_124DB,	SQ_OPEN_123DB,	SQ_OPEN_122DB,	SQ_OPEN_121DB,	SQ_OPEN_120DB,	SQ_OPEN_119DB,	SQ_OPEN_118DB,	SQ_OPEN_117DB,	SQ_OPEN_116DB,	SQ_OPEN_115DB,     //3 5 7 9
	SQ_OPEN_114DB,	SQ_OPEN_113DB,	SQ_OPEN_112DB,	SQ_OPEN_111DB,	SQ_OPEN_110DB,	SQ_OPEN_109DB,	SQ_OPEN_108DB,	SQ_OPEN_107DB,	SQ_OPEN_106DB,	SQ_OPEN_105DB,     //11 13 15 17 19
	SQ_OPEN_104DB,	SQ_OPEN_103DB,	SQ_OPEN_102DB,	SQ_OPEN_101DB,	SQ_OPEN_100DB,	SQ_OPEN_99DB,	SQ_OPEN_98DB,	SQ_OPEN_97DB,	SQ_OPEN_96DB,	SQ_OPEN_95DB,      //21 23 25 27 29
	SQ_OPEN_94DB,	SQ_OPEN_93DB,	SQ_OPEN_92DB,	SQ_OPEN_91DB,	SQ_OPEN_90DB,	SQ_OPEN_89DB,	SQ_OPEN_88DB,	SQ_OPEN_87DB,	SQ_OPEN_86DB,	SQ_OPEN_85DB,      //31 33 35 37 39
	SQ_OPEN_84DB,	SQ_OPEN_83DB,	SQ_OPEN_82DB,	SQ_OPEN_81DB,	SQ_OPEN_80DB,	SQ_OPEN_79DB,	SQ_OPEN_78DB,	SQ_OPEN_77DB,	SQ_OPEN_76DB,	SQ_OPEN_75DB,      //41 43 45 47 
	SQ_OPEN_74DB,	SQ_OPEN_73DB,	SQ_OPEN_72DB,	SQ_OPEN_71DB,	SQ_OPEN_70DB,	SQ_OPEN_69DB,	SQ_OPEN_68DB,	SQ_OPEN_67DB,	SQ_OPEN_66DB,	SQ_OPEN_65DB,      //51
	SQ_OPEN_64DB,	SQ_OPEN_63DB,	SQ_OPEN_62DB,	SQ_OPEN_61DB,	SQ_OPEN_60DB,	SQ_OPEN_59DB,	SQ_OPEN_58DB,	SQ_OPEN_57DB,	SQ_OPEN_56DB,	SQ_OPEN_55DB,      //61
	SQ_OPEN_54DB,	SQ_OPEN_53DB,	SQ_OPEN_52DB,	SQ_OPEN_51DB,	SQ_OPEN_50DB,	SQ_OPEN_49DB,	SQ_OPEN_48DB,	SQ_OPEN_47DB,	SQ_OPEN_46DB,	SQ_OPEN_45DB,      //71 77
	SQ_OPEN_44DB,	SQ_OPEN_43DB,	SQ_OPEN_42DB,	SQ_OPEN_41DB,	SQ_OPEN_40DB                                                         //82
};

uint sq_close_table[] = 
{
	SQ_CLOSE_127DB, SQ_CLOSE_126DB, SQ_CLOSE_125DB, SQ_CLOSE_124DB,	SQ_CLOSE_123DB,	SQ_CLOSE_122DB,	SQ_CLOSE_121DB,	SQ_CLOSE_120DB,	SQ_CLOSE_119DB,	SQ_CLOSE_118DB,	SQ_CLOSE_117DB,	SQ_CLOSE_116DB,	SQ_CLOSE_115DB,
	SQ_CLOSE_114DB,	SQ_CLOSE_113DB,	SQ_CLOSE_112DB,	SQ_CLOSE_111DB,	SQ_CLOSE_110DB,	SQ_CLOSE_109DB,	SQ_CLOSE_108DB,	SQ_CLOSE_107DB,	SQ_CLOSE_106DB,	SQ_CLOSE_105DB,
	SQ_CLOSE_104DB,	SQ_CLOSE_103DB,	SQ_CLOSE_102DB,	SQ_CLOSE_101DB,	SQ_CLOSE_100DB,	SQ_CLOSE_99DB,	SQ_CLOSE_98DB,	SQ_CLOSE_97DB,	SQ_CLOSE_96DB,	SQ_CLOSE_95DB,
	SQ_CLOSE_94DB,	SQ_CLOSE_93DB,	SQ_CLOSE_92DB,	SQ_CLOSE_91DB,	SQ_CLOSE_90DB,	SQ_CLOSE_89DB,	SQ_CLOSE_88DB,	SQ_CLOSE_87DB,	SQ_CLOSE_86DB,	SQ_CLOSE_85DB,
	SQ_CLOSE_84DB,	SQ_CLOSE_83DB,	SQ_CLOSE_82DB,	SQ_CLOSE_81DB,	SQ_CLOSE_80DB,	SQ_CLOSE_79DB,	SQ_CLOSE_78DB,	SQ_CLOSE_77DB,	SQ_CLOSE_76DB,	SQ_CLOSE_75DB,
	SQ_CLOSE_74DB,	SQ_CLOSE_73DB,	SQ_CLOSE_72DB,	SQ_CLOSE_71DB,	SQ_CLOSE_70DB,	SQ_CLOSE_69DB,	SQ_CLOSE_68DB,	SQ_CLOSE_67DB,	SQ_CLOSE_66DB,	SQ_CLOSE_65DB,
	SQ_CLOSE_64DB,	SQ_CLOSE_63DB,	SQ_CLOSE_62DB,	SQ_CLOSE_61DB,	SQ_CLOSE_60DB,	SQ_CLOSE_59DB,	SQ_CLOSE_58DB,	SQ_CLOSE_57DB,	SQ_CLOSE_56DB,	SQ_CLOSE_55DB,
	SQ_CLOSE_54DB,	SQ_CLOSE_53DB,	SQ_CLOSE_52DB,	SQ_CLOSE_51DB,	SQ_CLOSE_50DB,	SQ_CLOSE_49DB,	SQ_CLOSE_48DB,	SQ_CLOSE_47DB,	SQ_CLOSE_46DB,	SQ_CLOSE_45DB,
	SQ_CLOSE_44DB,	SQ_CLOSE_43DB,	SQ_CLOSE_42DB,	SQ_CLOSE_41DB,	SQ_CLOSE_40DB
};

/*-------------------------------------------------------------------------
*函数：setRfg  设置Rfg
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void setRfg(uchar RfgLevel)
{
	uchar rfg;	 
	PWM_MODDA_CLOSE;	
	if (RfgLevel == 0) rfg = 0;
	else if (RfgLevel == 1) rfg = 116;
	else if (RfgLevel == 2) rfg = 121;
	else if (RfgLevel == 3) rfg = 128;
	else if (RfgLevel == 4) rfg = 135;
	else if (RfgLevel == 5) rfg = 142;
	else if (RfgLevel == 6) rfg = 149;
	else if (RfgLevel == 7) rfg = 158;
	else if (RfgLevel == 8) rfg = 180;
	else if (RfgLevel == 9) rfg = 200;           //对应占空比来改变电压
	if (rfg != 0)
	{
		MODDA = rfg;
		PWM_MODDA_OPEN;
	}
	
}

/*-------------------------------------------------------------------------
*函数：SetTxPower  设置功率
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void SetTxPower()
{
	if(mCbParam.CountryTable==1 && mCbParam.Country==COUNTRY_EU && mCbParam.Modu==AM)
	{
		POW_4W = 1;
		POW_1W = 0;      //1W功率
	}
	else if(mCbParam.CountryTable==2 && (mCbParam.TxPower == POWER_HIGH))
	{
		POW_4W = 0;
		POW_1W = 0;      //8W功率
	}
	else 
	{
		POW_4W = 0;
		POW_1W = 1;		//4W功率
	}	
}
/*-------------------------------------------------------------------------
*函数：SetModu  设置调制
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void SetModu()
{
	if (mCbParam.Modu == FM)
	{
		SET_FM_EN;            //FM电源开启
		CLS_AM_EN;			  //AM电源开启
		AF_EN = 1;            //FM、AM通路选择
		
	}
	else
	{
		SET_AM_EN;
		CLS_FM_EN;
		AF_EN = 0;
	}
	
}

/*-------------------------------------------------------------------------
*函数：checkRssi  
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void checkRssi(void)
{
	uchar i;
	uint temp_asq,temp_rssi,temp_agca;	
	temp_asq = 0;
	temp_rssi = 0;
	temp_agca = 0;
	for(i=0; i<3; i++)
	{
		if(mSqParam.IsAsq==1)
		{
			temp_asq += Get_AD(ADC_ASQ);
		}
		temp_rssi += Get_AD(ADC_RSSI);
		temp_agca += Get_AD(ADC_AGCA);
		delayms(1);
	}
	if(mSqParam.IsAsq==1)
	{
		mSysParam.mAsqVoltage = temp_asq/3;
	}
	mSysParam.mRssiVoltage = temp_rssi/3;
	mSysParam.mAgcaVoltage = temp_agca/3;
}
/*-------------------------------------------------------------------------
*函数：SQ_Switch  SQ阈值
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void SQ_Switch()
{
	u16 val;
	u8 sqlevel;	
	if(mSqParam.IsAsq==0)
	{
		val=Get_AD(ADC_ASQ);
		sqlevel=(val-SQ_VOL_MIN)/((SQ_VOL_MAX-SQ_VOL_MIN)/28);     //旋钮电压平均分成28等分
	}	
}
/*-------------------------------------------------------------------------
*函数：VOX_Check  VOX打开
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void VOX_Check()
{
//	u16	val;
//	if (mSqParam.IsVox==1)
//	{
//		val = Get_AD(ADC_VOX);
//		if (val > VOX_GAIN_VAL)
//		{
//			MenuOperate(KEY_PPT_DN);
//			while (val > VOX_GAIN_VAL);
//			MenuOperate(KEY_PPT_UP);
//		}
//  }	
}









