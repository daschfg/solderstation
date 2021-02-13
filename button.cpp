#include <Arduino.h>
#include "button.h"
#include "helpers.h"

Button::Button(int pin)
    : _pin(pin), _debounce_start(0), _pressed(false)
{}

void Button::init(void)
{
    pinMode(_pin, INPUT_PULLUP);
}

void Button::refresh(void)
{
    if (_debounce_start == 0 || is_timeout_reached(_debounce_start, 50))
    {
        int current_state = digitalRead(_pin);
        if (current_state == HIGH && _last_state == LOW)
        {
            _pressed = true;
            _debounce_start = millis();
        }
        else
        {
            _debounce_start = 0;
        }
        _last_state = current_state;
    }
}

bool Button::was_pressed(void) const
{
    return _pressed;
}

void Button::reset_state(void)
{
    _pressed = false;
}
