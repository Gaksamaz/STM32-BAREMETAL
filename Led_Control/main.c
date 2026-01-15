#include <stdint.h>

#define RCC_APB2ENR   (*(volatile uint32_t*)0x40021018)
#define GPIOA_CRL     (*(volatile uint32_t*)0x40010800)
#define GPIOA_ODR     (*(volatile uint32_t*)0x4001080C)

void delay(volatile uint32_t count) {
    while(count--) {
        __asm__("nop");
    }
}

int main(void) {
    // 1. GPIOA saatini etkinleştir
    RCC_APB2ENR |= (1 << 2);  // IOPAEN

    // 2. PA5'i genel amaçlı push-pull çıkış olarak ayarla (output 2 MHz)
    GPIOA_CRL &= ~(0xF << 20);     // PA5 = bit 23..20
    GPIOA_CRL |=  (0x2 << 20);     // 0010: output push-pull, max 2 MHz

    while (1) {
        // PA5 HIGH → LED yanar
        GPIOA_ODR |= (1 << 5);
        delay(500000);

        // PA5 LOW → LED söner
        GPIOA_ODR &= ~(1 << 5);
        delay(500000);
    }
}
