MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K 
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 64K 
}

ENTRY(Reset_Handler)

SECTIONS
{
    
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector)      
        *(.text)            
        *(.text.*)          
        *(.rodata)          
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

    
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH

    ._user_heap_stack :
    {
        . = ALIGN(8);
        _estack = ORIGIN(RAM) + LENGTH(RAM); 
        . = . - 0x1000; 
        _eheap = .;    
    } > RAM

    _sidata = LOADADDR(.data); 
}
