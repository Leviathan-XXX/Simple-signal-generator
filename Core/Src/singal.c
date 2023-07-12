#include "singal.h"

void Menu_Init(MENU_DefType *menu)
{
    menu->name="menu";
    menu->func_number=5;
    menu->function[0].ID=1;
    menu->function[0].name="sin";
    menu->function[1].ID=2;
    menu->function[1].name="square";
    menu->function[2].ID=3;
    menu->function[2].name="ramp";
    menu->function[3].ID=4;
    menu->function[3].name="triangle";
    menu->function[4].ID=5;
    menu->function[4].name="trapezoid";
    
    menu->show_pointer[0]=0;
    menu->show_pointer[1]=1;
    menu->show_pointer[2]=2;
    
    menu->now_pointer=0;
}


void Sin_Init(SIN_DefType *sin)
{
    sin->name="sin";
    sin->para_number = 3;
    sin->parameter[0].ID=1;
    sin->parameter[0].name="fre";
    sin->parameter[0].value=10;//初始设定为10Hz
    sin->parameter[0].unit="Hz";
    
    sin->parameter[1].ID=2;
    sin->parameter[1].name="amp";
    sin->parameter[1].value=1;//初始设定为1
    sin->parameter[1].unit="V";
    
    sin->parameter[2].ID=3;
    sin->parameter[2].name="bias";
    sin->parameter[2].value=1;//初始设定为1
    sin->parameter[2].unit="V";
    
    sin->show_pointer[0]=0;
    sin->show_pointer[1]=1;
    sin->show_pointer[2]=2;
    
    sin->now_pointer=0;
}

void SQUARE_Init(SQUARE_DefType *sin)
{
    sin->name="square";
    sin->para_number = 4;
    
    sin->parameter[0].ID=1;
    sin->parameter[0].name="fre";
    sin->parameter[0].value=10;//初始设定为10Hz
    sin->parameter[0].unit="Hz";
    
    sin->parameter[1].ID=2;
    sin->parameter[1].name="amp";
    sin->parameter[1].value=1;//初始设定为1
    sin->parameter[1].unit="V";
    
    sin->parameter[2].ID=3;
    sin->parameter[2].name="bias";
    sin->parameter[2].value=1;//初始设定为1
    sin->parameter[2].unit="V";
    
    sin->parameter[3].ID=4;
    sin->parameter[3].name="duty";
    sin->parameter[3].value=50;//初始设定为50
    sin->parameter[3].unit="%";
    
    sin->show_pointer[0]=0;
    sin->show_pointer[1]=1;
    sin->show_pointer[2]=2;
    
    sin->now_pointer=0;
}

void RAMP_Init(RAMP_DefType *sin)
{
    sin->name="ramp";
    sin->para_number = 4;
    
    sin->parameter[0].ID=1;
    sin->parameter[0].name="fre";
    sin->parameter[0].value=10;//初始设定为10Hz
    sin->parameter[0].unit="Hz";
    
    sin->parameter[1].ID=2;
    sin->parameter[1].name="amp";
    sin->parameter[1].value=1;//初始设定为1
    sin->parameter[1].unit="V";
    
    sin->parameter[2].ID=3;
    sin->parameter[2].name="bias";
    sin->parameter[2].value=1;//初始设定为1
    sin->parameter[2].unit="V";
    
    sin->parameter[3].ID=4;
    sin->parameter[3].name="duty";
    sin->parameter[3].value=50;//初始设定为50
    sin->parameter[3].unit="%";
    
    sin->show_pointer[0]=0;
    sin->show_pointer[1]=1;
    sin->show_pointer[2]=2;
    
    sin->now_pointer=0;
}


void TRI_Init(TRI_DefType *sin)
{
    sin->name="triangle";
    sin->para_number = 5;
    
    sin->parameter[0].ID=1;
    sin->parameter[0].name="fre";
    sin->parameter[0].value=10;//初始设定为10Hz
    sin->parameter[0].unit="Hz";
    
    sin->parameter[1].ID=2;
    sin->parameter[1].name="amp";
    sin->parameter[1].value=1;//初始设定为1
    sin->parameter[1].unit="V";
    
    sin->parameter[2].ID=3;
    sin->parameter[2].name="bias";
    sin->parameter[2].value=1;//初始设定为1
    sin->parameter[2].unit="V";
    
    sin->parameter[3].ID=5;
    sin->parameter[3].name="up";
    sin->parameter[3].value=50;//初始设定为50
    sin->parameter[3].unit="%";
    
    sin->parameter[4].ID=6;
    sin->parameter[4].name="down";
    sin->parameter[4].value=50;//初始设定为50
    sin->parameter[4].unit="%";
    
    sin->show_pointer[0]=0;
    sin->show_pointer[1]=1;
    sin->show_pointer[2]=2;
    
    sin->now_pointer=0;
}

void TRA_Init(TRA_DefType *sin)
{
    sin->name="trapezoid";
    sin->para_number = 6;
    
    sin->parameter[0].ID=1;
    sin->parameter[0].name="fre";
    sin->parameter[0].value=10;//初始设定为10Hz
    sin->parameter[0].unit="Hz";
    
    sin->parameter[1].ID=2;
    sin->parameter[1].name="amp";
    sin->parameter[1].value=1;//初始设定为1
    sin->parameter[1].unit="V";
    
    sin->parameter[2].ID=3;
    sin->parameter[2].name="bias";
    sin->parameter[2].value=1;//初始设定为1
    sin->parameter[2].unit="V";
    
    sin->parameter[3].ID=5;
    sin->parameter[3].name="up";
    sin->parameter[3].value=20;//初始设定为20
    sin->parameter[3].unit="%";
    
    sin->parameter[4].ID=6;
    sin->parameter[4].name="down";
    sin->parameter[4].value=20;//初始设定为20
    sin->parameter[4].unit="%";
    
    sin->parameter[5].ID=7;
    sin->parameter[5].name="plat";
    sin->parameter[5].value=50;//初始设定为50
    sin->parameter[5].unit="%";
    
    sin->show_pointer[0]=0;
    sin->show_pointer[1]=1;
    sin->show_pointer[2]=2;
    
    sin->now_pointer=0;
}


void Alter_Para(PARA_DefType *para,uint16_t value,uint16_t dr)
{
    if(para->ID == 1) //频率
    {
        if(dr ==0)
        {para->value += (float)value/4;}
        else{para->value -= (float) value/4;}
        if (para->value>100.0)
        {para->value=100.0;}
        else if(para->value<1.0)
        {para->value=1.0;}
    }
    else if(para->ID >=2 && para->ID <4)
    {
        if(dr ==0)
        {para->value += ((float)value)/40;}
        else{para->value -= ((float)value)/40;}
        if (para->value>1.6)
        {para->value=1.6;}
        else if(para->value<0.0)
        {para->value=0.0;}
    }
    else if(para->ID >=4)
    {
        if(dr ==0)
        {para->value += (float)value/4;}
        else{para->value -= (float)value/4;}
        if (para->value>100.0)
        {para->value=100.0;}
        else if(para->value<0.0)
        {para->value=0.0;}
    }
}

