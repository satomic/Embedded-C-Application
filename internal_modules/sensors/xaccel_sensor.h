#ifndef XACCEL_SENSOR_H
#define XACCEL_SENSOR_H

#include <stdint.h>

typedef enum {
    XACCEL_RANGE_2G = 0,
    XACCEL_RANGE_4G = 1,
    XACCEL_RANGE_8G = 2,
    XACCEL_RANGE_16G = 3
} xaccel_range_t;

typedef enum {
    XACCEL_ODR_1HZ = 0,
    XACCEL_ODR_10HZ = 1,
    XACCEL_ODR_25HZ = 2,
    XACCEL_ODR_50HZ = 3,
    XACCEL_ODR_100HZ = 4,
    XACCEL_ODR_200HZ = 5,
    XACCEL_ODR_400HZ = 6
} xaccel_odr_t;

typedef enum {
    XACCEL_FILTER_NORMAL = 0,
    XACCEL_FILTER_LP_LIGHT = 1,
    XACCEL_FILTER_LP_MEDIUM = 2,
    XACCEL_FILTER_LP_STRONG = 3
} xaccel_filter_t;

typedef struct {
    float x_mg;
    float y_mg;
    float z_mg;
    uint32_t timestamp;
} xaccel_data_t;

typedef struct {
    uint32_t i2c_instance;
    uint8_t device_address;
    xaccel_range_t range;
    xaccel_odr_t output_data_rate;
    xaccel_filter_t filter_mode;
    uint8_t enable_fifo;
    uint16_t fifo_watermark;
} xaccel_config_t;

typedef void (*xaccel_data_ready_callback_t)(const xaccel_data_t* data);
typedef void (*xaccel_motion_callback_t)(uint8_t motion_detected);

int xaccel_init(const xaccel_config_t* config);
int xaccel_deinit(void);
int xaccel_read_data(xaccel_data_t* data);
int xaccel_read_raw_data(int16_t* x_raw, int16_t* y_raw, int16_t* z_raw);
int xaccel_calibrate(uint32_t sample_count);
int xaccel_set_offset(float x_offset, float y_offset, float z_offset);
int xaccel_get_offset(float* x_offset, float* y_offset, float* z_offset);
int xaccel_enable_motion_detection(float threshold_mg, uint8_t duration_ms);
int xaccel_disable_motion_detection(void);
int xaccel_set_data_ready_callback(xaccel_data_ready_callback_t callback);
int xaccel_set_motion_callback(xaccel_motion_callback_t callback);
int xaccel_read_fifo(xaccel_data_t* data_buffer, uint16_t buffer_size, uint16_t* samples_read);
int xaccel_get_temperature(float* temperature);
uint8_t xaccel_is_data_ready(void);

#endif // XACCEL_SENSOR_H