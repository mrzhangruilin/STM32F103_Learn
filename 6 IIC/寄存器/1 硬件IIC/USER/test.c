#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"
void IIC_init(void)
{
	RCC->APB2ENR |= 1<<3;		//GPIOBʱ��ʹ��
	RCC->APB1ENR |= 1<<21;		//IICʱ��ʹ��
	
	GPIOB->CRL &= 0x00FFFFFF;	
	GPIOB->CRL |= 0xFF000000;	//PB6 PB7���ù����������
	
	I2C1->CR1 |= 1<<15;//��λ
	I2C1->CR1 &= ~(1<<15);//�ر�IIC1��λ
	I2C1->CR1 |= 1<<0;//����IICģ��
	
	I2C1->CCR |= (360<<0);		//36MhzƵ�ʣ�CCR360������100kHz��SCLƵ��
	I2C1->TRISE |= (36+1<<0);	//36MhzƵ�ʣ�TRISE37���������ʱ��1us��1Mhz
	I2C1->CR2 |= 36<<0;			//36Mhz��ʱ��
	I2C1->CR1 |= (1<<0);		//0-IICʹ��
	I2C1->CR1 |= (1<<10);		//10-Ӧ��ʹ��	
}

void AT24C02_WriteByte(char add, char byte)	//addr�ǵ�ַ��byte��Ҫ���͵�����
{
	int j;
	I2C1->CR1 |= 1<<10;			//��Ӧ��
	while(I2C1->SR2 & 1<<1);	//�ȴ����߿���
	I2C1->CR1 |= (1<<8);		//��ʼ��������
	while(!(I2C1->SR1&1<<0));	//�ȴ���ʼ��������
	
	j=I2C1->SR1;				//��SR
	I2C1->DR = 0x50<<1;			//AT24C02��ַ1010 000;���һλΪ0�����뷢����ģʽ
	while(!(I2C1->SR1&1<<1));	//�ȴ���ַ���ͽ���
	j = I2C1->SR1;				//��ȡSR1��Ȼ���ȡSR2�����ADDRλ
	j = I2C1->SR2;
	
	I2C1->DR = add;				
	while(!(I2C1->SR1&1<<7));	//�ȴ����ݼĴ�����
	I2C1->DR = byte;			//д���ݽ�ȥ
	while(!(I2C1->SR1&1<<2));	//�ȴ�BTF
	
	I2C1->CR1 |= (1<<9);		//ֹͣ��������
	delay_ms(2);
}

char AT24C02_ReadByte(char add)	//addr�ǵ�ַ��byte��Ҫ���͵�����
{
	char data;
	char j;
	
	I2C1->CR1 |= 1<<10;			//��Ӧ��
	while(I2C1->SR2 & 1<<1);	//�ȴ����߿���
	
	I2C1->CR1 |= (1<<8);		//��ʼ��������
	while(!(I2C1->SR1 & 1<<0));	//�ȴ���ʼ��������
	j = I2C1->SR1;
	
	I2C1->DR = 0x50<<1;			//AT24C02��ַ1010 000;���һλΪ0�����뷢����ģʽ
	while(!(I2C1->SR1 & 1<<1));	//�ȴ�������ַ���ͽ���
	j = I2C1->SR1;
	j = I2C1->SR2;
	

	I2C1->DR = add;		
	while(!(I2C1->SR1 & 1<<2));	//�ȴ���ȡ��ַ���ͽ���
	/**********���²�����ʼ����**********/
	I2C1->CR1 |= (1<<8);		//��ʼ��������
	while(!(I2C1->SR1&1<<0));	//�ȴ���ʼ��������
	
	I2C1->DR = (0x50<<1) | (1<<0);	//AT24C02��ַ1010 000;//���һλΪ1�����������ģʽģʽ
	while(!(I2C1->SR1&1<<1));	//�ȴ���ַ���ͽ���
	j = I2C1->SR1;
	j = I2C1->SR2;
	
	while(!(I2C1->SR1&1<<6));	//�ȴ����ݼĴ����ǿ�
	I2C1->CR1 &= ~(1<<10);		//��һ���ֽڣ���Ӧ�𣬶����byebye
	data = (char)I2C1->DR;
	
	
	I2C1->CR1 |= (1<<9);		//ֹͣ��������
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
		printf("����00��%d\n" , data[0]);
		printf("����01��%d\n" , data[1]);
		printf("����02��%d\n" , data[2]);
		printf("����03��%d\n" , data[3]);
		delay_ms(500);
	}	 
} 






