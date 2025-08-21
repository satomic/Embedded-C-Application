#ifndef XGYRO_SENSOR_H
#define XGYRO_SENSOR_H

#include <stdint.h>

typedef enum {
    XGYRO_RANGE_250DPS = 0,
    XGYRO_RANGE_500DPS = 1,
    XGYRO_RANGE_1000DPS = 2,
    XGYRO_RANGE_2000DPS = 3
} xgyro_range_t;

typedef enum {
    XGYRO_ODR_12_5HZ = 0,
    XGYRO_ODR_26HZ = 1,
    XGYRO_ODR_52HZ = 2,
    XGYRO_ODR_104HZ = 3,
    XGYRO_ODR_208HZ = 4,
    XGYRO_ODR_416HZ = 5,
    XGYRO_ODR_833HZ = 6,
    XGYRO_ODR_1666HZ = 7
} xgyro_odr_t;

typedef enum {
    XGYRO_BW_LOW = 0,
    XGYRO_BW_MEDIUM = 1,
    XGYRO_BW_HIGH = 2,
    XGYRO_BW_ULTRA_HIGH = 3
} xgyro_bandwidth_t;

typedef struct {
    float x_dps;
    float y_dps;
    float z_dps;
    uint32_t timestamp;
} xgyro_data_t;

typedef struct {
    uint32_t spi_instance;
    uint32_t cs_pin;
    xgyro_range_t range;
    xgyro_odr_t output_data_rate;
    xgyro_bandwidth_t bandwidth;
    uint8_t enable_high_pass_filter;
    float high_pass_cutoff_hz;
    uint8_t enable_fifo;
} xgyro_config_t;

typedef void (*xgyro_data_ready_callback_t)(const xgyro_data_t* data);
typedef void (*xgyro_fifo_watermark_callback_t)(void);

int xgyro_init(const xgyro_config_t* config);
int xgyro_deinit(void);
int xgyro_read_data(xgyro_data_t* data);
int xgyro_read_raw_data(int16_t* x_raw, int16_t* y_raw, int16_t* z_raw);
int xgyro_calibrate_bias(uint32_t sample_count);
int xgyro_set_bias(float x_bias, float y_bias, float z_bias);
int xgyro_get_bias(float* x_bias, float* y_bias, float* z_bias);
int xgyro_perform_self_test(uint8_t* test_result);
int xgyro_set_data_ready_callback(xgyro_data_ready_callback_t callback);
int xgyro_set_fifo_watermark_callback(xgyro_fifo_watermark_callback_t callback);
int xgyro_read_fifo(xgyro_data_t* data_buffer, uint16_t buffer_size, uint16_t* samples_read);
int xgyro_reset_fifo(void);
int xgyro_get_device_id(uint8_t* device_id);
uint8_t xgyro_is_data_ready(void);

#endif // XGYRO_SENSOR_H