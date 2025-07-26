#include <stdio.h>      
#include <string.h>     

     
#include "acelero.h" //funções do MPU6050
#include "motores.h" // controle dos motores de passo



// --- Função Principal ---
int main() {
    stdio_init_all();           
    motor_setup();              
            

    mpu6050_setup_i2c();        
    mpu6050_reset();            

    // int16_t accel[3], gyro[3], temp; //movidas para controle na biblioteca
    bool dir_state = false;

    const float total_time = 10.0f; // 10 segundos para aceleração total
    const uint16_t max_speed = 10000; // Nosso wrap value
    const float step_time = 0.05f;    // 50ms entre atualizações

    while (1) {

        //processos do MPU
        // mpu6050_read_raw(accel, gyro, &temp); 

        calculate_angle();




        sleep_ms(1000); 


        // /*Processos dos motores */
        // printf("\nIniciando ciclo de aceleração...\n");
        
        // // Fase de aceleração
        // for (uint16_t speed = 0; speed <= max_speed; speed += 100) {
        //     motor_set_both_speed(speed, true);
        //     printf("Velocidade: %u/%u (%.1f%%)\r", speed, max_speed, (speed*100.0f)/max_speed);
        //     sleep_ms(step_time * 1000);
        // }

        // printf("\nAceleração completa. Mantendo por 2 segundos...\n");
        // sleep_ms(2000);

        // // Fase de desaceleração
        // for (uint16_t speed = max_speed; speed > 0; speed -= 100) {
        //     motor_set_both_speed(speed, true);
        //     printf("Velocidade: %u/%u (%.1f%%)\r", speed, max_speed, (speed*100.0f)/max_speed);
        //     sleep_ms(step_time * 1000);
        // }

        // motor_set_both_speed(0, true); // Para completamente
        // printf("\nCiclo completo. Pausa de 3 segundos...\n");
        // sleep_ms(3000);


    }

    return 0; 
}