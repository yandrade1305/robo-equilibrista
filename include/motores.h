#ifndef MOTORES_LIB
#define MOTORES_LIB

#include "pico/stdlib.h" 
#include "pico/binary_info.h" 
#include "hardware/pwm.h"   

// --- Definições do Driver do Motor MX1508 ---
#define MOTOR_LEFT_FORWARD      19  // IN1 para o motor esquerdo
#define MOTOR_LEFT_BACKWARD     20  // IN2 para o motor esquerdo
#define MOTOR_RIGHT_FORWARD     16  // IN1 para o motor direito
#define MOTOR_RIGHT_BACKWARD    17  // IN2 para o motor direito

#define PERIODO 255

// --- Funções do Driver do Motor MX1508 ---
void motor_setup();
void motor_set_right_level(uint8_t level, bool forward);
void motor_set_left_level(uint8_t level, bool forward);

#endif