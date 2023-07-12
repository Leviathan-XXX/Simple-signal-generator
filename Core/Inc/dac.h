#ifndef __DAC_H
#define __DAC_H


#include "core_cm3.h"
#include <stdint.h>
#include "tim.h"

#define DAC_Fre htim1

typedef struct
{
  __IO uint32_t MODE;
  __IO uint16_t DR;
  __IO uint16_t ADD; 
  __IO uint16_t counter;

} DAC_TypeDef;



void DAC_Alter_DR(DAC_TypeDef *hdac,uint16_t DR_value);
void DAC_Init(DAC_TypeDef *hdac);
void DAC_WriteCmd(DAC_TypeDef *hdac);

void DAC_Start(DAC_TypeDef *hdac,float fre);
void DAC_Stop(DAC_TypeDef *hdac);

#endif
