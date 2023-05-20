#ifndef _FREERTOS_DEMO_H__
#define _FREERTOS_DEMO_H__

#include "main.h"


/* 函数声明 */
void Task_Create( void );

/* 任务配置列表 */
    //任务名
    #define Name_Task1      "task1"
    #define Name_Task2      "task2"

    //任务优先级        
    #define Pri_Task1       1
    #define Pri_Task2       1

    //任务堆栈大小      
    #define Stack_Task1     128
    #define Stack_Task2     128

    //任务声明
    void Task1( void *para );
    void Task2( void *para );
#endif

