//----------------------------------------------------------------------------
//Module	：LDC1314
//Author	：ZL
//Version	：V1.0
//Date		: 2016年10月10日21:02:58
//Platform:STM32F103R8T6 
//Company	：星林科技
//ID			:	https://shop114415195.taobao.com
//QQ      :	2509528710
//----------Xing Lin electronic technology co., LTD---------------------------- 
#include "I2C.h"
/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_INIT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟
  
	GPIO_InitStructure.GPIO_Pin =  I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : IIC_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Delay (u8 z)
{
	uint32_t i;
	for (i = 0; i < (z - 0); i++);		//2
}

void delay5ms(void)
{
		
   int i=5000;  
   while(i) 
   { 
     i--; 
   }  
}
/*******************************************************************************
* Function Name  : IIC_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
void IIC_Start(void)
{
	I2C_SDA_1(); 
	I2C_SCL_1();	
	IIC_Delay(7);
	IIC_Delay(7);
 	I2C_SDA_0();	
	IIC_Delay(7);
	I2C_SCL_0();	
}	  
/*******************************************************************************
* Function Name  : IIC_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Stop(void)
{
	I2C_SCL_0();
	I2C_SDA_0();//STOP:when CLK is high DATA change form low to high
 	IIC_Delay(7);
	I2C_SCL_1();
	I2C_SDA_1();//??I2C??????
	IIC_Delay(7);						   	
}

/*******************************************************************************
* Function Name  : IIC_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Ack(void)
{
	I2C_SDA_0();
	IIC_Delay(7);
	I2C_SCL_1();
	IIC_Delay(7);
	I2C_SCL_0();	
	I2C_SDA_1();
	IIC_Delay(1);
	I2C_SDA_0();
	I2C_SCL_0();
}
/*******************************************************************************
* Function Name  : IIC_NAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_NAck(void)
{
	I2C_SCL_0();
	I2C_SDA_1();
	IIC_Delay(7);
	I2C_SCL_1();
	IIC_Delay(7);
	I2C_SCL_0();
	I2C_SDA_0();
}	

/*******************************************************************************
* Function Name  : I2C_Wait_Ack
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
u8 IIC_Wait_Ack(void)
{
	u32 ucErrTime = 0;
	I2C_SDA_1();
	IIC_Delay(7);
	I2C_SCL_1();
  IIC_Delay(7);

	while(I2C_SDA_READ())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	I2C_SCL_0();
	I2C_SDA_0();	
	IIC_Delay(7);
	return 0;  
} 

/*******************************************************************************
* Function Name  : IIC_Send_Byte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void IIC_Send_Byte(u8 Dat)
{                        
    u8 t;   
	
    for(t=0;t<8;t++)
    {       
				if(Dat & 0x80)
				{
					I2C_SDA_1(); 
				}
				else
				{
					I2C_SDA_0(); 
				}
        Dat<<=1; 	  
				IIC_Delay(7);			
				I2C_SCL_1();
				IIC_Delay(7);				
				I2C_SCL_0();
    }	 
} 	   
/*******************************************************************************
* Function Name  : I2C_Read_Byte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
u8 IIC_Read_Byte(unsigned char ack)
{
		unsigned char i,receive=0;
	
		I2C_SDA_1();
		for(i=0;i<8;i++ )
		{
			I2C_SCL_0();
			IIC_Delay(7);
			I2C_SCL_1();
			IIC_Delay(3);
      receive<<=1;
      if(I2C_SDA_READ())receive++;   
			IIC_Delay(3);
			I2C_SCL_0();
    }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();
    return receive;
}
//ZRX          
//单字节写入*******************************************

uint16_t Single_Write(u8 SlaveAddress, u8 REG_Address,uint16_t REG_data)		     //void
{
		static u8 buffer[2];
	
		buffer[0] = (REG_data >> 8);
		buffer[1] = (u8)(REG_data & 0x00ff);
	
  	IIC_Start();
	
    IIC_Send_Byte(SlaveAddress << 1); 
	
    if (IIC_Wait_Ack() == 1)
		{
			return 0;
		}

    IIC_Send_Byte(REG_Address);  
		if (IIC_Wait_Ack() == 1)
		{
			return 0;
		}
		
		IIC_Send_Byte(buffer[0]);
		if (IIC_Wait_Ack() == 1)
		{
			return 0;
		}
		
		IIC_Send_Byte(buffer[1]);
		if (IIC_Wait_Ack() == 1)
		{
			return 0;
		}
		
		IIC_Stop();
		
		return 1;
}


//单字节读取*****************************************
unsigned char Single_Read(u8 SlaveAddress, u8 reg_add,u16 *Read)
{  
	u8 Dat_L = 0;
	u8 Dat_H = 0;
	
	/* 器件地址 */
	IIC_Start();
	IIC_Send_Byte(SlaveAddress << 1);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* 寄存器地址 */
	IIC_Send_Byte(reg_add);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* 器件地址（读）*/
	IIC_Start();
	
	IIC_Send_Byte((SlaveAddress << 1) + 1);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
		
	
	Dat_H = IIC_Read_Byte(1);	//ack
	Dat_L = IIC_Read_Byte(0);	//Nack
	
	IIC_Stop();
		
	*Read = ((Dat_H << 8) | Dat_L);
	
	return 1;
}	


