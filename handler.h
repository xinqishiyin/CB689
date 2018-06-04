#define _HANDLER_H
#ifdef _HANDLER_H





//ASQ等级

#define ASQ_OPEN_LEVEL_127DB 0x0318
#define ASQ_OPEN_LEVEL_126DB 0x030f
#define ASQ_OPEN_LEVEL_125DB 0x0308
#define ASQ_OPEN_LEVEL_124DB 0x02ff
#define ASQ_OPEN_LEVEL_123DB 0x02f8
#define ASQ_OPEN_LEVEL_122DB 0x02ef
#define ASQ_OPEN_LEVEL_121DB 0x02e8  //
#define ASQ_OPEN_LEVEL_120DB 0x02df  
#define ASQ_OPEN_LEVEL_119DB 0x02d7  //       
#define ASQ_OPEN_LEVEL_118DB 0x02cf  
#define ASQ_OPEN_LEVEL_117DB 0x02c8  //
#define ASQ_OPEN_LEVEL_116DB 0x02bf  
#define ASQ_OPEN_LEVEL_115DB 0x02b8  //
#define ASQ_OPEN_LEVEL_114DB 0x02af 
#define ASQ_OPEN_LEVEL_113DB 0x02a9  //
#define ASQ_OPEN_LEVEL_112DB 0x029f
#define ASQ_OPEN_LEVEL_111DB 0x0298
#define ASQ_OPEN_LEVEL_110DB 0x028f
#define ASQ_OPEN_LEVEL_109DB 0x0288
#define ASQ_OPEN_LEVEL_108DB 0x027f

#define ASQ_CLOSE_LEVEL_127DB 0x0328
#define ASQ_CLOSE_LEVEL_126DB 0x0320
#define ASQ_CLOSE_LEVEL_125DB 0x0318
#define ASQ_CLOSE_LEVEL_124DB 0x0310  //
#define ASQ_CLOSE_LEVEL_123DB 0x0308
#define ASQ_CLOSE_LEVEL_122DB 0x0300  //
#define ASQ_CLOSE_LEVEL_121DB 0x02f8   
#define ASQ_CLOSE_LEVEL_120DB 0x02f0  //
#define ASQ_CLOSE_LEVEL_119DB 0x02e8        
#define ASQ_CLOSE_LEVEL_118DB 0x02e0  //
#define ASQ_CLOSE_LEVEL_117DB 0x02d8  
#define ASQ_CLOSE_LEVEL_116DB 0x02d0   //
#define ASQ_CLOSE_LEVEL_115DB 0x02c8
#define ASQ_CLOSE_LEVEL_114DB 0x02c0  //
#define ASQ_CLOSE_LEVEL_113DB 0x02b8
#define ASQ_CLOSE_LEVEL_112DB 0x02b0
#define ASQ_CLOSE_LEVEL_111DB 0x02a8
#define ASQ_CLOSE_LEVEL_110DB 0x02a0
#define ASQ_CLOSE_LEVEL_109DB 0x0298
#define ASQ_CLOSE_LEVEL_108DB 0x0290



#define ASQ_123DB 0x0307
#define ASQ_121DB 0x02fb
#define ASQ_119DB 0x02e1
#define ASQ_117DB 0x02da
#define ASQ_115DB 0x02c8

//SQ等级 
#define SQ_OPEN_127DB    0x0204
#define SQ_OPEN_126DB    0x0207
#define SQ_OPEN_125DB    0x020a
#define SQ_OPEN_124DB		0x020d//124-70 RSSI
#define SQ_OPEN_123DB		0x0210
#define SQ_OPEN_122DB		0x0213
#define SQ_OPEN_121DB		0x0216         
#define SQ_OPEN_120DB		0x0219
#define SQ_OPEN_119DB		0x021c          
#define SQ_OPEN_118DB		0x021e
#define SQ_OPEN_117DB		0x0220         
#define SQ_OPEN_116DB		0x0223
#define SQ_OPEN_115DB		0x0227         
#define SQ_OPEN_114DB		0x022b
#define SQ_OPEN_113DB		0x0231         
#define SQ_OPEN_112DB		0x0232
#define SQ_OPEN_111DB		0x0233          
#define SQ_OPEN_110DB		0x0236
#define SQ_OPEN_109DB		0x0239          
#define SQ_OPEN_108DB		0x023b
#define SQ_OPEN_107DB		0x0241          
#define SQ_OPEN_106DB		0x0243
#define SQ_OPEN_105DB		0x0246          
#define SQ_OPEN_104DB		0x0249
#define SQ_OPEN_103DB		0x024d          
#define SQ_OPEN_102DB		0x024f
#define SQ_OPEN_101DB		0x0251         
#define SQ_OPEN_100DB		0x0254
#define SQ_OPEN_99DB			0x0257          
#define SQ_OPEN_98DB			0x025a  
#define SQ_OPEN_97DB			0x025d          
#define SQ_OPEN_96DB			0x025e
#define SQ_OPEN_95DB			0x0260          
#define SQ_OPEN_94DB			0x0262
#define SQ_OPEN_93DB			0x0265         
#define SQ_OPEN_92DB			0x0269
#define SQ_OPEN_91DB			0x026e          
#define SQ_OPEN_90DB			0x0270
#define SQ_OPEN_89DB			0x0272          
#define SQ_OPEN_88DB			0x0274
#define SQ_OPEN_87DB			0x0277          
#define SQ_OPEN_86DB			0x027b
#define SQ_OPEN_85DB			0x027e         
#define SQ_OPEN_84DB			0x0281
#define SQ_OPEN_83DB			0x0284        
#define SQ_OPEN_82DB			0x0287
#define SQ_OPEN_81DB			0x0289          
#define SQ_OPEN_80DB			0x028b
#define SQ_OPEN_79DB			0x028e          
#define SQ_OPEN_78DB			0x0293
#define SQ_OPEN_77DB			0x0297         
#define SQ_OPEN_76DB			0x029a
#define SQ_OPEN_75DB			0x029e
#define SQ_OPEN_74DB			0x02a2
#define SQ_OPEN_73DB			0x02a5          
#define SQ_OPEN_72DB			0x02a8
#define SQ_OPEN_71DB			0x02ab
#define SQ_OPEN_70DB			0x02a9+(0x0200-0x0144) 
#define SQ_OPEN_69DB			0x02a9+(0x0200-0x013f)
#define SQ_OPEN_68DB			0x02a9+(0x0200-0x013a)   
#define SQ_OPEN_67DB			0x02a9+(0x0200-0x0136)
#define SQ_OPEN_66DB			0x02a9+(0x0200-0x0131)
#define SQ_OPEN_65DB			0x02a9+(0x0200-0x012d)
#define SQ_OPEN_64DB			0x02a9+(0x0200-0x0128)
#define SQ_OPEN_63DB			0x02a9+(0x0200-0x0124)  
#define SQ_OPEN_62DB			0x02a9+(0x0200-0x0120)
#define SQ_OPEN_61DB			0x02a9+(0x0200-0x011a)
#define SQ_OPEN_60DB			0x02a9+(0x0200-0x0116)
#define SQ_OPEN_59DB			0x02a9+(0x0200-0x0111)
#define SQ_OPEN_58DB			0x02a9+(0x0200-0x010b)
#define SQ_OPEN_57DB			0x02a9+(0x0200-0x0107)
#define SQ_OPEN_56DB			0x02a9+(0x0200-0x0102)
#define SQ_OPEN_55DB			0x02a9+(0x0200-0x00fe)
#define SQ_OPEN_54DB			0x02a9+(0x0200-0x00fa)
#define SQ_OPEN_53DB			0x02a9+(0x0200-0x00f5)   
#define SQ_OPEN_52DB			0x02a9+(0x0200-0x00f1)
#define SQ_OPEN_51DB			0x02a9+(0x0200-0x00ee)
#define SQ_OPEN_50DB			0x02a9+(0x0200-0x00ea)
#define SQ_OPEN_49DB			0x02a9+(0x0200-0x00e6)
#define SQ_OPEN_48DB			0x02a9+(0x0200-0x00e2)
#define SQ_OPEN_47DB			0x02a9+(0x0200-0x00db)  
#define SQ_OPEN_46DB			0x02a9+(0x0200-0x00d8)
#define SQ_OPEN_45DB			0x02a9+(0x0200-0x00d5)
#define SQ_OPEN_44DB			0x02a9+(0x0200-0x00d2)
#define SQ_OPEN_43DB			0x02a9+(0x0200-0x00cf)  
#define SQ_OPEN_42DB			0x02a9+(0x0200-0x00cc)
#define SQ_OPEN_41DB			0x02a9+(0x0200-0x00c9)
#define SQ_OPEN_40DB			0x02a9+(0x0200-0x00c6)

//SQ等级 
#define SQ_CLOSE_127DB    0x01f7
#define SQ_CLOSE_126DB    0x01fb
#define SQ_CLOSE_125DB    0x01ff
#define SQ_CLOSE_124DB		0x0203//124-70 RSSI  //1:203
#define SQ_CLOSE_123DB		0x0205
#define SQ_CLOSE_122DB		0x0207               //2:207
#define SQ_CLOSE_121DB		0x020b         
#define SQ_CLOSE_120DB		0x020f              //3:20f
#define SQ_CLOSE_119DB		0x0213          
#define SQ_CLOSE_118DB		0x0217              //4:217
#define SQ_CLOSE_117DB		0x021a         
#define SQ_CLOSE_116DB		0x021e              //5:21e
#define SQ_CLOSE_115DB		0x0222         
#define SQ_CLOSE_114DB		0x0226              //6:226
#define SQ_CLOSE_113DB		0x022a         
#define SQ_CLOSE_112DB		0x022e              //7:22e
#define SQ_CLOSE_111DB		0x0232          
#define SQ_CLOSE_110DB		0x0236              //8:236
#define SQ_CLOSE_109DB		0x0238         
#define SQ_CLOSE_108DB		0x023f              //9:23a
#define SQ_CLOSE_107DB		0x024d          
#define SQ_CLOSE_106DB		0x0240              //10:240
#define SQ_CLOSE_105DB		0x0244          
#define SQ_CLOSE_104DB		0x0248              //11:248
#define SQ_CLOSE_103DB		0x024a          
#define SQ_CLOSE_102DB		0x024d              //12:24d
#define SQ_CLOSE_101DB		0x0252         
#define SQ_CLOSE_100DB		0x0255              //13:255
#define SQ_CLOSE_99DB			0x0256          
#define SQ_CLOSE_98DB			0x0258            //14:258
#define SQ_CLOSE_97DB			0x025b          
#define SQ_CLOSE_96DB			0x025f            //15:25f
#define SQ_CLOSE_95DB			0x0260          
#define SQ_CLOSE_94DB			0x0262            //16:262
#define SQ_CLOSE_93DB			0x0264         
#define SQ_CLOSE_92DB			0x0266            //17:266
#define SQ_CLOSE_91DB			0x026a          
#define SQ_CLOSE_90DB			0x027f            //18:271
#define SQ_CLOSE_89DB			0x0272          
#define SQ_CLOSE_88DB			0x0275            //19:275
#define SQ_CLOSE_87DB			0x0278          
#define SQ_CLOSE_86DB			0x027d            //20:27d
#define SQ_CLOSE_85DB			0x027e         
#define SQ_CLOSE_84DB			0x0281            //21:281
#define SQ_CLOSE_83DB			0x0284        
#define SQ_CLOSE_82DB			0x0287            //22:287
#define SQ_CLOSE_81DB			0x028a          
#define SQ_CLOSE_80DB			0x028e            //23:28e
#define SQ_CLOSE_79DB			0x0291          
#define SQ_CLOSE_78DB			0x0293            
#define SQ_CLOSE_77DB			0x0295         
#define SQ_CLOSE_76DB			0x0297
#define SQ_CLOSE_75DB			0x0299           //24:299
#define SQ_CLOSE_74DB			0x029b
#define SQ_CLOSE_73DB			0x029e          
#define SQ_CLOSE_72DB			0x02a1
#define SQ_CLOSE_71DB			0x02a4
#define SQ_CLOSE_70DB			0x02a9+(0x0200-0x0144) 
#define SQ_CLOSE_69DB			0x02a9+(0x0200-0x013f)
#define SQ_CLOSE_68DB			0x02a9+(0x0200-0x013a)   
#define SQ_CLOSE_67DB			0x02a9+(0x0200-0x0136)
#define SQ_CLOSE_66DB			0x02a9+(0x0200-0x0131)
#define SQ_CLOSE_65DB			0x02a9+(0x0200-0x012d)
#define SQ_CLOSE_64DB			0x02a9+(0x0200-0x0128)
#define SQ_CLOSE_63DB			0x02a9+(0x0200-0x0124)  
#define SQ_CLOSE_62DB			0x02a9+(0x0200-0x0120)
#define SQ_CLOSE_61DB			0x02a9+(0x0200-0x011a)
#define SQ_CLOSE_60DB			0x02a9+(0x0200-0x0116)
#define SQ_CLOSE_59DB			0x02a9+(0x0200-0x0111)
#define SQ_CLOSE_58DB			0x02a9+(0x0200-0x010b)
#define SQ_CLOSE_57DB			0x02a9+(0x0200-0x0107)
#define SQ_CLOSE_56DB			0x02a9+(0x0200-0x0102)
#define SQ_CLOSE_55DB			0x02a9+(0x0200-0x00fe)
#define SQ_CLOSE_54DB			0x02a9+(0x0200-0x00fa)
#define SQ_CLOSE_53DB			0x02a9+(0x0200-0x00f5)   
#define SQ_CLOSE_52DB			0x02a9+(0x0200-0x00f1)
#define SQ_CLOSE_51DB			0x02a9+(0x0200-0x00ee)
#define SQ_CLOSE_50DB			0x02a9+(0x0200-0x00ea)
#define SQ_CLOSE_49DB			0x02a9+(0x0200-0x00e6)
#define SQ_CLOSE_48DB			0x02a9+(0x0200-0x00e2)
#define SQ_CLOSE_47DB			0x02a9+(0x0200-0x00db)  
#define SQ_CLOSE_46DB			0x02a9+(0x0200-0x00d8)
#define SQ_CLOSE_45DB			0x02a9+(0x0200-0x00d5)
#define SQ_CLOSE_44DB			0x02a9+(0x0200-0x00d2)
#define SQ_CLOSE_43DB			0x02a9+(0x0200-0x00cf)  
#define SQ_CLOSE_42DB			0x02a9+(0x0200-0x00cc)
#define SQ_CLOSE_41DB			0x02a9+(0x0200-0x00c9)
#define SQ_CLOSE_40DB			0x02a9+(0x0200-0x00c6)


#define SQ_VOL_MAX         0x03ff
#define SQ_VOL_MIN         0x0000

/*-------------------------------------------------------------------------
*函数：SetTxPower  设置发射功率
*参数：mCbParam.CountryTable 国家表   mCbParam.Country 国家 mCbParam.Modu 调制模式 mCbParam.TxPower  高低功率
*返回值：POW_4W 及  POW_1W对应修改
*-------------------------------------------------------------------------*/
void SetTxPower();
/*-------------------------------------------------------------------------
*函数：SetModu  设置发射功率
*参数：mCbParam.CountryTable 国家表   mCbParam.Country 国家 mCbParam.Modu 调制模式 mCbParam.TxPower  高低功率
*返回值：POW_4W 及  POW_1W对应修改
*-------------------------------------------------------------------------*/
void SetModu();
/*-------------------------------------------------------------------------
*函数：SQ_Switch SQ旋钮电压值获取
*参数：
*返回值：
*-------------------------------------------------------------------------*/
void SQ_Switch();
/*-------------------------------------------------------------------------
*函数：VOX_Check  VOX打开
*参数：无
*返回值：无
*-------------------------------------------------------------------------*/
void VOX_Check();
#endif