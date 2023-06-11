#include "bsp_at24c02.h"

/***
*function:	向AT24C02写入数据
*para：
	@addr:		从机地址
	@dataAdd:	数据地址
	@data:		数据指针
	@len:			写入数据长度
*retval：NULL
*注意，页写，八个字节一页，0-7是一页，8-15是一页
*/
void AT24C02_WriteByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)
{
	unsigned char i;
	if(len>8){len = 8;}			//判断读取长度是否超出范围
	SCL_H;									//释放总线
	SDA_H;									//释放SDA
	i = SDA_Read;
	while(!(SDA_Read));			//等待总线空闲
	IIC_Start();						//发送起始条件
	IIC_SendByte(addr<<1);	//发送七位地址，第零位0，写入
	IIC_ReadBck();					//读应答位
	IIC_SendByte(dataAdd);	//发送数据地址位
	IIC_ReadBck();					//读应答位
	
	for( i=0; i<len; i++)
	{
		IIC_SendByte(*(data+i));		//发送数据
		IIC_Delay();
		IIC_ReadBck();							//读应答位
		IIC_Delay();
	}
	
	IIC_Stop();				//发送停止条件
	Delay_ms(10);
}

/**
*function:	从AT24C02里读字节
*para
	@addr:		从机地址
	@dataAdd:	读取地址
	@data:		读取缓存区
	@len:			读取长度
*retval：		NULL
*/
void AT24C02_ReadByte(uint8_t addr, uint8_t dataAdd, unsigned char *data, uint8_t len)
{
	unsigned char i;
	SCL_H;													//释放总线
	SDA_H;													//释放SDA
	while(!(SDA_Read));							//等待总线空闲
	IIC_Start();										//发送起始条件，第零位0，写入
	IIC_ReadBck();									//读应答位
	IIC_SendByte(addr<<1);					//发送七位地址
	IIC_SendByte(dataAdd);					//发送数据地址位
	IIC_ReadBck();									//读应答位
	
	//重新发送起始条件
	SCL_H;													//释放总线
	SDA_H;													//释放SDA
	while(!(SDA_Read));							//等待总线空闲
	IIC_Start();										//发送起始条件
	IIC_SendByte(addr<<1|1<<0);			//发送七位地址，第零位1，读
	IIC_ReadBck();									//读应答位
	for(i=0; i<len; i++)
	{
		*(data+i) = IIC_ReadByte();		//读一个字节
		IIC_Delay();
		IIC_SendBck();								//发送应答
		IIC_Delay();
	}
	IIC_Stop();											//发送停止条件
	Delay_ms(10);
}
