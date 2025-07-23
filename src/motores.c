#include "motores.h"

void motor_setup() {
    // 1. Configura pinos de direção
    gpio_init(MOTOR_LEFT_FORWARD);
    gpio_init(MOTOR_LEFT_BACKWARD);
    gpio_init(MOTOR_RIGHT_FORWARD);
    gpio_init(MOTOR_RIGHT_BACKWARD);
    
    gpio_set_dir(MOTOR_LEFT_FORWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_LEFT_BACKWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_RIGHT_FORWARD, GPIO_OUT);
    gpio_set_dir(MOTOR_RIGHT_BACKWARD, GPIO_OUT);

    // 2. Configuração PWM correta
    gpio_set_function(MOTOR_LEFT_SIGNAL, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_RIGHT_SIGNAL, GPIO_FUNC_PWM);

    // Obtém os slices PWM
    uint slice_num_left = pwm_gpio_to_slice_num(MOTOR_LEFT_SIGNAL);
    uint slice_num_right = pwm_gpio_to_slice_num(MOTOR_RIGHT_SIGNAL);

    // Configuração PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, 10000);  // Wrap de 10000 para melhor resolução
    pwm_config_set_clkdiv(&config, 10.f); // Ajuste este valor conforme necessário
    
    pwm_init(slice_num_left, &config, true);
    pwm_init(slice_num_right, &config, true);
}

void motor_set_right_speed(uint16_t speed, bool forward) {
    speed = speed > 10000 ? 10000 : speed; // Limita ao wrap value
    pwm_set_gpio_level(MOTOR_RIGHT_SIGNAL, speed);
    gpio_put(MOTOR_RIGHT_FORWARD, forward);
    gpio_put(MOTOR_RIGHT_BACKWARD, !forward);
}

void motor_set_left_speed(uint16_t speed, bool forward) {
    speed = speed > 10000 ? 10000 : speed; // Limita ao wrap value
    pwm_set_gpio_level(MOTOR_LEFT_SIGNAL, speed);
    gpio_put(MOTOR_LEFT_FORWARD, forward);
    gpio_put(MOTOR_LEFT_BACKWARD, !forward);
}

void motor_set_both_speed(uint16_t speed, bool forward) {
    motor_set_right_speed(speed, forward);
    motor_set_left_speed(speed, forward);
}