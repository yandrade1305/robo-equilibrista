#ifndef ACEL_MPU_LIB
#define ACEL_MPU_LIB

#include "hardware/i2c.h" 
#include "pico/stdlib.h" 



// --- Funções do MPU6050 ---
void mpu6050_setup_i2c();
void mpu6050_reset();
uint8_t mpu6050_get_accel_range();
void mpu6050_set_accel_range(uint8_t range);
void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp);



#endif