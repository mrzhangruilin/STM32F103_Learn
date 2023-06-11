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

//���Ĵ�����дֵ
void RC522_WriteReg(u8 addr , u8 data)
{
	SPI_NSS_0;				//Ƭѡ
	
	data = SPI_ReadWriteByte((addr<<1)&0x7E);
	SPI_ReadWriteByte(data);
	SPI_NSS_1;
}

u8 RC522_ReadReg(u8 addr)
{
	u8 data;
	
	SPI_NSS_0;				//Ƭѡ
	
	SPI_ReadWriteByte(addr<<1 | 0x80);
	data = SPI_ReadWriteByte(0xff);
	SPI_NSS_1;
	
	return data;
}

void RC522_SetBitReg(u8 addr , u8 bit)
{
	uint8_t temp;

	temp = RC522_ReadReg(addr);			/* ��ȡ�Ĵ�����ǰֵ */
	RC522_WriteReg( addr, temp|bit );	/* ��ָ��λ������λ�������ٽ�ֵд��Ĵ��� */
}

void RC522_ClearBitReg(u8 addr , u8 bit)
{
	uint8_t temp;

	temp = RC522_ReadReg( addr );			/* ��ȡ�Ĵ�����ǰֵ */
	RC522_WriteReg( addr, temp&(~bit) );	/* ��ָ��λ������λ�������ٽ�ֵд��Ĵ��� */
}

/*
//function:��λRC522
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
//function: ��������
*/
void RC522_AntennaOn()
{
	if(!RC522_ReadReg(TxControlReg)&0x03)
	{
		RC522_SetBitReg(TxControlReg,0x03);
	}
}

/*
//function:�ر�����
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
//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
//����˵����Command[IN]:RC522������
//          pInData[IN]:ͨ��RC522���͵���Ƭ������
//          InLenByte[IN]:�������ݵ��ֽڳ���
//          pOutData[OUT]:���յ��Ŀ�Ƭ��������
//          *pOutLenBit[OUT]:�������ݵ�λ����
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
    
	//i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
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
//��    �ܣ�Ѱ��
//����˵��: req_code[IN]:Ѱ����ʽ
//                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
//                0x26 = Ѱδ��������״̬�Ŀ�
//          pTagType[OUT]����Ƭ���ʹ���
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char RC522_PcdRequest(u8 req_code , u8 *pTagType)
{
	char status;
	unsigned int unLen;
	u8 ucComMF522Buf[MAXRLEN];
	
	RC522_ClearBitReg(Status2Reg , 0x08);	//�Ĵ������㣬״̬�Ĵ���2��Ϊ0x08��3��λ�ġ�1��������������ͨ�Ŷ������ܣ���0��ʾ�������״̬��
	RC522_WriteReg(BitFramingReg , 0x07);	//00000111��ʾ���������һ���ֽڵ�����λ
	RC522_SetBitReg(TxControlReg , 0x03);	
	
	status = RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
	
	if ((status == MI_OK) && (unLen == 0x10))//����ɹ�ͨ�ŷ���pk�����򷵻ش���
   {    
       *pTagType     = ucComMF522Buf[0];
       *(pTagType+1) = ucComMF522Buf[1];
   }
   else
   {   status = MI_ERR;   }
   
   return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�����ײ
//����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////  
char RC522_PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    RC522_ClearBitReg(Status2Reg,0x08);	//�������״̬
    RC522_WriteReg(BitFramingReg,0x00);	//�������һ���ֽ�����λ
    RC522_ClearBitReg(CollReg,0x80);	//��ʼ����ײ���Ĵ���
 
    ucComMF522Buf[0] = PICC_ANTICOLL1; //0x93����ײģʽ
    ucComMF522Buf[1] = 0x20;

    status = RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK) //����ײ������ɡ�
    {
    	 for (i=0; i<4; i++)//У����Ϣ//�����õ���4λ���ǿ�����Ϣ
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

//��MF522����CRC16����
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
//��    �ܣ����Ƭ��������״̬
//��    ��: �ɹ�����MI_OK
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



