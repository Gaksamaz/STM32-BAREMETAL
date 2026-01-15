#include <stdint.h>

// RCC
#define RCC_APB2ENR    (*(volatile uint32_t*)0x40021018)
#define RCC_CR         (*(volatile uint32_t*)0x40021000)
#define RCC_CFGR       (*(volatile uint32_t*)0x40021004)

// GPIOA
#define GPIOA_CRL      (*(volatile uint32_t*)0x40010800)
#define GPIOA_IDR      (*(volatile uint32_t*)0x40010808)
#define GPIOA_ODR      (*(volatile uint32_t*)0x4001080C)

// AFIO
#define AFIO_EXTICR1   (*(volatile uint32_t*)0x40010008)
#define AFIO_ENR       (1 << 0)

// EXTI
#define EXTI_IMR       (*(volatile uint32_t*)0x40010400)
#define EXTI_FTSR      (*(volatile uint32_t*)0x4001040C)
#define EXTI_PR        (*(volatile uint32_t*)0x40010414)

// NVIC
#define NVIC_ISER0     (*(volatile uint32_t*)0xE000E100)

void GPIO_Config(void) {
    RCC_APB2ENR |= (1 << 2); // GPIOA clock enable
    RCC_APB2ENR |= (1 << 0); // AFIO clock enable

    // PA0 input (buton), PA5 output push-pull
    GPIOA_CRL &= ~((0xF << (0 * 4)) | (0xF << (5 * 4))); // temizle
    GPIOA_CRL |=  (0x4 << (0 * 4));  // PA0 input floating
    GPIOA_CRL |=  (0x2 << (5 * 4));  // PA5 output push-pull 2 MHz
}

void EXTI_Config(void) {
    // EXTI0 line PA0 ile bağlantılı
    AFIO_EXTICR1 &= ~(0xF << 0); // AFIO_EXTICR1[3:0] = 0000 => PA0

    EXTI_IMR |= (1 << 0);   // EXTI0 mask enable
    EXTI_FTSR |= (1 << 0);  // Falling edge trigger enable (butona basıldığında)

    NVIC_ISER0 |= (1 << 6); // EXTI0_IRQn enable in NVIC (IRQ6)
}

void EXTI0_IRQHandler(void) {
    if (EXTI_PR & (1 << 0)) {
        EXTI_PR |= (1 << 0);          // Pending flag temizlenir
        GPIOA_ODR ^= (1 << 5);        // PA5 toggle
    }
}

int main(void) {
    GPIO_Config();
    EXTI_Config();

    while (1);
}
