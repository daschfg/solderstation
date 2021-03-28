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
#define TEMPERATURE_LOW         300
#define TEMPERATURE_MID         350
#define TEMPERATURE_HIGH        400

#define ADC_GAIN    0.7869
#define ADC_OFFSET  29.8872

#define MEAS_REPEAT_COUNT       1
#define MEAS_RUNNING_MEAN_COUNT 1
#define MEAS_MAX_VALID          600     // Höchster noch gültiger Messwert
#define MEAS_MAX_JUMP           150     // Größter erlaubter Sprung zwischen zwei Messwerten

#define PWM_MAX_OUTPUT          100     // Maximal zulässiger PWM-Wert
#define PWM_COOLDOWN_PERIOD     3       // Wartezeit nach Abschalten PWM, bevor ADC-Messung beginnt

#endif
