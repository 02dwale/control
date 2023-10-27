void SystemClockConfig(void);
uint16_t SysTickInit(uint32_t amnt_in_sec);
void IncTick(void);
uint32_t GetTick(void);
void SuspendTick(void);
void ResumeTick(void);
void Delay(uint32_t ms);
void RCC_LED(void);


