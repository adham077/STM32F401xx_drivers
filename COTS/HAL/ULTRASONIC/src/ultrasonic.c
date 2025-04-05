#include "ultrasonic.h"

#define Ultrasonic_NO_OF_TIMERS         4

static void Ultrasonic1_vICUCallBack(uint32_t value);
static void Ultrasonic2_vICUCallBack(uint32_t value);

void Ultrasonic1_vRunnable(void);
void Ultrasonic2_vRunnable(void);

static volatile uint32_t Ultrasonic1_u32PulseWidth = 0;
static volatile uint32_t Ultrasonic2_u32PulseWidth = 0;

static void (*Ultrasonic_arrRunnables[NO_OF_ULTRASONICS])(void) = {
    Ultrasonic1_vRunnable,
    Ultrasonic2_vRunnable
};

static void (*Ultrasonic_arrCallBacks[NO_OF_ULTRASONICS])(uint32_t) = {
    Ultrasonic1_vICUCallBack,
    Ultrasonic2_vICUCallBack
};

static Ultrasonic_onMeasurmentCompletedCB Ultrasonic_arrUserCallBacks[NO_OF_ULTRASONICS] = {NULL};

static float32_t Ultrasonic_arrCalValues[NO_OF_ULTRASONICS] = {
  0.0  
};

uint64_t Ultrasonic_arrTIMClkMasks[Ultrasonic_NO_OF_TIMERS] = {
    RCC_TIM2,
    RCC_TIM3,
    RCC_TIM4,
    RCC_TIM5
};

NVIC_enuIRQn_t Ultrasonic_arrTimerIrqs[Ultrasonic_NO_OF_TIMERS] = {
    NVIC_enuTIM2,
    NVIC_enuTIM3,
    NVIC_enuTIM4,
    NVIC_enuTIM5
};

void Ultrasonic_vInit(void){
    uint8_t i=0;
    uint64_t Loc_u64GpioClkMask = 0;
    uint32_t Loc_u32SystemClk = 0;
    uint32_t Loc_u32InitialWait = 0;
    void (*Loc_u32Runnable)(void) = NULL;
    GPIO_stPinCFG_t Loc_stGpioCfg = {0};
    TIM2_5_stICUCfg_t Loc_stIcuCfg = {0};
    TIM2_5_stPulseCfg_t Loc_stPulseCfg = {0};
    uint32_t Loc_u32RunnablePriority = 23; 
    RCC_enuGetClkFreq(RCC_enu_AHB,&Loc_u32SystemClk);

    for(;i<NO_OF_ULTRASONICS;i++){
        if(Ultrasonic_arrCfgs[i].EchoPin.Port == GPIO_enu_GPIOH){
            Loc_u64GpioClkMask |= RCC_GPIOH;
        }
        else{
            Loc_u64GpioClkMask |= (1 << Ultrasonic_arrCfgs[i].EchoPin.Port);
        }

        if(Ultrasonic_arrCfgs[i].TriggerPin.Port == GPIO_enu_GPIOH){
            Loc_u64GpioClkMask |= RCC_GPIOH;
        }
        else{
            Loc_u64GpioClkMask |= (1 << Ultrasonic_arrCfgs[i].TriggerPin.Port);
        }

        RCC_enuCtlPeripheral(
            Ultrasonic_arrTIMClkMasks[Ultrasonic_arrCfgs[i].EchoPin.Timer],
            RCC_PER_ON
        );

        RCC_enuCtlPeripheral(
            Ultrasonic_arrTIMClkMasks[Ultrasonic_arrCfgs[i].TriggerPin.Timer],
            RCC_PER_ON 
        );

        NVIC_enuClearPendingIRQn(
            Ultrasonic_arrTimerIrqs[Ultrasonic_arrCfgs[i].TriggerPin.Timer]
        );
    
        NVIC_enuClearPendingIRQn(
            Ultrasonic_arrTimerIrqs[Ultrasonic_arrCfgs[i].EchoPin.Timer]
        );

        NVIC_enuEnableIRQn(
            Ultrasonic_arrTimerIrqs[Ultrasonic_arrCfgs[i].TriggerPin.Timer]
        );
        NVIC_enuEnableIRQn(
            Ultrasonic_arrTimerIrqs[Ultrasonic_arrCfgs[i].EchoPin.Timer]
        );

        Ultrasonic_arrCalValues[i] = ULTRASONIC_DEFAULT_CAL_FACTOR;
    }

    RCC_enuCtlPeripheral(Loc_u64GpioClkMask,RCC_PER_ON);

    for(i=0;i<NO_OF_ULTRASONICS;i++){

        Loc_stGpioCfg.port = Ultrasonic_arrCfgs[i].EchoPin.Port;
        Loc_stGpioCfg.pin = Ultrasonic_arrCfgs[i].EchoPin.Pin;
        Loc_stGpioCfg.mode = GPIO_enu_ALT_FN;
        Loc_stGpioCfg.AltFn = Ultrasonic_arrCfgs[i].EchoPin.altFun;
        Loc_stGpioCfg.speed = GPIO_enu_high_speed;
        Loc_stGpioCfg.InputType = GPIO_enu_PD;
        Loc_stGpioCfg.OutputType = GPIO_enu_PUSH_PULL;
        GPIO_enuCfgPin(&Loc_stGpioCfg);

        Loc_stGpioCfg.port = Ultrasonic_arrCfgs[i].TriggerPin.Port;
        Loc_stGpioCfg.pin = Ultrasonic_arrCfgs[i].TriggerPin.Pin;
        Loc_stGpioCfg.mode = GPIO_enu_ALT_FN;
        Loc_stGpioCfg.AltFn = Ultrasonic_arrCfgs[i].TriggerPin.altFun;
        Loc_stGpioCfg.speed = GPIO_enu_high_speed;
        Loc_stGpioCfg.InputType = GPIO_enu_PD;
        Loc_stGpioCfg.OutputType = GPIO_enu_PUSH_PULL;
        
        GPIO_enuCfgPin(&Loc_stGpioCfg);

        Loc_stIcuCfg.Timer = Ultrasonic_arrCfgs[i].EchoPin.Timer;
        Loc_stIcuCfg.Channel = Ultrasonic_arrCfgs[i].EchoPin.Channel;
        Loc_stIcuCfg.Prescaler = TIM2_5_enuICUNoPre;
        Loc_stIcuCfg.Mode = TIM2_5_enuICURisingEdge;
        Loc_stIcuCfg.Filter = 1;
        Loc_stIcuCfg.CallBack = Ultrasonic_arrCallBacks[i];

        TIM2_5_enuICUInit(&Loc_stIcuCfg);
        TIM2_5_enuSetPrescalerVal(
            Ultrasonic_arrCfgs[i].EchoPin.Timer,
            15
        );
        TIM2_5_enuSetARRVal(
            Ultrasonic_arrCfgs[i].EchoPin.Timer,
            0xFFFF 
        );
        TIM2_5_enuUpdateRegs(Ultrasonic_arrCfgs[i].EchoPin.Timer);
        TIM2_5_enuSetCountVal(Ultrasonic_arrCfgs[i].EchoPin.Timer,0);
        TIM2_5_enuStartICU(
            Ultrasonic_arrCfgs[i].EchoPin.Timer,
            Ultrasonic_arrCfgs[i].EchoPin.Channel
        );

        Loc_stPulseCfg.Timer = Ultrasonic_arrCfgs[i].TriggerPin.Timer;
        Loc_stPulseCfg.Channel = Ultrasonic_arrCfgs[i].TriggerPin.Channel;
        Loc_stPulseCfg.PulseWidthUs = Ultrasonic_arrCfgs[i].pulseWidth;
        Loc_stPulseCfg.SystemClockFreq = Loc_u32SystemClk;
        TIM_enuInitPulse(&Loc_stPulseCfg);

        Loc_u32Runnable = Ultrasonic_arrRunnables[i];

        SCHED_stTaskCfg_t Loc_stTask = {
            .CycleTime = 120,
            .InitialWait = Loc_u32InitialWait,
            .Priority = Loc_u32RunnablePriority,
            .CallBack = Loc_u32Runnable
        };
        Loc_u32InitialWait += 60;
        Loc_u32RunnablePriority++;
        SCHED_enuAddRunnable(&Loc_stTask);
    }
}

Ultrasonic_enuErrorStatus_t Ultrasonic_enuSendTrigger(uint8_t Copy_u8Ultrasonic){
    
    Ultrasonic_enuErrorStatus_t Loc_enuStatus = Ultrasonic_enu_OK;
    
    if(Copy_u8Ultrasonic >= NO_OF_ULTRASONICS){
        Loc_enuStatus = Ultrasonic_enu_INVALID_ULTRASONIC;
    }
    else{
        TIM_enuGeneratePulse(
            Ultrasonic_arrCfgs[Copy_u8Ultrasonic].TriggerPin.Timer
        );
    }
    return Loc_enuStatus;
}

uint32_t UltraSonic_u32GetPulseWidth(uint8_t Copy_u8Ultrasonic){
    if(Copy_u8Ultrasonic == ULTRASONIC_1){
        return Ultrasonic1_u32PulseWidth;
    }
    else{
        return Ultrasonic2_u32PulseWidth;
    }
}

Ultrasonic_enuErrorStatus_t Ultrasonic_enuSetCalFactor(uint8_t Copy_u8Ultrasonic,
float32_t Copy_f32CalVal){
    
    Ultrasonic_enuErrorStatus_t Loc_enuStatus = Ultrasonic_enu_OK;
    if(Copy_u8Ultrasonic >= NO_OF_ULTRASONICS){
        Loc_enuStatus = Ultrasonic_enu_INVALID_ULTRASONIC;
    }
    else{
        Ultrasonic_arrCalValues[Copy_u8Ultrasonic] = Copy_f32CalVal;
    }
    return Loc_enuStatus;
}

float32_t Ultrasonic_f32GetDistanceCm(uint8_t Copy_u8Ultrasonic){
    if(Copy_u8Ultrasonic == ULTRASONIC_1){
        return (((float32_t)Ultrasonic1_u32PulseWidth)*Ultrasonic_arrCalValues[ULTRASONIC_1]);
    }
    else{
        return (((float32_t)Ultrasonic2_u32PulseWidth)*Ultrasonic_arrCalValues[ULTRASONIC_2]);
    }
}

Ultrasonic_enuErrorStatus_t Ultrasonic_enuRegisterCallBack(
    uint8_t Copy_u8Ultrasonic,Ultrasonic_onMeasurmentCompletedCB Add_CB
){
    Ultrasonic_enuErrorStatus_t Loc_enuStatus = Ultrasonic_enu_OK;
    
    if(Copy_u8Ultrasonic >= NO_OF_ULTRASONICS){
        Loc_enuStatus = Ultrasonic_enu_INVALID_ULTRASONIC;
    }
    else{
        Ultrasonic_arrUserCallBacks[Copy_u8Ultrasonic] = Add_CB;
    }
    return Loc_enuStatus;
}

static void Ultrasonic1_vICUCallBack(uint32_t value){
    
    static uint8_t Loc_u8EdgeState = 0;
    if(Loc_u8EdgeState == 0){
        Loc_u8EdgeState = 1;
        TIM2_5_enuSetCountVal(Ultrasonic_arrCfgs[ULTRASONIC_1].EchoPin.Timer,0);
        TIM2_5_enuICUenableFallingEdge(
            Ultrasonic_arrCfgs[ULTRASONIC_1].EchoPin.Timer,
            Ultrasonic_arrCfgs[ULTRASONIC_1].EchoPin.Channel
        );
    }
    else{
        Ultrasonic1_u32PulseWidth = value;
        Loc_u8EdgeState = 0;
        if(Ultrasonic_arrUserCallBacks[ULTRASONIC_1] != NULL){
            Ultrasonic_arrUserCallBacks[ULTRASONIC_1](Ultrasonic1_u32PulseWidth);
        }
        TIM2_5_enuICUenableRisingEdge(
            Ultrasonic_arrCfgs[ULTRASONIC_1].EchoPin.Timer,
            Ultrasonic_arrCfgs[ULTRASONIC_1].EchoPin.Channel
        );
    }
}

static void Ultrasonic2_vICUCallBack(uint32_t value){
    
    static uint8_t Loc_u8EdgeState = 0;
    if(Loc_u8EdgeState == 0){
        Loc_u8EdgeState = 1;
        TIM2_5_enuSetCountVal(Ultrasonic_arrCfgs[ULTRASONIC_2].EchoPin.Timer,0);
        TIM2_5_enuICUenableFallingEdge(
            Ultrasonic_arrCfgs[ULTRASONIC_2].EchoPin.Timer,
            Ultrasonic_arrCfgs[ULTRASONIC_2].EchoPin.Channel
        );
    }
    else{
        Ultrasonic2_u32PulseWidth = value;
        Loc_u8EdgeState = 0;
        if(Ultrasonic_arrUserCallBacks[ULTRASONIC_2] != NULL){
            Ultrasonic_arrUserCallBacks[ULTRASONIC_2](Ultrasonic1_u32PulseWidth);
        }
        TIM2_5_enuICUenableRisingEdge(
            Ultrasonic_arrCfgs[ULTRASONIC_2].EchoPin.Timer,
            Ultrasonic_arrCfgs[ULTRASONIC_2].EchoPin.Channel
        );
    }
}

void Ultrasonic1_vRunnable(void){
    Ultrasonic_enuSendTrigger(ULTRASONIC_1);
}

void Ultrasonic2_vRunnable(void){
    Ultrasonic_enuSendTrigger(ULTRASONIC_2);
}