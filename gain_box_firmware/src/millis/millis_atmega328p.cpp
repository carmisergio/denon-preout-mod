#include <util/atomic.h>

#include "millis.hpp"

#if defined(__AVR_ATmega328P__)

#define PRESCALER 64
#define PRESCALER_FLAGS _BV(CS01) | _BV(CS00)

// Counter variable
uint32_t millis_count;

void millis_init()
{
    millis_count = 0;

    // CTC mode, Output compare A interrupt
    TCCR0A = _BV(WGM01);

    // Reset timer count
    TCNT0 = 0;

    // Set compare count so 1 compare per ms
    OCR0A = (F_CPU / PRESCALER) / 1000 - 1;

    // Set prescaler
    TCCR0B = PRESCALER_FLAGS;

    // Enable interrupts
    TIMSK0 = _BV(OCIE0A);

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

ISR(TIMER0_COMPA_vect)
{
    millis_count++;
}

#endif