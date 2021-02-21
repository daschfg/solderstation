/*
         _    _            _        _   _          
 ___ ___| |__| |___ _ _ __| |_ __ _| |_(_)___ _ _  
(_-</ _ \ / _` / -_) '_(_-<  _/ _` |  _| / _ \ '  \
/__/\___/_\__,_\___|_| /__/\__\__,_|\__|_\___/_||_|
                                                   
*/

#include "button.h"
#include "led.h"
#include "station.h"
#include "PID_debug.h"

#define BAUDRATE    115200

Button button_up(8);
Button button_down(9);
Button button_stdby(10);

Led led_low(2);
Led led_mid(3);
Led led_high(4);

int pwm_pin = 6;
int adc_pin = A0;

TemperatureView tempview(led_low, led_mid, led_high);
Heater heater(adc_pin, pwm_pin);
Station station(tempview, heater, button_up, button_down, button_stdby);

void setup(void)
{
    Serial.begin(BAUDRATE);
    station.init();
}

void loop(void)
{
    station.run();
    delay(1);
}
