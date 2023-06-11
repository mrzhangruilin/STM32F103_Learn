#include "stm32f10x.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "bsp_matrix_keyboard.h"

int main(void)
{				
	uint8_t res;

	Stm32_Clock_Init(9);
	Delay_Init(72);
	Usart1_Init(72,115200);

	Matrix_Keyboard_Init();
	while(1)
	{
		res = Matrix_Keyboard_Scanf();
		if (res)
		{
			if (res<=9)
			{
				printf("%d" , res);
			}
			
			if (res == 10)
			{
				printf(" ");
			}
			
			if (res == 11)
			{
				printf("0");
			}

			if (res == 12)
			{
				printf("\r\n");
			}
			
			
		}
		
	}	 
} 






