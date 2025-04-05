#include "led.h"
#include "scheduler.h"
#include "uart_int.h"
#include "nvic.h"
char receiveBuffer[100] = {0};

void ledRunnable(void);
void bufferRunnable(void);

#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)  

void EnableFPU(void) {
    SCB_CPACR |= ((3UL << 10*2) | (3UL << 11*2));  
    __asm volatile("DSB");
    __asm volatile("ISB");
}

int main(void){
    EnableFPU();
    SCHED_stTaskCfg_t ledRun = {
        .InitialWait = 5000,
        .CallBack = ledRunnable,
        .CycleTime = 1000,
        .Priority = 0
    };
    Usart_stCfg_t uart = {
        .BaudRate = 9600,
        .clkType = Usart_enu_async,
        .Mode = Usart_enu_Tx_Rx,
        .ParityMode = Usart_enu_noParity,
        .StopBit = Usart_enu_1StopBit,
        .WordLength = Usart_enu_word8,
        .Usart = Usart_enu_USART2
    };
    GPIO_stPinCFG_t gpio1 = {
        .AltFn =GPIO_enu_AltFn7,
        .InputType = GPIO_enu_NO_PU_PD,
        .OutputType = GPIO_enu_PUSH_PULL,
        .pin = GPIO_enu_PIN2,
        .port = GPIO_enu_GPIOA,
        .speed = GPIO_enu_high_speed,
        .mode = GPIO_enu_ALT_FN
    };
    GPIO_stPinCFG_t gpio2 = {
        .AltFn =GPIO_enu_AltFn7,
        .InputType = GPIO_enu_NO_PU_PD,
        .OutputType = GPIO_enu_PUSH_PULL,
        .pin = GPIO_enu_PIN3,
        .port = GPIO_enu_GPIOA,
        .speed = GPIO_enu_high_speed,
        .mode = GPIO_enu_ALT_FN
    };


    LED_vInit();
    SCHED_vInit();
    UsartInt_vInit();
    /*section to work*/
    RCC_enuCtlPeripheral(RCC_GPIOA,RCC_PER_ON);
    RCC_enuCtlPeripheral(RCC_USART2,RCC_PER_ON);
    GPIO_enuCfgPin(&gpio1);
    GPIO_enuCfgPin(&gpio2);
    Usart_enuInit(&uart);
    NVIC_enuClearPendingIRQn(NVIC_enuUSART2);
    NVIC_enuEnableIRQn(NVIC_enuUSART2);
    USART_enuEnableInt(Usart_enu_USART2,USART_enuRXNE_INT);

    SCHED_enuAddRunnable(&ledRun);
    LED_enuCtlLED(LED3,OFF);
    UartInt_enuReceiveBuffer(UART_1,receiveBuffer,10);
    SCHED_vStart();

    return 0;
}

void bufferRunnable(void){

}

void ledRunnable(void){
    static uint8_t ledState = 0;
    LED_enuCtlLED(LED1,ledState);
    ledState ^=1;
    char a = '\r\n';
}