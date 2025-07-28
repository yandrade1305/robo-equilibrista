#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "motores.h"
#include "acelero.h" //funções do MPU6050

// Parâmetros do efeito breathing
#define BREATHING_PERIOD_MS 10000  // 4 segundos para um ciclo completo
#define BREATHING_STEP_MS   20    // Atualização a cada 20ms
#define MAX_PWM_LEVEL       255   // Nível máximo de PWM

int main() {
    stdio_init_all();
    motor_setup();

    mpu6050_setup_i2c();        
    mpu6050_reset();      

    float breathing_phase = 0.0f;
    float breathing_increment = (2 * M_PI * BREATHING_STEP_MS) / BREATHING_PERIOD_MS;

    //processos do MPU
    // mpu6050_read_raw(accel, gyro, &temp); 

    calculate_angle();
    sleep_ms(1000); 

    printf("Iniciando efeito breathing nos motores...\n");

    while (1) {
        // Atualiza a fase do breathing
        breathing_phase += breathing_increment;
        if (breathing_phase > 2 * M_PI) {
            breathing_phase -= 2 * M_PI;
        }

        // Calcula o nível de PWM usando uma função senoidal
        float duty_cycle = (sinf(breathing_phase) + 1.0f) / 2.0f;  // Varia entre 0 e 1
        uint8_t pwm_level = (uint8_t)(duty_cycle * MAX_PWM_LEVEL);

        // Aplica aos motores (ambos na mesma direção)
        motor_set_both_level(255, true);

        // Debug opcional
        printf("PWM Level: %d\n", pwm_level);

        sleep_ms(BREATHING_STEP_MS);
    }

    return 0;
}