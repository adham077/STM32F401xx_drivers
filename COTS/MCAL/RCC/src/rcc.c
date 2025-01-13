#include "rcc.h"
#include "rcc_priv.h"

/*Pointer to the RCC registers*/
RCC_stReg_t* RCC = (RCC_stReg_t*)(RCC_BASE);

/*Struct to store the parameter values for PLL configuration*/
RCC_PLL_stParameters_t RCC_stPLL_Parameters = {
    /*Default Parameter Values*/
    .PLL_CLK = RCC_enu_HSI,
    .PLL_M = 1,
    .PLL_N = 1,
    .PLL_P = 1,
    .PLL_Q = 1
};

/*Struct to store the prescaler values for each bus*/
RCC_stBusPrescaler_t RCC_stBusPrescaler = {
    /*Default Prescaler Values*/
    .AHB = 1,
    .APB1 = 1,
    .APB2 = 1
};

/*Array to store the peripherals that are connected to the buses*/
static const uint8_t  RCC_arrPeripherals[NO_OF_BUSES*32] = {
    /*AHB1 Peripherals*/
    [RCC_enu_GPIOA] = 1,
    [RCC_enu_GPIOB] = 1,
    [RCC_enu_GPIOC] = 1,
    [RCC_enu_GPIOD] = 1,
    [RCC_enu_GPIOE] = 1,
    [RCC_enu_GPIOH] = 1,
    [RCC_enu_CRC] = 1,
    [RCC_enu_DMA1] = 1,
    [RCC_enu_DMA2] = 1,

    /*AHB2 Peripherals*/
    [RCC_enu_OTGFS] = 1,

    /*APB1 Peripherals*/
    [RCC_enu_TIM2] = 1,
    [RCC_enu_TIM3] = 1,
    [RCC_enu_TIM4] = 1,
    [RCC_enu_TIM5] = 1,
    [RCC_enu_WWDG] = 1,
    [RCC_enu_SPI2] = 1,
    [RCC_enu_SPI3] = 1,
    [RCC_enu_USART2] = 1,
    [RCC_enu_USART3] = 1,
    [RCC_enu_I2C1] = 1,
    [RCC_enu_I2C2] = 1,
    [RCC_enu_I2C3] = 1,
    [RCC_enu_PWR] = 1,

    /*APB2 Peripherals*/
    [RCC_enu_TIM1] = 1,
    [RCC_enu_SPI1] = 1,
    [RCC_enu_USART1] = 1,
    [RCC_enu_USART6] = 1,
    [RCC_enu_ADC1] = 1,
    [RCC_enu_SDIO] = 1,
    [RCC_enu_SPI4] = 1,
    [RCC_enu_SYSCFG] = 1,
    [RCC_enu_TIM9] = 1,
    [RCC_enu_TIM10] = 1,
    [RCC_enu_TIM11] = 1    
};


RCC_enuErorrStatus_t RCC_enuEnableClk(RCC_enuCLK_t Copy_enuClk){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    uint32_t Loc_u32TimeOut = 0;
    uint8_t Loc_u8Isready = (uint8_t)RCC_NOT_READY;
    switch(Copy_enuClk){
        case RCC_enu_HSI:
            SET_BIT(RCC->CR,RCC_CR_HSION);
            Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_HSIRDY);
            /*HSI timeout val*/
            Loc_u32TimeOut = RCC_HSI_TIMEOUT;
            /*Timeout loop for HSI*/
            while((!Loc_u8Isready)&&Loc_u32TimeOut--){
                Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_HSIRDY);
            }
            break;

        case RCC_enu_HSE:
            SET_BIT(RCC->CR,RCC_CR_HSEON);
            Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_HSERDY);
            /*HSE timeout val*/
            Loc_u32TimeOut = RCC_HSE_TIMEOUT;
            /*Timeout loop for HSE*/
            while((!Loc_u8Isready)&&Loc_u32TimeOut--){
                Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_HSERDY);
            }
            break;

        case RCC_enu_PLL:
            SET_BIT(RCC->CR,RCC_CR_PLLON);
            Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_PLLRDY);
            /*PLL timeout val*/
            Loc_u32TimeOut = RCC_PLL_TIMEOUT;
            /*Timeout loop for PLL*/
            while((!Loc_u8Isready)&&Loc_u32TimeOut--){
                Loc_u8Isready = GET_BIT(RCC->CR,RCC_CR_PLLRDY);
            }
            break;

        default:
            Loc_enuStatus = RCC_enu_INVALID_CLK_TYPE;
            break;
    }
    if(!Loc_u8Isready){
        Loc_enuStatus = RCC_enu_TIMEOUT;
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_enuClkStatus(RCC_enuCLK_t Copy_enuClk,uint32_t* Add_u8){
    
    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;

    if(Add_u8 == NULL){
        Loc_enuStatus = RCC_enu_NULL_POINTER;
    }
    else{
        switch(Copy_enuClk){
            case RCC_enu_HSI:
                *Add_u8 = GET_BIT(RCC->CR,RCC_CR_HSIRDY);
                break;
            case RCC_enu_HSE:
                *Add_u8 = GET_BIT(RCC->CR,RCC_CR_HSERDY);
                break;
            case RCC_enu_PLL:
                *Add_u8 = GET_BIT(RCC->CR,RCC_CR_PLLRDY);
                break;
            default:
                Loc_enuStatus = RCC_enu_INVALID_CLK_TYPE;
                break;
        }
    }
    return Loc_enuStatus;
}

RCC_enuCLK_t RCC_enuGetSysClk(void){   
    return GET_SWS_BITS(RCC->CFGR);
}

RCC_enuErorrStatus_t RCC_enuSetSysClk(RCC_enuCLK_t Copy_enuClkSrc){

    uint32_t Loc_32ClkStatus = 0;
    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuClkStatus(Copy_enuClkSrc,&Loc_32ClkStatus);
    if(RCC_enuGetSysClk() == Copy_enuClkSrc){
        /*The clk source is already set*/
        Loc_enuStatus = RCC_enuOK;
    }
    else if(Loc_32ClkStatus != RCC_enuOK){
        /*Check if the clk source is valid*/
    }
    else if(Loc_32ClkStatus == RCC_NOT_READY){
        Loc_enuStatus = RCC_enu_CLK_NOT_READY;
    }
    else{
        /*Set the clk source*/
        SET_SW_BITS(RCC->CFGR,Copy_enuClkSrc);
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_enuBypassHSE(RCC_HSE_BYPASS_t Copy_enuBypass){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    switch(Copy_enuBypass){
        case RCC_enu_HSE_BYPASS_ON:
            SET_BIT(RCC->CR,RCC_CR_HSE_BYPASS);
            break;

        case RCC_enu_HSE_BYPASS_OFF:
            CLR_BIT(RCC->CR,RCC_CR_HSE_BYPASS);
            break;

        default:
            Loc_enuStatus = RCC_enu_INVALID_PARAMETER;
            break;
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_enuConfigurePLL(uint8_t Copy_u8M,uint16_t Copy_u16N,uint8_t Copy_u8P,uint8_t Copy_u8Q,
RCC_enuCLK_t Copy_enuSource){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    uint8_t Loc_u8PLLState = GET_BIT(RCC->CR,RCC_CR_PLLON);
    if(Loc_u8PLLState){
        Loc_enuStatus = RCC_enu_err_PLL_ON;
    }
    else if(Copy_enuSource>MAX_PLL_CLK_INDEX){
        Loc_enuStatus = RCC_enu_INVALID_CLK_TYPE;
    }
    else if((Copy_u8Q<3)||(Copy_u8Q>15)){
        Loc_enuStatus = RCC_enu_INVALID_Q;
    }
    else if((!GET_BIT(Copy_u8P,0))||(Copy_u8P>8)||(!Copy_u8P)){
        Loc_enuStatus = RCC_enu_INVALID_P;
    }
    else if((Copy_u16N<193)||(Copy_u16N>432)){
        Loc_enuStatus = RCC_enu_INVALID_N;
    }
    else if((Copy_u8M<2)||(Copy_u8M>63)){
        Loc_enuStatus = RCC_enu_INVALID_M;
    }
    else{
        (Copy_enuSource==RCC_enu_HSE)? CLR_BIT(RCC->PLLCFGR,RCC_PLL_SRC):SET_BIT(RCC->PLLCFGR,RCC_PLL_SRC);
        SET_PLL_Q(RCC->PLLCFGR,Copy_u8Q);
        switch(Copy_u8P){
            case 2:
                SET_PLL_P(RCC->PLLCFGR,0);
                break;
            case 4:
                SET_PLL_P(RCC->PLLCFGR,1);
                break;
            case 6:
                SET_PLL_P(RCC->PLLCFGR,2);
                break;
            case 8:
                SET_PLL_P(RCC->PLLCFGR,3);
                break;
            default:
                break;
        }
        SET_PLL_N(RCC->PLLCFGR,Copy_u16N);
        SET_PLL_M(RCC->PLLCFGR,Copy_u8M);
        RCC_stPLL_Parameters.PLL_CLK = Copy_enuSource;
        RCC_stPLL_Parameters.PLL_M = Copy_u8M;
        RCC_stPLL_Parameters.PLL_N = Copy_u16N;
        RCC_stPLL_Parameters.PLL_Q = Copy_u8Q;
        RCC_stPLL_Parameters.PLL_P = Copy_u8P;
    }
    return Loc_enuStatus;
}


RCC_enuErorrStatus_t RCC_enuEnablePeriPheralClk(RCC_enuPeripherals_t Copy_enuPeripheral){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    if(Copy_enuPeripheral>MAX_PERIPHERAL_INDEX||(!RCC_arrPeripherals[Copy_enuPeripheral])){
        Loc_enuStatus = RCC_enu_INVALID_PERIPHERAL;
    }
    else{
        if(Copy_enuPeripheral<32){
            SET_BIT(RCC->AHB1ENR,Copy_enuPeripheral);
        }
        else if(Copy_enuPeripheral<64){
            SET_BIT(RCC->AHB2ENR,Copy_enuPeripheral-32);
        }
        else if(Copy_enuPeripheral<96){
            SET_BIT(RCC->APB1ENR,Copy_enuPeripheral-64);
        }
        else{
            SET_BIT(RCC->APB2ENR,Copy_enuPeripheral-96);
        }
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_enuDisablePeriPheralClk(RCC_enuPeripherals_t Copy_enuPeripheral){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    if(Copy_enuPeripheral>MAX_PERIPHERAL_INDEX||(!RCC_arrPeripherals[Copy_enuPeripheral])){
        Loc_enuStatus = RCC_enu_INVALID_PERIPHERAL;
    }
    else{
        if(Copy_enuPeripheral<32){
            CLR_BIT(RCC->AHB1ENR,Copy_enuPeripheral);
        }
        else if(Copy_enuPeripheral<64){
            CLR_BIT(RCC->AHB2ENR,Copy_enuPeripheral-32);
        }
        else if(Copy_enuPeripheral<96){
            CLR_BIT(RCC->APB1ENR,Copy_enuPeripheral-64);
        }
        else{
            CLR_BIT(RCC->APB2ENR,Copy_enuPeripheral-96);
        }
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_enuResetPeriPheral(RCC_enuPeripherals_t Copy_enuPeripheral){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    if(Copy_enuPeripheral>MAX_PERIPHERAL_INDEX||(!RCC_arrPeripherals[Copy_enuPeripheral])){
        Loc_enuStatus = RCC_enu_INVALID_PERIPHERAL;
    }
    else{
        if(Copy_enuPeripheral<32){
            SET_BIT(RCC->AHB1RSTR,Copy_enuPeripheral);
            CLR_BIT(RCC->AHB1RSTR,Copy_enuPeripheral);
        }
        else if(Copy_enuPeripheral<64){
            SET_BIT(RCC->AHB2RSTR,Copy_enuPeripheral-32);
            CLR_BIT(RCC->AHB2RSTR,Copy_enuPeripheral-32);
        }
        else if(Copy_enuPeripheral<96){
            SET_BIT(RCC->APB1RSTR,Copy_enuPeripheral-64);
            CLR_BIT(RCC->APB1RSTR,Copy_enuPeripheral-64);
        }
        else{
            SET_BIT(RCC->APB2RSTR,Copy_enuPeripheral-96);
            CLR_BIT(RCC->APB2RSTR,Copy_enuPeripheral-96);
        }
    }
    return Loc_enuStatus;
}



RCC_enuErorrStatus_t RCC_EnableLowPowerMode(RCC_enuPeripherals_t Copy_enuPeripheral){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    if(Copy_enuPeripheral==RCC_enu_SRAM1){
        SET_BIT(RCC->AHB1LPENR,RCC_APB1ENLR_SRAM);
    }
    else if(Copy_enuPeripheral==RCC_enu_FLITF){
        SET_BIT(RCC->APB2LPENR,RCC_APB1ENLR_FLITF);
    }
    else if(Copy_enuPeripheral>MAX_PERIPHERAL_INDEX||(!RCC_arrPeripherals[Copy_enuPeripheral])){
        Loc_enuStatus = RCC_enu_INVALID_PERIPHERAL;
    }
    else{
        if(Copy_enuPeripheral<32){
            SET_BIT(RCC->AHB1LPENR,Copy_enuPeripheral);
        }
        else if(Copy_enuPeripheral<64){
            SET_BIT(RCC->AHB2LPENR,Copy_enuPeripheral-32);
        }
        else if(Copy_enuPeripheral<96){
            SET_BIT(RCC->APB1LPENR,Copy_enuPeripheral-64);
        }
        else{
            SET_BIT(RCC->APB2LPENR,Copy_enuPeripheral-96);
        }
    }
    return Loc_enuStatus;
}

RCC_enuErorrStatus_t RCC_DisableLowPowerMode(RCC_enuPeripherals_t Copy_enuPeripheral){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    if(Copy_enuPeripheral==RCC_enu_SRAM1){
        CLR_BIT(RCC->AHB1LPENR,RCC_APB1ENLR_SRAM);
    }
    else if(Copy_enuPeripheral==RCC_enu_FLITF){
        CLR_BIT(RCC->APB2LPENR,RCC_APB1ENLR_FLITF);
    }
    else if(Copy_enuPeripheral>MAX_PERIPHERAL_INDEX||(!RCC_arrPeripherals[Copy_enuPeripheral])){
        Loc_enuStatus = RCC_enu_INVALID_PERIPHERAL;
    }
    else{
        if(Copy_enuPeripheral<32){
            CLR_BIT(RCC->AHB1LPENR,Copy_enuPeripheral);
        }
        else if(Copy_enuPeripheral<64){
            CLR_BIT(RCC->AHB2LPENR,Copy_enuPeripheral-32);
        }
        else if(Copy_enuPeripheral<96){
            CLR_BIT(RCC->APB1LPENR,Copy_enuPeripheral-64);
        }
        else{
            CLR_BIT(RCC->APB2LPENR,Copy_enuPeripheral-96);
        }
    }
    return Loc_enuStatus;
}

static uint32_t RCC_u32GetInternalClkVal(void){
    RCC_enuCLK_t Loc_enuCLK = RCC_enuGetSysClk();
    uint32_t Loc_u32ClkVal = 0;
    switch (Loc_enuCLK){
        case RCC_enu_HSI:
            Loc_u32ClkVal = HSI_CLK_FREQ;
            break;

        case RCC_enu_HSE:
            Loc_u32ClkVal = HSE_CLK_FREQ;
            break;
        
        case RCC_enu_PLL:
            /*PLL Factor = N/(M*P)*/
            uint32_t Loc_u32ClkFactor = 
            RCC_stPLL_Parameters.PLL_M/(RCC_stPLL_Parameters.PLL_N*RCC_stPLL_Parameters.PLL_P);
            if(RCC_stPLL_Parameters.PLL_CLK==RCC_enu_HSI){
                Loc_u32ClkVal = Loc_u32ClkFactor*HSI_CLK_FREQ;
            }
            else{
                Loc_u32ClkVal = Loc_u32ClkFactor*HSE_CLK_FREQ;
            }
            break;
        
        default:
            break;
    }
    return Loc_u32ClkVal;
}

RCC_enuErorrStatus_t RCC_enuGetBusFreq(RCC_enuBuses_t Copy_enuBus,uint32_t* Add_u32Freq){
    
    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    uint32_t Loc_u32InternalClk = RCC_u32GetInternalClkVal();
    if(Add_u32Freq==NULL){
        Loc_enuStatus = RCC_enu_NULL_POINTER;
    }
    else{
        switch (Copy_enuBus){
        case RCC_enu_AHB:
            *Add_u32Freq = Loc_u32InternalClk/RCC_stBusPrescaler.AHB;
            break;
        case RCC_enu_APB1:
            *Add_u32Freq = Loc_u32InternalClk/RCC_stBusPrescaler.APB1;
            break;
        case RCC_enu_APB2:
            *Add_u32Freq = Loc_u32InternalClk/RCC_stBusPrescaler.APB2;
            break;
        default:
            Loc_enuStatus = RCC_enu_INVALID_BUS;
            break;
        }
    }
    return Loc_enuStatus;
}

uint32_t RCC_getSystickClk(void){
    uint32_t Loc_u32Freq = 0;
    RCC_enuGetBusFreq(RCC_enu_AHB,&Loc_u32Freq);
    return Loc_u32Freq;
}

RCC_enuErorrStatus_t RCC_enuSetBusPrescaler(RCC_enuBuses_t Copy_enuBus,uint32_t Copy_u32Prescaler){

    RCC_enuErorrStatus_t Loc_enuStatus = RCC_enuOK;
    uint32_t Loc_u32InternalCLk = RCC_u32GetInternalClkVal();    
    uint32_t Loc_u32AHB_F = Loc_u32InternalCLk;
    switch (Copy_enuBus){
        case RCC_enu_AHB:
            Loc_u32AHB_F = Loc_u32InternalCLk/Copy_u32Prescaler;
            if(Loc_u32AHB_F>MAX_AHB_CLK_FREQ){
                Loc_enuStatus = RCC_enu_INVALID_CLK_CFG;
                break;
            }
            else{}
            switch(Copy_u32Prescaler){
                case 1:
                    SET_HPRE(RCC->CFGR,0);
                    break;
                case 2:
                    SET_HPRE(RCC->CFGR,8);
                    break;
                case 4:
                    SET_HPRE(RCC->CFGR,9);
                    break;
                case 8:
                    SET_HPRE(RCC->CFGR,10);
                    break;
                case 16:
                    SET_HPRE(RCC->CFGR,11);
                    break;
                case 64:
                    SET_HPRE(RCC->CFGR,12);
                    break;
                case 128:
                    SET_HPRE(RCC->CFGR,13);
                    break;
                case 256:
                    SET_HPRE(RCC->CFGR,14);
                    break;
                case 512:
                    SET_HPRE(RCC->CFGR,15);
                    break;
                default:
                    Loc_enuStatus = RCC_enu_INVALID_PRESCALER;
                    break;
            }
            if(Loc_enuStatus==RCC_enuOK){
                RCC_stBusPrescaler.AHB = Copy_u32Prescaler;
            }
            break;

        case RCC_enu_APB1:
            Loc_u32AHB_F = Loc_u32InternalCLk/(Copy_u32Prescaler*
            RCC_stBusPrescaler.AHB);
            if(Loc_u32AHB_F>MAX_AB1_CLK_FREQ){
                Loc_enuStatus = RCC_enu_INVALID_CLK_CFG;
                break;
            }
            switch(Copy_u32Prescaler){
                case 1:
                    SET_PPRE1(RCC->CFGR,0);
                    break;
                case 2:
                    SET_PPRE1(RCC->CFGR,4);
                    break;
                case 4:
                    SET_PPRE1(RCC->CFGR,5);
                    break;
                case 8:
                    SET_PPRE2(RCC->CFGR,6);
                    break;
                case 16:
                    SET_PPRE1(RCC->CFGR,7);
                    break;
                default:
                    Loc_enuStatus = RCC_enu_INVALID_PRESCALER;
                    break;
            }
            if(Loc_enuStatus==RCC_enuOK){
                RCC_stBusPrescaler.APB1 = Copy_u32Prescaler;
            }
            break;

        case RCC_enu_APB2:
            Loc_u32AHB_F = Loc_u32InternalCLk/(Copy_u32Prescaler*
            RCC_stBusPrescaler.AHB);
            if(Loc_u32AHB_F>MAX_AB2_CLK_FREQ){
                Loc_enuStatus = RCC_enu_INVALID_CLK_CFG;
                break;
            }
            switch(Copy_u32Prescaler){
                case 1:
                    SET_PPRE2(RCC->CFGR,0);
                    break;
                case 2:
                    SET_PPRE2(RCC->CFGR,4);
                    break;
                case 4:
                    SET_PPRE2(RCC->CFGR,5);
                    break;
                case 8:
                    SET_PPRE2(RCC->CFGR,6);
                    break;
                case 16:
                    SET_PPRE2(RCC->CFGR,7);
                    break;
                default:
                    Loc_enuStatus = RCC_enu_INVALID_PRESCALER;
                    break;
            }
            if(Loc_enuStatus==RCC_enuOK){
                RCC_stBusPrescaler.APB2=Copy_u32Prescaler;
            }
            break;
        
        default:
            Loc_enuStatus = RCC_enu_INVALID_BUS;
            break;
    }

    return Loc_enuStatus;
}