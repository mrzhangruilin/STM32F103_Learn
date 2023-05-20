#include "task_demo.h"

TaskHandle_t htask1;
TaskHandle_t htask2;

/*
@function:  任务开启函数，把要开启的任务放在这里面
@para:      NUll
@reval:     NULL
*/
void Task_Start(void)
{
    xTaskCreate(task1 , "LED1" , stack_task1 , NULL , pri_task1 , &htask1);
    xTaskCreate(task2 , "LED2" , stack_task2 , NULL , pri_task2 , &htask2);
    xTaskCreate(task3 , "KEY1" , stack_task3 , NULL , pri_task3 , NULL);
    xTaskCreate(task4 , "KEY2" , stack_task4 , NULL , pri_task4 , NULL);

    vTaskStartScheduler();
}

void task1(void *pvParameters)
{
    while(1)
    {
        printf("任务运行中1\n");
        HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin);
        vTaskDelay(500);
    }
}

void task2(void *pvParameters)
{
	while(1)
	{
        printf("任务运行中2\n");
        HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin);
        HAL_Delay(500);
        //vTaskDelay(500);
	}
}

void task3(void *pvParameters)
{
	while(1)
	{
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port , KEY1_Pin) == GPIO_PIN_RESET)
        {
            vTaskDelete(htask1);    //删除任务一
            printf("删除任务1\n");
            vTaskDelete(NULL);
        }
	}
}

void task4(void *pvParameters)
{
    uint8_t status=0;     //挂起标志位
	while(1)
	{
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port , KEY2_Pin) == GPIO_PIN_RESET)
        {
            vTaskDelay(10);
            if(status)
            {
                vTaskResume(htask2);    //恢复任务二
                printf("恢复2\n");
                status = 0;
            }
            else
            {
                vTaskSuspend(htask2);    //挂起任务二
                printf("挂起任务2\n");
                status = 1;
            }

            while(HAL_GPIO_ReadPin(KEY2_GPIO_Port , KEY2_Pin) == GPIO_PIN_RESET);
            vTaskDelay(10);
        }
	}
}

/*以下为空任务模板*/
// void task0(void *pvParameters)
// {
// 	while(1)
// 	{
        
// 	}
// }



