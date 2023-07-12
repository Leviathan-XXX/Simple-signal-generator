#include "oled.h"
#include "singal.h"


void Ui_Display(uint8_t Line,PARA_DefType *para,uint8_t mode)
{
    //·´°×ÏÔÊ¾Ãû×Ö
    if(mode==0)
    {OLED_ShowString(Line,1,para->name);}
    else{OLED_Reverse_ShowString(Line,1,para->name);}
    
    float value = para->value;
    uint8_t int_value=(uint8_t)value;
    uint8_t fra_value=(uint8_t)(value*10-int_value*10);
    
    if(value<10.0)
        {
            
            OLED_ShowString(Line,5,"   ");
            OLED_ShowNum(Line,8,int_value,1);
            OLED_ShowChar(Line,9,46);
            OLED_ShowNum(Line,10,fra_value,1);
        }
    else if(value<100.0 && value>=10.0)
        {
            OLED_ShowString(Line,5,"  ");
            OLED_ShowNum(Line,7,int_value,2);
            OLED_ShowChar(Line,9,46);
            OLED_ShowNum(Line,10,fra_value,1);
        }
    else
        {
            OLED_ShowString(Line,5," ");
            OLED_ShowNum(Line,6,int_value,3);
            OLED_ShowChar(Line,9,46);
            OLED_ShowNum(Line,10,fra_value,1);
        }
    OLED_ShowString(Line,12," ");
    OLED_ShowString(Line,13,para->unit);
}