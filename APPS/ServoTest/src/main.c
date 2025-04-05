#include "servo.h"
#include "systick.h"

#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)  

void EnableFPU(void){
    SCB_CPACR |= ((3UL << 10*2) | (3UL << 11*2));  
    __asm volatile("DSB");
    __asm volatile("ISB");
}

int main(void){
    EnableFPU();
    Systick_enuInit1Ms(SYSTICK_enu_PRESCALER_1);
    SERVO_vInit();
    Systick_vStart();

    while(1){
        SERVO_enuMoveToAngle(SERVO_2,0);
        Systick_vDelayMs(3000);
        SERVO_enuMoveToAngle(SERVO_2,90);
        Systick_vDelayMs(3000);
    }
    return 0;
}