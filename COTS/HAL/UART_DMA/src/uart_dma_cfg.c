#include "uart_dma.h"

extern uint8_t UartReceiveBuffer[UART_DMA_INITIAL_RX_BUFF_SIZE];
extern uint8_t uartTransferBuffer[UART_DMA_INITIAL_TX_BUFF_SIZE];

UartDMA_stCfg_t UartDMA_arrCfgs[UART_DMA_NO_OF_LINES] = {
    [UART_LINE_1] = {
        .UART = Usart_enu_USART2,
        .Port = GPIO_enu_GPIOA,
        .Pin = GPIO_enu_PIN2,
        .baudRate = 9600,
        .StopBit = Usart_enu_1StopBit,
        .ParityMode = Usart_enu_noParity,
        .Mode = Usart_enu_Tx
    } ,
    [UART_LINE_2] = {
        .UART = Usart_enu_USART2,
        .Port = GPIO_enu_GPIOA,
        .Pin = GPIO_enu_PIN3,
        .baudRate = 9600,
        .StopBit = Usart_enu_1StopBit,
        .ParityMode = Usart_enu_noParity,
        .Mode = Usart_enu_Rx
    } 
};