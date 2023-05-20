//���ڴ��STM32�Ĵ���ӳ��Ĵ���

typedef	unsigned		int	uint32_t;	/*�޷���32λ����*/
typedef	unsigned short	int	uint16_t;	/*�޷���16λ����*/

/*	�������ַ	*/
#define PERIPH_BASE		((unsigned int)0x40000000)

/*	RCC�������ַ	*/
#define RCC_BASE		(AHBPERIPH_BASE + 0x1000)
#define	RCC_APB2ENR		*(unsigned int*)(RCC_BASE + 0x18)
	
/*	AHBϵͳ���߻���ַ	*/
#define	APB1PERIPH_BASE		PERIPH_BASE
#define	APB2PERIPH_BASE		(PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0X00020000)

/*	GPIO�������ַ	*/
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
	uint32_t CRL;	/*GPIO�˿����õ�λ�Ĵ���	��ַƫ��0x00*/
	uint32_t CRH;	/*GPIO�˿����ø�λ�Ĵ���	��ַƫ��0x04*/
	uint32_t IDR;	/*GPIO��������Ĵ���		��ַƫ��0x08*/
	uint32_t ODR;	/*GPIO��������Ĵ���		��ַƫ��0x0C*/
	uint32_t BSRR;	/*GPIOλ����/����Ĵ���		��ַƫ��0x10*/
	uint32_t BRR;	/*GPIO�˿�λ����Ĵ���		��ַƫ��0x14*/
	uint32_t LCKR;	/*GPIO�˿����������Ĵ���	��ַƫ��0x18*/
} GPIO_TypeDef;

/*	ʹ��GPIO_TypeDef�ѵ�ַǿ��ת����ָ��	*/
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

/*	ʹ��RCC_TypeDef�ѵ�ַת��Ϊָ�� 	*/
#define RCC					((RCC_TypeDef *) RCC_BASE)

