/* *
* @brief    Configuration Clocking of MCU:
*           -SYSCLK config
*           -AHB and HCLK config
*           -APB1, APB2 config
            -SysTick()
            -GetTick()
            
            Configuration Clocking of others stuff
*/
#include "stm32f103xb.h"
#include "rcc.h"
#include "macro.h"
#include "system.h"

#ifndef   HSE_STARTUP_TIMEOUT
  #define HSE_STARTUP_TIMEOUT   100U     
#endif

__IO uint32_t Ticks; /* Amounts of ticks from launch moment*/



/********* Clocking GPIO module ****************/

/* Clocking PORT C for LED PIN*/
void RCC_LED(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN_Msk); // Input Output Port C Enable clocking
}




/* SystemClockConfig function. 
 * @brief: 
 * Clocking SYSCLK, AHB, APB1, APB2
 * Init SysTick
 *    -SysTick interrupt every 1 millisecond call IncTick.
 *    -HSE = 8 Mhz
 *    -PLL = x9
 *    -Freq SYSCLK = HSE - 72 MHz
 *    -AHB = 72 Mhz
 *    -APB1 = 72 Mhz, APB2 = 36 Mhz;
 *    -FLASH LATENCY = 2
 */
void SystemClockConfig(void)
{
  #define AMNT_DIV 1000UL   /* Divider of the freq SysTick. equal to amnt counts in 1 sec */

  SystemCoreClockUpdate();
  SysTickInit(AMNT_DIV);    /* Start of SysTick with CoreClock value */

  /* FLASH Latency*/
  SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_2);

  /* HSE Setting */
  SET_BIT(RCC->CR, RCC_CR_HSEON_Msk); //HSE = 8 Mhz

  /* Delay for turning on HSE */
  uint32_t tick = GetTick();
  while(READ_BIT(RCC->CR, RCC_CR_HSERDY_Msk) == 0)
  {
    if (GetTick() - tick > HSE_STARTUP_TIMEOUT )
    { 
      break; //Timeout
    }
  }
  
  /* PLL and buses setting  */
  SET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_HSE); // :1 in PLLXTRPE
  SET_BIT(RCC->CFGR, RCC_CFGR_PLLMULL9_Msk); //PLL x 9, Freq sys = 8Mhz x 9 = 72
  SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC_Msk);   //PLL source HSE

  SET_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);    //AHB Prescaler = 1
  SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);   //APB1 Prescaler = 2 
  SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV1);   //APB2 Prescaler = 1y

  
  /* PLL ON and SYSCKL Setting */
  SET_BIT(RCC->CR, RCC_CR_PLLON_Msk);      //PLL On
  while(!READ_BIT(RCC->CR, RCC_CR_PLLRDY_Msk)); //waiting

  SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);     //Switch Switcher to PLL */


  SystemCoreClockUpdate();
  SysTickInit(AMNT_DIV);  /* Refresh of SysTick frequency */
}




/*  */
uint16_t SysTickInit(uint32_t amnt)
{
  if (SysTick_Config( SystemCoreClock / amnt ) == !0) /* Freq in Mhz.  Hz is amnt/sec.  amnt = how many counts in second will be noted*/
  {
    UsageFault_Handler();
  }
  return 0;
}

void IncTick(void)
{
  Ticks++;
}

uint32_t GetTick(void)
{
  return Ticks;
}


void SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

void ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


void Delay(uint32_t ms)
{
  /* Waiting for some delay in ms */
  uint32_t start = GetTick();
  while ((start + ms) > GetTick());
}