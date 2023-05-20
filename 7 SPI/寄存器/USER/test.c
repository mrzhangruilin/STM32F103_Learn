#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "bsp_rc522.h"
#include "usart.h"

unsigned char g_ucTempbuf[4]; 
//SPI1
//SPI_RST	PA0		ͨ������
//SPI_NSS	PA4		ͨ������		�ֶ�����Ƭѡ
//SPI_CLK	PA5		���츴��
//SPI_MISO	PA6		����������
//SPI_MOSI	PA7		���츴��


int main(void)
{				 
	u8 status;
	
	Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	RC522_Init();

	printf("��ʼ���ɹ�\n");
  	while(1)
	{
		
		status = RC522_PcdRequest(PICC_REQALL , g_ucTempbuf);
		if(status!=MI_OK)continue;
		printf("����ײ");
		status = RC522_PcdAnticoll(g_ucTempbuf);		//����ײ
		if(status!=MI_OK)continue;
		
		printf("%d %d %d %d\n" , g_ucTempbuf[0] , g_ucTempbuf[1] , g_ucTempbuf[2] , g_ucTempbuf[3]);
		
		RC522_PcdHalt();   //���Ƭ��������״̬
	}	                              
} 







