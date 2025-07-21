#include "acelero.h"

// --- Definições do MPU6050 ---
#define I2C_PORT i2c1
#define I2C_SDA 2
#define I2C_SCL 3
#define MPU6050_ADDR 0x68

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
