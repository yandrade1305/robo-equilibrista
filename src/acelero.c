#include "acelero.h"


int16_t accel[3], gyro[3], temp;


// --- Funções do MPU6050 ---
void mpu6050_setup_i2c() {
    i2c_init(I2C_PORT, 400 * 1000); 
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void mpu6050_reset() {
    uint8_t buf[] = {0x6B, 0x80}; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, buf, 2, false);
    sleep_ms(100);
    buf[1] = 0x00; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, buf, 2, false);
    sleep_ms(10);
}

uint8_t mpu6050_get_accel_range() {
    uint8_t reg = 0x1C; 
    uint8_t val;
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true); 
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, &val, 1, false);
    return (val >> 3) & 0x03; 
}

void mpu6050_set_accel_range(uint8_t range) {
    uint8_t buf[2];
    buf[0] = 0x1C; 
    buf[1] = range << 3; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, buf, 2, false);
}

void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
    uint8_t buffer[6];
    uint8_t reg;

    reg = 0x3B; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true); 
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buffer, 6, false);
    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[2 * i] << 8) | buffer[2 * i + 1];
    }

    reg = 0x43; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true); 
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buffer, 6, false);
    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[2 * i] << 8) | buffer[2 * i + 1];
    }

    reg = 0x41; 
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true); 
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buffer, 2, false);
    *temp = (buffer[0] << 8) | buffer[1];
}

void calculate_angle(){
    mpu6050_read_raw(accel, gyro, &temp); 
    printf("Accel X: %d, Y: %d, Z: %d\n", accel[0], accel[1], accel[2]);
    printf("Gyro X: %d, Y: %d, Z: %d\n", gyro[0], gyro[1], gyro[2]);


 // 1. Determina a escala atual do acelerômetro
    uint8_t accel_range = mpu6050_get_accel_range();
    float scale_factor;
    
    switch(accel_range) {
        case 0: scale_factor = 16384.0; break; // ±2g
        case 1: scale_factor = 8192.0;  break; // ±4g
        case 2: scale_factor = 4096.0;  break; // ±8g
        case 3: scale_factor = 2048.0;  break; // ±16g
        default: scale_factor = 16384.0; break;
    }

    // 2. Converter valores brutos para aceleração em g's
    float accel_x_g = accel[0] / scale_factor;
    float accel_y_g = accel[1] / scale_factor;
    float accel_z_g = accel[2] / scale_factor;

    // 3. Calcular ângulo usando atan2 (considerando X e Z)
    float angle_rad = atan2(accel_y_g, accel_z_g);
    
    // 4. Se precisar em graus:
    float angle_deg = angle_rad * (180.0 / M_PI);
    
    // Debug (opcional)
    printf("Accel X: %.2fg, Z: %.2fg | Angle: %.2f°\n", 
           accel_x_g, accel_z_g, angle_deg);

    // return angle_rad; // Retorne radianos para controle PID

}
