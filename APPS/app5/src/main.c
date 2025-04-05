#include "led.h"
#include "scheduler.h"
#include "time2_5.h"

#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)  

void EnableFPU(void) {
    SCB_CPACR |= ((3UL << 10*2) | (3UL << 11*2));  
    __asm volatile("DSB");
    __asm volatile("ISB");
}

int main(void){
    EnableFPU();
    GPIO_stPinCFG_t gpioCfg = {
        .port = GPIO_enu_GPIOA,
        .pin = GPIO_enu_PIN0,
        .speed = GPIO_enu_high_speed,
        .AltFn = GPIO_enu_AltFn1,
        .mode = GPIO_enu_ALT_FN,
        .OutputType = GPIO_enu_PUSH_PULL,
        .InputType = GPIO_enu_NO_PU_PD
    };

    TIM2_5_stPWMCfg_t pwmCfg = {
        .Channel = TIM2_5_enuCH1,
        .Timer = TIM2_5_enuTIM2,
        .Frequency = 60,
        .SystemClkFreq = 16000000,
        .DutyCycle = 12.5
    };

    RCC_enuCtlPeripheral(RCC_GPIOA,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_TIM2,RCC_PER_ON);

    GPIO_enuCfgPin(&gpioCfg);
    TIM2_5_enuCfgPWM(&pwmCfg);
     int x = 10;
    while(1){
        x++;
    }

    return 0;
}