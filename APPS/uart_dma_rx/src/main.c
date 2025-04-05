#include "led.h"
#include "uart_dma.h"
#include "scheduler.h"

uint8_t buffRX[10] = {0};

void dmaRx_cb(DMA_enuEvents_t event){
    if(event == DMA_enuOnFullTransfer){
        UartDMA_enuStartTransfer(UART_LINE_1);
    }
}

void dmaTx_cb(DMA_enuEvents_t event){
    static uint8_t ledState = OFF;
    if(event == DMA_enuOnFullTransfer){
        ledState ^= 0x01;
        LED_enuCtlLED(LED3,ledState);
        UartDMA_enuStartTransfer(UART_LINE_2);
    }
}

int main(void){
    
    LED_vInit();
    UartDMA_vInit();

    UartDMA_enuRegisterBuff(UART_LINE_2,buffRX,5);
    UartDMA_enuRegisterBuff(UART_LINE_1,buffRX,5);

    UartDMA_enuRegisterCallBack(UART_LINE_2,dmaRx_cb);
    UartDMA_enuRegisterCallBack(UART_LINE_1,dmaTx_cb);

    UartDMA_enuStartTransfer(UART_LINE_2);
    SCHED_vInit();
    SCHED_vStart();

    return 0;
}