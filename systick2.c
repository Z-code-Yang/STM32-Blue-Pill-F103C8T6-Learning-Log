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

#define SysTick 0xE000E010UL
#define STK_CTRL  (*(volatile uint32_t *)(SysTick + 0x00))
#define STK_LOAD  (*(volatile uint32_t *)(SysTick + 0x04))
#define STK_VAL   (*(volatile uint32_t *)(SysTick + 0x08))

volatile uint32_t ticks = 0;

void delay_ms(uint32_t ms)
{
    STK_LOAD = 8000U - 1U;              // 1 ms count at 8 MHz
    STK_VAL = 0;                        // clear current counter value
    STK_CTRL = (1U << 0) | (1U << 2);   // counter enable and Processor clock source and no interrupt

    for(uint32_t i = 0; i < ms; i++) //for loop to create mutiple 1ms count
    {
        while((STK_CTRL & (1U << 16)) == 0) //create loop for bit 16 of the counter flag
        {
        }
    }

    STK_CTRL = 0; // disable all the systick
}

int main(void)
{
    RCC_APB2ENR |= (1U << 4);

    GPIOC_CRH &= ~(0xFU << 20);
    GPIOC_CRH |=  (0x2U << 20);

    STK_LOAD = 8000U - 1U; //load the cycle for counting formula is time = cycle/fre
    STK_VAL = 0;//reset the current count to 0
    STK_CTRL = (1U << 0) | (1U << 1) | (1U << 2);//turn on the interrupt and counter enable and select Processor clock source

    while(1)
    {
    }
}

void SysTick_Handler(void)
{
	ticks++;//tick incrment every 1ms base on the cycle and clock source 
	if(ticks >= 500)
	{
		GPIOC_ODR ^= (1U << 13);
		ticks = 0; //reset the tick 
	}

}
