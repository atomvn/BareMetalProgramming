#pragma once
#include <core/i2c.h>

/* I2C address */
#define MPU6050_ADDR       0x68

/* Registers */
#define MPU6050_WHO_AM_I      0x75
#define MPU6050_PWR_MGMT_1    0x6B
#define MPU6050_SMPLRT_DIV    0x19
#define MPU6050_GYRO_CFG      0x1B
#define MPU6050_ACCEL_CFG     0x1C
#define MPU6050_ACCEL_XH      0x3B

typedef struct {
    int16_t ax_raw;
    int16_t ay_raw;
    int16_t az_raw;
    int16_t gx_raw;
    int16_t gy_raw;
    int16_t gz_raw;
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
} mpu6050_raw_t;

void mpu6050_init(void);
uint8_t mpu6050_who_am_i(void);
bool is_mpu6050(void);
void mpu6050_write(uint8_t reg, uint8_t data);
uint8_t mpu6050_read(uint8_t reg);
void mpu6050_read_raw(mpu6050_raw_t *data);

