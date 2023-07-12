#include "stm32f10x.h"
#include "wave.h"
#include <math.h>

#define PI 3.14159265
//初始化



void generate_Sin_Twave(float *Twave)
{
    double gap= PI*2/100;
    double t=0;
    for (uint16_t i = 0;i<100;i++)
        {
            *(Twave+i)=(float)sin(t);
            t=t+gap;
        }
}

//生成初始波形序列

void generate_Twave(uint16_t origin,uint16_t up, uint16_t platform,uint16_t down,uint16_t length ,float *Twave)
{
    float max_amplitude = 1.0;
    float up_slope=max_amplitude/(up);
    float down_slope=max_amplitude/(down);
    //functional body
    for (uint16_t i = 0;i<length;i++)
        {
            if(i<(origin))
            {
                *(Twave+i)=0;
            }
            else if(i<((origin)+(up)))
            {
                *(Twave+i)=*(Twave+i-1)+up_slope;
                //if(*(Twave+i) >max_amplitude)
                //{ *(Twave+i)=max_amplitude; }
            }
            else if(i<((origin)+(up)+(platform)))
            {
                *(Twave+i)=*(Twave+i-1);
            }
            else if(i<((origin)+(up)+(platform)+(down)))
            {
                *(Twave+i)=*(Twave+i-1)-down_slope;
            }
            else
            {
                *(Twave+i)=0;
            }
        }
}

//生成数据波形 *幅值+偏置 转换为12位数据
void generate_Dwave(float amp,float bias ,uint16_t *Dwave, float *Twave)
{
    uint16_t length=100;
    float ratio=(amp)*(4096)/(3.3);
    float dbias=((bias)*(4096)/(3.3));
    
    for (uint16_t i = 0;i<length;i++)
        {
            *(Dwave+i)=(uint16_t)(*(Twave+i)*ratio+dbias+100);
            if(*(Dwave+i)>32767)
            {*(Dwave+i)=0;}
            else if(*(Dwave+i)>4096)
            {*(Dwave+i)=4096;}
        }
}



