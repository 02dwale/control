/* File of the functional program */

#include "stm32f103xb.h"
#include "macro.h"

void GPIOC_13_Toggle(void)
{
    /* Outup data register 13 Pin INVERT by XOR (^) operator*/
    TOGGLE_BIT(GPIOC->ODR, GPIO_ODR_ODR13);
}