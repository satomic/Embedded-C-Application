#ifndef XHW_TIMER_H
#define XHW_TIMER_H

#include <stdint.h>

typedef enum {
    XHW_TIMER_MODE_ONE_SHOT = 0,
    XHW_TIMER_MODE_PERIODIC = 1,
    XHW_TIMER_MODE_PWM = 2,
    XHW_TIMER_MODE_CAPTURE = 3
} xhw_timer_mode_t;

typedef enum {
    XHW_TIMER_PRESCALER_1 = 0,
    XHW_TIMER_PRESCALER_8 = 1,
    XHW_TIMER_PRESCALER_64 = 2,
    XHW_TIMER_PRESCALER_256 = 3,
    XHW_TIMER_PRESCALER_1024 = 4
} xhw_timer_prescaler_t;

typedef enum {
    XHW_TIMER_EDGE_RISING = 0,
    XHW_TIMER_EDGE_FALLING = 1,
    XHW_TIMER_EDGE_BOTH = 2
} xhw_timer_edge_t;

typedef enum {
    XHW_TIMER_STATUS_IDLE = 0,
    XHW_TIMER_STATUS_RUNNING = 1,
    XHW_TIMER_STATUS_EXPIRED = 2,
    XHW_TIMER_STATUS_ERROR = 3
} xhw_timer_status_t;

typedef struct {
    uint32_t instance;
    xhw_timer_mode_t mode;
    xhw_timer_prescaler_t prescaler;
    uint32_t period_us;
    uint32_t duty_cycle_percent;
    uint8_t auto_reload;
    uint8_t start_immediately;
} xhw_timer_config_t;

typedef struct {
    uint32_t instance;
    uint32_t channel;
    xhw_timer_edge_t edge;
    uint8_t filter_enable;
    uint8_t filter_value;
    uint32_t timeout_us;
} xhw_timer_capture_config_t;

typedef struct {
    uint32_t overflow_count;
    uint32_t capture_count;
    uint32_t match_count;
    uint32_t error_count;
    uint32_t max_period_us;
    uint32_t min_period_us;
    uint32_t avg_period_us;
} xhw_timer_stats_t;

typedef void (*xhw_timer_callback_t)(uint32_t instance);
typedef void (*xhw_timer_capture_callback_t)(uint32_t instance, uint32_t channel, uint32_t captured_value);
typedef void (*xhw_timer_overflow_callback_t)(uint32_t instance);

int xhw_timer_init(uint32_t instance, const xhw_timer_config_t* config);
int xhw_timer_deinit(uint32_t instance);
int xhw_timer_start(uint32_t instance);
int xhw_timer_stop(uint32_t instance);
int xhw_timer_reset(uint32_t instance);
int xhw_timer_set_period(uint32_t instance, uint32_t period_us);
uint32_t xhw_timer_get_period(uint32_t instance);
int xhw_timer_set_duty_cycle(uint32_t instance, uint32_t duty_cycle_percent);
uint32_t xhw_timer_get_duty_cycle(uint32_t instance);
uint32_t xhw_timer_get_counter_value(uint32_t instance);
int xhw_timer_set_counter_value(uint32_t instance, uint32_t value);
xhw_timer_status_t xhw_timer_get_status(uint32_t instance);
int xhw_timer_configure_capture(uint32_t instance, uint32_t channel, const xhw_timer_capture_config_t* config);
uint32_t xhw_timer_get_capture_value(uint32_t instance, uint32_t channel);
int xhw_timer_set_callback(uint32_t instance, xhw_timer_callback_t callback);
int xhw_timer_set_capture_callback(uint32_t instance, uint32_t channel, xhw_timer_capture_callback_t callback);
int xhw_timer_set_overflow_callback(uint32_t instance, xhw_timer_overflow_callback_t callback);
int xhw_timer_get_stats(uint32_t instance, xhw_timer_stats_t* stats);
int xhw_timer_reset_stats(uint32_t instance);
uint64_t xhw_timer_get_timestamp_us(void);
int xhw_timer_delay_us(uint32_t delay_us);

#endif // XHW_TIMER_H