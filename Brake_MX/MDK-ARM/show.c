#include "show.h"
#include "usart.h"

extern uint8_t SystemStatus;
extern uint8_t cardbuf[4];

void Show_State(void)
{
	printf("CLR(10);BL(0);SBC(10);\r\n");
	HAL_Delay(150);								/* ÿһ��������ʱ150ms */
	if(SystemStatus == SYSTEMSTATUS_WAIT)
	{
		printf("DCV32(90,215,'�ȴ�����',60);\r\n");
	}
	else if(SystemStatus == SYSTEMSTATUS_ADD)
	{
		printf("DCV32(70,215,'�������ӿ�Ƭ',6);\r\n");
	}
	else if(SystemStatus == SYSTEMSTATUS_DEL)
	{
		printf("DCV32(70,215,'����ɾ����Ƭ',3);\r\n");
	}
	else
	{
		printf("DCV32(90,215,'�ȴ�����',60);\r\n");
	}
}

/*
@function:	��ʾ���ӿ�Ƭ�Ľ��
@para:		0��ʾ����ʧ�ܣ�1��ʾ���ӳɹ�
@retval:	NULL
*/
void Show_Add(uint8_t type)
{
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(25,215,'��Ƭ���ӳɹ�������',1);\r\n");
	}
	else
	{
		printf("CLR(42);SBC(42);DCV32(25,215,'��Ƭ����ʧ�ܣ�����',63);\r\n");
	}
	HAL_Delay(2000);
}

/*
@function:	��ʾɾ����Ƭ�Ľ��
@para:		0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
@retval:	NULL
*/
void Show_Delete(uint8_t type)
{
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(25,215,'��Ƭɾ���ɹ�������',1);\r\n");
	}
	else
	{
		printf("CLR(42);SBC(42);DCV32(25,215,'��Ƭɾ��ʧ�ܣ�����',63);\r\n");
	}
	HAL_Delay(2000);
}

/*
@function:	��ʾ���ŵĽ��
@para:		0��ʾ��Ƭ�����ڣ�����ʧ�ܣ�1��ʾ�ɹ�
@retval:	NULL
*/
void Show_Open(uint8_t type)
{
	uint8_t i,num;
	
	if(type)
	{
		printf("CLR(29);SBC(29);DCV32(50,215,'���ųɹ�������',1);\r\n");
	}
	else
	{
		printf("CLR(44);SBC(44);DCV32(50,215,'����ʧ�ܣ�����',63);\r\n");
	}
	for(i=0;i<4;i++)
	{
		num=90+(35*i);
		printf("DCV32(%d,90,'%d',63);\r\n",num,*(cardbuf+i));
	}
}
