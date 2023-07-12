/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "singal.h"
#include "oled.h"
#include "ui.h"
#include "wave.h"
#include "dac.h"
#include "knob.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */


extern DAC_TypeDef hdac1;
extern uint16_t wave_table[100];
KNOB_TypeDef knob1;

__IO uint8_t ui_jump=1;
__IO uint8_t menu_pointer=1; //传递菜单当前选项
__IO uint32_t now_ui_pointer=0x00000002U;//初始为菜单



float ori_table[100];


/* USER CODE END Variables */
/* Definitions for ConsoleTask */
osThreadId_t ConsoleTaskHandle;
const osThreadAttr_t ConsoleTask_attributes = {
  .name = "ConsoleTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for SinTask */
osThreadId_t SinTaskHandle;
const osThreadAttr_t SinTask_attributes = {
  .name = "SinTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MenuTask */
osThreadId_t MenuTaskHandle;
const osThreadAttr_t MenuTask_attributes = {
  .name = "MenuTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SquareTask */
osThreadId_t SquareTaskHandle;
const osThreadAttr_t SquareTask_attributes = {
  .name = "SquareTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RampTask */
osThreadId_t RampTaskHandle;
const osThreadAttr_t RampTask_attributes = {
  .name = "RampTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TriangleTask */
osThreadId_t TriangleTaskHandle;
const osThreadAttr_t TriangleTask_attributes = {
  .name = "TriangleTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TrapezoidTask */
osThreadId_t TrapezoidTaskHandle;
const osThreadAttr_t TrapezoidTask_attributes = {
  .name = "TrapezoidTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for KonbTimer */
osTimerId_t KonbTimerHandle;
const osTimerAttr_t KonbTimer_attributes = {
  .name = "KonbTimer"
};
/* Definitions for ConsoleEvent */
osEventFlagsId_t ConsoleEventHandle;
const osEventFlagsAttr_t ConsoleEvent_attributes = {
  .name = "ConsoleEvent"
};
/* Definitions for OperateEvent */
osEventFlagsId_t OperateEventHandle;
const osEventFlagsAttr_t OperateEvent_attributes = {
  .name = "OperateEvent"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartConsoleTask(void *argument);
void StartSinTask(void *argument);
void StartMenuTask(void *argument);
void StartSquareTask(void *argument);
void StartRampTask(void *argument);
void StartTriangleTask(void *argument);
void StartTrapezoidTask(void *argument);
void KonbCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
    OLED_Init();
    DAC_Init(&hdac1);
    Knob_Init(&knob1);
    
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of KonbTimer */
  KonbTimerHandle = osTimerNew(KonbCallback, osTimerPeriodic, NULL, &KonbTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ConsoleTask */
  ConsoleTaskHandle = osThreadNew(StartConsoleTask, NULL, &ConsoleTask_attributes);

  /* creation of SinTask */
  SinTaskHandle = osThreadNew(StartSinTask, NULL, &SinTask_attributes);

  /* creation of MenuTask */
  MenuTaskHandle = osThreadNew(StartMenuTask, NULL, &MenuTask_attributes);

  /* creation of SquareTask */
  SquareTaskHandle = osThreadNew(StartSquareTask, NULL, &SquareTask_attributes);

  /* creation of RampTask */
  RampTaskHandle = osThreadNew(StartRampTask, NULL, &RampTask_attributes);

  /* creation of TriangleTask */
  TriangleTaskHandle = osThreadNew(StartTriangleTask, NULL, &TriangleTask_attributes);

  /* creation of TrapezoidTask */
  TrapezoidTaskHandle = osThreadNew(StartTrapezoidTask, NULL, &TrapezoidTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of ConsoleEvent */
  ConsoleEventHandle = osEventFlagsNew(&ConsoleEvent_attributes);

  /* creation of OperateEvent */
  OperateEventHandle = osEventFlagsNew(&OperateEvent_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */


  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartConsoleTask */
/**
  * @brief  Function implementing the ConsoleTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartConsoleTask */
void StartConsoleTask(void *argument)
{
  /* USER CODE BEGIN StartConsoleTask */
    uint32_t operate_flag;
    uint8_t now_interface;

  /* Infinite loop */
  for(;;)
  {
      osEventFlagsWait(ConsoleEventHandle, 0x00000001U, osFlagsWaitAny, osWaitForever);
      osDelay(10);
      //键盘情况判断
      if(1==HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1))
      {osEventFlagsSet(OperateEventHandle,0x00000004U);}
      else if(1==HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2))
      {osEventFlagsSet(OperateEventHandle,0x00000002U);}
      else if(1==HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3))
      {osEventFlagsSet(OperateEventHandle,0x00000001U);}
      else if(1==HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4))
      {osEventFlagsSet(OperateEventHandle,0x00000008U);}
      else{}
          
       //任务事件标志生成
      operate_flag=osEventFlagsGet(OperateEventHandle);
      if(0x00000002U == now_ui_pointer)
      {
          now_interface=0;
      }
      else
      {
          now_interface=1;
      }
      switch(now_interface)
      {
          case 0:
              if(operate_flag == 1 || operate_flag == 4)
              {
                  //当前页跳转
                  osEventFlagsSet(ConsoleEventHandle,now_ui_pointer);
                 ui_jump=0;
              }
              else if(operate_flag == 2)
              {
                  switch(menu_pointer)
                  { 
                      case 1:
                        osEventFlagsSet(ConsoleEventHandle,0x00000004U);//sin
                      break;
                      case 2:
                        osEventFlagsSet(ConsoleEventHandle,0x00000008U);//square
                      break;
                      case 3:
                        osEventFlagsSet(ConsoleEventHandle,0x00000010U);//ramp
                      break;
                      case 4:
                        osEventFlagsSet(ConsoleEventHandle,0x00000020U);//triangle
                      break;
                      case 5:
                        osEventFlagsSet(ConsoleEventHandle,0x00000040U);//trapezoid
                      break;
                  }
                  ui_jump=1;
                  osEventFlagsClear(OperateEventHandle,0x00000002U);
              }
              else{osEventFlagsClear(OperateEventHandle,0x00000008U);}
              break;
          case 1:
              if(operate_flag == 8)
              {
                  osEventFlagsSet(ConsoleEventHandle,0x00000002U);
                  ui_jump=1;
                  osEventFlagsClear(OperateEventHandle,0x00000008U);
              }
              else
              {
                //当前页跳转
                  osEventFlagsSet(ConsoleEventHandle,now_ui_pointer);
                  ui_jump=0;
              }
          break;
      }
          
          
  }
  /* USER CODE END StartConsoleTask */
}

/* USER CODE BEGIN Header_StartSinTask */
/**
* @brief Function implementing the SinTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSinTask */
void StartSinTask(void *argument)
{
  /* USER CODE BEGIN StartSinTask */
    //初始化
    SIN_DefType sin1;
    Sin_Init(&sin1);
    
  /* Infinite loop */
  for(;;)
  {
      
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000004U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        //参数显示
        for(uint8_t i=0;i<3;i++)
        {
            Ui_Display(i+2,&sin1.parameter[sin1.show_pointer[i]] ,0);
        }
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        
        osEventFlagsClear(OperateEventHandle,0x00000001U);
        
        sin1.show_pointer[0]=(sin1.show_pointer[0]+1) % sin1.para_number;
        sin1.show_pointer[1]=(sin1.show_pointer[1]+1) % sin1.para_number;
        sin1.show_pointer[2]=(sin1.show_pointer[2]+1) % sin1.para_number;
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000004U);
        for (uint8_t i=0;i<3;i++)
        {
            if(sin1.show_pointer[i]==0)
            {sin1.show_pointer[i]=(sin1.show_pointer[i]-1+sin1.para_number);}
            else {sin1.show_pointer[i]=(sin1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    //参数数值发生改变
    if(osEventFlagsGet(OperateEventHandle) == 0x00000010U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000010U);
        Alter_Para(&sin1.parameter[sin1.show_pointer[0]],knob1.vary,knob1.dr);
        
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    if(osEventFlagsGet(OperateEventHandle) == 0x00000002U)//是否生成波形
    {
       osEventFlagsClear(OperateEventHandle,0x00000002U);
       generate_Sin_Twave(ori_table);
       generate_Dwave(sin1.parameter[1].value,sin1.parameter[2].value,wave_table,ori_table);
       OLED_Reverse_ShowString(1,1,sin1.name);
       DAC_Start(&hdac1,sin1.parameter[0].value);
        
    }
    
  }
  /* USER CODE END StartSinTask */
}

/* USER CODE BEGIN Header_StartMenuTask */
/**
* @brief Function implementing the MenuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMenuTask */
void StartMenuTask(void *argument)
{
  /* USER CODE BEGIN StartMenuTask */
  
    
   //初始化
    MENU_DefType menu1;
    Menu_Init (&menu1);
    Knob_Start();
    osTimerStart(KonbTimerHandle,20);
    osEventFlagsSet(ConsoleEventHandle, 0x00000002U);
  /* Infinite loop */
  for(;;)
  {
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000002U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,menu1.name);
        //参数显示
        OLED_Reverse_ShowString(2,1,menu1.function[menu1.show_pointer[0]].name);
        OLED_ShowString(3,1,menu1.function[menu1.show_pointer[1]].name);
        OLED_ShowString(4,1,menu1.function[menu1.show_pointer[2]].name);
        
        DAC_Stop(&hdac1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        OLED_Clear();
        OLED_ShowString(1,1,menu1.name);
        menu1.show_pointer[0]=(menu1.show_pointer[0]+1) % menu1.func_number;
        menu1.show_pointer[1]=(menu1.show_pointer[1]+1) % menu1.func_number;
        menu1.show_pointer[2]=(menu1.show_pointer[2]+1) % menu1.func_number;
        OLED_Reverse_ShowString(2,1,menu1.function[menu1.show_pointer[0]].name);
        OLED_ShowString(3,1,menu1.function[menu1.show_pointer[1]].name);
        OLED_ShowString(4,1,menu1.function[menu1.show_pointer[2]].name);
        osEventFlagsClear(OperateEventHandle,0x00000001U);
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        for (uint8_t i=0;i<3;i++)
        {
            if(menu1.show_pointer[i]==0)
            {menu1.show_pointer[i]=(menu1.show_pointer[i]-1+menu1.func_number);}
            else {menu1.show_pointer[i]=(menu1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,menu1.name);
        OLED_Reverse_ShowString(2,1,menu1.function[menu1.show_pointer[0]].name);
        OLED_ShowString(3,1,menu1.function[menu1.show_pointer[1]].name);
        OLED_ShowString(4,1,menu1.function[menu1.show_pointer[2]].name);
        osEventFlagsClear(OperateEventHandle,0x00000004U);
    }
    menu_pointer=menu1.show_pointer[0]+1;
    

  }
  /* USER CODE END StartMenuTask */
}

/* USER CODE BEGIN Header_StartSquareTask */
/**
* @brief Function implementing the SquareTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSquareTask */
void StartSquareTask(void *argument)
{
  /* USER CODE BEGIN StartSquareTask */
    
    //初始化
    SQUARE_DefType sin1;
    SQUARE_Init(&sin1);
    
  /* Infinite loop */
  for(;;)
  {
      
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000008U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        //参数显示
        for(uint8_t i=0;i<3;i++)
        {
            Ui_Display(i+2,&sin1.parameter[sin1.show_pointer[i]] ,0);
        }
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        
        osEventFlagsClear(OperateEventHandle,0x00000001U);
        
        sin1.show_pointer[0]=(sin1.show_pointer[0]+1) % sin1.para_number;
        sin1.show_pointer[1]=(sin1.show_pointer[1]+1) % sin1.para_number;
        sin1.show_pointer[2]=(sin1.show_pointer[2]+1) % sin1.para_number;
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000004U);
        for (uint8_t i=0;i<3;i++)
        {
            if(sin1.show_pointer[i]==0)
            {sin1.show_pointer[i]=(sin1.show_pointer[i]-1+sin1.para_number);}
            else {sin1.show_pointer[i]=(sin1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    //参数数值发生改变
    if(osEventFlagsGet(OperateEventHandle) == 0x00000010U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000010U);
        Alter_Para(&sin1.parameter[sin1.show_pointer[0]],knob1.vary,knob1.dr);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    if(osEventFlagsGet(OperateEventHandle) == 0x00000002U)//是否生成波形-----------------------
    {
       osEventFlagsClear(OperateEventHandle,0x00000002U);
       uint16_t plat=sin1.parameter[3].value-1;
       uint16_t ori=100-plat-1;
       generate_Twave(ori,1,plat,1,100,ori_table);
       generate_Dwave(sin1.parameter[1].value,sin1.parameter[2].value,wave_table,ori_table);
       OLED_Reverse_ShowString(1,1,sin1.name);
       DAC_Start(&hdac1,sin1.parameter[0].value);
        
    }
    
  }
  
  /* USER CODE END StartSquareTask */
}

/* USER CODE BEGIN Header_StartRampTask */
/**
* @brief Function implementing the RampTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRampTask */
void StartRampTask(void *argument)
{
  /* USER CODE BEGIN StartRampTask */
  
    
//初始化
    RAMP_DefType sin1;
    RAMP_Init(&sin1);
    
  /* Infinite loop */
  for(;;)
  {
      
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000010U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        //参数显示
        for(uint8_t i=0;i<3;i++)
        {
            Ui_Display(i+2,&sin1.parameter[sin1.show_pointer[i]] ,0);
        }
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        
        osEventFlagsClear(OperateEventHandle,0x00000001U);
        
        sin1.show_pointer[0]=(sin1.show_pointer[0]+1) % sin1.para_number;
        sin1.show_pointer[1]=(sin1.show_pointer[1]+1) % sin1.para_number;
        sin1.show_pointer[2]=(sin1.show_pointer[2]+1) % sin1.para_number;
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000004U);
        for (uint8_t i=0;i<3;i++)
        {
            if(sin1.show_pointer[i]==0)
            {sin1.show_pointer[i]=(sin1.show_pointer[i]-1+sin1.para_number);}
            else {sin1.show_pointer[i]=(sin1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    //参数数值发生改变
    if(osEventFlagsGet(OperateEventHandle) == 0x00000010U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000010U);
        Alter_Para(&sin1.parameter[sin1.show_pointer[0]],knob1.vary,knob1.dr);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    if(osEventFlagsGet(OperateEventHandle) == 0x00000002U)//是否生成波形-----------------------
    {
       osEventFlagsClear(OperateEventHandle,0x00000002U);
       uint16_t up=sin1.parameter[3].value;
       uint16_t ori=100-up-1;
       generate_Twave(ori,up,0,1,100,ori_table);
        
       generate_Dwave(sin1.parameter[1].value,sin1.parameter[2].value,wave_table,ori_table);
       OLED_Reverse_ShowString(1,1,sin1.name);
       DAC_Start(&hdac1,sin1.parameter[0].value);
        
    }
    
  }
  
  /* USER CODE END StartRampTask */
}

/* USER CODE BEGIN Header_StartTriangleTask */
/**
* @brief Function implementing the TriangleTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTriangleTask */
void StartTriangleTask(void *argument)
{
  /* USER CODE BEGIN StartTriangleTask */
    
    
//初始化
    TRI_DefType sin1;
    TRI_Init(&sin1);
    
  /* Infinite loop */
  for(;;)
  {
      
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000020U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        //参数显示
        for(uint8_t i=0;i<3;i++)
        {
            Ui_Display(i+2,&sin1.parameter[sin1.show_pointer[i]] ,0);
        }
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        
        osEventFlagsClear(OperateEventHandle,0x00000001U);
        
        sin1.show_pointer[0]=(sin1.show_pointer[0]+1) % sin1.para_number;
        sin1.show_pointer[1]=(sin1.show_pointer[1]+1) % sin1.para_number;
        sin1.show_pointer[2]=(sin1.show_pointer[2]+1) % sin1.para_number;
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000004U);
        for (uint8_t i=0;i<3;i++)
        {
            if(sin1.show_pointer[i]==0)
            {sin1.show_pointer[i]=(sin1.show_pointer[i]-1+sin1.para_number);}
            else {sin1.show_pointer[i]=(sin1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    //参数数值发生改变
    if(osEventFlagsGet(OperateEventHandle) == 0x00000010U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000010U);
        Alter_Para(&sin1.parameter[sin1.show_pointer[0]],knob1.vary,knob1.dr);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    if(osEventFlagsGet(OperateEventHandle) == 0x00000002U)//是否生成波形-----------------------
    {
       osEventFlagsClear(OperateEventHandle,0x00000002U);
       uint16_t up=sin1.parameter[3].value;
       uint16_t down=sin1.parameter[4].value;
       uint16_t ori=100-up-down;
       generate_Twave(ori,up,0,down,100,ori_table);
        
       generate_Dwave(sin1.parameter[1].value,sin1.parameter[2].value,wave_table,ori_table);
       OLED_Reverse_ShowString(1,1,sin1.name);
       DAC_Start(&hdac1,sin1.parameter[0].value);
        
    }
    
  }
  
  
  /* USER CODE END StartTriangleTask */
}

/* USER CODE BEGIN Header_StartTrapezoidTask */
/**
* @brief Function implementing the TrapezoidTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTrapezoidTask */
void StartTrapezoidTask(void *argument)
{
  /* USER CODE BEGIN StartTrapezoidTask */
    
    
//初始化
    TRA_DefType sin1;
    TRA_Init(&sin1);
    
  /* Infinite loop */
  for(;;)
  {
      
      //等待事件产生
    now_ui_pointer = osEventFlagsWait(ConsoleEventHandle, 0x00000040U, osFlagsWaitAny, osWaitForever);
    //显示整个界面
    if(ui_jump == 1 && osEventFlagsGet(OperateEventHandle) != 0x00000010U)
    {
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        //参数显示
        for(uint8_t i=0;i<3;i++)
        {
            Ui_Display(i+2,&sin1.parameter[sin1.show_pointer[i]] ,0);
        }
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    
    //当前选项的变化
    if( osEventFlagsGet(OperateEventHandle) == 0x00000001U )
    {
        
        osEventFlagsClear(OperateEventHandle,0x00000001U);
        
        sin1.show_pointer[0]=(sin1.show_pointer[0]+1) % sin1.para_number;
        sin1.show_pointer[1]=(sin1.show_pointer[1]+1) % sin1.para_number;
        sin1.show_pointer[2]=(sin1.show_pointer[2]+1) % sin1.para_number;
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    else if(osEventFlagsGet(OperateEventHandle) == 0x00000004U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000004U);
        for (uint8_t i=0;i<3;i++)
        {
            if(sin1.show_pointer[i]==0)
            {sin1.show_pointer[i]=(sin1.show_pointer[i]-1+sin1.para_number);}
            else {sin1.show_pointer[i]=(sin1.show_pointer[i]-1) ;}
        }
        OLED_Clear();
        OLED_ShowString(1,1,sin1.name);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
        Ui_Display(3,&sin1.parameter[sin1.show_pointer[1]],0);
        Ui_Display(4,&sin1.parameter[sin1.show_pointer[2]],0);
        
    }
    //参数数值发生改变
    if(osEventFlagsGet(OperateEventHandle) == 0x00000010U)
    {
        osEventFlagsClear(OperateEventHandle,0x00000010U);
        Alter_Para(&sin1.parameter[sin1.show_pointer[0]],knob1.vary,knob1.dr);
        Ui_Display(2,&sin1.parameter[sin1.show_pointer[0]],1);
    }
    if(osEventFlagsGet(OperateEventHandle) == 0x00000002U)//是否生成波形-----------------------
    {
       osEventFlagsClear(OperateEventHandle,0x00000002U);
       uint16_t up=sin1.parameter[3].value;
       uint16_t down=sin1.parameter[4].value;
       uint16_t plat=sin1.parameter[5].value;
       uint16_t ori=100-up-down-plat;
       generate_Twave(ori,up,plat,down,100,ori_table);
        
       generate_Dwave(sin1.parameter[1].value,sin1.parameter[2].value,wave_table,ori_table);
       OLED_Reverse_ShowString(1,1,sin1.name);
       DAC_Start(&hdac1,sin1.parameter[0].value);
        
    }
    
  }
  
  /* USER CODE END StartTrapezoidTask */
}

/* KonbCallback function */
void KonbCallback(void *argument)
{
  /* USER CODE BEGIN KonbCallback */
    Get_Knob_value(&knob1);
    if(knob1.vary != 0)
    {
        osEventFlagsSet(OperateEventHandle,0x00000010U);
        osEventFlagsSet(ConsoleEventHandle,now_ui_pointer);
    }
  /* USER CODE END KonbCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    osEventFlagsSet(ConsoleEventHandle,0x00000001U);
}



/* USER CODE END Application */

