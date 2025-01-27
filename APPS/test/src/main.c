#include "led.h"

int main(void){
    LED_vInit();


    while(1){
        LED_enuCtlLED(LED1,LED_HIGH);
        LED_enuCtlLED(LED2,LED_HIGH);
        LED_enuCtlLED(LED2,LED_HIGH);
    }
    return 0;
}