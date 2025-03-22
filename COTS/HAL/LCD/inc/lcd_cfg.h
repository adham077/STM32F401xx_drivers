#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "../../MCAL/GPIO/inc/GPIO.h"
#include "rcc.h"
#include "../../HAL/SCHED/inc/scheduler.h"
#include "std_types.h"

#define NO_OF_LCDS                  1

#define LCD_1                       0

#define LCD_8_BIT_MODE              0
#define LCD_4_BIT_MODE              1

#ifndef LCD_MODE
#define LCD_MODE    LCD_8_BIT_MODE
#endif

#if LCD_MODE == LCD_8_BIT_MODE
#define LCD_NO_OF_DATA_PINS         8
#define LCD_TOTAL_NO_OF_PINS        11
#else
#define LCD_NO_OF_DATA_PINS         4
#define LCD_TOTAL_NO_OF_PINS        7
#endif 

typedef struct{
    GPIO_enuPorts_t port;
    GPIO_enuPins_t pin;
}LCD_stPinNo_t;


typedef struct{
    LCD_stPinNo_t LCDPins[LCD_TOTAL_NO_OF_PINS];
    uint32_t FunSet;
    uint32_t EntryMode;
    uint32_t DisplaySettings;
}LCD_stLcdCfg_t;

extern LCD_stLcdCfg_t LCD_arrCfgs[NO_OF_LCDS];

#endif