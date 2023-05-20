#include "FreeRTOS_Demo.h"

/* 全局变量列表 */

/* 任务句柄列表 */
TaskHandle_t hTask1;
TaskHandle_t hTask2;


/* 任务创建函数，把要创建的任务放到这里 */
void Task_Create( void )
{
    xTaskCreate(Task1 , Name_Task1 , Stack_Task1 , NULL , Pri_Task1 , &hTask1);
    xTaskCreate(Task2 , Name_Task2 , Stack_Task2 , NULL , Pri_Task2 , &hTask2);

    vTaskStartScheduler();          //开启任务调度器
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

//  空任务模板
// void task0( void *para )
// {

// }


