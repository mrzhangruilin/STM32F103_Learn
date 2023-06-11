#include "bsp_spi.h"

//SPI1
//RC522_RST	PA0		ͨ������
//SPI_NSS	PA4		ͨ������
//SPI_CLK	PA5		���츴��
//SPI_MISO	PA6		����������
//SPI_MOSI	PA7		���츴��
void SPI_Init()
{
	//GPIO����
	RCC->APB2ENR |= 1<<2;		//GPIOAʱ��
	GPIOA->CRL &= 0x00000FF0;
	GPIOA->CRL |= 0xB8B30003;	//PA4ͨ������������ֶ�����Ƭѡ
	GPIOA->ODR |= 0XF<<4 | 1<<3;	//PA5.6.7������PA0.4����

	//SPI����
	RCC->APB2ENR |= 1<<12;	//SPIʱ��
	
	//ʱ�Ӽ���CPOLλ����ʱ�͵�ƽ
	//ʱ�Ӳ�����Ϊʱ�������أ������أ�
	SPI1->CR1 |= 1<<9; 		//���nss����
	SPI1->CR1 |= 1<<8; 		//Ƭѡ
	SPI1->CR1 |= 7<<3; 		//Fsck=Fcpu/256
	SPI1->CR1 |= 1<<2;		//����Ϊ���豸
	SPI1->CR1 |= 1<<1; 		//����ģʽ��SCKΪ1 CPOL=1
	SPI1->CR1 |= 1<<0; 		//���ݲ����ӵڶ���ʱ����ؿ�ʼ,CPHA=1 
	
	SPI1->CR1 |= 1<<6;		//ʹ��SPI
	
	SPI_ReadWriteByte(0xff);
}

u8 SPI_ReadWriteByte(u8 data)
{
	while((SPI1->SR&1<<1) == 0);	//�ȴ���������

	
	SPI1->DR = data;
	
	while((SPI1->SR&1<<1) == 0);	//�ȴ�������һ��byte
	
	return SPI1->DR;
}
