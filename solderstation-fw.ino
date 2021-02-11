/*
         _    _            _        _   _          
 ___ ___| |__| |___ _ _ __| |_ __ _| |_(_)___ _ _  
(_-</ _ \ / _` / -_) '_(_-<  _/ _` |  _| / _ \ '  \
/__/\___/_\__,_\___|_| /__/\__\__,_|\__|_\___/_||_|
                                                   
*/

#include "PID_v2.h"
#include "button.h"
#include "led.h"
#include "station.h"

#define BAUDRATE    115200

Button button_up(6);
Button button_down(7);
Button button_stdby(8);

Led led_low(2);
Led led_mid(4);
Led led_high(5);

int pwm_pin = 3;
int adc_pin = A0;

TemperatureView tempview(led_low, led_mid, led_high);
Heater heater;
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
