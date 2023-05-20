#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

extern uint32_t SystemCoreClock;

/* 基础配置 */
#define configUSE_PREEMPTION		    1                               /* 1-抢占式调度器  0-时间片调度器（协作式）*/
#define configUSE_IDLE_HOOK			    0                               /* 1-使用空闲钩子 0-不使用*/
#define configUSE_TICK_HOOK			    0                               /* 1-使用时间片钩子 0-不使用*/
#define configCPU_CLOCK_HZ			    SystemCoreClock                 /* CPU主频，单位 */
#define configTICK_RATE_HZ			    20                            /* 系统节拍频率，单位Hz */
#define configMAX_PRIORITIES		    ( 5 )                           /* 最大优先级数 */
#define configMINIMAL_STACK_SIZE	    ( ( unsigned short ) 128 )      /* 空闲任务堆栈空间 */
#define configMAX_TASK_NAME_LEN		    ( 16 )                          /* 任务名最大字符数 */
#define configUSE_TRACE_FACILITY	    0                               /* 启用可视化跟踪调试 */
#define configUSE_16_BIT_TICKS		    0                               /* 系统节拍计数器变量数据类型 1-16位无符号 0-32位无符号*/
#define configIDLE_SHOULD_YIELD		    1                               /* 空闲任务放弃CPU使用权给其它同优先级的用户任务 */
#define configUSE_QUEUE_SETS            0                               /* 启用队列 */
#define configUSE_TASK_NOTIFICATIONS    1                               /* 开启任务通知功能，默认开启 */       
#define configUSE_MUTEXES			    0                               /* 使用互斥信号量 */
#define configUSE_RECURSIVE_MUTEXES		0                               /* 使用递归互斥信号量 */
#define configUSE_COUNTING_SEMAPHORES	0                               /* 为1时使用计数信号 */
#define configQUEUE_REGISTRY_SIZE		10                              /* 设置可以注册的信号量和消息队列个数 */



/* 可选函数配置 */
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

/* 内存相关 */
#define configSUPPORT_DYNAMIC_ALLOCATION        1                               /* 支持动态内存申请 */
#define configSUPPORT_STATIC_ALLOCATION			0                               /* 支持静态内存 */
#define configTOTAL_HEAP_SIZE		            ( ( size_t ) ( 17 * 1024 ) )    /* 系统所有总的堆大小 (17*1024) = 17K RAM 空间 */

/* 中断服务函数相关 */
//因为在it.c里每个中断调用了相应的函数，所以这里不定义
// #define xPortPendSVHandler 	PendSV_Handler
// #define vPortSVCHandler 	SVC_Handler
// #define xPortSysTickHandler SysTick_Handler

/* 与中断有关的配置 */
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4
#endif
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15          //中断最低优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5           //系统可管理的最高中断优先级
#define configKERNEL_INTERRUPT_PRIORITY 		        ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	        ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	        15


/* 软件定时器有关配置 */
#define configUSE_TIMERS				        0                               /* 启用软件定时器 */
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        /* 软件定时器优先级 */
#define configTIMER_QUEUE_LENGTH		        10                              /* 软件定时器队列长度 */
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    /* 软件定时器任务堆栈大小 */

#endif /* FREERTOS_CONFIG_H */

