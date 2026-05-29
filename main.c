#include <stdint.h>


#define GPIOC_BASE 0x40011000UL
#define GPIOC_CRH  (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

#define GPIOA_BASE 0x40010800UL
#define GPIOA_CRH  (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR  (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

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
    // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 4);
    RCC_APB2ENR |= (1 << 2);

    // Configure PC13 and PC14 and PA8 as push-pull output 2MHz
    GPIOC_CRH |= (1 << 21);
    GPIOC_CRH |= (1 << 25);
    GPIOA_CRH |= (1 << 1);


    while (1)
    {
        // PC 13 low or LED ON (active low) and PC14 low
        GPIOC_ODR ^= (1 << 13);
        delay(100000);
        // PC 13 High or LED off (deactive High) and PC14 High

    }
}
