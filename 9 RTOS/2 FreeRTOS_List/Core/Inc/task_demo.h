#ifndef _TASK_DEMO_H__
#define _TASK_DEMO_H__

#include "main.h"
#include "usart.h"

void Task_Start(void);


/*任务列表，任务配置及其声明，任务句柄应在task_demo.c文件中定义*/
    //任务声明
void task1(void *pvParameters);
void task2(void *pvParameters);


    //优先级配置
#define pri_task1   1
#define pri_task2   1


    //任务堆栈配置
#define stack_task1     128
#define stack_task2     128


#endif


