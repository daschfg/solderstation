#ifndef _LED_H_
#define _LED_H_


class Led {
public:
    Led(int pin);
    void init(void);

private:
    int _pin;
};

class TemperatureView {
public:
    TemperatureView(Led& led_low, Led& led_mid, Led& led_high);
    void init(void);
    void refresh(void);

private:
    Led _led_low;
    Led _led_mid;
    Led _led_high;
};

#endif
