#ifndef _CONFIG_H_
#define _CONFIG_H_

#define UI_REFRESH_TIME         50
#define CONTROLLER_REFRESH_TIME 100
//#define CONTROLLER_REFRESH_TIME 10

// Parameter übernommen vom Maiskolben (https://hannio.org)
//#define PID_Kp 3.0    // * (P)roportional Tuning Parameter
//#define PID_Ki 0.0  // * (I)ntegral Tuning Parameter
#define PID_Kp 0.003    // * (P)roportional Tuning Parameter
#define PID_Ki 0.00001  // * (I)ntegral Tuning Parameter
#define PID_Kd 0.0      // * (D)erivative Tuning Parameter -> Für thermische Vorgänge weitestgehend unnötig

// TODO: Anti-Windup

#define TEMPERATURE_STANDBY     20
#define TEMPERATURE_LOW         250
#define TEMPERATURE_MID         300
#define TEMPERATURE_HIGH        350

#define ADC_GAIN    0.7869
#define ADC_OFFSET  29.8872

#endif