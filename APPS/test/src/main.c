#include "led.h"
#include "scheduler.h"
#include "uart_int.h"

void ledRunnable(void);

int main(void){

    SCHED_stTaskCfg_t ledRun = {
        .CallBack = &ledRunnable,
        .CycleTime = 1000,
        .Priority = 20
    };

    LED_vInit();
    SCHED_vInit();
    UsartInt_vInit();
    SCHED_enuAddRunnable(&ledRun);
    SCHED_vStart();

    return 0;
}

void ledRunnable(void){
    static  int ledState = 0;
    ledState ^=1;
    LED_enuCtlLED(LED3,ledState);
    UartInt_enuSendString(UART_1,"Toggled led state\r\n");
}