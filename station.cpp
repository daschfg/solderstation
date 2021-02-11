#include <Arduino.h>
#include "station.h"
#include "helpers.h"

Station::Station(
            TemperatureView& tempview,
            Heater heater,
            Button& button_up,
            Button& button_down,
            Button& button_stdby)
    : _tempview(tempview),
      _heater(heater),
      _button_up(button_up),
      _button_down(button_down),
      _button_stdby(button_stdby),
      _last_controller_update(0),
      _last_ui_update(0)
{ }

void Station::init(void)
{
    _button_up.init();
    _button_down.init();
    _button_stdby.init();
    _tempview.init();
}

void Station::run(void)
{
    refresh_inputs();

    if (is_timeout_reached(_last_controller_update, CONTROLLER_REFRESH_TIME))
    {
        update_controller();
        _last_controller_update = millis();
    }

    if (is_timeout_reached(_last_ui_update, UI_REFRESH_TIME))
    {
        update_userinterface();
        _last_ui_update = millis();
    }

}

void Station::refresh_inputs(void)
{
    // Alle aktuellen Buttonzustände einlesen
    _button_up.refresh();
    _button_down.refresh();
    _button_stdby.refresh();
}

void Station::update_userinterface(void)
{
    // Bei Bedarf: Aktualisierung Sollwert
    if (_button_up.was_pressed())
    {
        _heater.increase_temperature();
        _button_up.reset_state();
    }

    if (_button_down.was_pressed())
    {
        _heater.decrease_temperature();
        _button_down.reset_state();
    }

    if (_button_stdby.was_pressed())
    {
        _heater.toggle_standby();
        _button_stdby.reset_state();
    }

    // LED-Zustand setzen. Bei Bedarf: Blinktimer starten
    _tempview.refresh();

    /*
    if (station.is_in_standby())
    {
        tempview->blink_all(500);
    }
    else if (station.is_low_temperature())
    {
        tempview->set_led_low();
    }*/
}

void Station::update_controller(void)
{
    // TODO ...
    // Aktuellen ADC-Wert einlesen
    // Umrechnen in Temperaturwert
    // Abschaltung bei ungültigen Messwerten
    // Berechnung PID-Regler
    // Grenzwertlimitierung
    // PWM-Einstellung
}
