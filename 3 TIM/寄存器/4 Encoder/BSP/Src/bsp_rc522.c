#include "bsp_rc522.h"

void RC522_Init()
{
	SPI_Init();
	RC522_Reset();
	RC522_AntennaOff();
	RC522_AntennaOn();
	RC522_Config('A');
	
	delay_ms(20);
}

//往寄存器里写值
void RC522_WriteReg(u8 addr , u8 data)
{
	SPI_NSS_0;				//片选
	
	data = SPI_ReadWriteByte((addr<<1)&0x7E);
	SPI_ReadWriteByte(data);
	SPI_NSS_1;
}

u8 RC522_ReadReg(u8 addr)
{
	u8 data;
	
	SPI_NSS_0;				//片选
	
	SPI_ReadWriteByte(addr<<1 | 0x80);
	data = SPI_ReadWriteByte(0xff);
	SPI_NSS_1;
	
	return data;
}

void RC522_SetBitReg(u8 addr , u8 bit)
{
	uint8_t temp;

	temp = RC522_ReadReg(addr);			/* 获取寄存器当前值 */
	RC522_WriteReg( addr, temp|bit );	/* 对指定位进行置位操作后，再将值写入寄存器 */
}

void RC522_ClearBitReg(u8 addr , u8 bit)
{
	uint8_t temp;

	temp = RC522_ReadReg( addr );			/* 获取寄存器当前值 */
	RC522_WriteReg( addr, temp&(~bit) );	/* 对指定位进行清位操作后，再将值写入寄存器 */
}

/*
//function:复位RC522
//return:	MI_OK
*/
u8 RC522_Reset(void)
{
	RC522_RST_1;
	delay_us(1);
	RC522_RST_0;
	delay_us(1);
	RC522_RST_1;
	delay_us(1);
	RC522_WriteReg(CommandReg , PCD_RESETPHASE);
	delay_us(1);

	RC522_WriteReg(ModeReg , 0x3D);
	RC522_WriteReg(TReloadRegL , 30);
	RC522_WriteReg(TReloadRegH , 0);
	RC522_WriteReg(TModeReg , 0x8D);
	RC522_WriteReg(TPrescalerReg , 0x3E);
	RC522_WriteReg(TxAutoReg , 0x40);
	
	return MI_OK;
}

/*
//function: 开启天线
*/
void RC522_AntennaOn()
{
	if(!RC522_ReadReg(TxControlReg)&0x03)
	{
		RC522_SetBitReg(TxControlReg,0x03);
	}
}

/*
//function:关闭天线
*/
void RC522_AntennaOff()
{
	RC522_ClearBitReg(TxControlReg , 0x03);
}

char RC522_Config(u8 type)
{
	if(type == 'A')		//ISO14443_A
	{
		RC522_ClearBitReg(Status2Reg , 0x08);
		
		RC522_WriteReg(ModeReg , 0x3D);
		
		RC522_WriteReg(RxSelReg , 0x86);
		
		RC522_WriteReg(RFCfgReg , 0X7F);
		
		RC522_WriteReg(TReloadRegL , 30);
		RC522_WriteReg(TReloadRegH , 0);
		RC522_WriteReg(TModeReg , 0x8D);
		RC522_WriteReg(TPrescalerReg , 0x3E);
		
		delay_ms(10);
		RC522_AntennaOn();
	}
	
	return MI_OK;
}

/////////////////////////////////////////////////////////////////////
//功    能：通过RC522和ISO14443卡通讯
//参数说明：Command[IN]:RC522命令字
//          pInData[IN]:通过RC522发送到卡片的数据
//          InLenByte[IN]:发送数据的字节长度
//          pOutData[OUT]:接收到的卡片返回数据
//          *pOutLenBit[OUT]:返回数据的位长度
/////////////////////////////////////////////////////////////////////
char RC522_PcdComMF522(u8 Command, unsigned char *pInData, u8 InLenByte , unsigned char *pOutData, unsigned int *pOutLenBit)
{
	char status = MI_ERR;
    unsigned char irqEn   = 0x00;
    unsigned char waitFor = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;
    switch (Command)
    {
       case PCD_AUTHENT:
          irqEn   = 0x12;
          waitFor = 0x10;
          break;
       case PCD_TRANSCEIVE:
          irqEn   = 0x77;
          waitFor = 0x30;
          break;
       default:
         break;
    }
	
	RC522_WriteReg(ComIEnReg , irqEn|0x80);
	RC522_ClearBitReg(ComIrqReg , 0x80);
	RC522_WriteReg(CommandReg , PCD_IDLE);
	RC522_SetBitReg(FIFOLevelReg , 0x80);
	
	for (i=0; i<InLenByte; i++){RC522_WriteReg(FIFODataReg, pInData[i]);}
    RC522_WriteReg(CommandReg, Command);
   
    
    if (Command == PCD_TRANSCEIVE){RC522_SetBitReg(BitFramingReg,0x80);}
    
	//i = 600;//根据时钟频率调整，操作M1卡最大等待时间25ms
	i = 2000;
    do 
    {
         n = RC522_ReadReg(ComIrqReg);
         i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    RC522_ClearBitReg(BitFramingReg,0x80);
	
	if (i!=0)
    {    
         if(!(RC522_ReadReg(ErrorReg)&0x1B))
         {
             status = MI_OK;
             if (n & irqEn & 0x01)
             {   status = MI_NOTAGERR;   }
             if (Command == PCD_TRANSCEIVE)
             {
               	n = RC522_ReadReg(FIFOLevelReg);
              	lastBits = RC522_ReadReg(ControlReg) & 0x07;
                if (lastBits)
                {   *pOutLenBit = (n-1)*8 + lastBits;   }
                else
                {   *pOutLenBit = n*8;   }
                if (n == 0)
                {   n = 1;    }
                if (n > MAXRLEN)
                {   n = MAXRLEN;   }
                for (i=0; i<n; i++)
                {   pOutData[i] = RC522_ReadReg(FIFODataReg);    }
            }
         }
         else
         {   status = MI_ERR;   }
        
   }
   

   RC522_SetBitReg(ControlReg,0x80);           // stop timer now
   RC522_WriteReg(CommandReg,PCD_IDLE); 
   return status;
}

/////////////////////////////////////////////////////////////////////
//功    能：寻卡
//参数说明: req_code[IN]:寻卡方式
//                0x52 = 寻感应区内所有符合14443A标准的卡
//                0x26 = 寻未进入休眠状态的卡
//          pTagType[OUT]：卡片类型代码
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////
char RC522_PcdRequest(u8 req_code , u8 *pTagType)
{
	char status;
	unsigned int unLen;
	u8 ucComMF522Buf[MAXRLEN];
	
	RC522_ClearBitReg(Status2Reg , 0x08);	//寄存器清零，状态寄存器2置为0x08，3号位的“1”卡的所有数据通信都被加密，置0表示解除加密状态。
	RC522_WriteReg(BitFramingReg , 0x07);	//00000111表示不传输最后一个字节的所有位
	RC522_SetBitReg(TxControlReg , 0x03);	
	
	status = RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
	
	if ((status == MI_OK) && (unLen == 0x10))//如果成功通信返回pk，否则返回错误。
   {    
       *pTagType     = ucComMF522Buf[0];
       *(pTagType+1) = ucComMF522Buf[1];
   }
   else
   {   status = MI_ERR;   }
   
   return status;
}

/////////////////////////////////////////////////////////////////////
//功    能：防冲撞
//参数说明: pSnr[OUT]:卡片序列号，4字节
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////  
char RC522_PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    RC522_ClearBitReg(Status2Reg,0x08);	//解除加密状态
    RC522_WriteReg(BitFramingReg,0x00);	//传输最后一个字节所有位
    RC522_ClearBitReg(CollReg,0x80);	//初始化碰撞检测寄存器
 
    ucComMF522Buf[0] = PICC_ANTICOLL1; //0x93防冲撞模式
    ucComMF522Buf[1] = 0x20;

    status = RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK) //防冲撞流程完成。
    {
    	 for (i=0; i<4; i++)//校验信息//这里拿到是4位就是卡号信息
         {   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];
         }
         if (snr_check != ucComMF522Buf[i])
         {   status = MI_ERR;    }
    }
    
    RC522_SetBitReg(CollReg,0x80);
    return status;
}

//用MF522计算CRC16函数
void RC522_CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData)
{
    unsigned char i,n;
    RC522_ClearBitReg(DivIrqReg,0x04);
    RC522_WriteReg(CommandReg,PCD_IDLE);
    RC522_SetBitReg(FIFOLevelReg,0x80);
    for (i=0; i<len; i++){RC522_WriteReg(FIFODataReg, *(pIndata+i));}
    RC522_WriteReg(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = RC522_ReadReg(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOutData[0] = RC522_ReadReg(CRCResultRegL);
    pOutData[1] = RC522_ReadReg(CRCResultRegM);
}

/////////////////////////////////////////////////////////////////////
//功    能：命令卡片进入休眠状态
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////
char RC522_PcdHalt(void)
{
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    RC522_CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    return MI_OK;
}



