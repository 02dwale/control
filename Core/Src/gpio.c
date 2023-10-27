/* IN file RCC enable clocking of gpio block. */

#include "stm32f103xb.h" /* Define base adress and base structures of registers */
#include "gpio.h"       /* Declare of functions defining in this file */
#include "macro.h"      /* Including  stdint.h*/

void GPIOC_13_CFG_Output(void) 
{
    /*Configuration pin C13 in "01 - " General purpose output: Open-drain"*/
    CLEAR_BIT(GPIOC->CRH, GPIO_CRH_CNF13_1); /* Reset first bit of Configuration flag of 13 pin of Configuration register High (7-15 pins) - */
    SET_BIT(GPIOC->CRH, GPIO_CRH_CNF13_0);   /* Set second bit of flag 13 pin in Config Register High */
    
    /*Configuration pin C13 in  01 - "Output MODE 10 MHz" */
    CLEAR_BIT(GPIOC->CRH, GPIO_CRH_MODE13_1); /* Reset first bit of mode flag of 13 pin in CRG (7-15 pin)*/
    SET_BIT(GPIOC->CRH, GPIO_CRH_MODE13_0);   /* Reset first bit of mode flag of 13 pin in CRG (7-15 pin)*/
}





