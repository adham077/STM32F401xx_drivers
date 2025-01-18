#ifndef RCC_H_
#define RCC_H_
#include "std_types.h"

#define HSI_CLK_FREQ            (16000000ULL)  /*16MHz*/
#define HSE_CLK_FREQ            (24000000ULL)   /*24MHz*/

#define MAX_AHB_CLK_FREQ        (84000000ULL) /*84MHz*/
#define MAX_AB1_CLK_FREQ        (42000000ULL) /*42MHz*/
#define MAX_AB2_CLK_FREQ        (84000000ULL) /*42MHz*/

#define MAX_CLK_TYPE_INDEX      2
#define MAX_PERIPHERAL_INDEX    114
#define MAX_BYPASS_VAL          2
#define MAX_PLL_CLK_INDEX       1
#define MAX_BUS_INDEX           2

#define RCC_NOT_READY           0
#define RCC_READY               1   

#define NO_OF_BUSES             4   /*AHB1,AHB2,APB1,APB2*/

/*Error Status*/
typedef enum{
    RCC_enuOK,
    RCC_enuNOK,
    RCC_enu_INVALID_CLK_TYPE,
    RCC_enu_CLK_NOT_READY,
    RCC_enu_NULL_POINTER,
    RCC_enu_INVALID_PERIPHERAL,
    RCC_enu_INVALID_PARAMETER,
    RCC_enu_TIMEOUT,
    RCC_enu_err_PLL_ON,
    RCC_enu_INVALID_Q,
    RCC_enu_INVALID_M,
    RCC_enu_INVALID_P,
    RCC_enu_INVALID_N,
    RCC_enu_INVALID_BUS,
    RCC_enu_INVALID_PRESCALER,
    RCC_enu_INVALID_CLK_CFG
}RCC_enuErorrStatus_t;

/*Clock Types*/
typedef enum{
    RCC_enu_HSI,
    RCC_enu_HSE,
    RCC_enu_PLL
}RCC_enuCLK_t;

typedef enum{
    RCC_enu_HSE_BYPASS_OFF,
    RCC_enu_HSE_BYPASS_ON
}RCC_HSE_BYPASS_t;

/*Buses*/
typedef enum{
    RCC_enu_AHB,
    RCC_enu_APB1,
    RCC_enu_APB2
}RCC_enuBuses_t;

/*Peripherals*/
typedef enum{
    /*AHB1 Peripherals*/
    RCC_enu_GPIOA,
    RCC_enu_GPIOB,
    RCC_enu_GPIOC,
    RCC_enu_GPIOD,
    RCC_enu_GPIOE,
    RCC_enu_GPIOH=7,
    RCC_enu_CRC=12,
    RCC_enu_DMA1=21,
    RCC_enu_DMA2,

    /*AHB2 Peripherals*/
    RCC_enu_OTGFS=41,

    /*APB1 Peripherals*/
    RCC_enu_TIM2=64,
    RCC_enu_TIM3,
    RCC_enu_TIM4,
    RCC_enu_TIM5,
    RCC_enu_WWDG=75,
    RCC_enu_SPI2=78,
    RCC_enu_SPI3,
    RCC_enu_USART2=81,
    RCC_enu_USART3,
    RCC_enu_I2C1=85,
    RCC_enu_I2C2,
    RCC_enu_I2C3,
    RCC_enu_PWR=92,

    /*APB2 Peripherals*/
    RCC_enu_TIM1=96,
    RCC_enu_USART1=100,
    RCC_enu_USART6,
    RCC_enu_ADC1=104,
    RCC_enu_SDIO=107,
    RCC_enu_SPI1=108,
    RCC_enu_SPI4, 
    RCC_enu_SYSCFG,
    RCC_enu_TIM9=112,
    RCC_enu_TIM10,
    RCC_enu_TIM11,
    RCC_enu_SRAM1,
    RCC_enu_FLITF
}RCC_enuPeripherals_t;


/*Function Prototypes*/

/*Enable Clock (HSI,HSE or PLL)*/
RCC_enuErorrStatus_t RCC_enuEnableClk(RCC_enuCLK_t Copy_enuClk);

/*Disable clock (HSI,HSE or PLL)*/
RCC_enuErorrStatus_t RCC_enuDisableClk(RCC_enuCLK_t Copy_enuClk);

/*Check Clock Status (HSI,HSE or PLL)*/
RCC_enuErorrStatus_t RCC_enuClkStatus(RCC_enuCLK_t Copy_enuClk,uint32_t* Add_u8);

/*Get System Clock Source (HSI,HSE or PLL)*/
RCC_enuCLK_t RCC_enuGetSysClk(void);

/*Set HSE bypass (ON/OFF)*/
RCC_enuErorrStatus_t RCC_enuBypassHSE(RCC_HSE_BYPASS_t Copy_enuBypass);

/*PLL Configuration 
valid inputs: 
    M in the range of (2->63)
    N in the range of (192->432)
    P {2,4,6,8}
    Q in the range of (2->15)

M parameter must be configured accordingly for vco input frequency to be in the range of
(1->2MHz) and recommended to be (2MHz)
Q parameter must be configured accordingly for an output frequency of 48Mhz
*/
RCC_enuErorrStatus_t RCC_enuConfigurePLL(RCC_PLL_stParameters_t Loc_stParams);
/*Set System Clock Source (HSI,HSE or PLL)*/
RCC_enuErorrStatus_t RCC_enuSetSysClk(RCC_enuCLK_t Copy_enuClkSrc);

/*Enable Peripheral Clock*/
RCC_enuErorrStatus_t RCC_enuEnablePeriPheralClk(RCC_enuPeripherals_t Copy_enuPeripheral);

/*Disable Peripheral Clock*/
RCC_enuErorrStatus_t RCC_enuDisablePeriPheralClk(RCC_enuPeripherals_t Copy_enuPeripheral);

/*Reset Peripheral*/
RCC_enuErorrStatus_t RCC_enuResetPeriPheral(RCC_enuPeripherals_t Copy_enuPeripheral);

/*Enable Peripheral in low power mode*/
RCC_enuErorrStatus_t RCC_EnableLowPowerMode(RCC_enuPeripherals_t Copy_enuPeripheral);

/*Disable Peripheral in low power mode*/
RCC_enuErorrStatus_t RCC_DisableLowPowerMode(RCC_enuPeripherals_t Copy_enuPeripheral);

/*Get AHB,APB1 or APB2 bus frequency*/
RCC_enuErorrStatus_t RCC_enuGetBusFreq(RCC_enuBuses_t Copy_enuBus,uint32_t* Add_u32Freq);

/*Get system clock*/
uint32_t RCC_getSystickClk(void);

/*Bus Prescaler Configuration
valid inputs:
    AHB : prescaler values {2,4,8,16,64,128,256,512}
    APB1: prescaler values {2,4,8,16}
    APB2: prescaler values {2,4,8,16}
    only a valid configuration of parameters will be accepted:
    AHB MAX FREQ : 84 MHZ
    APB1 MAX FREQ: 48 MHZ
    APB2 MAX FREQ: 84 MHZ
*/
RCC_enuErorrStatus_t RCC_enuSetBusPrescaler(RCC_enuBuses_t Copy_enuBus,uint32_t Copy_u32Prescaler);

#endif