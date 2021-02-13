#ifndef _LED_H_
#define _LED_H_


class Led {
public:
    Led(int pin);
    void init(void);
    void refresh(void);

    void activate(void);
    void deactivate(void);
    bool is_activated(void) const;

    bool is_on(void) const;
    void blink(bool should_activate, uint32_t time);

private:
    int _pin;
    int _state;
    bool _is_activated;

    bool _blinking;
    uint32_t _blinktime;
    uint32_t _last_toggle;

    void set(bool active);
};

class TemperatureView {
public:
    TemperatureView(Led& led_low, Led& led_mid, Led& led_high);
    void init(void);
    void refresh(void);

    void set_blink(bool state, uint32_t time);
    void set_led_low(void);
    void set_led_mid(void);
    void set_led_high(void);

private:
    Led _led_low;
    Led _led_mid;
    Led _led_high;
};

#endif
