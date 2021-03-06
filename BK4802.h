#define _BK4802_H
#ifdef _BK4802_H
/*-------------------------------------------------------------------------
*函数：BK_4802_Init  4802初使化
*-------------------------------------------------------------------------*/
void BK4802_Init();
void BK4802_RX();
/*-------------------------------------------------------------------------
*函数：BK4802_RXtoTX  接收转发射
*-------------------------------------------------------------------------*/
void BK4802_RXtoTX();
/*-------------------------------------------------------------------------
*函数：BK4802_TXtoRX  发射转接收
*-------------------------------------------------------------------------*/
void BK4802_TXtoRX();
/*-------------------------------------------------------------------------
*函数：BK4802_RssiAndSnr  SQ值获取
*返回值：SQ值
*-------------------------------------------------------------------------*/
u16 BK4802_RssiAndSnr();
/*-------------------------------------------------------------------------
*函数：BK4802_ASQ  ASQ值获取
*返回值：ASQ值
*-------------------------------------------------------------------------*/
u16 BK4802_ASQ();

#endif