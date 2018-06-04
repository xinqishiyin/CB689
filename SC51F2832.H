#ifndef	__SC51F2832_H__
#define	__SC51F2832_H__

/*2011.10.08 修改为MCU1101P版本
1.将寄存器按模块划分，与寄存器表对应一致
2.增加ADC等模块控制。
*/
	
/*说明:
[2010.4.26]
  1 前面小x打头的寄存器表示需要由dptr来访问;
  2 符号ASM: 用户程序若使用的是汇编语言,应定义ASM为1,即#define	ASM 1, C语言应使ASM不为1;
*/

#define  ASM    0  // =1,用户编译的是汇编语言

/*  BYTE Register  */

sfr  P0    = 0x80;
sfr  P1    = 0x90;
sfr  P2    = 0xA0;
sfr  P3    = 0xB0;
sfr  PSW   = 0xD0;
sfr  ACC   = 0xE0;
sfr  B     = 0xF0;
sfr  SP    = 0x81;
sfr  DPL   = 0x82;
sfr  DPH   = 0x83;
sfr  PCON  = 0x87;
sfr  TCON  = 0x88;
sfr  TMOD  = 0x89;
sfr  TL0   = 0x8A;
sfr  TL1   = 0x8B;
sfr  TH0   = 0x8C;
sfr  TH1   = 0x8D;
sfr  IE    = 0xA8;
sfr  IP    = 0xB8;
sfr  AUXR1 = 0xA2;
sfr  MOVXRH = 0xA1;
/*  BIT Register  */

/*	P0    */
sbit  P00 = P0^0;
sbit  P01 = P0^1;
sbit  P02 = P0^2;
sbit  P03 = P0^3;
sbit  P04 = P0^4;
sbit  P05 = P0^5;
sbit  P06 = P0^6;
sbit  P07 = P0^7;

/*	P1    */
sbit  P10 = P1^0;
sbit  P11 = P1^1;
sbit  P12 = P1^2;
sbit  P13 = P1^3;
sbit  P14 = P1^4;
sbit  P15 = P1^5;
sbit  P16 = P1^6;
sbit  P17 = P1^7;

/*	P2    */
sbit  P20 = P2^0;
sbit  P21 = P2^1;
sbit  P22 = P2^2;
sbit  P23 = P2^3;
sbit  P24 = P2^4;
sbit  P25 = P2^5;
sbit  P26 = P2^6;
sbit  P27 = P2^7;

/*	P3    */
sbit  P30 = P3^0;
sbit  P31 = P3^1;
sbit  P32 = P3^2;
sbit  P33 = P3^3;
sbit  P34 = P3^4;
sbit  P35 = P3^5;
sbit  P36 = P3^6;
sbit  P37 = P3^7;

/*  PSW   */
sbit  CY   = 0xD7;
sbit  AC   = 0xD6;
sbit  F0   = 0xD5;
sbit  RS1  = 0xD4;
sbit  RS0  = 0xD3;
sbit  OV   = 0xD2;
sbit  P    = 0xD0;

/*  TCON  */
sbit  TF1  = 0x8F;
sbit  TR1  = 0x8E;
sbit  TF0  = 0x8D;
sbit  TR0  = 0x8C;
sbit  IE1  = 0x8B;
sbit  IT1  = 0x8A;
sbit  IE0  = 0x89;
sbit  IT0  = 0x88;

/*  IE   */
sbit  EA   = 0xAF;
sbit  ET2  = 0xAD;
sbit  ES   = 0xAC;
sbit  ET1  = 0xAB;
sbit  EX1  = 0xAA;
sbit  ET0  = 0xA9;
sbit  EX0  = 0xA8;

/*  IP   */ 
sbit  PT2  = 0xBD;
sbit  PS   = 0xBC;
sbit  PT1  = 0xBB;
sbit  PX1  = 0xBA;
sbit  PT0  = 0xB9;
sbit  PX0  = 0xB8;

/*  SCON  */
sbit  SM0  = 0x9E;		   // 反了
sbit  SM1  = 0x9F;		   //
sbit  SM2  = 0x9D;
sbit  REN  = 0x9C;
sbit  TB8  = 0x9B;
sbit  RB8  = 0x9A;
sbit  TI   = 0x99;
sbit  RI   = 0x98;


/*******************************INTC***********************/
sfr  EIE1    = 0xA9;	// 中断允许控制
sfr  EIE2    = 0xAA;	// 中断允许控制
sfr  EIP1    = 0xB9;	// 中断优先级控制
sfr  EIP2    = 0xBA;	// 中断优先级控制
sfr  EINTCS0 = 0xAC;  // 外部中断控制与状态寄存器
sfr  EINTCS1 = 0xBC;   

/******************************PMU**************************************************************************/
sfr	 VMC0 	 = 0xA5;  // 低压控制
sfr  LVRCON  = 0xA6;  // 低压复位电压设置，Enable
sfr  SPMC0	 = 0xA6;  // 系统电源管理
#if  ASM == 1
xSTOPCFG  EQU  0FFA0H  //STOP模式配置
#else
#define  xSTOPCFG  (*(volatile unsigned char xdata *)0xFFA0)  //STOP模式配置
#endif

/**************************RESET**************************************************************************/
sfr  RSTSRC  = 0xA7;  // 复位标志

/**************************WDT**********************************************************************/
sfr  WDTCON   = 0xBD;  // WDT 分频控制
sfr  WDTCLR0  = 0x84;  // WDT清0
sfr  WDTCLR1  = 0xEB;  // WDT清0

/**************************CKM******************************************************************/  
sfr  MCKDIV  = 0x91;
sfr  MCKSEL  = 0x92;
sfr  CLKEN   = 0x93;   
sfr  WPKEY   = 0x95;
sfr  PLLCON  = 0x96;
#if  ASM == 1
xSYSCFG    EQU  0FFA2H  // 时钟配置
xSYSCFG2   EQU  0FFA3H  // 时钟配置
#else
#define  xSYSCFG   (*(volatile unsigned char xdata *)0xFFA2)  //时钟配置
#define  xSYSCFG2  (*(volatile unsigned char xdata *)0xFFA3)  //时钟配置
#endif


/**************************IOPort寄存器**********************************************************/
sfr  P0MDL   = 0xEC;  //P0.0~P0.3 IO模式控制，00:施密特输入，无上拉，01：输入，有上拉，10：推挽输出，11：开漏输出
sfr  P1MDL   = 0xED;  //P1.0~P1.3
sfr  P2MDL   = 0xEE;  //P2.0~P2.3
sfr  P3MDL   = 0xEF;  //P3.0~P3.3
sfr  P0MDH   = 0xFC;  //P0.4~P0.7
sfr  P1MDH   = 0xFD;  //P1.4~P1.7
sfr  P2MDH   = 0xFE;  //P2.4~P2.7
sfr  P3MDH   = 0xFF;  //P3.4~P3.7

#if  ASM == 1
xP4      EQU  0FF94H
xP9      EQU  0FF99H   
xP10     EQU  0FF9AH   
xP4MDL   EQU  0FFA4H  // P4.0~P4.3
xP4MDH   EQU  0FFB4H  // P4.4~P4.7
xP9MDL   EQU  0FFA9H 
xP10MDL  EQU	0FFEAH 
xP0AEN   EQU  0FFC0H
xP1AEN   EQU  0FFC1H
xP2AEN   EQU  0FFC2H
xP3AEN   EQU  0FFC3H   
xP4AEN   EQU  0FFC4H 
xP9AEN   EQU  0FFC9H 
#else
#define  xP4      (*(volatile unsigned char xdata *)0xFF94)
#define  xP9      (*(volatile unsigned char xdata *)0xFF99)
#define  xP10     (*(volatile unsigned char xdata *)0xFF9A)
#define  xP4MDL   (*(volatile unsigned char xdata *)0xFFA4)
#define  xP4MDH   (*(volatile unsigned char xdata *)0xFFB4)
#define  xP9MDL   (*(volatile unsigned char xdata *)0xFFA9)
#define  xP10MDL	(*(volatile unsigned char xdata *)0xFFEA)
#define	 xP0AEN   (*(volatile unsigned char xdata *)0xFFC0)
#define	 xP1AEN   (*(volatile unsigned char xdata *)0xFFC1)
#define	 xP2AEN   (*(volatile unsigned char xdata *)0xFFC2)
#define  xP3AEN   (*(volatile unsigned char xdata *)0xFFC3)
#define	 xP4AEN   (*(volatile unsigned char xdata *)0xFFC4)
#define	 xP9AEN   (*(volatile unsigned char xdata *)0xFFC9)
#endif
 


/****************************UART0***************************************************************/
sfr  SBUF0   = 0x99;    // 接收发送缓存
sfr  SCON0   = 0x98;    // 控制寄存器
sfr  BRCON0  = 0x8E;    // 波特率控制寄存器
sfr  BRTIM0  = 0x8F;    // 波特率设置寄存器
sbit S0M0    = SCON0^7;
sbit S0M1    = SCON0^6;
sbit S0M2    = SCON0^5;
sbit S0REN   = SCON0^4;
sbit S0TB8   = SCON0^3;
sbit S0RB8   = SCON0^2;
sbit S0TI    = SCON0^1;
sbit S0RI    = SCON0^0;

/****************************UART1***************************************************************/
sfr  SCON1   = 0xF1;
sfr  SBUF1   = 0xF2;
#if  ASM == 1
xBRCON1 EQU  0FFCEH
xBRTIM1 EQU  0FFCFH
#else
#define xBRCON1  (*(volatile unsigned char xdata *)0xFFCE)
#define xBRTIM1  (*(volatile unsigned char xdata *)0xFFCF)
#endif

/*********************RTC**********************************************************************/
sfr	RTCSEL  = 0xBE;
sfr RTCDATA = 0xBF;

/***********************KBI********************************************************************/
sfr  KBIFLG  = 0x9E;  

#if  ASM == 1
xKBICON   EQU  0FFAAH   // 设置对应的P1[7:0]为输入
xKBIWKP   EQU  0FFABH   // KBI唤醒极性设置寄存器
xKBIRMP   EQU  0FFACH   // KBI键盘重映射寄存器
#else
#define  xKBICON  (*(volatile unsigned char xdata *)0xFFAA)  // 设置对应的P1[7:0]为输入
#define  xKBIWKP  (*(volatile unsigned char xdata *)0xFFAB)  // KBI唤醒极性设置寄存器
#define  xKBIRMP  (*(volatile unsigned char xdata *)0xFFAC)  // KBI键盘重映射寄存器
#endif

/*********************PWM**********************************************************************/
#if  ASM == 1
xPWMPSC 	EQU 	0FF79H
xPWMCN		EQU 	0FF7AH
xPWMP			EQU		0FF7BH
xPWM0D		EQU		0FF7CH
xPWM1D		EQU		0FF7DH
xPWM2D		EQU		0FF7EH
xPWM3D		EQU		0FF7FH
#else
#define  xPWMPSC  (*(volatile unsigned char xdata *)0xFF79)
#define  xPWMCN   (*(volatile unsigned char xdata *)0xFF7A)
#define  xPWMP    (*(volatile unsigned char xdata *)0xFF7B)
#define  xPWM0D   (*(volatile unsigned char xdata *)0xFF7C)
#define  xPWM1D	  (*(volatile unsigned char xdata *)0xFF7D)
#define  xPWM2D	  (*(volatile unsigned char xdata *)0xFF7E)
#define  xPWM3D	  (*(volatile unsigned char xdata *)0xFF7F)
#endif

/*********************TIME************************************************************************/
//Timer2 接口寄存器
sfr   T2CON1  = 0xC8;	  //T2 控制，TF2,EXF2,RCLK0,TCLK0,EXEN2,TR2,C/T2,CP/R2

sbit  TF2     = T2CON1^7;
sbit  EXF2    = T2CON1^6;
sbit  RCLK    = T2CON1^5;
sbit  TCLK    = T2CON1^4;
sbit  RCPFEN2 = T2CON1^3;
sbit  TR2     = T2CON1^2;
sbit  CT2     = T2CON1^1;
sbit  CPRL2   = T2CON1^0;

sfr  RCAP2L  = 0xCA;	//Cap 的低字节
sfr  RCAP2H  = 0xCB;	//Cap 的高字节
sfr  TL2  = 0xCC;  //定时器初值L
sfr  TH2  = 0xCD;  //定时器初值H

#if  ASM == 1
xTIMPRS   EQU  0FFCAH   // Timer预分频控制寄存器
xT2CON2   EQU  0FFCBH
#else
#define  xTIMPRS   (*(volatile unsigned char xdata *)0xFFCA)   // Timer预分频控制寄存器
#define  xT2CON2   (*(volatile unsigned char xdata *)0xFFCB)
#endif


/***********************CRT***********************************************************************************/
//载波Timer接口寄存器
sfr  CRTCON1   = 0xE1;	//载波定时器控制，CRTEN,CRTMODE,CRTEXEN,CRTOVEN,REMSYN,REMOPS,CRTEXF,CRTF
sfr  CRTCON2   = 0xE2;	//载波定时器分频系数：CRTCKD3,CRTCKD2,CRTCKD1,CRTCKD0
sfr  CRTCNT    = 0xE3;	//载波定时器计数，CRTCNT
sfr  CRTDATA0  = 0xE4;	//载波定时器初值，CRTDATA0
sfr  CRTDATA1  = 0xE5;	//载波定时器初值，CRTDATA1

/**********************T168********************************************************************/
sfr  T168CON    = 0xE8;
sfr  T168DATA1  = 0xE9;
sfr  T168DATA0  = 0xEA;

/***********************IIC***********************************************************/
sfr  IIC0CON  = 0xC0;    // IIC控制寄存器
sfr  IIC0STA  = 0xC1;    // IIC状态寄存器
sfr  IIC0DAT  = 0xC2;    // 接收发送缓冲寄存器
sfr  IIC0ADDR = 0xC3;    // 从机地址
sfr	 SMBUSSEL = 0xC4;
sfr	 SMBUSDAT = 0xC5;

sbit  IICENS1 = IIC0CON^6;
sbit  IICSTA  = IIC0CON^5;
sbit  IICSTO	= IIC0CON^4;
sbit  IICSI		= IIC0CON^3;
sbit  IICAA   = IIC0CON^2;


/***********************SPI************************************************************/
sfr  SPICON0 = 0xF8;    // SPI控制器0
sfr  SPICON1 = 0xF9;    // SPI控制器1
sfr  SPIFLG  = 0xFA;    // SPI标志寄存器
sfr  SPIBUF  = 0xFB;    // SPI收发缓冲寄存器

/********************ACMP**************************************************************/
sfr  CP0CON  = 0xAE;  // 模拟比较器控制与状态
sfr	 CP0VRCON = 0xAF;  // 模拟比较器参考电压控制 

#if  ASM == 1
xCP0CFG   EQU  0FFADH   // 
#else
#define  xCP0CFG   (*(volatile unsigned char xdata *)0xFFAD)   
#endif 

/********************LCD****************************************************************/
#if	ASM == 1
//LCD 寄存器
xLCDCON     EQU  0FF80H   // LCDEn,--,FCKS1,FCKS0,--,BIAS,DUTY[1:0]
xLCDPCON    EQU  0FF81H   
xLCDTKCON   EQU  0FF82H   // TKEN,TKMOD,--,--,TKFS[1:0],--,--
xTKADDR0    EQU  0FF84H   // H3bit--com, L5bit, SEG
xLCDDATA0   EQU  0FF00H
xLCDDATA1   EQU  0FF01H
xLCDDATA2   EQU  0FF02H
xLCDDATA3   EQU  0FF03H
xLCDDATA4   EQU  0FF04H
xLCDDATA5   EQU  0FF05H
xLCDDATA6   EQU  0FF06H
xLCDDATA7   EQU  0FF07H 
xLCDDATA8   EQU  0FF08H
xLCDDATA9   EQU  0FF09H
xLCDDATA10  EQU  0FF0AH
xLCDDATA11  EQU  0FF0BH
xLCDDATA12  EQU  0FF0CH
xLCDDATA13  EQU  0FF0DH
xLCDDATA14  EQU  0FF0EH
xLCDDATA15  EQU  0FF0FH 
xLCDDATA16  EQU  0FF10H
xLCDDATA17  EQU  0FF11H
xLCDDATA18  EQU  0FF12H
xLCDDATA19  EQU  0FF13H
xLCDDATA20  EQU  0FF14H
xLCDDATA21  EQU  0FF15H
xLCDDATA22  EQU  0FF16H
xLCDDATA23  EQU  0FF17H 
xLCDDATA24  EQU  0FF18H
xLCDDATA25  EQU  0FF19H
xLCDDATA26  EQU  0FF1AH
xLCDDATA27  EQU  0FF1BH
xLCDDATA28  EQU  0FF1CH
xLCDDATA29  EQU  0FF1DH
xLCDDATA30  EQU  0FF1EH
xLCDDATA31  EQU  0FF1FH 

#else
//LCD 寄存器
#define	xLCDCON     (*(volatile unsigned char xdata *)0xFF80)   //LCDEn,--,FCKS1,FCKS0,--,BIAS,DUTY[1:0]
#define	xLCDPCON    (*(volatile unsigned char xdata *)0xFF81)   
#define	xLCDTKCON   (*(volatile unsigned char xdata *)0xFF82)   //TKEN,TKMOD,--,--,TKFS[1:0],--,TK2EN,TK1EN
#define	xTKADDR0    (*(volatile unsigned char xdata *)0xFF84)   //H3bit--com, L5bit, SEG
#define	xLCDDATA0   (*(volatile unsigned char xdata *)0xFF00)		
#define	xLCDDATA1   (*(volatile unsigned char xdata *)0xFF01)
#define	xLCDDATA2   (*(volatile unsigned char xdata *)0xFF02)
#define	xLCDDATA3   (*(volatile unsigned char xdata *)0xFF03)
#define	xLCDDATA4   (*(volatile unsigned char xdata *)0xFF04)
#define	xLCDDATA5   (*(volatile unsigned char xdata *)0xFF05)
#define	xLCDDATA6   (*(volatile unsigned char xdata *)0xFF06)
#define	xLCDDATA7   (*(volatile unsigned char xdata *)0xFF07) 
#define	xLCDDATA8   (*(volatile unsigned char xdata *)0xFF08)
#define	xLCDDATA9   (*(volatile unsigned char xdata *)0xFF09)
#define	xLCDDATA10  (*(volatile unsigned char xdata *)0xFF0A)
#define	xLCDDATA11  (*(volatile unsigned char xdata *)0xFF0B)
#define	xLCDDATA12  (*(volatile unsigned char xdata *)0xFF0C)
#define	xLCDDATA13  (*(volatile unsigned char xdata *)0xFF0D)
#define	xLCDDATA14  (*(volatile unsigned char xdata *)0xFF0E)
#define	xLCDDATA15  (*(volatile unsigned char xdata *)0xFF0F) 
#define	xLCDDATA16  (*(volatile unsigned char xdata *)0xFF10)
#define	xLCDDATA17  (*(volatile unsigned char xdata *)0xFF11)
#define	xLCDDATA18  (*(volatile unsigned char xdata *)0xFF12)
#define	xLCDDATA19  (*(volatile unsigned char xdata *)0xFF13)
#define	xLCDDATA20  (*(volatile unsigned char xdata *)0xFF14)
#define	xLCDDATA21  (*(volatile unsigned char xdata *)0xFF15)
#define	xLCDDATA22  (*(volatile unsigned char xdata *)0xFF16)
#define	xLCDDATA23  (*(volatile unsigned char xdata *)0xFF17) 
#define	xLCDDATA24  (*(volatile unsigned char xdata *)0xFF18)
#define	xLCDDATA25  (*(volatile unsigned char xdata *)0xFF19)
#define	xLCDDATA26  (*(volatile unsigned char xdata *)0xFF1A)
#define	xLCDDATA27  (*(volatile unsigned char xdata *)0xFF1B)
#define	xLCDDATA28  (*(volatile unsigned char xdata *)0xFF1C)
#define	xLCDDATA29  (*(volatile unsigned char xdata *)0xFF1D)
#define	xLCDDATA30  (*(volatile unsigned char xdata *)0xFF1E)
#define	xLCDDATA31  (*(volatile unsigned char xdata *)0xFF1F) 

#endif


/*********************ADC*******************************************************/
sfr  ADCON    = 0xD8;
sfr	 ADRL	    = 0xD9;
sfr	 ADRH 	  = 0xDA;

#if	ASM == 1
xADCFG		EQU		0FFAEH
#else
#define	xADCFG  (*(volatile unsigned char xdata *)0xFFAE) 
#endif

/******************PINMUX************************************************************/
#if  ASM == 1
xLCDPEN0  EQU  0FF20H   // LCD驱动管脚允许位寄存器0  1816-->P3端口
xLCDPEN1  EQU  0FF21H   // LCD驱动管脚允许位寄存器1  1816-->P0端口
xLCDPEN2  EQU  0FF22H   // LCD驱动管脚允许位寄存器2  1816-->P4端口
xLCDPEN3  EQU  0FF23H   // LCD驱动管脚允许位寄存器3  1816-->P1端口
xLCDPEN4  EQU  0FF24H   // LCD驱动管脚允许位寄存器4  1816-->P2端口
xIOMUX0   EQU  0FFE0H   // I2C,--,CPOE,BUZEN,NBUZEN,WTIRQOE,PWMEN,--
xIOMUX1   EQU  0FFE1H   // --,--,--,--,NBUZEN_1,BUZEN_1,WTIRQOE_1,PWMEN_1
xIOMUX2   EQU  0FFE2H 

#else

#define  xLCDPEN0  (*(volatile unsigned char xdata *)0xFF20)   // LCD驱动管脚允许位寄存器0  1816-->P3端口
#define  xLCDPEN1  (*(volatile unsigned char xdata *)0xFF21)   // LCD驱动管脚允许位寄存器1  1816-->P0端口
#define  xLCDPEN2  (*(volatile unsigned char xdata *)0xFF22)   // LCD驱动管脚允许位寄存器2  1816-->P4端口
#define  xLCDPEN3  (*(volatile unsigned char xdata *)0xFF23)   // LCD驱动管脚允许位寄存器3  1816-->P1端口
#define  xLCDPEN4  (*(volatile unsigned char xdata *)0xFF24)   // LCD驱动管脚允许位寄存器4  1816-->P2端口
#define  xIOMUX0   (*(volatile unsigned char xdata *)0xFFE0)   // I2C,--,CPOE,BUZEN,NBUZEN,WTIRQOE,PWMEN,--
#define  xIOMUX1   (*(volatile unsigned char xdata *)0xFFE1)   // --,--,--,--,NBUZEN_1,BUZEN_1,WTIRQOE_1,PWMEN_1
#define  xIOMUX2   (*(volatile unsigned char xdata *)0xFFE2) 
#endif

/************************FLASH IAP ****************************************************************************************/
sfr  FSHADRH  = 0xD1;
sfr  FSHADRL  = 0xD2;
sfr  FSHDAT   = 0xD3;
sfr  FSHCON  = 0xD4;
sfr  FSHKEY  = 0xD5;
sfr	 FSHTIM	 = 0xD6;

/*************************驱动能力设置 *******************************************/
#if ASM == 1
xLEDDCFG  EQU 	0FFBFH
#else
#define  xLEDDCFG  (*(volatile unsigned char xdata *)0xFFBF) 
#endif

/*************************TEST************************************/
#if  ASM == 1
xTESTCON  EQU  0FFAFH   // 测试控制寄存器，测试脚,LVR_TE,SysRst_TE,CKOS[1:0],CKTE
xTESTCON2 EQU  0FF9FH
#else
#define  xTESTCON   (*(volatile unsigned char xdata *)0xFFAF)   //测试控制寄存器，测试脚,LVR_TE,SysRst_TE,CKOS[1:0],CKTE
#define  xTESTCON2  (*(volatile unsigned char xdata *)0xFF9F)
#endif

#endif