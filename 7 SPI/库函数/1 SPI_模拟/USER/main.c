#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "bsp_rc522.h"
#include "bsp_usart.h"

u8 SelectedSnr[4],DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
u8 bufr[16]={0};

int main(void)
{
	char status,i,j,snr;
	
	Stm32_Clock_Init(9);
	InitializeSystem();
	USART1_Init();
	
	printf("初始化成功\r\n");
	while(1)
	{
		status = PcdRequest(PICC_REQALL, SelectedSnr);
		if (status != MI_OK){continue;}
		status = PcdAnticoll(SelectedSnr);//防冲撞
		if (status != MI_OK){continue;}
		status = PcdSelect(SelectedSnr);
		if(status!=MI_OK){continue;}
		
		printf("卡的序列号：%d %d %d %d\n" , SelectedSnr[0], SelectedSnr[1], SelectedSnr[2], SelectedSnr[3]);
		
		for(snr = 0;snr<3;snr++)
		{
			status = PcdAuthState(KEYA, (snr*4+3), DefaultKey, SelectedSnr);// 校验扇区密码，密码位于每一扇区第3块
			if(status!=MI_OK){printf("扇区%d密码A验证失败\n",snr); continue;}
			status = PcdAuthState(KEYB, (snr*4+3), DefaultKey, SelectedSnr);
			if(status!=MI_OK){printf("扇区%d密码B验证失败\n",snr); continue;}
			
			for(i=0;i<4;i++)
			{
				status = PcdRead(i+snr*4, bufr);
				if(status!=MI_OK){printf("块%d数据读取失败\n",i+snr*4);continue;}
				printf("块%d数据：",i+snr*4);
				for(j=0;j<16;j++)
				{
					if((j==6 || j==10)&&i==3)printf("  ");
					printf("%d ",bufr[j]);
				}
				printf("\n");
			}
			printf("\n");
		}
		
		PcdHalt();   //命令卡片进入休眠状态
		PcdWaitDepart();
		
	}
}

