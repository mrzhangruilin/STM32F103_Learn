#include "bsp_spi.h"

//SPI1
//RC522_RST	PA0		通用推挽
//SPI_NSS	PA4		通用推挽
//SPI_CLK	PA5		推挽复用
//SPI_MISO	PA6		带上拉输入
//SPI_MOSI	PA7		推挽复用
void SPI_Init()
{
	//GPIO配置
	RCC->APB2ENR |= 1<<2;		//GPIOA时钟
	GPIOA->CRL &= 0x00000FF0;
	GPIOA->CRL |= 0xB8B30003;	//PA4通用推挽输出，手动控制片选
	GPIOA->ODR |= 0XF<<4 | 1<<3;	//PA5.6.7上拉，PA0.4上拉

	//SPI配置
	RCC->APB2ENR |= 1<<12;	//SPI时钟
	
	//时钟极性CPOL位空闲时低电平
	//时钟采样点为时钟奇数沿（上升沿）
	SPI1->CR1 |= 1<<9; 		//软件nss管理
	SPI1->CR1 |= 1<<8; 		//片选
	SPI1->CR1 |= 7<<3; 		//Fsck=Fcpu/256
	SPI1->CR1 |= 1<<2;		//配置为主设备
	SPI1->CR1 |= 1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPI1->CR1 |= 1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1 
	
	SPI1->CR1 |= 1<<6;		//使能SPI
	
	SPI_ReadWriteByte(0xff);
}

u8 SPI_ReadWriteByte(u8 data)
{
	while((SPI1->SR&1<<1) == 0);	//等待发送区空

	
	SPI1->DR = data;
	
	while((SPI1->SR&1<<1) == 0);	//等待接收完一个byte
	
	return SPI1->DR;
}
