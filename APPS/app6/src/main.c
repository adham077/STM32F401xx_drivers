#include "ultrasonic.h"
#include "scheduler.h"
#include "led.h"

#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)  
 
void Ultrasonic_CB(uint32_t);

void EnableFPU(void) {
    SCB_CPACR |= ((3UL << 10*2) | (3UL << 11*2));  
    __asm volatile("DSB");
    __asm volatile("ISB");
}



int main(void){

    EnableFPU();
    Ultrasonic_enuRegisterCallBack(ULTRASONIC_2,Ultrasonic_CB);
    LED_vInit();
    Ultrasonic_vInit();
    SCHED_vInit();
   
    SCHED_vStart();
}

void Ultrasonic_CB(uint32_t val){
    volatile float32_t distance = Ultrasonic_f32GetDistanceCm(ULTRASONIC_2);
    if(distance < 20.0){
        LED_enuCtlLED(LED3,ON);
    }
    else{
        LED_enuCtlLED(LED3,OFF);
    }
}