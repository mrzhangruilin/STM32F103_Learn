#include "show.h"
#include "usart.h"

extern uint8_t SystemStatus;
extern uint8_t cardbuf[4];

void Show_State(void)
{
	printf("CLR(10);BL(0);SBC(10);\r\n");
	HAL_Delay(150);								/* 每一句命令延时150ms */
	if(SystemStatus == SYSTEMSTATUS_WAIT)
	{
		printf("DCV32(90,215,'等待开门',60);\r\n");
	}
	else if(SystemStatus == SYSTEMSTATUS_ADD)
	{
		printf("DCV32(70,215,'正在增加卡片',6);\r\n");
	}
	else if(SystemStatus == SYSTEMSTATUS_DEL)
	{
		printf("DCV32(70,215,'正在删除卡片',3);\r\n");
	}
	else
	{
		printf("DCV32(90,215,'等待开门',60);\r\n");
	}
}

/*
@function:	显示增加卡片的结果
@para:		0表示增加失败，1表示增加成功
@retval:	NULL
*/
void Show_Add(uint8_t type)
{
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(25,215,'卡片增加成功！！！',1);\r\n");
	}
	else
	{
		printf("CLR(42);SBC(42);DCV32(25,215,'卡片增加失败！！！',63);\r\n");
	}
	HAL_Delay(2000);
}

/*
@function:	显示删除卡片的结果
@para:		0表示删除失败，1表示删除成功
@retval:	NULL
*/
void Show_Delete(uint8_t type)
{
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(25,215,'卡片删除成功！！！',1);\r\n");
	}
	else
	{
		printf("CLR(42);SBC(42);DCV32(25,215,'卡片删除失败！！！',63);\r\n");
	}
	HAL_Delay(2000);
}

/*
@function:	显示开门的结果
@para:		0表示卡片不存在，开门失败，1表示成功
@retval:	NULL
*/
void Show_Open(uint8_t type)
{
	uint8_t i,num;
	
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(50,215,'开门成功！！！',1);\r\n");
	}
	else
	{
		printf("CLR(44);SBC(44);DCV32(50,215,'开门失败！！！',63);\r\n");
	}
	for(i=0;i<4;i++)
	{
		num=90+(35*i);
		printf("DCV32(%d,90,'%d',63);\r\n",num,*(cardbuf+i));
	}
}
