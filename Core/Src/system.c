/* This file describes SystemInit(), SystemCoreClock variable and SystemCoreClockUpdate() 
* Note: SystemInit() calls before main() from startup file. 
*/
  
#include "stm32f103xb.h"
#include "system.h"
#include "macro.h"
#include <stdint.h>

#if !defined  (HSE_VALUE) 
  #define HSE_VALUE               8000000U /* Default value of the External oscillator in Hz. */                                       
#endif

#if !defined  (HSI_VALUE)
  #define HSI_VALUE               8000000U /* Default value of the Internal oscillator in Hz. */                                
#endif

uint32_t SystemCoreClock;
const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9}; //Powers of 2
const uint8_t APBPrescTable[8U] =  {0, 0, 0, 0, 1, 2, 3, 4};


/* SystemInit() - Setup the MCU system */

void SystemInit(void)
{

}  



/* SystemCoreClockUpdate() - Update SystemCoreClock global variable according to clock register values */

void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0U, pllmull = 0U, pllsource = 0U;

  /* Get SYSCLK source -------------------------------------------------------*/
  
  tmp = RCC->CFGR & RCC_CFGR_SWS; /* SWS - system clock switch status */

  switch (tmp)
  {
    case 0x00U:  /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04U:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08U:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL; /* PLL multiplication factor */
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC; /* PLL entry clock source*/
      
      pllmull = ( pllmull >> 18U) + 2U; //If PLLMUL has 0000 then we multiply by 2 by default
      
      /* Source of PLLmul*/
      if (pllsource == 0x00U)
      {
        /* HSI oscillator is a source for PLL, HSI clock divided by 2 selected as PLL clock entry */
        SystemCoreClock = (HSI_VALUE >> 1U) * pllmull;
      }
      else
      {
        /* HSE selected as PLL clock entry */
        if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t) RESET)
        {
          /* HSE oscillator clock divided by 2 */
          SystemCoreClock = (HSE_VALUE >> 1U) * pllmull;
        }
        else
        {
          SystemCoreClock = HSE_VALUE * pllmull;
        }
      }
      break;

    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
  
  /* Compute HCLK clock frequency ---------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4U)]; //4U - its POS of the BIT MASK HPRE flags in CFGR reg and we choose one elemnets by pos of the table
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;  //Divide of core clock by tmp
}
