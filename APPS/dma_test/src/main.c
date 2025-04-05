#include "dma.h"
#include "rcc.h"
#include "nvic.h"
#include "GPIO.h"
#include "usart.h"
#include "scheduler.h"



uint8_t Buff[100];

char* str2 = "walaa\r\n";

void transferTask(void){
    DMA_enuStopTransfer(DMA_enuDMA1,DMA_enuStream6);
    DMA_enuClearALlFlags(DMA_enuDMA1);
    DMA_enuChangeM0Addr(DMA_enuDMA1,DMA_enuStream6,str2);
    DMA_enuResizeBuffer(DMA_enuDMA1,DMA_enuStream6,7);
    DMA_enuStartTransfer(DMA_enuDMA1,DMA_enuStream6);
}

int main(void){
    
    char* str  = "adham\r\n";

    RCC_enuCtlPeripheral(RCC_GPIOA,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_DMA1,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_USART2,RCC_PER_ON);
    
    GPIO_stPinCFG_t gpio = {
        .AltFn = GPIO_enu_AltFn7,
        .mode = GPIO_enu_ALT_FN,
        .port = GPIO_enu_GPIOA,
        .pin = GPIO_enu_PIN2,
        .speed = GPIO_enu_high_speed,
        .OutputType = GPIO_enu_PUSH_PULL,
        .InputType = GPIO_enu_NO_PU_PD
    };

    Usart_stCfg_t usart = {
        .BaudRate = 9600,
        .clkType = Usart_enu_async,
        .Mode = Usart_enu_Tx,
        .ParityMode = Usart_enu_noParity,
        .StopBit = Usart_enu_1StopBit,
        .Usart = Usart_enu_USART2,
        .WordLength = Usart_enu_word8
    };  

    DMA_stCfg_t dma = {
        .DMA = DMA_enuDMA1,
        .Stream = DMA_enuStream6,
        .Channel = DMA_enuCH4,
        .memIncState = DMA_enuIncEn,
        .perIncState = DMA_enuIncDis,
        .Circularity = DMA_enuNonCirc,
        .BuffSize = 7,
        .BuffType = DMA_enuSingleBuff,
        .Priority = DMA_enuLOW_p,
        .wordSize = DMA_enu8bit,
        .srcAdd = &str,
        .dstAdd1 =  0x40004404,
        .TransferType = DMA_enuMEM2PER
    };

    SCHED_stTaskCfg_t task = {
        .InitialWait = 1000,
        .CycleTime = 1000,
        .Priority = 0,
        .CallBack = transferTask
    };

    uint8_t i=0;
    for(;str[i];i++){
        Buff[i] = str[i];
    }

    i++;
    Buff[i] = '\0';

    GPIO_enuCfgPin(&gpio);
    Usart_enuInit(&usart);
    USART_enuEnableDMA_TX(Usart_enu_USART2);
    DMA_enuInit(&dma);
    SCHED_vInit();
    SCHED_enuAddRunnable(&task);
    SCHED_vStart();
    return 0;
}