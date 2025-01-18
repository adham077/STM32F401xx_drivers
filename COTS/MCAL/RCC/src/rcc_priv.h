#ifndef RCC_PRIV_H_
#define RCC_PRIV_H_
#include "bit_math.h"

#define RCC_BASE    0x40023800

#define RCC_HSI_ON_MASK     0x00000001
#define RCC_HSI_RDY_MASK    0x00000002

#define RCC_HSE_ON_MASK     0x00010000
#define RCC_HSE_ON_MASK     0x00020000

#define RCC_CR_PLLON_MASK   0x01000000
#define RCC_CR_PLLRDY_MASK  0x02000000

#define RCC_HSE_BYPASS_MASK 0x00040000

#define RCC_CR_HSION    0
#define RCC_CR_HSIRDY   1

#define RCC_CR_HSEON    16
#define RCC_CR_HSERDY   17

#define RCC_CR_PLLON    24
#define RCC_CR_PLLRDY   25

#define RCC_CR_HSE_BYPASS 18

#define RCC_PLL_SRC     22

#define RCC_APB1ENLR_SRAM 16 
#define RCC_APB1ENLR_FLITF 15 


#define RCC_HSI_TIMEOUT 500
#define RCC_HSE_TIMEOUT 100000
#define RCC_PLL_TIMEOUT 5000

#define SET_SW_BITS(CFGR_REG,VAL) (CFGR_REG = ((CFGR_REG & 0xFFFFFFFC) | (VAL)))
#define GET_SW_BITS(CFGR_REG) ((CFGR_REG & 0x00000003))
#define GET_SWS_BITS(CFGR_REG) ((CFGR_REG & 0x0000000C)>>2)

/*FOR PLL_Q
bits 24->27
1111 0000 1111 1111 1111 1111 1111 1111
F0FFFFFF
*/
#define SET_PLL_Q(PLLCFGR,VAL) (PLLCFGR = ((PLLCFGR&0xF0FFFFFF)|(VAL<<24)))
/*FOR PLL_P
bits 16->17
1111 1111 1111 1100 1111 1111 1111 1111
FFFCFFFF
*/
#define SET_PLL_P(PLLCFGR,VAL) (PLLCFGR = ((PLLCFGR&0xFFFCFFFF)|(VAL<<16)))
/*FOR PLL_N
bits 6->14
1111 1111 1111 1111 1000 0000 0011 1111
FFFF803F
*/
#define SET_PLL_N(PLLCFGR,VAL) (PLLCFGR = ((PLLCFGR&0xFFFF803F)|(VAL<<6)))
/*FOR PLL_M
bits 0->5
1111 1111 1111 1111 1111 1111 1110 0000
FFFFFFE0
*/
#define SET_PLL_M(PLLCFGR,VAL) (PLLCFGR = ((PLLCFGR&0xFFFFFFE0)|(VAL)))

/*For AHB Prescaler*/
#define SET_HPRE(CFGR_REG,VAL) (CFGR_REG = ((CFGR_REG & 0xFFFFFF0F) | (VAL<<4)))
/*For APB1 High Speed Prescaler*/
#define SET_PPRE1(CFGR_REG,VAL) (CFGR_REG = ((CFGR_REG & 0xFFFF8FFF) | (VAL<<10)))
/*For APB2 Low Speed Prescaler*/
#define SET_PPRE2(CFGR_REG,VAL) (CFGR_REG = ((CFGR_REG & 0xFFFC7FFF) | (VAL<<13)))

typedef struct{
    volatile uint32_t CR;       /*Control register*/
    volatile uint32_t PLLCFGR;  /*PLL configuration register*/
    volatile uint32_t CFGR;     /*Clock configuration register*/
    volatile uint32_t CIR;      /*Clock interrupt register*/
    volatile uint32_t AHB1RSTR; /*AHB1 peripheral reset register*/
    volatile uint32_t AHB2RSTR; /*AHB2 peripheral reset register*/
    volatile const uint64_t reserved1;/*Reserved*/
    volatile uint32_t APB1RSTR; /*APB1 peripheral reset register*/
    volatile uint32_t APB2RSTR; /*APB2 peripheral reset register*/
    volatile const uint64_t reserved2;/*Reserved*/
    volatile uint32_t AHB1ENR;  /*AHB1 peripheral clock enable register*/
    volatile uint32_t AHB2ENR;  /*AHB2 peripheral clock enable register*/
    volatile const uint64_t reserved3;/*Reserved*/
    volatile uint32_t APB1ENR;  /*APB1 peripheral clock enable register*/
    volatile uint32_t APB2ENR;  /*APB2 peripheral clock enable register*/
    volatile const uint64_t reserved4;/*Reserved*/
    volatile uint32_t AHB1LPENR;/*AHB1 peripheral clock enable in low power mode register*/
    volatile uint32_t AHB2LPENR;/*AHB2 peripheral clock enable in low power mode register*/
    volatile const uint64_t reserved5;/*Reserved*/
    volatile uint32_t APB1LPENR;/*APB1 peripheral clock enable in low power mode register*/
    volatile uint32_t APB2LPENR;/*APB2 peripheral clock enable in low power mode register*/
    volatile const uint64_t reserved6;/*Reserved*/
    volatile uint32_t RCC_BDCR; /*Backup domain control register*/
    volatile uint32_t RCC_CSR;  /*Control/status register*/
    volatile const uint64_t reserved7;/*Reserved*/
    volatile uint32_t RCC_SSCGR;/*Spread spectrum clock generation register*/
    volatile uint32_t RCC_PLLI2SCFGR;/*PLLI2S configuration register*/
    volatile const uint32_t reserved8;/*Reserved*/
    volatile uint32_t RCC_DCKCFGR;/*Dedicated Clock Configuration Register*/
}RCC_stReg_t;

typedef struct{
    RCC_enuCLK_t PLL_CLK;
    uint8_t PLL_M;
    uint16_t PLL_N;
    uint8_t PLL_P;
    uint8_t PLL_Q;
}RCC_PLL_stParameters_t;

typedef struct{
    uint32_t AHB;
    uint32_t APB1;
    uint32_t APB2;
}RCC_stBusPrescaler_t;

#endif