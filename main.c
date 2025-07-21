#include <stdio.h>      
#include <string.h>     


#include <math.h>       
#include "acelero.h" //funções do MPU6050
#include "motores.h" // controle dos motores de passo



// --- Função Principal ---
int main() {
    stdio_init_all();           
    motor_setup();              
    // motor_enable();             

    mpu6050_setup_i2c();        
    mpu6050_reset();            

    int16_t accel[3], gyro[3], temp;

    while (1) {
        float control_signal = -0.30f * 255.0f; 

        bool forward = control_signal > 0;     
        float magnitude = fabsf(control_signal); 
        float limitado = fminf(magnitude, 255.0f); 
        uint16_t level = (uint16_t)limitado << 8; 

        motor_set_both_level(level, forward); 

        mpu6050_read_raw(accel, gyro, &temp); 

        printf("Accel X: %d, Y: %d, Z: %d\n", accel[0], accel[1], accel[2]);
        printf("Gyro X: %d, Y: %d, Z: %d\n", gyro[0], gyro[1], gyro[2]);
        
        sleep_ms(1000); 

        motor_set_both_level(0, true);
        
        sleep_ms(2000); 
    }

    return 0; 
}