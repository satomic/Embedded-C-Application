#ifndef XTEMP_SENSOR_H
#define XTEMP_SENSOR_H

#include <stdint.h>

typedef enum {
    XTEMP_RESOLUTION_9BIT = 0,
    XTEMP_RESOLUTION_10BIT = 1,
    XTEMP_RESOLUTION_11BIT = 2,
    XTEMP_RESOLUTION_12BIT = 3
} xtemp_resolution_t;

typedef enum {
    XTEMP_MODE_CONTINUOUS = 0,
    XTEMP_MODE_ONE_SHOT = 1,
    XTEMP_MODE_SHUTDOWN = 2
} xtemp_mode_t;

typedef enum {
    XTEMP_ALERT_COMPARATOR = 0,
    XTEMP_ALERT_INTERRUPT = 1
} xtemp_alert_mode_t;

typedef struct {
    float temperature_c;
    float temperature_f;
    uint32_t timestamp;
    uint8_t alert_status;
} xtemp_data_t;

typedef struct {
    uint32_t i2c_instance;
    uint8_t device_address;
    xtemp_resolution_t resolution;
    xtemp_mode_t operating_mode;
    float high_threshold_c;
    float low_threshold_c;
    xtemp_alert_mode_t alert_mode;
    uint8_t alert_polarity;
} xtemp_config_t;

typedef void (*xtemp_alert_callback_t)(float temperature, uint8_t alert_type);
typedef void (*xtemp_conversion_callback_t)(const xtemp_data_t* data);

int xtemp_init(const xtemp_config_t* config);
int xtemp_deinit(void);
int xtemp_read_temperature(xtemp_data_t* data);
int xtemp_read_temperature_c(float* temperature);
int xtemp_read_temperature_f(float* temperature);
int xtemp_read_raw_temperature(int16_t* raw_temp);
int xtemp_start_conversion(void);
int xtemp_set_thresholds(float high_temp_c, float low_temp_c);
int xtemp_get_thresholds(float* high_temp_c, float* low_temp_c);
int xtemp_enable_alerts(void);
int xtemp_disable_alerts(void);
int xtemp_clear_alert(void);
int xtemp_set_alert_callback(xtemp_alert_callback_t callback);
int xtemp_set_conversion_callback(xtemp_conversion_callback_t callback);
int xtemp_calibrate(float reference_temp_c);
uint8_t xtemp_is_conversion_ready(void);
int xtemp_enter_shutdown_mode(void);
int xtemp_exit_shutdown_mode(void);

#endif // XTEMP_SENSOR_H