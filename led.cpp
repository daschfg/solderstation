#include <Arduino.h>
#include "led.h"
#include "helpers.h"

Led::Led(int pin)
    : _pin(pin), _blinking(false)
{}

void Led::init(void)
{
    pinMode(_pin, OUTPUT);
    deactivate();
    refresh();
}

void Led::activate(void)
{
    _is_activated = true;
}

void Led::deactivate(void)
{
    _is_activated = false;
}

bool Led::is_on(void) const
{
    return _state == HIGH;
}

void Led::set(bool active)
{
    _state = active ? HIGH : LOW;
    digitalWrite(_pin, _state);
}

bool Led::is_activated(void) const
{
    return _is_activated;
}

void Led::blink(bool should_activate, uint32_t time)
{
    if (should_activate)
    {
        _blinking = true;
        _blinktime = time;
        _last_toggle = millis();
        set(true);
    }
    else
    {
        _blinking = false;
    }
}

void Led::refresh(void)
{
    if (_blinking && is_activated())
    {
        if (is_timeout_reached(_last_toggle, _blinktime))
        {
            set(!is_on());
            _last_toggle = millis();
        }
    }
    else
    {
        set(is_activated());
    }
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

void TemperatureView::set_blink(bool activate, uint32_t time)
{
    _led_low.blink(activate, time);
    _led_mid.blink(activate, time);
    _led_high.blink(activate, time);
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
    _led_low.refresh();
    _led_mid.refresh();
    _led_high.refresh();
}
