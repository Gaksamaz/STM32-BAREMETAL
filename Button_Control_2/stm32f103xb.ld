ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

PROVIDE(__StackTop = ORIGIN(RAM) + LENGTH(RAM));

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data : AT (ADDR(.text) + SIZEOF(.text)) {
    *(.data*)
  } > RAM

  .bss :
  {
    *(.bss*)
    *(COMMON)
  } > RAM

  .stack (COPY):
  {
    __StackLimit = .;
    . = . + 0x400; /* 1 KB stack */
    __StackTop = .;
  } > RAM
}
