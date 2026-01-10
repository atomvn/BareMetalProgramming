#include <mpu_6050.h>
#include <core/uart.h>
#include <core/systick.h>

// Write data to mpu6050
void mpu6050_write(uint8_t reg, uint8_t data)
{
    i2c_start();
    // uart1_send_string("Start successfully\n");
    i2c_send_address(MPU6050_ADDR, 0);
    // uart1_send_string("MPU address sent\n");
    i2c_write_byte(reg);
    // uart1_send_string("Write reg sucessfully\n");
    i2c_write_byte(data);
    // uart1_send_string("Write byte sucessfully\n");
    i2c_stop();
    // uart1_send_string("Stop sucessfully\n");
}

// Read data from mpu6050
uint8_t mpu6050_read(uint8_t reg)
{
    uint8_t data;

    i2c_start();
    i2c_send_address(MPU6050_ADDR, 0);
    i2c_write_byte(reg);

    i2c_start();
    i2c_send_address(MPU6050_ADDR, 1);

    I2C1_CR1 &= ~(1 << 10);   // ACK = 0
    data = i2c_read_byte();
    i2c_stop();
    I2C1_CR1 |= (1 << 10);    // ACK = 1

    return data;
}

// Init mpu6050
void mpu6050_init(void)
{
    if (is_mpu6050()) {
            // /* Wake up MPU6050 */
        mpu6050_write(MPU6050_PWR_MGMT_1, 0x00);

        /* Sample rate = Gyro rate / (1 + SMPLRT_DIV) */
        mpu6050_write(MPU6050_SMPLRT_DIV, 0x07); // ~1kHz

        // /* DLPF = 42Hz */
        // mpu6050_write(MPU6050_CONFIG, 0x03);

        /* Gyro ±250 deg/s */
        mpu6050_write(MPU6050_GYRO_CFG, 0x00);

        /* Accel ±2g */
        mpu6050_write(MPU6050_ACCEL_CFG, 0x00);
        delay_ms(100);
    }
}

// Read who am i reg
uint8_t mpu6050_who_am_i(void)
{
    return mpu6050_read(MPU6050_WHO_AM_I);
}

// Check if is mpu6050
bool is_mpu6050(void) {
    if (mpu6050_who_am_i() == MPU6050_ADDR) {
        uart1_send_string("MPU6050 addr checked \n");
        return true;
    }
    uart1_send_string("MPU6050 addr check failed \n");
    return false;
}

// Read data from mpu6050
void mpu6050_read_raw(mpu6050_raw_t *d)
{
    // Buffer to store mpu data
    uint8_t buf[14];

    // Start I2C
    i2c_start();
    // Send slave addr and choose write mode
    i2c_send_address(MPU6050_ADDR, 0);
    // Send reg addr
    i2c_write_byte(MPU6050_ACCEL_XH);
    // Restart, keep connect with current bus
    i2c_start();
    // Change to read mode
    i2c_send_address(MPU6050_ADDR, 1);

    // Allow hardware to automatically send ACK after each byte received
    I2C1_CR1 |= (1 << 10); // ACK = 1

    // Receive all bytes except for last byte
    for (int i = 0; i < 13; i++) {
        while (!(I2C1_SR1 & (1 << 6))); // Check if receive reg not empty
        buf[i] = I2C1_DR;
    }

    // Stop I2C
    i2c_stop();
    // Turn off ACK
    I2C1_CR1 &= ~(1 << 10); // ACK = 0
    // Check RXNE
    while (!(I2C1_SR1 & (1 << 6)));
    // Get last byte
    buf[13] = I2C1_DR;

    // Turn on ACK for the next read
    I2C1_CR1 |= (1 << 10); // ACK = 1

    // Get raw value
    d->ax_raw = (int16_t)((buf[0] << 8) | buf[1]);
    d->ay_raw = (int16_t)((buf[2] << 8) | buf[3]);
    d->az_raw = (int16_t)((buf[4] << 8) | buf[5]);
    d->gx_raw = (int16_t)((buf[8] << 8) | buf[9]);
    d->gy_raw = (int16_t)((buf[10] << 8) | buf[11]);
    d->gz_raw = (int16_t)((buf[12] << 8) | buf[13]);

    // Conver to float value
    d->ax = d->ax_raw/16384.0;
    d->ay = d->ay_raw/16384.0;
    d->az = d->az_raw/16384.0;
    d->gx = d->gx_raw/131.0;
    d->gy = d->gy_raw/131.0;
    d->gz = d->gz_raw/131.0;
}
