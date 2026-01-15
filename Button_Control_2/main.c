#include <stdint.h>

#define RCC_APB2ENR     (*(volatile uint32_t*)0x40021018)
#define GPIOA_CRL       (*(volatile uint32_t*)0x40010800)
#define GPIOA_ODR       (*(volatile uint32_t*)0x4001080C)
#define GPIOB_CRL       (*(volatile uint32_t*)0x40010C00)
#define GPIOB_ODR       (*(volatile uint32_t*)0x40010C0C)
#define GPIOB_IDR       (*(volatile uint32_t*)0x40010C08)

void RCC_Config(void)
{
    RCC_APB2ENR |= (1 << 2);  // GPIOA clock enable
    RCC_APB2ENR |= (1 << 3);  // GPIOB clock enable
}

void GPIO_Config(void)
{
    GPIOA_CRL &= ~(0xF << 20);     
    GPIOA_CRL |=  (0x2 << 20);     // PA5 output 2MHz push-pull

    GPIOB_CRL &= ~(0xF << 0);      
    GPIOB_CRL |=  (0x8 << 0);      // PB0 input pull-up/down
    GPIOB_ODR |=  (1 << 0);        // pull-up etkinleştir
}

void delay(volatile uint32_t time)
{
    while(time--);
}

int main(void)
{
    RCC_Config();
    GPIO_Config();

    int button_state = 0;

    while (1)
    {
        if (!(GPIOB_IDR & (1 << 0)))  
        {
            delay(100000);  // debounce
            if (!(GPIOB_IDR & (1 << 0)))
            {
                button_state = (button_state + 1) % 4;

                while (!(GPIOB_IDR & (1 << 0)));  
            }
        }

        if (button_state == 1)
        {
            GPIOA_ODR |= (1 << 5);  
        }
        else if (button_state == 2)
        {
            GPIOA_ODR |= (1 << 5);
            delay(500000);
            GPIOA_ODR &= ~(1 << 5);
            delay(500000);
        }
        else if (button_state == 3)
        {
            GPIOA_ODR |= (1 << 5);
            delay(50000);
            GPIOA_ODR &= ~(1 << 5);
            delay(50000);
        }
        else
        {
            GPIOA_ODR &= ~(1 << 5);  
        }
    }
}
