#ifndef _HEATER_H_
#define _HEATER_H_

class Heater {
public:
    Heater(void);

    void increase_temperature(void);
    void decrease_temperature(void);
    void toggle_standby(void);

    bool is_in_standby(void) const;
};

#endif
