#include <stdint.h>

#define GPIOC_BASE 0x40011000
#define RCC_BASE   0x40021000

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH   (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR   (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

void delay(int count) {
    while(count--) {
        __asm__("nop");
    }
}

int main(void) {
    // 1. RCC ile GPIOC portunu aktif et (APB2ENR bit 4)
    RCC_APB2ENR |= (1 << 4);

    // 2. GPIOC pin 13 çıkış olarak ayarla (CRH bit 20-23) (push-pull output 2MHz)
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |= (0x2 << 20);

    while(1) {
        // LED ON (GPIOC pin 13 LOW - Blue Pill'de LED aktif LOW)
        GPIOC_ODR &= ~(1 << 13);
        delay(500000);

        // LED OFF (GPIOC pin 13 HIGH)
        GPIOC_ODR |= (1 << 13);
        delay(500000);
    }

    return 0;
}
