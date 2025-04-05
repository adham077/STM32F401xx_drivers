#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "ultrasonic_cfg.h"

typedef enum{
    Ultrasonic_enu_OK,
    Ultrasonic_enu_INVALID_ULTRASONIC,
    Ultrasonic_enu_NOK
}Ultrasonic_enuErrorStatus_t;

extern void Ultrasonic_vInit(void);

extern Ultrasonic_enuErrorStatus_t Ultrasonic_enuSendTrigger(uint8_t Copy_u8Ultrasonic);

extern uint32_t UltraSonic_u32GetPulseWidth(uint8_t Copy_u8Ultrasonic);

extern float32_t Ultrasonic_f32GetDistanceCm(uint8_t Copy_u8Ultrasonic);

extern Ultrasonic_enuErrorStatus_t Ultrasonic_enuRegisterCallBack(
    uint8_t Copy_u8Ultrasonic,Ultrasonic_onMeasurmentCompletedCB Add_CB
);

#endif