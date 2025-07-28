#include "motores.h"

void motor_setup() {
    // Configuração do motor esquerdo
    gpio_set_dir(MOTOR_LEFT_FORWARD, GPIO_OUT);
    gpio_set_function(MOTOR_LEFT_FORWARD, GPIO_FUNC_PWM);
    uint slice_left_fwd = pwm_gpio_to_slice_num(MOTOR_LEFT_FORWARD);
    pwm_set_clkdiv_int_frac(slice_left_fwd, 19, 9);
    pwm_set_wrap(slice_left_fwd, PERIODO);
    pwm_set_gpio_level(MOTOR_LEFT_FORWARD, 0);
    pwm_set_enabled(slice_left_fwd, true);

    gpio_set_dir(MOTOR_LEFT_BACKWARD, GPIO_OUT);
    gpio_set_function(MOTOR_LEFT_BACKWARD, GPIO_FUNC_PWM);
    uint slice_left_bwd = pwm_gpio_to_slice_num(MOTOR_LEFT_BACKWARD);
    pwm_set_clkdiv_int_frac(slice_left_bwd, 19, 9);
    pwm_set_wrap(slice_left_bwd, PERIODO);
    pwm_set_gpio_level(MOTOR_LEFT_BACKWARD, 0);
    pwm_set_enabled(slice_left_bwd, true);

    // Configuração do motor direito
    gpio_set_dir(MOTOR_RIGHT_FORWARD, GPIO_OUT);
    gpio_set_function(MOTOR_RIGHT_FORWARD, GPIO_FUNC_PWM);
    uint slice_right_fwd = pwm_gpio_to_slice_num(MOTOR_RIGHT_FORWARD);
    pwm_set_clkdiv_int_frac(slice_right_fwd, 19, 9);
    pwm_set_wrap(slice_right_fwd, PERIODO);
    pwm_set_gpio_level(MOTOR_RIGHT_FORWARD, 0);
    pwm_set_enabled(slice_right_fwd, true);

    gpio_set_dir(MOTOR_RIGHT_BACKWARD, GPIO_OUT);
    gpio_set_function(MOTOR_RIGHT_BACKWARD, GPIO_FUNC_PWM);
    uint slice_right_bwd = pwm_gpio_to_slice_num(MOTOR_RIGHT_BACKWARD);
    pwm_set_clkdiv_int_frac(slice_right_bwd, 19, 9);
    pwm_set_wrap(slice_right_bwd, PERIODO);
    pwm_set_gpio_level(MOTOR_RIGHT_BACKWARD, 0);
    pwm_set_enabled(slice_right_bwd, true);
}

void motor_set_right_level(uint8_t level, bool forward) {
    if(forward) {
        pwm_set_gpio_level(MOTOR_RIGHT_FORWARD, level);
        pwm_set_gpio_level(MOTOR_RIGHT_BACKWARD, 0);
    } else {
        pwm_set_gpio_level(MOTOR_RIGHT_FORWARD, 0);
        pwm_set_gpio_level(MOTOR_RIGHT_BACKWARD, level);
    }
}

void motor_set_left_level(uint8_t level, bool forward) {
    if(forward) {
        pwm_set_gpio_level(MOTOR_LEFT_FORWARD, level);
        pwm_set_gpio_level(MOTOR_LEFT_BACKWARD, 0);
    } else {
        pwm_set_gpio_level(MOTOR_LEFT_FORWARD, 0);
        pwm_set_gpio_level(MOTOR_LEFT_BACKWARD, level);
    }
}