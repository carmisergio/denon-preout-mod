#include "signal.hpp"

#include "millis.hpp"

SignalDelay::SignalDelay(uint32_t delay, DelayType type)
{
    // Save configuration
    this->delay = delay;
    this->type = type;

    // Initialize state
    this->state = type == DelayType::RISING ? State::INACTIVE : State::ACTIVE;
    this->wait_start = 0;
}

bool SignalDelay::process(bool input)
{
    uint32_t time = millis();
    return this->process(input, time);
}

bool SignalDelay::process(bool input, uint32_t time)
{
    // If signal is de-excitation state for this type of delay
    if ((this->type == DelayType::RISING && !input) ||
        (this->type == DelayType::FALLING && input))
    {
        // Set signal as inactive
        this->state = State::INACTIVE;

        // Output inactive signal
        return this->get_output();
    }

    // Signal is in excitation state
    switch (this->state)
    {
    case State::INACTIVE:
        // Start wait
        this->state = State::WAITING;
        this->wait_start = time;
        break;
    case State::WAITING:
        // Check if delay has elapsed
        if (time - this->wait_start >= this->delay)
            this->state = State::ACTIVE;
        break;
    default:
        break;
    }

    return this->get_output();
}

// Compute output for state of delay
bool SignalDelay::get_output()
{
    if (this->type == DelayType::RISING)
        return this->state == State::ACTIVE;
    else
        return this->state != State::ACTIVE;
}