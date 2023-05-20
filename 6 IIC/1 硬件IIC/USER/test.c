#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"
void IIC_init(void)
{
	RCC->APB2ENR |= 1<<3;		//GPIOB时钟使能
	RCC->APB1ENR |= 1<<21;		//IIC时钟使能
	
	GPIOB->CRL &= 0x00FFFFFF;	
	GPIOB->CRL |= 0xFF000000;	//PB6 PB7复用功能推挽输出
	
	I2C1->CR1 |= 1<<15;//复位
	I2C1->CR1 &= ~(1<<15);//关闭IIC1复位
	I2C1->CR1 |= 1<<0;//启用IIC模块
	
	I2C1->CCR |= (360<<0);		//36Mhz频率，CCR360，产生100kHz的SCL频率
	I2C1->TRISE |= (36+1<<0);	//36Mhz频率，TRISE37，最大上升时间1us，1Mhz
	I2C1->CR2 |= 36<<0;			//36Mhz的时钟
	I2C1->CR1 |= (1<<0);		//0-IIC使能
	I2C1->CR1 |= (1<<10);		//10-应答使能	
}

void AT24C02_WriteByte(char add, char byte)	//addr是地址，byte是要发送的数据
{
	int j;
	I2C1->CR1 |= 1<<10;			//打开应答
	while(I2C1->SR2 & 1<<1);	//等待总线空闲
	I2C1->CR1 |= (1<<8);		//起始条件产生
	while(!(I2C1->SR1&1<<0));	//等待起始条件发送
	
	j=I2C1->SR1;				//读SR
	I2C1->DR = 0x50<<1;			//AT24C02地址1010 000;最后一位为0，进入发送器模式
	while(!(I2C1->SR1&1<<1));	//等待地址发送结束
	j = I2C1->SR1;				//读取SR1，然后读取SR2，清除ADDR位
	j = I2C1->SR2;
	
	I2C1->DR = add;				
	while(!(I2C1->SR1&1<<7));	//等待数据寄存器空
	I2C1->DR = byte;			//写数据进去
	while(!(I2C1->SR1&1<<2));	//等待BTF
	
	I2C1->CR1 |= (1<<9);		//停止条件产生
	delay_ms(2);
}

char AT24C02_ReadByte(char add)	//addr是地址，byte是要发送的数据
{
	char data;
	char j;
	
	I2C1->CR1 |= 1<<10;			//打开应答
	while(I2C1->SR2 & 1<<1);	//等待总线空闲
	
	I2C1->CR1 |= (1<<8);		//起始条件产生
	while(!(I2C1->SR1 & 1<<0));	//等待起始条件发送
	j = I2C1->SR1;
	
	I2C1->DR = 0x50<<1;			//AT24C02地址1010 000;最后一位为0，进入发送器模式
	while(!(I2C1->SR1 & 1<<1));	//等待器件地址发送结束
	j = I2C1->SR1;
	j = I2C1->SR2;
	

	I2C1->DR = add;		
	while(!(I2C1->SR1 & 1<<2));	//等待读取地址发送结束
	/**********重新产生起始条件**********/
	I2C1->CR1 |= (1<<8);		//起始条件产生
	while(!(I2C1->SR1&1<<0));	//等待起始条件发送
	
	I2C1->DR = (0x50<<1) | (1<<0);	//AT24C02地址1010 000;//最后一位为1，进入接收器模式模式
	while(!(I2C1->SR1&1<<1));	//等待地址发送结束
	j = I2C1->SR1;
	j = I2C1->SR2;
	
	while(!(I2C1->SR1&1<<6));	//等待数据寄存器非空
	I2C1->CR1 &= ~(1<<10);		//读一个字节，不应答，读完就byebye
	data = (char)I2C1->DR;
	
	
	I2C1->CR1 |= (1<<9);		//停止条件产生
	delay_ms(2);
	return data;
}
int main(void)
{				
	char data[4];
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	IIC_init();
	
//	AT24C02_WriteByte(0x00, 0x41);
//	AT24C02_WriteByte(0x01, 0x42);
//	AT24C02_WriteByte(0x02, 0x44);
//	AT24C02_WriteByte(0x03, 0x48);
	
	delay_ms(2);
	
	data[0] = AT24C02_ReadByte(0x00);
	data[1] = AT24C02_ReadByte(0x01);
	data[2] = AT24C02_ReadByte(0x02);
	data[3] = AT24C02_ReadByte(0x03);

  	while(1)
	{
		printf("数据00：%d\n" , data[0]);
		printf("数据01：%d\n" , data[1]);
		printf("数据02：%d\n" , data[2]);
		printf("数据03：%d\n" , data[3]);
		delay_ms(500);
	}	 
} 






