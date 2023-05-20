#include "brake.h"
#include "bsp_rc522.h"
#include "bsp_at24c02.h"
#include "stdio.h"
#include "tim.h"

extern uint8_t EEPORM[256];

uint8_t RC522_Read(uint8_t SelectedSnr[4])
{
    int8_t status;
    
    status = PcdRequest(PICC_REQALL, SelectedSnr);
	if (status != MI_OK){return 0;}
	status = PcdAnticoll(SelectedSnr);//防冲撞
	if (status != MI_OK){return 0;}
	status = PcdSelect(SelectedSnr);
	if(status!=MI_OK){return 0;}
	

    PcdHalt();          //卡片进入休眠
    PcdWaitDepart();    //等待卡片离开
    return 1;
}

/*
@function:      清空AT24C02数据
@para:          0xFF或0x00，清空后的数据
*/
void AT24C02_Clear(uint8_t data)
{
    uint8_t i;
    for(i = 0;i<0xff;i++)
    {
        EEPORM[i] = data;
    }
    
    Card_UnLoad();
}

/*
@function:  读取AT24C02的所有卡片信息
*/
void AT24C02_Read()
{
    uint8_t cardNum,i;
    cardNum = EEPORM[0];
    if(cardNum == 0)
    {
        printf("没有卡片\r\n");
        return;
    }
    printf("卡片数量：%d\r\n" , cardNum);
    for(i=1;i<=cardNum;i++)
    {
        printf("卡片%2d：0x%2x 0x%2x 0x%2x 0x%2x\r\n" , i , EEPORM[i*4-3] , EEPORM[i*4-2] , EEPORM[i*4-1] , EEPORM[i*4-0]);
    }
}

/*
@function：     检查卡号是否存在，并返回卡号的索引
@para：         卡号
@retval：       返回索引值，0表示没有卡，索引值从1开始
*/
uint8_t Card_Check(uint8_t *cardId)
{
    uint8_t cardNum,i;
    uint8_t cardIdBuf[4];       /* 读出卡号的缓存 */
    cardNum = EEPORM[0];        /* 读取卡的数量  */
    if(cardNum)
    {
        for(i=1;i<=cardNum;i++)
        {
            /* 读出卡号，索引值为i*/
            cardIdBuf[0] = EEPORM[i*4-3];
            cardIdBuf[1] = EEPORM[i*4-2];
            cardIdBuf[2] = EEPORM[i*4-1];
            cardIdBuf[3] = EEPORM[i*4-0];
             
            if( cardIdBuf[0] == cardId[0] && 
                cardIdBuf[1] == cardId[1] && 
                cardIdBuf[2] == cardId[2] &&
                cardIdBuf[3] == cardId[3])
            {
                return i;
            }

        }
        return 0;
    }
    else
    {
        return 0;   /* 没有卡片，肯定不存在 */
    }
}

/*
@function:  保存卡号，不检查，直接到末尾保存
@para：     卡号
@retval：   返回索引值，0表示卡满了，存不下了
**/
uint8_t Card_Save(uint8_t *cardId)
{
    uint8_t cardNum;

    cardNum = EEPORM[0];
    if(cardNum==63)     //卡满了
    {
        return 0;
    }
    if(Card_Check(cardId))
    {
        return 0;
    }
    cardNum ++;

    EEPORM[0] = cardNum;                //保存卡片数量

    EEPORM[cardNum*4-3] = cardId[0];    //保存卡片
    EEPORM[cardNum*4-2] = cardId[1];
    EEPORM[cardNum*4-1] = cardId[2];
    EEPORM[cardNum*4-0] = cardId[3];

    Card_UnLoad();
    return cardNum;
}

/*
@function:  根据索引值读取卡号
@para:      index：索引值       cardId：保存卡号的指针
@retval:    返回索引值，如果为0表示读取错误    
*/
uint8_t Card_Read(uint8_t index , uint8_t cardId[4])
{
    uint8_t cardNum;
    cardNum = EEPORM[0];
    if(index == 0 || index>cardNum)return 0;

    cardId[0] = EEPORM[index*4-3];
    cardId[1] = EEPORM[index*4-2];
    cardId[2] = EEPORM[index*4-1];
    cardId[3] = EEPORM[index*4-0];
    return index;
}

/**
 * function:    删除卡片
 * para：       卡片索引
 * retval：     0-删除失败，删除成功返回索引值
*/
uint8_t Card_Del(uint8_t index)
{
    uint8_t cardNum;
    uint8_t i;
    cardNum = EEPORM[0];
    if(index == 0 || index>cardNum)return 0;

    for(i=index;i<cardNum;i++)
    {
        EEPORM[i*4-3] = EEPORM[i*4+1];
        EEPORM[i*4-2] = EEPORM[i*4+2];
        EEPORM[i*4-1] = EEPORM[i*4+3];
        EEPORM[i*4-0] = EEPORM[i*4+4];
    }
    cardNum--;
    EEPORM[0] = cardNum;

    Card_UnLoad();
    return index;
}


void Door_Open()
{
    __HAL_TIM_SET_COMPARE(&htim2 , TIM_CHANNEL_2 ,25);
    Brake_Switch(1);            /* 开启电闸 */
    HAL_Delay(2000);
    __HAL_TIM_SET_COMPARE(&htim2 , TIM_CHANNEL_2 ,5);
}

/**
 * function：   检测人体红外感应，五十次input，阈值在头文件里定义
 * retval:      1-有人 0-无人  
*/
uint8_t Check_SR(void)
{
    uint8_t i;
    uint8_t num=0;
    for(i=0;i<SR_TEST_NUM;i++)
    {
        if(HAL_GPIO_ReadPin(SR_GPIO_Port , SR_Pin))
        {
            num++;
        }
    }
    if(num>=SR_TEST_THRESHOLD)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * function:    电闸状态控制
 * para：       0-关闭电闸，1-打开电闸
*/
void Brake_Switch(uint8_t state)
{
    if(state)
    {
        HAL_GPIO_WritePin(RELAY_Cmd_GPIO_Port , RELAY_Cmd_Pin , GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(RELAY_Cmd_GPIO_Port , RELAY_Cmd_Pin , GPIO_PIN_RESET);
    }
}

/**
 * 从AT24C02里加载卡片数据到内存中
*/
void Card_Load(void)
{
    AT24C02_ReadByte(AT24C02_ADDR , 0x00 , EEPORM   ,   1);     /* 读出卡片数量 */
    printf("卡片数量：%d\r\n" , *EEPORM);
    AT24C02_ReadByte(AT24C02_ADDR , 0x01 , EEPORM+1 ,   (*EEPORM)*4);     /* 读出卡号 */
    for(int i=0;i<*EEPORM;i++)
    {
        printf("卡%d:%d %d %d %d\r\n" , i , *(EEPORM+i*4+1),*(EEPORM+i*4+2),*(EEPORM+i*4+3),*(EEPORM+i*4+4));
    }
}

/**
 * 保存卡片数据到AT24C02中
*/
void Card_UnLoad(void)
{
    uint8_t i;
    AT24C02_WriteByte(AT24C02_ADDR , 0x00 , EEPORM , 1);   /* 写卡片数量 */
    for(i=0;i<*EEPORM;i++)
    {
        AT24C02_WriteByte(AT24C02_ADDR , i*4+1 , EEPORM+i*4+1 , 4);     /* 写入卡号，一次写一张 */
    }
}
