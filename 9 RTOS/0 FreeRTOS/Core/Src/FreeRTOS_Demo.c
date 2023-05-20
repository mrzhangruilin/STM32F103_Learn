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
    while(1)
    {
        HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin);
        vTaskDelay(500);
    }
}

void Task2( void *para )
{
    while(1)
    {
        HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin);
        vTaskDelay(500);
    }
}

//  ������ģ��
// void task0( void *para )
// {

// }


