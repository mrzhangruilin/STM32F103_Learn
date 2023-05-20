#include "bsp_spi.h"

/*
Ӳ��SPI�ĳ�ʼ��
RC522_RST	PA1	�������
SPI1_SCK	PA5	���츴�����
SPI1_MOSI	PA7	���츴�����
SPI1_MISO	PA6	��������
SPI1_NSS	PA4	���츴�������Ӳ������
*/
void SPI1_Init(void)
{
	#define SPI_Hardware
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef	SPI_InitStructure;

	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(SPI_GPIO_Clock, ENABLE);
	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Mode = SPI_SCK_GPIO_MODE;
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SPI_SCK_GPIO_SPEED;
	GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = SPI_MOSI_GPIO_MODE;
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SPI_MOSI_GPIO_SPEED;
	GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = SPI_MISO_GPIO_MODE;
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SPI_MISO_GPIO_SPEED;
	GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = SPI_NSS_GPIO_MODE;
	GPIO_InitStructure.GPIO_Pin = SPI_NSS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SPI_NSS_GPIO_SPEED;
	GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStructure);

	/* ʹ��SPIʱ��*/
	RCC_APB2PeriphClockCmd(SPI_Clock, ENABLE);
	/* ����SPI*/
	SPI_InitStructure.SPI_BaudRatePrescaler = SPIx_BaudRatePrescaler;
	SPI_InitStructure.SPI_CPHA = SPIx_CPHA;
	SPI_InitStructure.SPI_CPOL = SPIx_CPOL;
	SPI_InitStructure.SPI_CRCPolynomial = SPIx_CRCPolynomial;
	SPI_InitStructure.SPI_DataSize = SPIx_DataSize;
	SPI_InitStructure.SPI_Direction = SPIx_Direction;
	SPI_InitStructure.SPI_FirstBit = SPIx_FirstBit;
	SPI_InitStructure.SPI_Mode = SPIx_Mode;
	SPI_InitStructure.SPI_NSS = SPIx_NSS;
	SPI_Init(SPI1 , &SPI_InitStructure);

	SPI_Cmd(SPI1 , ENABLE);
	SPI_NSS_ReSet();
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
	u8 retry=0;	 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//���ָ����SPI��־λ�������:���ͻ���ձ�־λ		  
	SPI_I2S_SendData(SPI1, byte); //ͨ������SPIx����һ������
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ   			
	retry = SPI_I2S_ReceiveData(SPI1);		    
	return retry; //����ͨ��SPIx������յ�����		
}

////////////////////////
//SPI_NSSѡ��
////////////////////////
void SPI_NSS_Set(void)
{
	GPIO_ResetBits(GPIOA , GPIO_Pin_4);
}

////////////////////////
//SPI_NSSȡ��ѡ��
////////////////////////
void SPI_NSS_ReSet(void)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
}

