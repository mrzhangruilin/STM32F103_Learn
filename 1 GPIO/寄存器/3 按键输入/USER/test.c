#include "stm32f10x.h" 

int main(void)
{ 
 RCC->APB2ENR |= 1<<2;    //ʹ��GPIOA��ʱ��
 GPIOA->CRL &= 0;     //��տ���PA0�Ķ˿�λ
 GPIOA->CRL |= 0x88881111;   //����PA0Ϊͨ������������ٶ�Ϊ10M��PA4��Ϊ����������
 GPIOA->ODR |= 0xFF;     //PA4����Ϊ��������
 
   while(1)
 {
  if(GPIOA->IDR &(1<<4)) //PAin(4)==0�ж��Ƿ���
  {
	GPIOA->ODR |= (1<<0);  //��1
  }else
  {
	  GPIOA->ODR &= ~(1<<0);  //����
   
  }
  if(GPIOA->IDR &(1<<5)) //�ж��Ƿ���
  {
	GPIOA->ODR |= (1<<1);  //��1
  }else
  {
	  GPIOA->ODR &= ~(1<<1);  //����
   
  }
  if(GPIOA->IDR &(1<<6)) //�ж��Ƿ���
  {
   GPIOA->ODR |= (1<<2);  //��1
  }else
  {
	  GPIOA->ODR &= ~(1<<2);  //����
   
  }
  if(GPIOA->IDR &(1<<7)) //�ж��Ƿ���
  {
    GPIOA->ODR |= (1<<3);  //��1	
  }else
  {
	  GPIOA->ODR &= ~(1<<3);  //����
  
  }
 } 
} 





