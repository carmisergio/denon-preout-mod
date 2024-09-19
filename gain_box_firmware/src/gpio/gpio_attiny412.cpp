#include <avr/io.h>

#ifdef __AVR_ATtiny412__

#include "gpio.hpp"

// Bit manipulation macros
#define OUT_IO_BIT(port, bit) port = _BV(bit)
#define SET_IO_BIT(port, bit) port |= _BV(bit)
#define CLEAR_IO_BIT(port, bit) port &= ~_BV(bit)
#define TOGGLE_IO_BIT(port, bit) port ^= _BV(bit)
#define IS_IO_BIT_SET(port, bit) (port & _BV(bit)) != 0

DigitalOutput::DigitalOutput(Pin pin)
{
    // Save configuration
    this->pin = pin;

    // Set pin as output
    OUT_IO_BIT(PORTA_DIRSET, bit_from_pin(this->pin));
}

DigitalOutput::~DigitalOutput()
{
    // Reset data direction
    OUT_IO_BIT(PORTA_DIRCLR, bit_from_pin(this->pin));
}

void DigitalOutput::toggle()
{
    OUT_IO_BIT(PORTA_OUTTGL, bit_from_pin(this->pin));
}

void DigitalOutput::set()
{
    OUT_IO_BIT(PORTA_OUTSET, bit_from_pin(this->pin));
}

void DigitalOutput::clear()
{
    OUT_IO_BIT(PORTA_OUTCLR, bit_from_pin(this->pin));
}

void DigitalOutput::change(bool val)
{
    if (val)
        this->set();
    else
        this->clear();
}

DigitalInput::DigitalInput(Pin pin, InputCfg cfg)
{
    // Save configuration
    this->pin = pin;

    // Set pullup
    if (cfg == InputCfg::PULLUP || cfg == InputCfg::INVERTED_PULLUP)
        SET_IO_BIT(*pinctrl_reg_from_pin(this->pin), PORT_PULLUPEN_bp);

    // Set inverted
    if (cfg == InputCfg::INVERTED_NOPULLUP || cfg == InputCfg::INVERTED_PULLUP)
        SET_IO_BIT(*pinctrl_reg_from_pin(this->pin), PORT_INVEN_bp);
}

DigitalInput::~DigitalInput()
{
    // Reset pin configuration
    if (cfg == InputCfg::PULLUP || cfg == InputCfg::INVERTED_PULLUP)
        CLEAR_IO_BIT(*pinctrl_reg_from_pin(this->pin), PORT_PULLUPEN_bp);

    // Set inverted
    if (cfg == InputCfg::INVERTED_NOPULLUP || cfg == InputCfg::INVERTED_PULLUP)
        CLEAR_IO_BIT(*pinctrl_reg_from_pin(this->pin), PORT_INVEN_bp);
}

bool DigitalInput::get()
{
    return IS_IO_BIT_SET(PORTA_IN, bit_from_pin(this->pin));
}

#endif