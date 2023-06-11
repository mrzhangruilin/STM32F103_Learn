#include "usart.h"	  

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

/**
	*	�ض���fputc����

*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
//////////////////////////////////////////////////////////////////


#if EN_USART1_RX   //���ʹ���˽���

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void USART1_IRQHandler(void)
{
	u8 res;	

	if(USART1->SR&(1<<5))	//���յ�����
	{	 
		res = USART1->DR;			/* ��ȡDR�Ĵ���֮���Զ������־λ */
	}

} 
#endif

/**
*function:	��ʼ������1
*para��			pclk������1��ʱ�ӣ�bound����1������
*/
void Usart1_Init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);	//�õ�USARTDIV
	mantissa=temp;				 									//�õ���������
	fraction=(temp-mantissa)*16; 						//�õ�С������	 
	mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   									//ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  									//ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;									//IO״̬����
	GPIOA->CRH|=0X000008B0;									//IO״̬���� 
	RCC->APB2RSTR|=1<<14;   								//��λ����1
	RCC->APB2RSTR&=~(1<<14);								//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; 									//����������	 
	USART1->CR1|=0X200C;  									//1λֹͣ,��У��λ.
#if EN_USART1_RX		  									//���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    									//���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);						//��2��������ȼ� 
#endif
}
