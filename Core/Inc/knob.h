#ifndef __KNOB_H
#define __KNOB_H

#include "main.h"
#define TIM_ENCODER htim3

typedef struct
{
  __IO uint16_t encoder_last_value;
  __IO uint16_t encoder_now_value;
  __IO uint16_t dr;//0 ����˳ʱ��ת������ֵ��1������ʱ��ת����Сֵ
  __IO uint16_t vary; 

} KNOB_TypeDef;


void Knob_Init( KNOB_TypeDef *knob );
void Knob_Start(void);
void Knob_Stop(void);
void Get_Knob_value(KNOB_TypeDef *knob);

#endif
