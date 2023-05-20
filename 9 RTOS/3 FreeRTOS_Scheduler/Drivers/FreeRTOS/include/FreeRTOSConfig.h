#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

extern uint32_t SystemCoreClock;

/* �������� */
#define configUSE_PREEMPTION		    1                               /* 1-��ռʽ������  0-ʱ��Ƭ��������Э��ʽ��*/
#define configUSE_IDLE_HOOK			    0                               /* 1-ʹ�ÿ��й��� 0-��ʹ��*/
#define configUSE_TICK_HOOK			    0                               /* 1-ʹ��ʱ��Ƭ���� 0-��ʹ��*/
#define configCPU_CLOCK_HZ			    SystemCoreClock                 /* CPU��Ƶ����λ */
#define configTICK_RATE_HZ			    20                            /* ϵͳ����Ƶ�ʣ���λHz */
#define configMAX_PRIORITIES		    ( 5 )                           /* ������ȼ��� */
#define configMINIMAL_STACK_SIZE	    ( ( unsigned short ) 128 )      /* ���������ջ�ռ� */
#define configMAX_TASK_NAME_LEN		    ( 16 )                          /* ����������ַ��� */
#define configUSE_TRACE_FACILITY	    0                               /* ���ÿ��ӻ����ٵ��� */
#define configUSE_16_BIT_TICKS		    0                               /* ϵͳ���ļ����������������� 1-16λ�޷��� 0-32λ�޷���*/
#define configIDLE_SHOULD_YIELD		    1                               /* �����������CPUʹ��Ȩ������ͬ���ȼ����û����� */
#define configUSE_QUEUE_SETS            0                               /* ���ö��� */
#define configUSE_TASK_NOTIFICATIONS    1                               /* ��������֪ͨ���ܣ�Ĭ�Ͽ��� */       
#define configUSE_MUTEXES			    0                               /* ʹ�û����ź��� */
#define configUSE_RECURSIVE_MUTEXES		0                               /* ʹ�õݹ黥���ź��� */
#define configUSE_COUNTING_SEMAPHORES	0                               /* Ϊ1ʱʹ�ü����ź� */
#define configQUEUE_REGISTRY_SIZE		10                              /* ���ÿ���ע����ź�������Ϣ���и��� */



/* ��ѡ�������� */
#define INCLUDE_vTaskPrioritySet		        1
#define INCLUDE_uxTaskPriorityGet		        1
#define INCLUDE_vTaskDelete				        1
#define INCLUDE_vTaskCleanUpResources	        0
#define INCLUDE_vTaskSuspend			        1
#define INCLUDE_vTaskDelayUntil			        1
#define INCLUDE_vTaskDelay				        1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_eTaskGetState			        1
#define INCLUDE_xTimerPendFunctionCall	        0
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0

/* �ڴ���� */
#define configSUPPORT_DYNAMIC_ALLOCATION        1                               /* ֧�ֶ�̬�ڴ����� */
#define configSUPPORT_STATIC_ALLOCATION			0                               /* ֧�־�̬�ڴ� */
#define configTOTAL_HEAP_SIZE		            ( ( size_t ) ( 17 * 1024 ) )    /* ϵͳ�����ܵĶѴ�С (17*1024) = 17K RAM �ռ� */

/* �жϷ�������� */
//��Ϊ��it.c��ÿ���жϵ�������Ӧ�ĺ������������ﲻ����
// #define xPortPendSVHandler 	PendSV_Handler
// #define vPortSVCHandler 	SVC_Handler
// #define xPortSysTickHandler SysTick_Handler

/* ���ж��йص����� */
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4
#endif
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15          //�ж�������ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5           //ϵͳ�ɹ��������ж����ȼ�
#define configKERNEL_INTERRUPT_PRIORITY 		        ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	        ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	        15


/* �����ʱ���й����� */
#define configUSE_TIMERS				        0                               /* ���������ʱ�� */
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        /* �����ʱ�����ȼ� */
#define configTIMER_QUEUE_LENGTH		        10                              /* �����ʱ�����г��� */
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    /* �����ʱ�������ջ��С */

#endif /* FREERTOS_CONFIG_H */

