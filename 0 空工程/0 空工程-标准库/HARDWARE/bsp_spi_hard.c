#include "bsp_spi.h"

/*
硬件SPI的初始化
RC522_RST	PA1	推挽输出
SPI1_SCK	PA5	推挽复用输出
SPI1_MOSI	PA7	推挽复用输出
SPI1_MISO	PA6	浮空输入
SPI1_NSS	PA4	推挽复用输出，硬件控制
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

	/* 使能SPI时钟*/
	RCC_APB2PeriphClockCmd(SPI_Clock, ENABLE);
	/* 配置SPI*/
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
//SPI移位收发一个字节
//低电平期间移出一位，高电平期间读取一位
//在只接收字节时，应发送0xff
//
//function：收发一个字节
//@byte:要发送的字节
//return：接收到的字节
////////////////////////
unsigned char SPI_ReadWriteByte(unsigned char byte)
{
	u8 retry=0;	 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//检查指定的SPI标志位设置与否:发送缓存空标志位		  
	SPI_I2S_SendData(SPI1, byte); //通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//检查指定的SPI标志位设置与否:接受缓存非空标志位   			
	retry = SPI_I2S_ReceiveData(SPI1);		    
	return retry; //返回通过SPIx最近接收的数据		
}

////////////////////////
//SPI_NSS选中
////////////////////////
void SPI_NSS_Set(void)
{
	GPIO_ResetBits(GPIOA , GPIO_Pin_4);
}

////////////////////////
//SPI_NSS取消选中
////////////////////////
void SPI_NSS_ReSet(void)
{
	GPIO_SetBits(GPIOA , GPIO_Pin_4);
}

