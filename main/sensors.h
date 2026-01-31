#ifndef SENSORS_H
#define SENSORS_H
#include "driver/gpio.h"

#define IR_A 4
#define IR_B 5

static inline void init_sensors() {
    gpio_reset_pin(IR_A);
    gpio_set_direction(IR_A, GPIO_MODE_INPUT);
    gpio_set_pull_mode(IR_A, GPIO_PULLUP_ONLY);

    gpio_reset_pin(IR_B);
    gpio_set_direction(IR_B, GPIO_MODE_INPUT);
    gpio_set_pull_mode(IR_B, GPIO_PULLUP_ONLY);
}
#endif
