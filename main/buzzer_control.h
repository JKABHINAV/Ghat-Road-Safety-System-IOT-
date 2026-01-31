#ifndef BUZZER_H
#define BUZZER_H
#include "driver/gpio.h"

#define BUZZER_A 19
#define BUZZER_B 22

static inline void init_buzzers() {
    gpio_reset_pin(BUZZER_A);
    gpio_set_direction(BUZZER_A, GPIO_MODE_OUTPUT);
    gpio_reset_pin(BUZZER_B);
    gpio_set_direction(BUZZER_B, GPIO_MODE_OUTPUT);
    
    gpio_set_level(BUZZER_A, 0);
    gpio_set_level(BUZZER_B, 0);
}
#endif
