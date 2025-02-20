#include "../inc/lcd.h"

#define RS_  0
#define RW_  1
#define EN_  2
#define D0_  3
#define D1_  4
#define D2_  5
#define D3_  6
#if HLCD_MODE==HLCD_8BIT_MODE
#define D4_  7
#define D5_  8
#define D6_  9
#define D7_  10
#endif

typedef enum{
    LCD_enuInitState,
    LCD_enuWriteCmdState,
    LCD_enuFreeState
}LCD_enuState_t;

static uint32_t LCD_u32Counter = 0;

static uint32_t LCD_u32State = 0;

LCD_enuErrorStatus_t LCD_enuWriteCMD(uint16_t Copy_u16CMD,uint8_t Copy_u8LCD){
    
    LCD_enuErrorStatus_t Loc_enuStatus = LCD_enu_OK;
    uint8_t i = 0;
    uint16_t Loc_u16State = 0;

    GPIO_enuSetPinState(LCD_arrCfgs[Copy_u8LCD].LCDPins[RS_].port,
    LCD_arrCfgs[Copy_u8LCD].LCDPins[RS_].pin,GPIO_LOW_STATE);

    GPIO_enuSetPinState(LCD_arrCfgs[Copy_u8LCD].LCDPins[EN_].port,
    LCD_arrCfgs[Copy_u8LCD].LCDPins[RS_].pin,GPIO_LOW_STATE);  

    GPIO_enuSetPinState(LCD_arrCfgs[Copy_u8LCD].LCDPins[RW_].port,
    LCD_arrCfgs[Copy_u8LCD].LCDPins[RS_].pin,GPIO_LOW_STATE);    
    
    if(LCD_u32State!=LCD_enuFreeState){
        Loc_enuStatus = LCD_enu_LCD_BUSY;
    }
    else{
        for(i=D0_;i<LCD_NO_OF_DATA_PINS;i++){
            Loc_u16State = (1>>i) & 0x0001; 
            GPIO_enuSetPinState(
                LCD_arrCfgs[Copy_u8LCD].LCDPins[i].port,
                LCD_arrCfgs[Copy_u8LCD].LCDPins[i].pin,
                Loc_u16State
            );
        }
    }

    return Loc_enuStatus;
} 



void LCD_vRunnable(void){

    switch (LCD_u32Counter){
    case LCD_enuInitState:
        
        
        LCD_u32Counter++;
        break;
    
    default:
        break;
    }
}

void LCD_vInit(void){
    
    uint8_t i = 0;
    uint8_t j = 0;
    GPIO_stPinCFG_t Loc_stPinCfg  = {0};
    uint64_t Loc_u64ClkMask = 0;
    SCHED_stTaskCfg_t  Loc_stLCDtask = {
        .CallBack = LCD_vRunnable,
        .CycleTime = 1,
        .Priority = 5
    };
    

    for(i=0;i<NO_OF_LCDS;i++){
        for(j=0;j<LCD_TOTAL_NO_OF_PINS;j++){
            if(LCD_arrCfgs[i].LCDPins[j].port == GPIO_enu_GPIOH){
                Loc_u64ClkMask |= RCC_GPIOH;
            }
            else{
                Loc_u64ClkMask |= (1<<LCD_arrCfgs[i].LCDPins[j].port);
            }
        }
    }

    RCC_enuCtlPeripheral(Loc_u64ClkMask,RCC_PER_ON);
    Loc_stPinCfg.AltFn = GPIO_enu_NoAF;
    Loc_stPinCfg.InputType = GPIO_enu_NO_PU_PD;
    Loc_stPinCfg.mode = GPIO_enu_OUTPUT;
    Loc_stPinCfg.OutputType = GPIO_enu_PUSH_PULL;
    Loc_stPinCfg.speed = GPIO_enu_low_speed;

    for(i=0;i<NO_OF_LCDS;i++){
        for(j=0;j<LCD_TOTAL_NO_OF_PINS;j++){
            Loc_stPinCfg.pin = LCD_arrCfgs[i].LCDPins[j].pin;
            Loc_stPinCfg.port = LCD_arrCfgs[i].LCDPins[j].port;
            GPIO_enuCfgPin(&Loc_stPinCfg);
        }
    }
    
    SCHED_enuAddRunnable(&Loc_stLCDtask);
}


#undef RS_  
#undef RW_  
#undef EN_  
#undef D0_  
#undef D1_  
#undef D2_  
#undef D3_  
#if HLCD_MODE==HLCD_8BIT_MODE
#undef D4_  
#undef D5_  
#undef D6_  
#undef D7_ 
#endif 