#include <stdint.h>

#define RCC_APB2ENR     (*(volatile uint32_t*)0x40021018)
#define GPIOA_CRL       (*(volatile uint32_t*)0x40010800)
#define GPIOA_ODR       (*(volatile uint32_t*)0x4001080C)
#define GPIOB_IDR       (*(volatile uint32_t*)0x40010C08)
#define GPIOB_CRL       (*(volatile uint32_t*)0x40010C00)
#define GPIOB_ODR       (*(volatile uint32_t*)0x40010C0C)

void delay(volatile uint32_t time) {
    while (time--);
}

int main(void)
{
    //Enable RCC A and B clocks
    RCC_APB2ENR |= (1 << 2);
    RCC_APB2ENR |= (1 << 3);

    GPIOA_CRL &= ~(0xF << 20);
    GPIOA_CRL |=  (0x2 << 20);

    GPIOB_CRL &= ~(0xF << 0);
    GPIOB_CRL |=  (0x8 << 0);

    GPIOB_ODR |= (1 << 0);   

    while (1)
    {
        if (!(GPIOB_IDR & (1 << 0)))
        {
            GPIOA_ODR |= (1 << 5);
        }

        else
        {
            GPIOA_ODR &= ~(1 << 5);
        }

        delay(100000);
        
    }
    
}

