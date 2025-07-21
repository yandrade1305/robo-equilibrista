#ifndef MOTORES_LIB
#define MOTORES_LIB

#include "pico/stdlib.h" 
#include "pico/binary_info.h" 
#include "hardware/pwm.h"   

// --- Definições do Driver do Motor MX1508 ---
// #define MOTOR_STDBY             20
#define MOTOR_LEFT_FORWARD      4  // IN1 para o motor esquerdo
#define MOTOR_LEFT_BACKWARD     20 // IN2 para o motor esquerdo (Ajustado)
#define MOTOR_LEFT_SIGNAL       8  // PWM para o motor esquerdo (Pino original do PWM)
#define MOTOR_RIGHT_FORWARD     16 // IN1 para o motor direito
#define MOTOR_RIGHT_BACKWARD    17 // IN2 para o motor direito
#define MOTOR_RIGHT_SIGNAL      18 // PWM para o motor direito (Pino ajustado para PWM)

// --- Funções do Driver do Motor MX1508 ---
void motor_setup();
void motor_set_right_level(uint16_t level, bool forward);
void motor_set_left_level(uint16_t level, bool forward);
void motor_set_both_level(uint16_t level, bool forward);



#endif