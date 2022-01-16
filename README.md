# solderstation

This project provides firmware and schematics for a simple solderstation based on the RT tips from Weller, which can be connected through a standard 3,5 mm jack.

The electronic is mostly based on the original project from [Martin Kumm](http://martin-kumm.de/wiki/doku.php?id=05Misc:SMD_Solderstation).
Most notable differences: The user interface is simplified (no display, just some LEDs and buttons) and a (optional) circuit for protection against a PWM freeze is added.

The firmware is a complete rewrite for Arduino Uno.

The used PID module is Brett Beauregards [Arduino PID library](https://github.com/br3ttb/Arduino-PID-Library) with some minor formatting adjustments.

For PWM generation Sam Knights [Arduino PWM frequency library](https://code.google.com/archive/p/arduino-pwm-frequency-library/) is used.
