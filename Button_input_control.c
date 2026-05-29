#include <stdint.h>


#define GPIOC_BASE 0x40011000UL
#define GPIOC_CRH  (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_IDR  (*(volatile uint32_t *)(GPIOC_BASE + 0x08))

#define GPIOA_BASE 0x40010800UL
#define GPIOA_CRH  (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR  (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR  (*(volatile uint32_t *)(GPIOA_BASE + 0x08))

#define RCC_BASE   0x40021000UL
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

void delay(volatile int count)
{
    while(count != 0)
    {
        count--;
    }
}

int main(void)
{
    // Enable GPIOC clock for GPIOA and GPIOC
    RCC_APB2ENR |= (1U << 4);
    RCC_APB2ENR |= (1U << 2);

    // PC13 output push-pull 2MHz
    GPIOC_CRH &= ~(0xFU << 20);
    GPIOC_CRH |= (0x2U << 20);
    // PA8 floating input
    GPIOA_CRH &= ~(0xFU << 0);
    GPIOA_CRH |=  (0x4U << 0);


    while (1)
    {
        if (GPIOA_IDR & (1U << 8)){//check if IDR bits are TRUE using 1U<<8 for masking
        	GPIOC_ODR ^= (1U << 13);//toggle PC13
            delay(100000);//software button debounce

            while (GPIOA_IDR & (1U << 8))//while looping for only one toggle
            {
            }

        }
    }
}
