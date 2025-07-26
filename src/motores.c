#include "motores.h"




// --- Funções do Driver do Motor MX1508 ---
void motor_setup() {
    // gpio_init(MOTOR_STDBY);
    // gpio_init(MOTOR_LEFT_FORWARD);
    // gpio_init(MOTOR_LEFT_BACKWARD);
    // gpio_init(MOTOR_RIGHT_FORWARD);
    // gpio_init(MOTOR_RIGHT_BACKWARD);

    // gpio_set_dir(MOTOR_STDBY, true);
    gpio_set_dir(MOTOR_LEFT_FORWARD, GPIO_OUT);
    gpio_set_function(MOTOR_LEFT_FORWARD, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(MOTOR_LEFT_FORWARD);
    pwm_set_clkdiv_int_frac4(slice,19,9);
    pwm_set_wrap(slice,PERIODO);
    pwm_set_gpio_level(MOTOR_LEFT_FORWARD,0);
    pwm_set_enabled(slice,true);




    gpio_set_dir(MOTOR_LEFT_BACKWARD, GPIO_OUT);
    gpio_set_function(MOTOR_LEFT_BACKWARD, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(MOTOR_LEFT_BACKWARD);
    pwm_set_clkdiv_int_frac4(slice,19,9);
    pwm_set_wrap(slice,PERIODO);
    pwm_set_gpio_level(MOTOR_LEFT_BACKWARD,0);
    pwm_set_enabled(slice,true);





    // gpio_set_dir(MOTOR_RIGHT_FORWARD, true);
    // gpio_set_function(MOTOR_RIGHT_FORWARD, GPIO_FUNC_PWM);
    // pwm_set_clkdiv_int_frac4(pwm_slice_right_foward,19,9);
    // pwm_set_wrap(pwm_slice_right_foward,PERIODO);
    // pwm_set_enabled(pwm_slice_right_foward,true);




    // gpio_set_dir(MOTOR_RIGHT_BACKWARD, true);
    // gpio_set_function(MOTOR_RIGHT_BACKWARD, GPIO_FUNC_PWM);


    // uint pwm_slice_right_foward = pwm_gpio_to_slice_num(MOTOR_RIGHT_FORWARD);
    // uint pwm_slice_right_back = pwm_gpio_to_slice_num(MOTOR_RIGHT_BACKWARD);

    // pwm_config config = pwm_get_default_config();
    // pwm_config_set_clkdiv(&config, 4.f); 

    // pwm_set_clkdiv_int_frac4(pwm_slice_right_back,19,9);


    // pwm_set_wrap(pwm_slice_right_back,PERIODO);

    // pwm_set_enabled(pwm_slice_right_back,true);

}

void motor_set_right_level(uint8_t level, bool forward) {

    if(forward){
        pwm_set_gpio_level(MOTOR_RIGHT_FORWARD, level);
        pwm_set_gpio_level(MOTOR_RIGHT_BACKWARD, 0);
    } else{
        pwm_set_gpio_level(MOTOR_RIGHT_FORWARD, 0);
        pwm_set_gpio_level(MOTOR_RIGHT_BACKWARD, level);
    }

    // pwm_set_gpio_level(MOTOR_RIGHT_SIGNAL, level);
    // gpio_put(MOTOR_RIGHT_FORWARD, forward);
    // gpio_put(MOTOR_RIGHT_BACKWARD, !forward);
}

void motor_set_left_level(uint8_t level, bool forward) {
    if(forward){
        pwm_set_gpio_level(MOTOR_LEFT_FORWARD, level);
        pwm_set_gpio_level(MOTOR_LEFT_BACKWARD, 0);
    } else{
        pwm_set_gpio_level(MOTOR_LEFT_FORWARD, 0);
        pwm_set_gpio_level(MOTOR_LEFT_BACKWARD, level);
    }
}

void motor_set_both_level(uint8_t level, bool forward) {
    motor_set_right_level(level, forward);
    motor_set_left_level(level, forward);
}

// #define motor_disable() gpio_put(MOTOR_STDBY, false)
// #define motor_enable() gpio_put(MOTOR_STDBY, true)