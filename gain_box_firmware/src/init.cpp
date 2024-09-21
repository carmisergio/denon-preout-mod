#include <avr/io.h>

#include "init.hpp"

#if defined(__AVR_ATmega328P__)
void init()
{
    // No initialization needed
}
#endif

#if defined(__AVR_ATtiny412__)
#define CLK_PRESCALER_FLAGS CLKCTRL_PDIV_8X_gc // Divide by 8 = 2 MHz
void init()
{
    // Enable clock prescaler
    _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, CLK_PRESCALER_FLAGS | CLKCTRL_PEN_bm);
}
#endif