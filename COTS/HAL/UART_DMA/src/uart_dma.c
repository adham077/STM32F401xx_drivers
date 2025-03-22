#include "uart_dma.h"

#define UART_DMA_NO_OF_UARTS            3
#define UART_DMA_NO_OF_DMAS             2

#define UART_DMA_NO_OF_STATES           2
#define UART_DMA_ON_TX                  0
#define UART_DMA_ON_RX                  1

typedef struct{
    DMA_enuDMA_t DMA;
    DMA_enuStream_t stream[UART_DMA_NO_OF_STATES];
    DMA_enuChannelSel_t channel;
    NVIC_enuIRQn_t IRQn[UART_DMA_NO_OF_STATES];
}UartDMA_stDMAdata_t;

static const UartDMA_stDMAdata_t UartDMA_arrDMAdata[UART_DMA_NO_OF_UARTS] = {
    [Usart_enu_USART1] = {
        .DMA = DMA_enuDMA2,
        .stream[UART_DMA_ON_TX] = DMA_enuStream7,
        .stream[UART_DMA_ON_RX] = DMA_enuStream5,
        .channel = DMA_enuCH4,
        .IRQn[UART_DMA_ON_TX] = NVIC_enuDMA2_Stream7,
        .IRQn[UART_DMA_ON_RX] = NVIC_enuDMA2_Stream5
    },
    [Usart_enu_USART2] = {
        .DMA = DMA_enuDMA1,
        .stream[UART_DMA_ON_TX] = DMA_enuStream6,
        .stream[UART_DMA_ON_RX] = DMA_enuStream5,
        .channel = DMA_enuCH4,
        .IRQn[UART_DMA_ON_TX] = NVIC_enuDMA1_Stream6,
        .IRQn[UART_DMA_ON_RX] = NVIC_enuDMA1_Stream5
    },
    [Usart_enu_USART6] = {
        .DMA = DMA_enuDMA2,
        .stream[UART_DMA_ON_TX] = DMA_enuStream7,
        .stream[UART_DMA_ON_RX] = DMA_enuStream2,
        .channel = DMA_enuCH4,
        .IRQn[UART_DMA_ON_TX] = NVIC_enuDMA2_Stream7,
        .IRQn[UART_DMA_ON_RX] = NVIC_enuDMA2_Stream2
    }
};

static const uint64_t UartDMA_arrUsartCLkMasks[UART_DMA_NO_OF_UARTS] = {
    RCC_USART1,
    RCC_USART2,
    RCC_USART6
};

static const void* UartDMA_arrUSART_DR_Add[UART_DMA_NO_OF_UARTS] = {
    (void*)0x40011004UL,
    (void*)0x40004404UL,
    (void*)0x40011404UL 
};

static const uint64_t UartDMA_arrDMAClkMasks[UART_DMA_NO_OF_DMAS] = {
    RCC_DMA1,
    RCC_DMA2
};


void UartDMA_vInit(void){
    uint8_t i = 0;
    uint8_t Loc_u8UsartMap[3] = {0};
    uint64_t Loc_u64GpioClkMask = 0;
    uint64_t Loc_u64DmaClkMask = 0;
    uint64_t Loc_u64UsartClkMask = 0;
    DMA_enuDMA_t Loc_enuDMA = 0;
    GPIO_stPinCFG_t Loc_stGPIOcfg = {0};
    Usart_stCfg_t Loc_stUSartCfg = {0};
    DMA_stCfg_t Loc_stDMAcfg = {0};


    for(i=0;i<UART_DMA_NO_OF_LINES;i++){

        Loc_enuDMA = UartDMA_arrDMAdata[UartDMA_arrCfgs[i].UART].DMA;
        Loc_u64DmaClkMask = UartDMA_arrDMAClkMasks[Loc_enuDMA];
        Loc_u64UsartClkMask = UartDMA_arrUsartCLkMasks[UartDMA_arrCfgs[i].UART];

        if(UartDMA_arrCfgs[i].Port == GPIO_enu_GPIOH){
            Loc_u64GpioClkMask |= RCC_GPIOH;
        }
        else{
            Loc_u64GpioClkMask |= (1 << UartDMA_arrCfgs[i].Port);
        }

        RCC_enuCtlPeripheral(Loc_u64DmaClkMask,RCC_PER_ON);
        RCC_enuCtlPeripheral(Loc_u64UsartClkMask,RCC_PER_ON);
    }
    for(i = 0;i<UART_DMA_NO_OF_LINES;i++){
        RCC_enuCtlPeripheral(Loc_u64GpioClkMask,RCC_PER_ON);

        Loc_stGPIOcfg.port = UartDMA_arrCfgs[i].Port;
        Loc_stGPIOcfg.pin = UartDMA_arrCfgs[i].Pin;
        Loc_stGPIOcfg.mode = GPIO_enu_ALT_FN;
        Loc_stGPIOcfg.OutputType = GPIO_enu_PUSH_PULL;
        Loc_stGPIOcfg.InputType = GPIO_enu_NO_PU_PD;
        Loc_stGPIOcfg.speed = GPIO_enu_high_speed;
        if(UartDMA_arrCfgs[i].UART == Usart_enu_USART6){
            Loc_stGPIOcfg.AltFn = GPIO_enu_AltFn8;
        }
        else{
            Loc_stGPIOcfg.AltFn = GPIO_enu_AltFn7;
        }
        GPIO_enuCfgPin(&Loc_stGPIOcfg);

        Loc_stUSartCfg.BaudRate = UartDMA_arrCfgs[i].baudRate;
        Loc_stUSartCfg.Usart = UartDMA_arrCfgs[i].UART;
        Loc_stUSartCfg.clkType = Usart_enu_sync;
        Loc_stUSartCfg.StopBit = UartDMA_arrCfgs[i].StopBit;
        Loc_stUSartCfg.WordLength = Usart_enu_word8;
        Loc_stUSartCfg.ParityMode = UartDMA_arrCfgs[i].ParityMode;
        Loc_stUSartCfg.Mode = UartDMA_arrCfgs[i].Mode;

        Loc_stDMAcfg.DMA = UartDMA_arrDMAdata[UartDMA_arrCfgs[i].UART].DMA;
        Loc_stDMAcfg.Channel = UartDMA_arrDMAdata[UartDMA_arrCfgs[i].UART].channel;
        Loc_stDMAcfg.memIncState = DMA_enuIncEn;
        Loc_stDMAcfg.perIncState = DMA_enuIncDis;
        Loc_stDMAcfg.wordSize = DMA_enu8bit;
        Loc_stDMAcfg.Priority = DMA_enuHIGH_p;
        Loc_stDMAcfg.Circularity = DMA_enuNonCirc;
        Loc_stDMAcfg.BuffType = DMA_enuSingleBuff;

        switch(UartDMA_arrCfgs[i].Mode){
            case Usart_enu_Tx:
            Loc_stDMAcfg.TransferType = DMA_enuMEM2PER;
            Loc_stDMAcfg.BuffSize = UART_DMA_INITIAL_TX_BUFF_SIZE;
            Loc_stDMAcfg.Stream = UartDMA_arrDMAdata[UartDMA_arrCfgs[i].UART]
            .stream[UART_DMA_ON_TX];
            Loc_stDMAcfg.srcAdd = &uartTransferBuffer;
            Loc_stDMAcfg.dstAdd1 = UartDMA_arrUSART_DR_Add[UartDMA_arrCfgs[i].UART];
            break;

            case Usart_enu_Rx:
            Loc_stDMAcfg.TransferType = DMA_enuPER2MEM;
            Loc_stDMAcfg.BuffSize = UART_DMA_INITIAL_RX_BUFF_SIZE;
            Loc_stDMAcfg.Stream = UartDMA_arrDMAdata[UartDMA_arrCfgs[i].UART]
            .stream[UART_DMA_ON_RX];
            Loc_stDMAcfg.srcAdd = UartDMA_arrUSART_DR_Add[UartDMA_arrCfgs[i].UART];
            Loc_stDMAcfg.dstAdd1 = &UartReceiveBuffer;
            break;

            default:
            break;
        }

        if(Loc_u8UsartMap[i]){
            Loc_stUSartCfg.Mode = Usart_enu_Tx_Rx;
        }
        else{
            Loc_u8UsartMap[UartDMA_arrCfgs[i].UART]++;
        }
        DMA_enuInit(&Loc_stDMAcfg);
        Usart_enuInit(&Loc_stUSartCfg);
    }
}

UartDMA_enuErrorStatus_t UartDMA_enuRegisterCallBack(uint8_t Copy_u8Line,
DMA_CB Add_cb){

    UartDMA_enuErrorStatus_t Loc_enuStatus = UartDMA_enu_OK;
    DMA_enuDMA_t Loc_enuDMA = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
    .DMA;
    DMA_enuStream_t Loc_enuStream = 0;    
    NVIC_enuIRQn_t Loc_enuIRQn;
    switch(UartDMA_arrCfgs[Copy_u8Line].Mode){
        
        case Usart_enu_Tx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_TX];
        Loc_enuIRQn = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .IRQn[UART_DMA_ON_TX];
        break;

        case Usart_enu_Rx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_RX];
        Loc_enuIRQn = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .IRQn[UART_DMA_ON_RX];
        break;

        default:
        break;
    }

    if(Add_cb == NULL){
        Loc_enuStatus = UartDMA_enu_NULL_POINTER;
    }
    else if(Copy_u8Line > (UART_DMA_NO_OF_LINES - 1)){
        Loc_enuStatus = UartDMA_enu_INVALID_LINE;
    }
    else{
        DMA_enuRegisterCb(Loc_enuDMA,Loc_enuStream,Add_cb,DMA_enuOnFullTransfer);
        NVIC_enuClearPendingIRQn(Loc_enuIRQn);
        NVIC_enuEnableIRQn(Loc_enuIRQn);
    }
    return Loc_enuStatus;
}

UartDMA_enuErrorStatus_t UartDMA_enuStartTransfer(uint8_t Copy_u8Line){

    UartDMA_enuErrorStatus_t Loc_enuStatus = UartDMA_enu_OK;
    DMA_enuDMA_t Loc_enuDMA = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
    .DMA;
    DMA_enuStream_t Loc_enuStream = 0;    
    switch(UartDMA_arrCfgs[Copy_u8Line].Mode){
        
        case Usart_enu_Tx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_TX];
        break;

        case Usart_enu_Rx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_RX];
        break;

        default:
        break;
    }

    if(Copy_u8Line > (UART_DMA_NO_OF_LINES - 1)){
        Loc_enuStatus = UartDMA_enu_INVALID_LINE;
    }
    else{
        DMA_enuStartTransfer(Loc_enuDMA,Loc_enuStream);
    }
    return Loc_enuStatus;
}

UartDMA_enuErrorStatus_t UartDMA_enuStopTransfer(uint8_t Copy_u8Line){

    UartDMA_enuErrorStatus_t Loc_enuStatus = UartDMA_enu_OK;
    DMA_enuDMA_t Loc_enuDMA = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
    .DMA;
    DMA_enuStream_t Loc_enuStream = 0;    
    switch(UartDMA_arrCfgs[Copy_u8Line].Mode){
        
        case Usart_enu_Tx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_TX];
        break;

        case Usart_enu_Rx:
        Loc_enuStream = UartDMA_arrDMAdata[UartDMA_arrCfgs[Copy_u8Line].UART]
        .stream[UART_DMA_ON_RX];
        break;

        default:
        break;
    }

    if(Copy_u8Line > (UART_DMA_NO_OF_LINES - 1)){
        Loc_enuStatus = UartDMA_enu_INVALID_LINE;
    }
    else{
        DMA_enuStopTransfer(Loc_enuDMA,Loc_enuStream);
    }
    return Loc_enuStatus;
}
