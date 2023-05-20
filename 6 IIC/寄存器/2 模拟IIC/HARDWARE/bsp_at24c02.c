#include "bsp_at24c02.h"

/***
addr:从机地址
dataAdd:数据地址
data:数据指针
len:写入数据长度
*/

void AT24C02_WriteByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len)		//写AT24C02一个字节,addr是七位地址
{
	{
		unsigned char i;
		SCL = 1;				//释放总线
		SDA = 1;				//释放SDA
		while(!PBin(scl));		//等待总线空闲
		IIC_Start();			//发送起始条件
		IIC_SendByte(addr<<1);	//发送七位地址，第零位0，写入
		IIC_ReadBck();			//读应答位
		IIC_SendByte(dataAdd);	//发送数据地址位
		IIC_ReadBck();			//读应答位
		
		for( i=0; i<len; i++)
		{
			IIC_SendByte(*(data+i));		//发送数据
			IIC_ReadBck();							//读应答位
		}
		
		IIC_Stop();				//发送停止条件
		delay_ms(10);
	}
	{
		unsigned char i;
		SCL = 1;				//释放总线
		SDA = 1;				//释放SDA
		while(!PBin(scl));		//等待总线空闲
		IIC_Start();			//发送起始条件
		IIC_SendByte(addr<<1);	//发送七位地址，第零位0，写入
		IIC_ReadBck();			//读应答位
		IIC_SendByte(dataAdd);	//发送数据地址位
		IIC_ReadBck();			//读应答位
		
		for( i=0; i<len; i++)
		{
			IIC_SendByte(*(data+i));		//发送数据
			IIC_ReadBck();							//读应答位
		}
		
		IIC_Stop();				//发送停止条件
		delay_ms(10);
	}
}

void AT24C02_ReadByte(u8 addr, u8 dataAdd, unsigned char *data, u8 len)				//从AT24C02里读一个字节，addr是七位地址
{
	unsigned char i;
	SCL = 1;					//释放总线
	SDA = 1;					//释放SDA
	while(!PBin(scl));			//等待总线空闲
	IIC_Start();				//发送起始条件
	IIC_SendByte(addr<<1);		//发送七位地址，第零位0，写入
	IIC_ReadBck();				//读应答位
	IIC_SendByte(dataAdd);		//发送数据地址位
	IIC_ReadBck();				//读应答位
	
	//重新发送起始条件
	SCL = 1;						//释放总线
	SDA = 1;						//释放SDA
	while(!PBin(scl));				//等待总线空闲
	IIC_Start();					//发送起始条件
	IIC_SendByte(addr<<1|1<<0);		//发送七位地址，第零位1，读
	IIC_ReadBck();					//读应答位
	for(i=0; i<len; i++)
	{
		*(data+i) = IIC_ReadByte();			//读一个字节
		IIC_SendBck();						//发送应答
	}
	IIC_Stop();						//发送停止条件
	delay_ms(10);
}
