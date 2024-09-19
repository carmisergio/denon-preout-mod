#pragma once

#if defined(__AVR_ATmega328P__)

#include <stdint.h>
#include <avr/io.h>

// Pins
enum class Pin
{
    P_PB0,
    P_PB1,
    P_PB2,
    P_PB3,
    P_PB4,
    P_PB5,
    P_PB6,
    P_PB7,
    P_PC0,
    P_PC1,
    P_PC2,
    P_PC3,
    P_PC4,
    P_PC5,
    P_PC6,
    P_PD0,
    P_PD1,
    P_PD2,
    P_PD3,
    P_PD4,
    P_PD5,
    P_PD6,
    P_PD7,
};

// Get port on which a digital IO pin is located
constexpr uint8_t volatile *port_from_pin(Pin pin)
{
    switch (pin)
    {
    case Pin::P_PB0:
    case Pin::P_PB1:
    case Pin::P_PB2:
    case Pin::P_PB3:
    case Pin::P_PB4:
    case Pin::P_PB5:
    case Pin::P_PB6:
    case Pin::P_PB7:
        return &PORTB;
    case Pin::P_PC0:
    case Pin::P_PC1:
    case Pin::P_PC2:
    case Pin::P_PC3:
    case Pin::P_PC4:
    case Pin::P_PC5:
    case Pin::P_PC6:
        return &PORTC;
    case Pin::P_PD0:
    case Pin::P_PD1:
    case Pin::P_PD2:
    case Pin::P_PD3:
    case Pin::P_PD4:
    case Pin::P_PD5:
    case Pin::P_PD6:
    case Pin::P_PD7:
        return &PORTD;
    }

    return nullptr;
}

// Get bit in its port on through which a digital IO pin can be accessed
constexpr uint8_t bit_from_pin(Pin pin)
{
    switch (pin)
    {
    case Pin::P_PB0:
    case Pin::P_PC0:
    case Pin::P_PD0:
        return 0;
    case Pin::P_PB1:
    case Pin::P_PC1:
    case Pin::P_PD1:
        return 1;
    case Pin::P_PB2:
    case Pin::P_PC2:
    case Pin::P_PD2:
        return 2;
    case Pin::P_PB3:
    case Pin::P_PC3:
    case Pin::P_PD3:
        return 3;
    case Pin::P_PB4:
    case Pin::P_PC4:
    case Pin::P_PD4:
        return 4;
    case Pin::P_PB5:
    case Pin::P_PC5:
    case Pin::P_PD5:
        return 5;
    case Pin::P_PB6:
    case Pin::P_PC6:
    case Pin::P_PD6:
        return 6;
    case Pin::P_PB7:
    case Pin::P_PD7:
        return 7;
    }

    return 0;
}

#endif
