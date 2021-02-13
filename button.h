#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button {
public:
    Button(int pin);

    void init(void);
    void refresh(void);
    bool was_pressed(void) const;
    void reset_state(void);

private:
    int _pin;
    int _last_state;
    uint32_t _debounce_start;
    bool _pressed;
};

#endif
