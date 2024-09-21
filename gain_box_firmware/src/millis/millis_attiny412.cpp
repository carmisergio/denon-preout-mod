#include <util/atomic.h>

#include "millis.hpp"

#if defined(__AVR_ATtiny412__)

#define PRESCALER 8
#define PRESCALER_FLAGS TCA_SINGLE_CLKSEL_DIV8_gc

// Counter variable
uint32_t millis_count;

void millis_init()
{
    millis_count = 0;

    // Reset timer count
    TCA0_SINGLE_CNT = 0;

    // Set compare count so 1 compare per ms
    TCA0_SINGLE_PER = (F_CPU / PRESCALER) / 1000 - 1;

    // Enable interrupts
    TCA0_SINGLE_INTCTRL = TCA_SINGLE_OVF_bm;

    // Normal mode
    TCA0_SINGLE_CTRLA = TCA_SINGLE_ENABLE_bm | PRESCALER_FLAGS;

    // Enable global interrupts
    sei();
}

uint32_t millis()
{
    uint32_t val;

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        val = millis_count;
    }

    return val;
}

ISR(TCA0_OVF_vect)
{
    millis_count++;
}

#endif