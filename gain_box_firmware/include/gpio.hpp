#pragma once

// Pin definitions
#include "gpio/gpio_atmega328p.hpp"
#include "gpio/gpio_attiny412.hpp"

// Pullup setting options
enum class InputCfg
{
    PULLUP,
    NOPULLUP,
    INVERTED_PULLUP,
    INVERTED_NOPULLUP,
};

/**
 * Digital output pin classs
 *
 * Represents a digital output pin, allowing its state to be manipulated
 */
class DigitalOutput
{
public:
    /**
     * Constructor
     *
     * Configures the pin for output
     *
     * @param pin pin to attach to
     */
    DigitalOutput(Pin pin);

    /**
     * Destructor
     *
     * Resets the pin configuration
     */
    ~DigitalOutput();

    /**
     * Set pin state to HIGH
     */
    void set();

    /**
     * Set pin state to LOW
     */
    void clear();

    /**
     * Toggle pin state
     */
    void toggle();

    /**
     * Change pin state to a specific boolean value
     *
     * @param val boolean value
     */
    void change(bool val);

private:
    Pin pin;
};

/**
 * Digital input pin classs
 *
 * Represents a digital input pin, allowing its state to be read
 */
class DigitalInput
{
public:
    /**
     * Constructor
     *
     * Configures the pin for input with or without pullup
     *
     * @param pin pin to attach to
     * @param pullup pullup configuration
     */
    DigitalInput(Pin pin, InputCfg pullup);

    /**
     * Destructor
     *
     * Resets the pin configuration
     */
    ~DigitalInput();

    /**
     * Set pin state to HIGH
     */
    bool get();

private:
    Pin pin;
    InputCfg cfg;
};
