#ifndef _FREERTOS_DEMO_H__
#define _FREERTOS_DEMO_H__

#include "main.h"


/* �������� */
void Task_Create( void );

/* ���������б� */
    //������
    #define Name_Task1      "task1"
    #define Name_Task2      "task2"

    //�������ȼ�        
    #define Pri_Task1       1
    #define Pri_Task2       1

    //�����ջ��С      
    #define Stack_Task1     128
    #define Stack_Task2     128

    //��������
    void Task1( void *para );
    void Task2( void *para );
#endif

