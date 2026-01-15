.syntax unified
.cpu cortex-m3
.thumb

.section .stack
.word 0x20005000     // 20 KB RAM’in son adresi
.global _estack
_estack:

.global Reset_Handler

.section .isr_vector, "a", %progbits
.type isr_vector, %object
isr_vector:
    .word _estack            // stack pointer
    .word Reset_Handler      // reset handler

.section .text
.type Reset_Handler, %function
Reset_Handler:
    bl main
    b .
