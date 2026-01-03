#include <mpu_6050.h>
#include <core/i2c.h>

uint8_t mpu6050_who_am_i(void) {
    uint8_t id;
    i2c_read(MPU6050_ADDR, MPU6050_WHO_AM_I, &id, 1);
    return id;
}

void mpu6050_init(void) {
    // Wake up MPU6050
    i2c_write(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);
    // Set gyro full scale ±250 dps
    i2c_write(MPU6050_ADDR, 0x1B, 0x00);

    // Set accel full scale ±2g
    i2c_write(MPU6050_ADDR, 0x1C, 0x00);
}

bool is_mpu6050(void){
    uint8_t whoami = mpu6050_who_am_i();

    if (whoami == MPU6050_ADDR){
        return true;
    }
    return false;
}

void mpu6050_read_accel(int16_t *ax, int16_t *ay, int16_t *az) {
    uint8_t buf[6];
    i2c_read(MPU6050_ADDR, MPU6050_ACCEL_XOUT, buf, 6);

    *ax = (buf[0] << 8 | buf[1]);
    *ay = (buf[2] << 8 | buf[3]);
    *az = (buf[4] << 8 | buf[5]);
}

