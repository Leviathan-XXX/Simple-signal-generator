#include "i2c.h"
#include "dac.h"


//初始化DAC
void DAC_Init(DAC_TypeDef *hdac)
{
  hdac->ADD=0xC0;
  hdac->MODE=1;
  hdac->DR=0;
  hdac->counter=0;
}


void DAC_Alter_DR(DAC_TypeDef *hdac,uint16_t DR_value)
{
    hdac->DR=DR_value;
}


void DAC_Start(DAC_TypeDef *hdac,float fre)
{
    hdac->counter=0;
    float fre_real=fre*100;//100个采样点
    uint16_t per;
    uint16_t Rcounter;
    if(fre>=11.0)
    {
        per=1;
    }
    else if(fre>=1.0 && fre<11.0)
    {
        per=11;
    }
    else
    {
        per=110;
    }
    __HAL_TIM_SET_PRESCALER(&DAC_Fre,per-1);
    Rcounter=(uint16_t)(72000000/(fre_real*per)-1);
    __HAL_TIM_SET_AUTORELOAD(&DAC_Fre,Rcounter);
    HAL_TIM_Base_Start_IT(&DAC_Fre);
}

void DAC_Stop(DAC_TypeDef *hdac)
{
    hdac->counter=0;
    DAC_Alter_DR(hdac,0);
    DAC_WriteCmd(hdac);
    HAL_TIM_Base_Stop_IT(&DAC_Fre);
}

//使用快速模式写命令写DAC寄存器
void DAC_WriteCmd(DAC_TypeDef *hdac)   //
{
  uint8_t data[2];
  if (hdac->MODE == 1)
  {
    data[0]=((hdac->DR >> 8)& 0x0F);//高位
    data[1]=((hdac->DR)& 0xFF);//低位
    HAL_I2C_Master_Transmit(&hi2c1,hdac->ADD,data,2,1);
  }
  else
  {
    data[0]=0x30;//关断，500k电阻接地
    data[1]=0x00;//
    HAL_I2C_Master_Transmit(&hi2c1,hdac->ADD,data,2,1);
  }
}


