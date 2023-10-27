/*
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  *                     -SysTick interrupt every 1 millisecond call IncTick.
  *                     -Freq SYSCLK = 72 MHz
  *                     -AHB = 72 Mhz
  *                     -APB1 = 36 Mhz, APB2 = 72 Mhz;
  ******************************************************************************
  */

#include "main.h"

int main(void)
{
  SystemClockConfig();
  RCC_LED();
  GPIOC_13_CFG_Output();
  
  //__disable_irq(); 
  
  while (1)
  {
    GPIOC_13_Toggle();
    Delay(1000);
  }
}




