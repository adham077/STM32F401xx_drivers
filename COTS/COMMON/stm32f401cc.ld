MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 64K
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector)      /* Vector table */
        *(.text)            /* Code */
        *(.text.*)          /* Other code */
        *(.rodata)          /* Read-only data */
        *(.rodata.*)        
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;         
        *(.data)        
        *(.data.*)          
        . = ALIGN(4);
        _edata = .;         
    } > RAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;          
        *(.bss)             
        *(.bss.*)           
        *(COMMON)           
        . = ALIGN(4);
        _ebss = .;          
    } > RAM

    /* Maximize stack allocation by using the remaining available RAM */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        _sheap = .;
        _eheap = .;
        . += ORIGIN(RAM) + LENGTH(RAM) - .; /* Allocate remaining space to stack */
        _estack = .;
    } > RAM

    /* C++ exception handling sections */
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH

    /* Address of initialized data in FLASH */
    _sidata = LOADADDR(.data);
}
