#ifndef __WAVE_H
#define __WAVE_H


#include "core_cm3.h"
#include <stdint.h>




//º¯ÊıÉùÃ÷

void generate_Twave(uint16_t origin,uint16_t up,__IO uint16_t platform,uint16_t down ,uint16_t length,float *Twave);
void generate_Dwave(float amp,float bias ,uint16_t *Dwave, float *Twave);
void generate_Sin_Twave(float *Twave);

#endif
