#include "ultrasonic.h"

Ultrasonic_stCfg_t Ultrasonic_arrCfgs[NO_OF_ULTRASONICS] = {
    [ULTRASONIC_1] = {
        .EchoPin = {
            .Port = GPIO_enu_GPIOB,
            .Pin = GPIO_enu_PIN4, 
            .Timer = TIM2_5_enuTIM3,
            .Channel = TIM2_5_enuCH1,
            .altFun = GPIO_enu_AltFn2
        },
        .TriggerPin = {
            .Port = GPIO_enu_GPIOB,
            .Pin = GPIO_enu_PIN6,
            .Timer = TIM2_5_enuTIM4,
            .Channel = TIM2_5_enuCH1,
            .altFun = GPIO_enu_AltFn2
        },
        .pulseWidth = 10
    },
    [ULTRASONIC_2] = {
        .EchoPin = {
            .Port = GPIO_enu_GPIOB,
            .Pin = GPIO_enu_PIN5, 
            .Timer = TIM2_5_enuTIM3,
            .Channel = TIM2_5_enuCH2,
            .altFun = GPIO_enu_AltFn2
        },
        .TriggerPin = {
            .Port = GPIO_enu_GPIOB,
            .Pin = GPIO_enu_PIN10,
            .Timer = TIM2_5_enuTIM2,
            .Channel = TIM2_5_enuCH3,
            .altFun = GPIO_enu_AltFn1
        },
        .pulseWidth = 10
    }
};