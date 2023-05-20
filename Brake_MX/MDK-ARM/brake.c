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
	status = PcdAnticoll(SelectedSnr);//����ײ
	if (status != MI_OK){return 0;}
	status = PcdSelect(SelectedSnr);
	if(status!=MI_OK){return 0;}
	

    PcdHalt();          //��Ƭ��������
    PcdWaitDepart();    //�ȴ���Ƭ�뿪
    return 1;
}

/*
@function:      ���AT24C02����
@para:          0xFF��0x00����պ������
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
@function:  ��ȡAT24C02�����п�Ƭ��Ϣ
*/
void AT24C02_Read()
{
    uint8_t cardNum,i;
    cardNum = EEPORM[0];
    if(cardNum == 0)
    {
        printf("û�п�Ƭ\r\n");
        return;
    }
    printf("��Ƭ������%d\r\n" , cardNum);
    for(i=1;i<=cardNum;i++)
    {
        printf("��Ƭ%2d��0x%2x 0x%2x 0x%2x 0x%2x\r\n" , i , EEPORM[i*4-3] , EEPORM[i*4-2] , EEPORM[i*4-1] , EEPORM[i*4-0]);
    }
}

/*
@function��     ��鿨���Ƿ���ڣ������ؿ��ŵ�����
@para��         ����
@retval��       ��������ֵ��0��ʾû�п�������ֵ��1��ʼ
*/
uint8_t Card_Check(uint8_t *cardId)
{
    uint8_t cardNum,i;
    uint8_t cardIdBuf[4];       /* �������ŵĻ��� */
    cardNum = EEPORM[0];        /* ��ȡ��������  */
    if(cardNum)
    {
        for(i=1;i<=cardNum;i++)
        {
            /* �������ţ�����ֵΪi*/
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
        return 0;   /* û�п�Ƭ���϶������� */
    }
}

/*
@function:  ���濨�ţ�����飬ֱ�ӵ�ĩβ����
@para��     ����
@retval��   ��������ֵ��0��ʾ�����ˣ��治����
**/
uint8_t Card_Save(uint8_t *cardId)
{
    uint8_t cardNum;

    cardNum = EEPORM[0];
    if(cardNum==63)     //������
    {
        return 0;
    }
    if(Card_Check(cardId))
    {
        return 0;
    }
    cardNum ++;

    EEPORM[0] = cardNum;                //���濨Ƭ����

    EEPORM[cardNum*4-3] = cardId[0];    //���濨Ƭ
    EEPORM[cardNum*4-2] = cardId[1];
    EEPORM[cardNum*4-1] = cardId[2];
    EEPORM[cardNum*4-0] = cardId[3];

    Card_UnLoad();
    return cardNum;
}

/*
@function:  ��������ֵ��ȡ����
@para:      index������ֵ       cardId�����濨�ŵ�ָ��
@retval:    ��������ֵ�����Ϊ0��ʾ��ȡ����    
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
 * function:    ɾ����Ƭ
 * para��       ��Ƭ����
 * retval��     0-ɾ��ʧ�ܣ�ɾ���ɹ���������ֵ
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
    Brake_Switch(1);            /* ������բ */
    HAL_Delay(2000);
    __HAL_TIM_SET_COMPARE(&htim2 , TIM_CHANNEL_2 ,5);
}

/**
 * function��   �����������Ӧ����ʮ��input����ֵ��ͷ�ļ��ﶨ��
 * retval:      1-���� 0-����  
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
 * function:    ��բ״̬����
 * para��       0-�رյ�բ��1-�򿪵�բ
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
 * ��AT24C02����ؿ�Ƭ���ݵ��ڴ���
*/
void Card_Load(void)
{
    AT24C02_ReadByte(AT24C02_ADDR , 0x00 , EEPORM   ,   1);     /* ������Ƭ���� */
    printf("��Ƭ������%d\r\n" , *EEPORM);
    AT24C02_ReadByte(AT24C02_ADDR , 0x01 , EEPORM+1 ,   (*EEPORM)*4);     /* �������� */
    for(int i=0;i<*EEPORM;i++)
    {
        printf("��%d:%d %d %d %d\r\n" , i , *(EEPORM+i*4+1),*(EEPORM+i*4+2),*(EEPORM+i*4+3),*(EEPORM+i*4+4));
    }
}

/**
 * ���濨Ƭ���ݵ�AT24C02��
*/
void Card_UnLoad(void)
{
    uint8_t i;
    AT24C02_WriteByte(AT24C02_ADDR , 0x00 , EEPORM , 1);   /* д��Ƭ���� */
    for(i=0;i<*EEPORM;i++)
    {
        AT24C02_WriteByte(AT24C02_ADDR , i*4+1 , EEPORM+i*4+1 , 4);     /* д�뿨�ţ�һ��дһ�� */
    }
}
