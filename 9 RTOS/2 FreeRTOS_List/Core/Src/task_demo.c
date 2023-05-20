#include "task_demo.h"

/* 任务句柄定义 */
TaskHandle_t htask1;
TaskHandle_t htask2;

/* 全局变量 */
List_t      TestList;       /* 定义测试列表 */
ListItem_t  ListItem1;      /* 测试列表项1 */
ListItem_t  ListItem2;      /* 测试列表项2 */
ListItem_t  ListItem3;      /* 测试列表项3 */


/*
@function:  任务开启函数，把要开启的任务放在这里面
@para:      NUll
@reval:     NULL
*/
void Task_Start(void)
{
    xTaskCreate(task1 , "task1" , stack_task1 , NULL , pri_task1 , &htask1);
    xTaskCreate(task2 , "task2" , stack_task2 , NULL , pri_task2 , &htask2);

    vTaskStartScheduler();
}

/* 翻转LED灯 */
void task1(void *pvParameters)
{
    while(1)
    {
        HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin);
        vTaskDelay(500);
    }
}

/* 任务二 列表插入和删除实验*/
void task2(void *pvParameters)
{
    /* 初始化列表和列表项 */
    vListInitialise(&TestList);         /* 初始化列表 */
    vListInitialiseItem(&ListItem1);    /*初始化列表项*/
    vListInitialiseItem(&ListItem2);    /*初始化列表项*/
    vListInitialiseItem(&ListItem3);    /*初始化列表项*/
    ListItem1.xItemValue = 40;          
    ListItem2.xItemValue = 60;          
    ListItem3.xItemValue = 50;   

    /* 打印列表和列表项地址 */
    printf("列表：\t\t0x%p\r\n" , &TestList);
    printf("List->pxIndex:\t0x%p\r\n" , &TestList.pxIndex);
    printf("List->xListEnd:\t0x%p\r\n" , &TestList.xListEnd);
    printf("列表项1：\t0x%p\r\n" , &ListItem1);
    printf("列表项2：\t0x%p\r\n" , &ListItem2);
    printf("列表项3：\t0x%p\r\n" , &ListItem3);
    printf("\r\n");

    /* 列表项1插入列表 */
    vListInsert(&TestList , &ListItem1);
    printf("列表项数：\t%d\r\n" , TestList.uxNumberOfItems);
    printf("列表第1项\t0x%p\r\n" , TestList.xListEnd.pxPrevious);
    printf("\r\n");

    /* 列表项2插入列表 */
    vListInsert(&TestList , &ListItem2);
    printf("列表项数：\t%d\r\n" , TestList.uxNumberOfItems);
    printf("列表第1项：\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("列表第2项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("\r\n");

    /* 列表项3插入列表 */
    vListInsert(&TestList , &ListItem3);
    printf("列表项数：\t%d\r\n" , TestList.uxNumberOfItems);
    printf("列表第1项：\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("列表第2项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("列表第3项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext->pxNext);
    printf("\r\n");

    /* 移除列表项3 */
    uxListRemove(&ListItem3);
    printf("列表项数：\t%d\r\n" , TestList.uxNumberOfItems);
    printf("列表第1项：\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("列表第2项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("\r\n");

    /* 末尾插入列表项3 */
    vListInsertEnd(&TestList , &ListItem3);
    printf("列表项数：\t%d\r\n" , TestList.uxNumberOfItems);
    printf("列表第1项：\t0x%p\r\n" , TestList.xListEnd.pxNext);
    printf("列表第2项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext);
    printf("列表第3项：\t0x%p\r\n" , TestList.xListEnd.pxNext->pxNext->pxNext);
    printf("\r\n");
	while(1)
	{
	}
}






/*以下为空任务模板*/
// void task0(void *pvParameters)
// {
// 	while(1)
// 	{
        
// 	}
// }



