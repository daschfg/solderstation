#include <Arduino.h>
#include "button.h"

Button::Button(int pin)
    : _pin(pin)
{}

void Button::init(void)
{
    pinMode(_pin, INPUT_PULLUP);
}

void Button::refresh(void)
{

}

bool Button::was_pressed(void) const
{
#warning Dummy
    return false;
}
