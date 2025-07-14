#include <stdio.h>      
#include <string.h>     
#include "pico/stdlib.h" 
#include "pico/binary_info.h" 
#include "hardware/i2c.h"   
#include "hardware/pwm.h"   
#include <math.h>       

// --- Definições do Driver do Motor MX1508 ---
#define MOTOR_STDBY             20
#define MOTOR_LEFT_FORWARD      4  // IN1 para o motor esquerdo
#define MOTOR_LEFT_BACKWARD     5  // IN2 para o motor esquerdo (Ajustado)
#define MOTOR_LEFT_SIGNAL       8  // PWM para o motor esquerdo (Pino original do PWM)
#define MOTOR_RIGHT_FORWARD     16 // IN1 para o motor direito
#define MOTOR_RIGHT_BACKWARD    17 // IN2 para o motor direito
#define MOTOR_RIGHT_SIGNAL      18 // PWM para o motor direito (Pino ajustado para PWM)


// --- Funções do Driver do Motor MX1508 ---
void motor_setup() {
    gpio_init(MOTOR_STDBY);
    gpio_init(MOTOR_LEFT_FORWARD);
    gpio_init(MOTOR_LEFT_BACKWARD);
    gpio_init(MOTOR_RIGHT_FORWARD);
    gpio_init(MOTOR_RIGHT_BACKWARD);

    gpio_set_dir(MOTOR_STDBY, true);
    gpio_set_dir(MOTOR_LEFT_FORWARD, true);
    gpio_set_dir(MOTOR_LEFT_BACKWARD, true);
    gpio_set_dir(MOTOR_RIGHT_FORWARD, true);
    gpio_set_dir(MOTOR_RIGHT_BACKWARD, true);

    gpio_set_function(MOTOR_LEFT_SIGNAL, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_RIGHT_SIGNAL, GPIO_FUNC_PWM);

    uint motor_left_pwm_slice = pwm_gpio_to_slice_num(MOTOR_LEFT_SIGNAL);
    uint motor_right_pwm_slice = pwm_gpio_to_slice_num(MOTOR_RIGHT_SIGNAL);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f); 
    pwm_init(motor_left_pwm_slice, &config, true);
    pwm_init(motor_right_pwm_slice, &config, true);
}

void motor_set_right_level(uint16_t level, bool forward) {
    pwm_set_gpio_level(MOTOR_RIGHT_SIGNAL, level);
    gpio_put(MOTOR_RIGHT_FORWARD, forward);
    gpio_put(MOTOR_RIGHT_BACKWARD, !forward);
}

void motor_set_left_level(uint16_t level, bool forward) {
    pwm_set_gpio_level(MOTOR_LEFT_SIGNAL, level);
    gpio_put(MOTOR_LEFT_FORWARD, forward);
    gpio_put(MOTOR_LEFT_BACKWARD, !forward);
}

void motor_set_both_level(uint16_t level, bool forward) {
    motor_set_right_level(level, forward);
    motor_set_left_level(level, forward);
}

#define motor_disable() gpio_put(MOTOR_STDBY, false)
#define motor_enable() gpio_put(MOTOR_STDBY, true)


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


// --- Função Principal ---
int main() {
    stdio_init_all();           
    motor_setup();              
    motor_enable();             

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
        
        sleep_ms(1000); 

        motor_set_both_level(0, true);
        
        sleep_ms(2000); 
    }

    return 0; 
}