#include "task_demo.h"

/* ���������� */
TaskHandle_t htask1;
TaskHandle_t htask2;

/* ȫ�ֱ��� */
List_t      TestList;       /* ��������б� */
ListItem_t  ListItem1;      /* �����б���1 */
ListItem_t  ListItem2;      /* �����б���2 */
ListItem_t  ListItem3;      /* �����б���3 */


/*
@function:  ��������������Ҫ�������������������
@para:      NUll
@reval:     NULL
*/
void Task_Start(void)
{
    xTaskCreate(task1 , "task1" , stack_task1 , NULL , pri_task1 , &htask1);
    xTaskCreate(task2 , "task2" , stack_task2 , NULL , pri_task2 , &htask2);

    vTaskStartScheduler();
}

/* ��תLED�� */
void task1(void *pvParameters)
{
    while(1)
    {
        HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin);
        vTaskDelay(500);
    }
}

/* ����� �б�����ɾ��ʵ��*/
void task2(void *pvParameters)
{
    /* ��ʼ���б���б��� */
    vListInitialise(&TestList);         /* ��ʼ���б� */
    vListInitialiseItem(&ListItem1);    /*��ʼ���б���*/
    vListInitialiseItem(&ListItem2);    /*��ʼ���б���*/
    vListInitialiseItem(&ListItem3);    /*��ʼ���б���*/
    ListItem1.xItemValue = 40;          
    ListItem2.xItemValue = 60;          
    ListItem3.xItemValue = 50;   

    /* ��ӡ�б���б����ַ */
    printf("�б�\t\t0x%p\r\n" , &TestList);
    printf("List->pxIndex:\t0x%p\r\n" , &TestList.pxIndex);
    printf("List->xListEnd:\t0x%p\r\n" , &TestList.xListEnd);
    printf("�б���1��\t0x%p\r\n" , &ListItem1);
    printf("�б���2��\t0x%p\r\n" , &ListItem2);
    printf("�б���3��\t0x%p\r\n" , &ListItem3);
    printf("\r\n");

    /* �б���1�����б� */
    vListInsert(&TestList , &ListItem1);
    printf("�б�������\t%d\r\n" , TestList.uxNumberOfItems);
    printf("�б��1��\t0x%p\r\n" , TestList.xListEnd.pxPrevious);
    printf("\r\n");

    /* �б���2�����б� */
    vListInsert(&TestList , &ListItem2);
    printf("�б�������\t%d\r\n" , TestList.uxNumberOfItems);
    printf("�б��1�\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("�б��2�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("\r\n");

    /* �б���3�����б� */
    vListInsert(&TestList , &ListItem3);
    printf("�б�������\t%d\r\n" , TestList.uxNumberOfItems);
    printf("�б��1�\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("�б��2�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("�б��3�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext->pxNext);
    printf("\r\n");

    /* �Ƴ��б���3 */
    uxListRemove(&ListItem3);
    printf("�б�������\t%d\r\n" , TestList.uxNumberOfItems);
    printf("�б��1�\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("�б��2�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("\r\n");

    /* ĩβ�����б���3 */
    vListInsertEnd(&TestList , &ListItem3);
    printf("�б�������\t%d\r\n" , TestList.uxNumberOfItems);
    printf("�б��1�\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("�б��2�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("�б��3�\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext->pxNext);
    printf("\r\n");
	while(1)
	{
	}
}






/*����Ϊ������ģ��*/
// void task0(void *pvParameters)
// {
// 	while(1)
// 	{
        
// 	}
// }



