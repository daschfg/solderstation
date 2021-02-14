#ifndef _HEATER_H_
#define _HEATER_H_

#include <stdint.h>
#include "PID_debug.h"

enum tempsetpoint_t {
    SETPOINT_LOW,
    SETPOINT_MID,
    SETPOINT_HIGH
};

class Heater {
public:
    Heater(int adc_pin, int pwm_pin);
    void init(void);

    void increase_temperature(void);
    void decrease_temperature(void);
    void toggle_standby(void);

    bool is_in_standby(void) const;
    tempsetpoint_t get_setpoint(void) const;

    void refresh(void);

private:
    bool _standby;
    tempsetpoint_t _setpoint;

    int _adc_pin;
    int _pwm_pin;
    PID _pidcontroller;

    double _pid_input;
    double _pid_output;
    double _pid_setpoint;

    double get_setpoint_temperature(void) const;
    double read_current_temperature(void);
    double measurement_to_temperature(uint16_t measurement) const;
    
    void set_pwm(uint16_t value);
};

#endif
