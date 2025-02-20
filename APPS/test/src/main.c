#include "switch.h"
#include "led.h"

int led1State = 0;
int led2State = 0;
int led3State = 0;

void onButton1Pressed(void){
    led1State ^=0x1;
    LED_enuCtlLED(LED1,led1State);
}

void onButton2Pressed(void){
    led2State ^=0x1;
    LED_enuCtlLED(LED2,led2State);
}

void onButton3Pressed(void){
    led3State ^=0x1;
    LED_enuCtlLED(LED3,led3State);
}

int main(void){
    SWITCH_vInit();
    LED_vInit();
    SWITCH_enuSetCallBack(SWITCH_1,&onButton1Pressed);
    SWITCH_enuSetCallBack(SWITCH_2,&onButton2Pressed);    
    SWITCH_enuSetCallBack(SWITCH_3,&onButton3Pressed);    
    
    while(1){

    }
    return 0;
}