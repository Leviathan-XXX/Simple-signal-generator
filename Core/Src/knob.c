#include "tim.h"
#include "knob.h"



void Knob_Init( KNOB_TypeDef *knob )
{
    knob->encoder_last_value=0;
    knob->encoder_now_value=0;
    knob->dr=0;
    knob->vary=0;
}

void Knob_Start(void)
{
    
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

void Knob_Stop(void)
{
    
    HAL_TIM_Encoder_Stop(&htim3,TIM_CHANNEL_ALL);
}

void Get_Knob_value(KNOB_TypeDef *knob)
{
    knob->encoder_now_value=__HAL_TIM_GetCounter(&htim3);
    if(knob->encoder_now_value >= knob->encoder_last_value)
    {
        if(knob->encoder_now_value >32768 && knob->encoder_last_value <=32767)
        {
            knob->dr=1;
            knob->vary=knob->encoder_last_value - knob->encoder_now_value + 65536;
        }
        else
        {
            knob->dr=0;
            knob->vary=knob->encoder_now_value - knob->encoder_last_value;
        }
    }
    else
    {
        if(knob->encoder_last_value >32768 && knob->encoder_now_value <=32767)
        {
            knob->dr=0;
            knob->vary=knob->encoder_now_value - knob->encoder_last_value+65536;
        }
        else
        {
            knob->dr=1;
            knob->vary=knob->encoder_last_value - knob->encoder_now_value;
        }
    }
    knob->encoder_last_value=knob->encoder_now_value;
}

