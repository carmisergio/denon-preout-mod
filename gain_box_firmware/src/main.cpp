#include <avr/io.h>
#include <util/delay.h>

#include "init.hpp"
#include "millis.hpp"
#include "gpio.hpp"
#include "signal.hpp"

// Pin configuration
#if defined(__AVR_ATmega328P__)
constexpr Pin IN_AC_PULSE_PIN = Pin::P_PD3;
constexpr Pin IN_EXTTRIG_PIN = Pin::P_PD4;
constexpr Pin OUT_AC_EN_PIN = Pin::P_PB3;
constexpr Pin OUT_TRIG_PIN = Pin::P_PB4;
constexpr Pin OUT_UNMUTE_PIN = Pin::P_PB5;
#elif defined(__AVR_ATtiny412__)
constexpr Pin IN_AC_PULSE_PIN = Pin::P_PA1;
constexpr Pin IN_EXTTRIG_PIN = Pin::P_PA2;
constexpr Pin OUT_AC_EN_PIN = Pin::P_PA3;
constexpr Pin OUT_UNMUTE_PIN = Pin::P_PA6;
constexpr Pin OUT_TRIG_PIN = Pin::P_PA7;
#else
#error Unsupported MCU!
#endif

// Delay configuration
constexpr uint32_t D_AC_DETECT_TIME = 1000;
constexpr uint32_t D_AC_EN_OFF_TIME = 1000;
constexpr uint32_t D_EXTTRIG_TIME = 10000;
constexpr uint32_t D_AC_OK_TIME = 2000;
constexpr uint32_t D_TRIG_OUT_TIME = 200;

int main()
{
  // Initizlize MCU
  mcu_init();

  // Start millis() counter
  millis_init();

  // IO
  DigitalInput in_ac_pulse(IN_AC_PULSE_PIN, InputCfg::INVERTED_PULLUP);
  DigitalInput in_exttrig(IN_EXTTRIG_PIN, InputCfg::INVERTED_PULLUP);
  DigitalOutput out_ac_en(OUT_AC_EN_PIN);
  DigitalOutput out_unmute(OUT_UNMUTE_PIN);
  DigitalOutput out_trig(OUT_TRIG_PIN);

  // // Delays
  SignalDelay d_ac_detect(D_AC_DETECT_TIME, DelayType::FALLING);
  SignalDelay d_ac_en_off(D_AC_EN_OFF_TIME, DelayType::FALLING);
  SignalDelay d_exttrig_ok(D_EXTTRIG_TIME, DelayType::RISING);
  SignalDelay d_ac_ok(D_AC_OK_TIME, DelayType::RISING);
  SignalDelay d_trig_out(D_TRIG_OUT_TIME, DelayType::RISING);

  // Main loop
  while (true)
  {
    // Get current time
    uint32_t time = millis();

    // Get values of inputs
    bool ac_pulse = in_ac_pulse.get(); // Inverted
    bool exttrig = in_exttrig.get();   // Inverted

    // Process
    bool ac_detect = d_ac_detect.process(ac_pulse, time); // True when AC is present
    bool ac_en = d_ac_en_off.process(exttrig, time);      // AC_EN output signal
    bool exttrig_ok = d_exttrig_ok.process(exttrig, time);
    bool ac_ok = d_ac_ok.process(ac_detect, time);
    bool sigchain_ok = exttrig_ok && ac_ok;            // UNMUTE output signal
    bool trig = d_trig_out.process(sigchain_ok, time); // TRIG output signal

    // Write outputs
    out_ac_en.change(ac_en);
    out_unmute.change(sigchain_ok);
    out_trig.change(trig);
  }
}