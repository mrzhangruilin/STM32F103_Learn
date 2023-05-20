#include "bsp_spi.h"

void SPI_GPIO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_RST_CLK, ENABLE);
	
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(SPI_RST_PORT, &GPIO_InitStructure);
		
	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_MISO_CLK, ENABLE);
	
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(SPI_MISO_PORT, &GPIO_InitStructure);
		
	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_MOSI_CLK, ENABLE);
	
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStructure);
		
	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_SCK_CLK, ENABLE);
	
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(SPI_SCK_PORT, &GPIO_InitStructure);
		
	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_NSS_CLK, ENABLE);
	
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_NSS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(SPI_NSS_PORT, &GPIO_InitStructure);
}




////////////////////////
//SPI��λ�շ�һ���ֽ�
//�͵�ƽ�ڼ��Ƴ�һλ���ߵ�ƽ�ڼ��ȡһλ
//��ֻ�����ֽ�ʱ��Ӧ����0xff
//
//function���շ�һ���ֽ�
//@byte:Ҫ���͵��ֽ�
//return�����յ����ֽ�
////////////////////////
unsigned char SPI_ReadWriteByte(unsigned char byte)
{
	int i,rByte;

	for(i=0;i<8;i++)
    {
		SCK_L;
		rByte <<= 1;
		if(byte&0x80)
        	MOSI_H;
		else
			MOSI_L;
        SCK_H;
		if(READ_MISO == 1)
			rByte |=1;
        byte <<= 1;
    }
	SCK_H;
	
	return rByte;
}

////////////////////////
//SPI_NSSѡ��
////////////////////////
void SPI_NSS_Set(void)
{
	NSS_L;
}

////////////////////////
//SPI_NSSȡ��ѡ��
////////////////////////
void SPI_NSS_ReSet(void)
{
	NSS_H;
}

