//用于存放STM32寄存器映射的代码

typedef	unsigned		int	uint32_t;	/*无符号32位变量*/
typedef	unsigned short	int	uint16_t;	/*无符号16位变量*/

/*	外设基地址	*/
#define PERIPH_BASE		((unsigned int)0x40000000)

/*	RCC外设基地址	*/
#define RCC_BASE		(AHBPERIPH_BASE + 0x1000)
#define	RCC_APB2ENR		*(unsigned int*)(RCC_BASE + 0x18)
	
/*	AHB系统总线基地址	*/
#define	APB1PERIPH_BASE		PERIPH_BASE
#define	APB2PERIPH_BASE		(PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0X00020000)

/*	GPIO外设基地址	*/
#define GPIOA_BASE	(APB2PERIPH_BASE + 0x0800)
#define	GPIOB_BASE	(APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE	(APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE	(APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE	(APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE	(APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE	(APB2PERIPH_BASE + 0x2000)


typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_TypeDef;

typedef struct
{
	uint32_t CRL;	/*GPIO端口配置低位寄存器	地址偏移0x00*/
	uint32_t CRH;	/*GPIO端口配置高位寄存器	地址偏移0x04*/
	uint32_t IDR;	/*GPIO数据输入寄存器		地址偏移0x08*/
	uint32_t ODR;	/*GPIO数据输出寄存器		地址偏移0x0C*/
	uint32_t BSRR;	/*GPIO位设置/清除寄存器		地址偏移0x10*/
	uint32_t BRR;	/*GPIO端口位清除寄存器		地址偏移0x14*/
	uint32_t LCKR;	/*GPIO端口配置锁定寄存器	地址偏移0x18*/
} GPIO_TypeDef;

/*	使用GPIO_TypeDef把地址强制转换成指针	*/
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

/*	使用RCC_TypeDef把地址转换为指针 	*/
#define RCC					((RCC_TypeDef *) RCC_BASE)

