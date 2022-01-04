#include <Arduino.h>
#include "heater.h"
#include "config.h"
#include "PWM.h"
#include "helpers.h"

Heater::Heater(int adc_pin, int pwm_pin)
    : _adc_pin(adc_pin), 
      _pwm_pin(pwm_pin),
      _pidcontroller(&_pid_input, &_pid_output, &_pid_setpoint, PID_Kp, PID_Ki, PID_Kd, DIRECT)
{ }

void Heater::init(void)
{
    _pidcontroller.Reconfigure(&_pid_input, &_pid_output, &_pid_setpoint);
    _pidcontroller.SetMode(AUTOMATIC);
    set_error(ERR_NONE);
    reset_change();
}

void Heater::increase_temperature(void)
{
    switch (_setpoint)
    {
    case SETPOINT_LOW:
        _setpoint = SETPOINT_MID;
        break;
    case SETPOINT_MID:
        _setpoint = SETPOINT_HIGH;
        break;
    case SETPOINT_HIGH:
        break;
    }
}

void Heater::decrease_temperature(void)
{
    switch (_setpoint)
    {
    case SETPOINT_LOW:
        break;
    case SETPOINT_MID:
        _setpoint = SETPOINT_LOW;
        break;
    case SETPOINT_HIGH:
        _setpoint = SETPOINT_MID;
        break;
    }
}

void Heater::toggle_standby(void)
{
    _standby = !_standby;
    _pidcontroller.Reset();
}

bool Heater::is_in_standby(void) const
{
    return _standby;
}

void Heater::set_error(heatererror_t error)
{
    if (_error != error)
        _status_changed = true;
    _error = error;
}

bool Heater::is_in_error(void) const
{
    return _error != ERR_NONE;
}

const char* Heater::error_to_text(void) const
{
    switch (_error)
    {
    case ERR_INVALID_MEASUREMENT:
        return "Ungueltiger Messwert";
    case ERR_NONE:
        return "Kein Fehler";
    default:
        return "<Beschreibung fehlt>";
    }
}

bool Heater::has_status_changed(void) const
{
    return _status_changed;
}

void Heater::reset_change(void)
{
    _status_changed = false;
}

tempsetpoint_t Heater::get_setpoint(void) const
{
    return _setpoint;
}

double Heater::get_setpoint_temperature(void) const
{
    switch (_setpoint)
    {
    case SETPOINT_LOW:
        return TEMPERATURE_LOW;
    case SETPOINT_MID:
        return TEMPERATURE_MID;
    case SETPOINT_HIGH:
        return TEMPERATURE_HIGH;
    default:
        return 0;
    }
}

double Heater::read_current_temperature(void)
{
    // Zur Glättung der Temperaturmessung:
    // - Mehrfach hintereinander lesen und Mittelwert berechnen
    // - Laufenden Mittelwert über mehrere Messungen bilden
    uint16_t measurement = 0;
    for (uint8_t i = 0; i < MEAS_REPEAT_COUNT; i++)
    {
        uint16_t read = analogRead(_adc_pin);
        if (is_valid_measurement(read))
            measurement += analogRead(_adc_pin);
        else
            set_error(ERR_INVALID_MEASUREMENT);
    }
    measurement /= MEAS_REPEAT_COUNT;
    _prev_measurement = measurement;


    // TODO Laufenden Mittelwert bilden
    return measurement_to_temperature(measurement);
}

bool Heater::is_valid_measurement(uint16_t measurement) const
{
    uint16_t diff = 
        measurement < _prev_measurement 
        ? _prev_measurement - measurement
        : measurement - _prev_measurement;
    Serial.print(diff);
    Serial.print("|");
    Serial.print(measurement);
    Serial.print("|");
    Serial.print(_prev_measurement);
    Serial.print("| ");
    return measurement < MEAS_MAX_VALID && diff < MEAS_MAX_JUMP;
}

double Heater::measurement_to_temperature(uint16_t measurement) const
{
    return (double)measurement * ADC_GAIN + ADC_OFFSET;
}

void Heater::set_pwm(uint16_t value)
{
    pwmWrite(_pwm_pin, value);
}

void Heater::refresh(void)
{
    set_pwm(0); // PWM abschalten, um Messen zu können
    if (PWM_COOLDOWN_PERIOD > 0)
        delay(PWM_COOLDOWN_PERIOD);
    double temperature = read_current_temperature();

    _pid_setpoint = get_setpoint_temperature();
    _pid_input = temperature;

    if (is_in_error())
    {

        Serial.print(temperature);
        Serial.print(" - Error ");
        Serial.println(error_to_text());
        set_pwm(0);
    }
    else if (!is_in_standby())
    {
        bool result = _pidcontroller.Compute();

        if (is_in_error())
            return;

        uint16_t pwmvalue = MIN(PWM_MAX_OUTPUT, (uint16_t)(_pid_output * 255.0));
        set_pwm(pwmvalue);

        if (!result)
            Serial.print(" !Compute error! ");
        Serial.print(temperature);
        Serial.print(" - Setpoint: ");
        Serial.print(_pid_setpoint);
        Serial.print(" - PID out: ");
        Serial.print(_pid_output);
        Serial.print(" - PWM: ");
        Serial.println(pwmvalue);
    }
    else
    {
        Serial.println(temperature);
        set_pwm(0);
    }
}
