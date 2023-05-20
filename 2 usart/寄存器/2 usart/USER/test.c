#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"


//void USART1_IRQHandler(void)		//USART1�����жϴ�����
//{
//	u8 data;
//	data = USART1->DR;		//��ȡ���յ�������
//	USART1->DR = data;      
//}

void usart1_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	//ʱ��ʹ��
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���1ʱ��
	//��������
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬����
	GPIOA->ODR|=(1<<10);	//RX����
	
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	 
	
	USART1->BRR=mantissa; // ����������
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	
	USART1->CR1|=1<<5;					//���ջ������ǿ��ж�ʹ��
	MY_NVIC_Init(0,0,USART1_IRQn,0);	//��2��������ȼ� 
	
}

void usart1_sendbyte(uint8_t byte)
{
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = byte;      	//дDR,����1����������
}



int main(void)
{			
	Stm32_Clock_Init(9);	//9��Ƶ��72Mhz
	delay_init(72);
	usart1_init(72,9600);	//usart1��ʼ��
	
	delay_ms(100);
  	while(1)
	{
		usart1_sendbyte(0x41);
	}	 
} 






