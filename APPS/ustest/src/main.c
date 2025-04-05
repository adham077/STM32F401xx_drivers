#include "ultrasonic.h"
#include "scheduler.h"

#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)  

void EnableFPU(void) {
    SCB_CPACR |= ((3UL << 10*2) | (3UL << 11*2));  
    __asm volatile("DSB");
    __asm volatile("ISB");
}

void pulseRunnable(void){
    TIM_enuGeneratePulse(TIM2_5_enuTIM4);
}

void ICUCallBack(uint32_t val){
    static uint8_t state = 0;
    volatile uint32_t myVal = 0;

    if(state == 0){
        TIM2_5_enuSetCountVal(TIM2_5_enuTIM2,0);
        state = 1;
        TIM2_5_enuICUenableFallingEdge(TIM2_5_enuTIM2,TIM2_5_enuCH1);
    }
    else{
        myVal = val;
        state = 0;
        TIM2_5_enuICUenableRisingEdge(TIM2_5_enuTIM2,TIM2_5_enuCH1);
    }
}

int main(void){
    EnableFPU();

    TIM2_5_stICUCfg_t Tim_icuCfg = {
        .CallBack = ICUCallBack,
        .Mode = TIM2_5_enuICURisingEdge,
        .Prescaler = TIM2_5_enuICUNoPre,
        .Filter = 1,
        .Timer = TIM2_5_enuTIM2,
        .Channel = TIM2_5_enuCH1,
    };

    TIM2_5_stPulseCfg_t Tim_pulseCfg = {
        .Timer = TIM2_5_enuTIM4,
        .PulseWidthUs = 10,
        .SystemClockFreq = 16000000,
        .Channel = TIM2_5_enuCH1
    };

    GPIO_stPinCFG_t GpioCfg1 = {
        .port = GPIO_enu_GPIOA,
        .pin = GPIO_enu_PIN0,
        .AltFn = GPIO_enu_AltFn1,
        .mode = GPIO_enu_ALT_FN,
        .InputType = GPIO_enu_PD,
        .OutputType = GPIO_enu_PUSH_PULL,
        .speed = GPIO_enu_high_speed
    };

    GPIO_stPinCFG_t GpioCfg2 = {
        .port = GPIO_enu_GPIOB,
        .pin = GPIO_enu_PIN6,
        .AltFn = GPIO_enu_AltFn2,
        .mode = GPIO_enu_ALT_FN,
        .InputType = GPIO_enu_PD,
        .OutputType = GPIO_enu_PUSH_PULL,
        .speed = GPIO_enu_high_speed
    };


    SCHED_stTaskCfg_t pulseRun = {
        .CallBack = pulseRunnable,
        .CycleTime = 100,
        .InitialWait = 0,
        .Priority = 0
    };

    SCHED_vInit();
    SCHED_enuAddRunnable(&pulseRun);

    RCC_enuCtlPeripheral(RCC_GPIOA,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_GPIOB,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_TIM2,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_TIM4,RCC_PER_ON);

    GPIO_enuCfgPin(&GpioCfg1);
    GPIO_enuCfgPin(&GpioCfg2);
    NVIC_enuEnableIRQn(NVIC_enuTIM2);

    TIM2_5_enuICUInit(&Tim_icuCfg);
    TIM2_5_enuSetPrescalerVal(TIM2_5_enuTIM2,15);
    TIM2_5_enuSetARRVal(TIM2_5_enuTIM2,0xFFFF);
    TIM2_5_enuUpdateRegs(TIM2_5_enuTIM2);
    TIM2_5_enuSetCountVal(TIM2_5_enuTIM2,0);

    TIM2_5_enuStartICU(TIM2_5_enuTIM2,TIM2_5_enuCH1);


    TIM_enuInitPulse(&Tim_pulseCfg);


    SCHED_vStart();

    return 0;
}