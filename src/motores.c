#include "motores.h"




// --- Funções do Driver do Motor MX1508 ---
void motor_setup() {
    // gpio_init(MOTOR_STDBY);
    gpio_init(MOTOR_LEFT_FORWARD);
    gpio_init(MOTOR_LEFT_BACKWARD);
    gpio_init(MOTOR_RIGHT_FORWARD);
    gpio_init(MOTOR_RIGHT_BACKWARD);

    // gpio_set_dir(MOTOR_STDBY, true);
    gpio_set_dir(MOTOR_LEFT_FORWARD, true);
    gpio_set_dir(MOTOR_LEFT_BACKWARD, true);
    gpio_set_dir(MOTOR_RIGHT_FORWARD, true);
    gpio_set_dir(MOTOR_RIGHT_BACKWARD, true);

    gpio_set_function(MOTOR_LEFT_SIGNAL, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_RIGHT_SIGNAL, GPIO_FUNC_PWM);

    uint motor_left_pwm_slice = pwm_gpio_to_slice_num(MOTOR_LEFT_SIGNAL);
    uint motor_right_pwm_slice = pwm_gpio_to_slice_num(MOTOR_RIGHT_SIGNAL);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f); 
    pwm_init(motor_left_pwm_slice, &config, true);
    pwm_init(motor_right_pwm_slice, &config, true);
}

void motor_set_right_level(uint16_t level, bool forward) {
    pwm_set_gpio_level(MOTOR_RIGHT_SIGNAL, level);
    gpio_put(MOTOR_RIGHT_FORWARD, forward);
    gpio_put(MOTOR_RIGHT_BACKWARD, !forward);
}

void motor_set_left_level(uint16_t level, bool forward) {
    pwm_set_gpio_level(MOTOR_LEFT_SIGNAL, level);
    gpio_put(MOTOR_LEFT_FORWARD, forward);
    gpio_put(MOTOR_LEFT_BACKWARD, !forward);
}

void motor_set_both_level(uint16_t level, bool forward) {
    motor_set_right_level(level, forward);
    motor_set_left_level(level, forward);
}

// #define motor_disable() gpio_put(MOTOR_STDBY, false)
// #define motor_enable() gpio_put(MOTOR_STDBY, true)