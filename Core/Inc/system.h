extern uint32_t SystemCoreClock;            /* System Clock Frequency  */
extern const uint8_t  AHBPrescTable[16U];   /* AHB prescalers table values */
extern const uint8_t  APBPrescTable[8U];    /* APB prescalers table values */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
