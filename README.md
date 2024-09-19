# Denon AVR-X1300W Pre-out mod

The scope of this project is adding line-level outputs to the Denon AVR-X1300W AV Receiver.
This can be acheived by getting the low-level signals from the digital board of the receiver before they make their way to the power amp board.

The "Vampire PCB" is soldered directly to the digital board of the receiverr, and provides an 8-pin JST PH connector with the signals. A small length of shielded cable brings them to the back panel of the unit, where removing the AM/FM tuner unit provides a convenient place to mount a miniature circular connector.

An external "Gain Box" amplifies the ~150Vrms internal signal to a usable (variable) line level with a single stage of op-amp amplification. It also processes the 12V signal coming from the receiver to operate muting relays on the output and generate a standard 12V trigger signal which can be used to control the amplifiers.
