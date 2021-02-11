#include <Arduino.h>
#include "led.h"

Led::Led(int pin)
    : _pin(pin)
{}

void Led::init(void)
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

TemperatureView::TemperatureView(Led& led_low, Led& led_mid, Led& led_high)
    : _led_low(led_low), _led_mid(led_mid), _led_high(led_high)
{ }

void TemperatureView::init(void)
{
    _led_low.init();
    _led_mid.init();
    _led_high.init();
}
