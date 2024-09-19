#pragma once

#include <stdint.h>

/**
 * Initialize program time counter
 * 
 * Sets up timers and interrupts
 */
void millis_init();

/**
 * Get program time counter value since initialization
 * 
 * @return timer value in milliseconds
 */
uint32_t millis();
