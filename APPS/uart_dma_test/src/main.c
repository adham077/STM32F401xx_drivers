#include "uart_dma.h"
#include "scheduler.h"
#include "led.h"

void dma_runnable(void){
    UartDMA_enuStartTransfer(UART_LINE_1);    
}

void dma_cb(DMA_enuEvents_t event){
    if(event == DMA_enuOnFullTransfer){
        static uint8_t ledState = 0;
        ledState ^= 1;
        LED_enuCtlLED(LED3,ledState);
    }
}

int main(void){

    char str[50] = "adham\r\n";    

    SCHED_stTaskCfg_t dma_run = {
        .InitialWait = 1000,
        .CycleTime = 1000,
        .Priority = 0,
        .CallBack = dma_runnable
    };

    LED_vInit();
    UartDMA_vInit();
    UartDMA_enuRegisterBuff(UART_LINE_1,(void*)str,7);
    UartDMA_enuRegisterCallBack(UART_LINE_1,dma_cb);
    SCHED_vInit();
    SCHED_enuAddRunnable(&dma_run);
    SCHED_vStart();
    return 0;
}