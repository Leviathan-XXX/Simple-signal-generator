#ifndef __SINGAL_H
#define __SINGAL_H

#include "stdint.h"

//����
typedef struct
{
    uint8_t ID;
    char *name;
    float value;//����������������������
    char *unit;
}PARA_DefType;

typedef struct
{
    uint8_t ID;
    char *name;
}FUNC_DefType;

typedef struct
{
    char *name;
    uint8_t func_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    FUNC_DefType function[5];
    
}MENU_DefType;

typedef struct
{
    char *name;
    uint8_t para_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    PARA_DefType parameter[3];
    
}SIN_DefType;

typedef struct
{
    char *name;
    uint8_t para_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    PARA_DefType parameter[4];
    
}SQUARE_DefType;

typedef struct
{
    char *name;
    uint8_t para_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    PARA_DefType parameter[4];
    
}RAMP_DefType;

typedef struct
{
    char *name;
    uint8_t para_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    PARA_DefType parameter[5];
    
}TRI_DefType;

typedef struct
{
    char *name;
    uint8_t para_number;
    uint8_t show_pointer[3];
    uint8_t now_pointer;//ָ��123ѡ��
    PARA_DefType parameter[6];
    
}TRA_DefType;

//��������
void Menu_Init(MENU_DefType *menu);
void Sin_Init(SIN_DefType *sin);
void SQUARE_Init(SQUARE_DefType *sin);
void RAMP_Init(RAMP_DefType *sin);
void TRI_Init(TRI_DefType *sin);
void TRA_Init(TRA_DefType *sin);

void Alter_Para(PARA_DefType *para,uint16_t value,uint16_t dr);
#endif
