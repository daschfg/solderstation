#ifndef _STATION_H_
#define _STATION_H_

#include <stdint.h>
#include "button.h"
#include "heater.h"
#include "led.h"

#define UI_REFRESH_TIME         50
#define CONTROLLER_REFRESH_TIME 10

class Station {
public:
    Station(
            TemperatureView& tempview,
            Heater heater,
            Button& button_up,
            Button& button_down,
            Button& button_stdby);

    void init(void);
    void run(void);

private:
    TemperatureView _tempview;
    Heater _heater;

    Button _button_up;
    Button _button_down;
    Button _button_stdby;

    uint32_t _last_controller_update;
    uint32_t _last_ui_update;

    void refresh_inputs(void);
    void update_controller(void);
    void update_userinterface(void);
};

#endif
