#pragma once

#if defined(__AVR_ATtiny412__)

#include <stdint.h>
#include <avr/io.h>

// Pins
enum class Pin
{
    P_PA0,
    P_PA1,
    P_PA2,
    P_PA3,
    P_PA6,
    P_PA7,
};


// Get bit in port through which a digital IO pin can be accessed
constexpr uint8_t bit_from_pin(Pin pin)
{
    switch (pin)
    {
    case Pin::P_PA0:
        return 0;
    case Pin::P_PA1:
        return 1;
    case Pin::P_PA2:
        return 2;
    case Pin::P_PA3:
        return 3;
    case Pin::P_PA6:
        return 6;
    case Pin::P_PA7:
        return 7;
    }

    return 0;
}

// Get pin control register from pin
constexpr uint8_t volatile *pinctrl_reg_from_pin(Pin pin)
{
    switch (pin)
    {
    case Pin::P_PA0:
        return &PORTA_PIN0CTRL;
    case Pin::P_PA1:
        return &PORTA_PIN1CTRL;
    case Pin::P_PA2:
        return &PORTA_PIN2CTRL;
    case Pin::P_PA3:
        return &PORTA_PIN3CTRL;
    case Pin::P_PA6:
        return &PORTA_PIN6CTRL;
    case Pin::P_PA7:
        return &PORTA_PIN7CTRL;
    }

    return 0;
}

#endif