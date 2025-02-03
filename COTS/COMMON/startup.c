#include <stdint.h>

/* Symbols from the linker script */
extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

/* Function prototypes for exception handlers */
void Reset_Handler(void);
void Default_Handler(void);

/* Cortex-M4 Processor Exception Handlers */
void NMI_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)         __attribute__((weak, alias("Default_Handler")));

/* STM32F401CC Peripheral Interrupt Handlers (placeholders) */
void WWDG_Handler(void)            __attribute__((weak, alias("Default_Handler")));
void PVD_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler(void)           __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
/* Add more peripheral handlers as needed */

/* Vector Table */
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))&_estack,   /* Initial stack pointer */
    Reset_Handler,             /* Reset handler */
    NMI_Handler,               /* NMI handler */
    HardFault_Handler,          /* Hard fault handler */
    MemManage_Handler,          /* Memory management fault handler */
    BusFault_Handler,           /* Bus fault handler */
    UsageFault_Handler,         /* Usage fault handler */
    0, 0, 0, 0,                 /* Reserved */
    SVC_Handler,                /* SVCall handler */
    DebugMon_Handler,           /* Debug monitor handler */
    0,                          /* Reserved */
    PendSV_Handler,             /* PendSV handler */
    SysTick_Handler,            /* SysTick handler */
    WWDG_Handler,               /* Window Watchdog */
    PVD_Handler,                /* PVD through EXTI Line detection */
    TAMP_STAMP_Handler,         /* Tamper and TimeStamp */
    RTC_WKUP_Handler,           /* RTC Wakeup through EXTI */
    FLASH_Handler,              /* Flash */
    RCC_Handler,                /* RCC */
    EXTI0_Handler,              /* EXTI Line0 */
    EXTI1_Handler,              /* EXTI Line1 */
    EXTI2_Handler,              /* EXTI Line2 */
    EXTI3_Handler,              /* EXTI Line3 */
    EXTI4_Handler,              /* EXTI Line4 */
    DMA1_Stream0_Handler,        /* DMA1 Stream 0 */
    /* Add remaining interrupt handlers here */
};

/* Reset handler */
void Reset_Handler(void) {
    /* Copy .data section from flash to RAM */
    uint32_t *pSrc = &_sidata;
    uint32_t *pDest = &_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    /* Zero initialize the .bss section */
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    /* Call main function */
    main();

    /* Infinite loop if main returns */
    while (1);
}

/* Default handler */
void Default_Handler(void) {
    while (1);
}
