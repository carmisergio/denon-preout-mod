#pragma once

#include <stdint.h>

// Delay type option
enum class DelayType
{
    RISING,  // Delay on RISING edge, default INACTIVE
    FALLING, // Delay on FALLING edge, default ACTIVE
};

/**
 * Delay rising edge of signal
 */
class SignalDelay
{
public:
    /**
     * Constructor
     *
     * @param delay delay in milliseconds
     * @param type type of delay to apply
     */
    SignalDelay(uint32_t delay, DelayType type);

    /**
     * Apply delay to a signal
     *
     * Depends on millis() for timing
     *
     * @param input value to process
     */
    bool process(bool input);

    /**
     * Apply delay to a signal
     *
     * Takes external timing
     *
     * @param input value to process
     * @param time current time in milliseconds
     */
    bool process(bool input, uint32_t time);

private:
    // Compute output for state of delay
    bool get_output();

    //////// Configuration
    uint32_t delay;
    DelayType type;

    //////// State
    enum class State
    {
        INACTIVE,
        WAITING,
        ACTIVE,
    };
    State state;
    uint32_t wait_start;
};