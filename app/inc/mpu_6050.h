#pragma once
#include <stdbool.h>
#include <stdint.h>

#define MPU6050_ADDR        (0x68)
#define MPU6050_WHO_AM_I    (0x75)
#define MPU6050_PWR_MGMT_1  (0x6B)
#define MPU6050_ACCEL_XOUT  (0x3B)
#define MPU6050_G           (0x43)

void mpu6050_init(void);
uint8_t mpu6050_who_am_i(void);
bool is_mpu6050(void);
void mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az);

