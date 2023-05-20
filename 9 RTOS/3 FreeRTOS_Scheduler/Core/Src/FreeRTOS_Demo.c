#include "FreeRTOS_Demo.h"

/* ȫ�ֱ����б� */

/* �������б� */
TaskHandle_t hTask1;
TaskHandle_t hTask2;


/* ���񴴽���������Ҫ����������ŵ����� */
void Task_Create( void )
{
    xTaskCreate(Task1 , Name_Task1 , Stack_Task1 , NULL , Pri_Task1 , &hTask1);
    xTaskCreate(Task2 , Name_Task2 , Stack_Task2 , NULL , Pri_Task2 , &hTask2);

    vTaskStartScheduler();          //�������������
}

void Task1( void *para )
{
    uint32_t task1_num;
    while(1)
    {
        task1_num ++;
        HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin);
        printf("task1���д���%d\r\n" , task1_num);
        HAL_Delay(10);
    }
}

void Task2( void *para )
{
    uint32_t task2_num;
    while(1)
    {
        task2_num ++;
        HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin);
        printf("task2���д���%d\r\n" , task2_num);
        HAL_Delay(10);
    }
}

//  ������ģ��
// void task0( void *para )
// {

// }


