#ifndef _HEATER_H_
#define _HEATER_H_

enum tempsetpoint_t {
    SETPOINT_LOW,
    SETPOINT_MID,
    SETPOINT_HIGH
};

class Heater {
public:
    Heater(void);

    void increase_temperature(void);
    void decrease_temperature(void);
    void toggle_standby(void);

    bool is_in_standby(void) const;
    tempsetpoint_t get_setpoint(void) const;

private:
    bool _standby;
    tempsetpoint_t _setpoint;
};

#endif
