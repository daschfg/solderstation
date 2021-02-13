#include "heater.h"


Heater::Heater(void)
{}

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
}

bool Heater::is_in_standby(void) const
{
    return _standby;
}

tempsetpoint_t Heater::get_setpoint(void) const
{
    return _setpoint;
}
