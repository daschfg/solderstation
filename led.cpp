#include <Arduino.h>
#include "led.h"

Led::Led(int pin)
    : _pin(pin)
{}

void Led::init(void)
{
    pinMode(_pin, OUTPUT);
    deactivate();
}

void Led::activate(void)
{
    digitalWrite(_pin, HIGH);
}

void Led::deactivate(void)
{
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

void TemperatureView::set_blink(bool state, uint32_t time)
{
    // TODO
}

void TemperatureView::set_led_low(void)
{
    _led_low.activate();
    _led_mid.deactivate();
    _led_high.deactivate();
}

void TemperatureView::set_led_mid(void)
{
    _led_low.activate();
    _led_mid.activate();
    _led_high.deactivate();
}

void TemperatureView::set_led_high(void)
{
    _led_low.activate();
    _led_mid.activate();
    _led_high.activate();
}

void TemperatureView::refresh(void)
{

}
