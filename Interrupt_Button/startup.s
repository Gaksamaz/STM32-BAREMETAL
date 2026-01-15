.section .isr_vector, "a", %progbits
.type _estack, %object
.word 0x20005000            // Stack pointer (20KB RAM sonu)

.word Reset_Handler         // Reset
.word NMI_Handler           // NMI
.word HardFault_Handler     // HardFault
.word 0                     // MemManage (yok)
.word 0                     // BusFault (yok)
.word 0                     // UsageFault (yok)
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word 0
.word 0
.word PendSV_Handler
.word SysTick_Handler

// IRQ0 - IRQ15 (ilk 16 harici interrupt)
.word EXTI0_IRQHandler      // IRQ6 - EXTI0
.word Default_Handler       // EXTI1
.word Default_Handler       // EXTI2
.word Default_Handler       // EXTI3
.word Default_Handler       // EXTI4
.word Default_Handler       // DMA1_Channel1
.word Default_Handler       // DMA1_Channel2
.word Default_Handler       // DMA1_Channel3
.word Default_Handler       // DMA1_Channel4
.word Default_Handler       // DMA1_Channel5
.word Default_Handler       // DMA1_Channel6
.word Default_Handler       // DMA1_Channel7
.word Default_Handler       // ADC1_2
.word Default_Handler       // USB_HP_CAN_TX
.word Default_Handler       // USB_LP_CAN_RX0
.word Default_Handler       // CAN_RX1

.section .text
.global Reset_Handler
Reset_Handler:
    bl main
    b .

.global Default_Handler
Default_Handler:
    b .

.global NMI_Handler
NMI_Handler:
    b .

.global HardFault_Handler
HardFault_Handler:
    b .

.global SVC_Handler
SVC_Handler:
    b .

.global PendSV_Handler
PendSV_Handler:
    b .

.global SysTick_Handler
SysTick_Handler:
    b .

.global EXTI0_IRQHandler
