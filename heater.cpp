#include <Arduino.h>
#include "heater.h"
#include "config.h"

Heater::Heater(int adc_pin, int pwm_pin)
    : _adc_pin(adc_pin), 
      _pwm_pin(pwm_pin),
      _pidcontroller(&_pid_input, &_pid_output, &_pid_setpoint, PID_Kp, PID_Ki, PID_Kd, DIRECT)
{ }

void Heater::init(void)
{
    _pidcontroller.Reconfigure(&_pid_input, &_pid_output, &_pid_setpoint);
    _pidcontroller.SetMode(AUTOMATIC);
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
    uint16_t measurement = analogRead(_adc_pin);
    // TODO Laufenden Mittelwert bilden
    return measurement_to_temperature(measurement);
}

double Heater::measurement_to_temperature(uint16_t measurement) const
{
    return (double)measurement * ADC_GAIN + ADC_OFFSET;
}

void Heater::set_pwm(uint16_t value)
{
    analogWrite(_pwm_pin, value);
}

void Heater::refresh(void)
{
    set_pwm(0);
    double temperature = read_current_temperature();

    _pid_setpoint = get_setpoint_temperature();
    _pid_input = temperature;

    if (!is_in_standby())
    {
        bool result = _pidcontroller.Compute();

        /*Serial.print("AddrOut: ");
        Serial.print((uint32_t)&_pid_output);*/
        uint16_t pwmvalue = min(255, (uint16_t)(_pid_output * 255.0));
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
