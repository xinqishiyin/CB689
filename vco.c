#include "system.h"
#include "vco.h"

/***************************************修改记录*****************************************************
 Function List：
		1、calculateFreq       4802VCO  频率计算
 Change Log:


****************************************************************************************************/
xdata u8   NDIV_FRE=80;
xdata tVcoParam mVcoParam;



/*-------------------------------------------------------------------------
*函数：calculateFreq  计算发射 接收频率  保存到  mXn31202Ch1_Rx  和 mXn31202Ch1_Tx
*参数：mCbParam.Channel   信道号     mCbParam.Country 国家制式  cFreqStep 步进  
*返回值：无
*-------------------------------------------------------------------------*/
void calculateFreq(void)
{
	double temp;
  u32 mCurrentFreq = 0;		//当前信道的频率，通过信道1和步进频率计算
	//
	switch(mCbParam.Country)
	{
		/*-----------table1------------*/
		case COUNTRY_EU:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;		
					default:
						break;
				}				
			}
			else if(mCbParam.Channel==23)	mCurrentFreq=27255 ;
			else if(mCbParam.Channel==24)	mCurrentFreq=27235 ;
			else if(mCbParam.Channel==25)	mCurrentFreq=27245 ;
			else mCurrentFreq=27265 +(mCbParam.Channel-26)*10;	 
			break;
		case COUNTRY_CE:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}				
			}			
			else if(mCbParam.Channel==23)	mCurrentFreq=27255 ;
			else if(mCbParam.Channel==24)	mCurrentFreq=27235 ;
			else if(mCbParam.Channel==25)	mCurrentFreq=27245 ;
			else mCurrentFreq=27265 +(mCbParam.Channel-26)*10;	
			break;
		case COUNTRY_UK:
			mCurrentFreq=27601+(mCbParam.Channel-1)*10;
			break;
		case COUNTRY_PL:
			if(mCbParam.Channel==1) mCurrentFreq= 26960;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26960 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26960 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26960 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26960 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}				
			}			
			else if(mCbParam.Channel==23)	mCurrentFreq=27250 ;
			else if(mCbParam.Channel==24)	mCurrentFreq=27230 ;
			else if(mCbParam.Channel==25)	mCurrentFreq=27240 ;
			else mCurrentFreq=27260 +(mCbParam.Channel-26)*10;		
			break;
		case COUNTRY_I0:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}				
			}			
			else if(mCbParam.Channel==23) mCurrentFreq=27255;
			else if(mCbParam.Channel==24) mCurrentFreq=27235;
			else if(mCbParam.Channel==25) mCurrentFreq=27245;
			else if(mCbParam.Channel<=40) mCurrentFreq=27265+(mCbParam.Channel-26)*10;
			break;
		case COUNTRY_I2:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}				
			}				
			else if(mCbParam.Channel==23) mCurrentFreq=27255;
			else if(mCbParam.Channel==24) mCurrentFreq=27245;
			else if(mCbParam.Channel<=34) mCurrentFreq=26865+ (mCbParam.Channel-25)*10;
			//else if(mCbParam.Channel==35) mCurrentFreq=26855;
			//else if(mCbParam.Channel==36) mCurrentFreq=26865;
			break;
		case COUNTRY_DE:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}
			}				
			else if(mCbParam.Channel==23) mCurrentFreq=27255;
			else if(mCbParam.Channel==24) mCurrentFreq=27235;
			else if(mCbParam.Channel==25) mCurrentFreq=27245;
			else if(mCbParam.Channel<=40) mCurrentFreq=27265+(mCbParam.Channel-26)*10;
			else mCurrentFreq=26565+(mCbParam.Channel-41)*10;
			break;
		case COUNTRY_IN:
			if(mCbParam.Channel==1) mCurrentFreq= 26965;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50;
						break;
					case 1:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+10;
						break;
					case 2:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+20;
						break;
					case 3:mCurrentFreq=26965 +(mCbParam.Channel-1)/4*50+40;
						break;					
				}				
			}				
			else if(mCbParam.Channel==23)	mCurrentFreq=27255;
			else if(mCbParam.Channel==24)	mCurrentFreq=27235;
			else if(mCbParam.Channel==25)	mCurrentFreq=27245;
			else if(mCbParam.Channel==26)	mCurrentFreq=27265;
			else if(mCbParam.Channel==27)	mCurrentFreq=27275;
			break;
		/*-----------table2-----------*/
		case COUNTRY_RU:
			if(mCbParam.Channel==1) mCurrentFreq= mCbParam.Band*450+25615;
			else if(mCbParam.Channel<=22)
			{
				switch((mCbParam.Channel-1)%4)
				{
					case 0:mCurrentFreq=25615 +(mCbParam.Channel-1)/4*50+mCbParam.Band*450;
						break;
					case 1:mCurrentFreq=25615 +(mCbParam.Channel-1)/4*50+10+ mCbParam.Band*450;
						break;
					case 2:mCurrentFreq=25615 +(mCbParam.Channel-1)/4*50+20+ mCbParam.Band*450;
						break;
					case 3:mCurrentFreq=25615 +(mCbParam.Channel-1)/4*50+40+ mCbParam.Band*450;
						break;					
				}				
			}			
			else if(mCbParam.Channel==23)	mCurrentFreq=25905+ mCbParam.Band*450 ;
			else if(mCbParam.Channel==24)	mCurrentFreq=25885+ mCbParam.Band*450 ;
			else if(mCbParam.Channel==25)	mCurrentFreq=25895+ mCbParam.Band*450 ;
			else mCurrentFreq=25915+ mCbParam.Band*450 +(mCbParam.Channel-26)*10;	
     
			break;
		case COUNTRY_HX:
			mCurrentFreq=28.000 + (mCbParam.Channel-1)*0.005 + mCbParam.Band*0.2;		
			break;	
		default:
			break;
	}
	
	
	temp=((double)mCurrentFreq)/1000;	
	if(mCbParam.Country==COUNTRY_UK) 
	{
		temp+=0.00025;
	}
	//temp=27.6683;

	//mCurrentFreq=(26.5078+((temp+IF+IF4802)-38.556)*20/29.093)*mVcoParam.NDIV_FRE*8388608/21.7;//29.095????
	mCurrentFreq=(temp+ CAFREQ+ IF4802)*mVcoParam.NDIV_FRE*BK4802_EXP;
	mVcoParam.h_Fre_Rx=mCurrentFreq>>16;
	mVcoParam.l_Fre_Rx=mCurrentFreq;
	if (mCbParam.Modu==AM && mMenu.isTx == 0)
	{
		//36.310-40.805  四等分 并取每等分的中间值做计算
		if (temp < 26.733)
		{
			mCurrentFreq = (FADE_1 + ((temp + IF) - 36.872) * BK4802_FADE_EXP)*mVcoParam.NDIV_FRE * BK4802_EXP;//29.095
		}
		else if (temp < 27.856)
		{
			mCurrentFreq = (FADE_2 + ((temp + IF ) - 37.995) * BK4802_FADE_EXP)*mVcoParam.NDIV_FRE * BK4802_EXP;//29.095
		}
		else if (temp < 28.979)
		{
			mCurrentFreq = (FADE_3 + ((temp + IF ) - 39.118) * BK4802_FADE_EXP)*mVcoParam.NDIV_FRE * BK4802_EXP;//29.095
		}
		else
		{
			mCurrentFreq = (FADE_4 + ((temp + IF ) - 40.244) * BK4802_FADE_EXP)*mVcoParam.NDIV_FRE * BK4802_EXP;//29.095
		}
	}
	else
	{
		mCurrentFreq = (temp + CAFREQ )*mVcoParam.NDIV_FRE * BK4802_EXP;		
	} 
	//mCurrentFreq=(temp+0.00335)*mVcoParam.NDIV_FRE*8388608/21.7;	  //天气预报段  161-163   NDIV=24  REG2  0x2000
	
	mVcoParam.h_Fre_Tx=mCurrentFreq>>16;
	mVcoParam.l_Fre_Tx=mCurrentFreq;
}
