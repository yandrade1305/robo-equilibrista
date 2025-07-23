#include <stdio.h>
#include <string.h>
#include <math.h>
#include "acelero.h"
#include "motores.h"

int main() {
    stdio_init_all();
    motor_setup();

    const float total_time = 10.0f; // 10 segundos para aceleração total
    const uint16_t max_speed = 10000; // Nosso wrap value
    const float step_time = 0.05f;    // 50ms entre atualizações

    while (1) {
        printf("\nIniciando ciclo de aceleração...\n");
        
        // Fase de aceleração
        for (uint16_t speed = 0; speed <= max_speed; speed += 100) {
            motor_set_both_speed(speed, true);
            printf("Velocidade: %u/%u (%.1f%%)\r", speed, max_speed, (speed*100.0f)/max_speed);
            sleep_ms(step_time * 1000);
        }

        printf("\nAceleração completa. Mantendo por 2 segundos...\n");
        sleep_ms(2000);

        // Fase de desaceleração
        for (uint16_t speed = max_speed; speed > 0; speed -= 100) {
            motor_set_both_speed(speed, true);
            printf("Velocidade: %u/%u (%.1f%%)\r", speed, max_speed, (speed*100.0f)/max_speed);
            sleep_ms(step_time * 1000);
        }

        motor_set_both_speed(0, true); // Para completamente
        printf("\nCiclo completo. Pausa de 3 segundos...\n");
        sleep_ms(3000);
    }

    return 0;
}