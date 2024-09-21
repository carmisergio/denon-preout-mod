#include <avr/io.h>

#if defined(__AVR_ATmega328P__)

#include "gpio.hpp"

// Get data direction register of a certain port
#define PORT_FROM_PIN(pin) *(port_from_pin(pin))
#define DDR_FROM_PIN(pin) *(port_from_pin(pin) - 1)
#define PIN_FROM_PIN(pin) *(port_from_pin(pin) - 2)

// Bit manipulation macros
#define SET_IO_BIT(port, bit) port |= _BV(bit)
#define CLEAR_IO_BIT(port, bit) port &= ~_BV(bit)
#define TOGGLE_IO_BIT(port, bit) port ^= _BV(bit)
#define IS_IO_BIT_SET(port, bit) (port & _BV(bit)) != 0

DigitalOutput::DigitalOutput(Pin pin)
{
    // Save configuration
    this->pin = pin;

    // Set pin as output
    SET_IO_BIT(DDR_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

DigitalOutput::~DigitalOutput()
{
    // Reset data direction
    CLEAR_IO_BIT(DDR_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

void DigitalOutput::toggle()
{
    TOGGLE_IO_BIT(PORT_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

void DigitalOutput::set()
{
    SET_IO_BIT(PORT_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

void DigitalOutput::clear()
{
    CLEAR_IO_BIT(PORT_FROM_PIN(this->pin), bit_from_pin(this->pin));
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
    this->cfg = cfg;

    // Set pullup
    if (this->cfg == InputCfg::PULLUP || this->cfg == InputCfg::INVERTED_PULLUP)
        SET_IO_BIT(PORT_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

DigitalInput::~DigitalInput()
{
    // Reset pullup
    if (this->cfg == InputCfg::PULLUP || this->cfg == InputCfg::INVERTED_PULLUP)
        CLEAR_IO_BIT(PORT_FROM_PIN(this->pin), bit_from_pin(this->pin));
}

bool DigitalInput::get()
{
    bool val = IS_IO_BIT_SET(PIN_FROM_PIN(this->pin), bit_from_pin(this->pin));

    // Invert signal if requested
    if (this->cfg == InputCfg::INVERTED_NOPULLUP || this->cfg == InputCfg::INVERTED_PULLUP)
        val = !val;

    return val;
}

#endif