#ifndef XPOWER_MGMT_H
#define XPOWER_MGMT_H

#include <stdint.h>

typedef enum {
    XPOWER_MODE_ACTIVE = 0,
    XPOWER_MODE_IDLE = 1,
    XPOWER_MODE_SLEEP = 2,
    XPOWER_MODE_DEEP_SLEEP = 3,
    XPOWER_MODE_STANDBY = 4,
    XPOWER_MODE_SHUTDOWN = 5
} xpower_mode_t;

typedef enum {
    XPOWER_DOMAIN_CPU = 0,
    XPOWER_DOMAIN_MEMORY = 1,
    XPOWER_DOMAIN_PERIPHERAL = 2,
    XPOWER_DOMAIN_RADIO = 3,
    XPOWER_DOMAIN_DISPLAY = 4,
    XPOWER_DOMAIN_SENSORS = 5
} xpower_domain_t;

typedef enum {
    XPOWER_WAKEUP_SOURCE_RTC = 0x01,
    XPOWER_WAKEUP_SOURCE_GPIO = 0x02,
    XPOWER_WAKEUP_SOURCE_UART = 0x04,
    XPOWER_WAKEUP_SOURCE_TIMER = 0x08,
    XPOWER_WAKEUP_SOURCE_WATCHDOG = 0x10,
    XPOWER_WAKEUP_SOURCE_USB = 0x20
} xpower_wakeup_source_t;

typedef struct {
    float voltage_v;
    float current_ma;
    float power_mw;
    uint32_t energy_consumed_mwh;
    uint32_t uptime_seconds;
    xpower_mode_t current_mode;
} xpower_status_t;

typedef struct {
    xpower_mode_t default_mode;
    uint32_t idle_timeout_ms;
    uint32_t sleep_timeout_ms;
    uint8_t enable_voltage_scaling;
    uint8_t enable_clock_gating;
    uint8_t wakeup_sources;
    float low_battery_threshold_v;
    float critical_battery_threshold_v;
} xpower_config_t;

typedef struct {
    uint32_t mode_transitions;
    uint32_t time_in_active_ms;
    uint32_t time_in_idle_ms;
    uint32_t time_in_sleep_ms;
    uint32_t time_in_deep_sleep_ms;
    float avg_power_consumption_mw;
    float peak_power_consumption_mw;
    uint32_t wakeup_count;
} xpower_stats_t;

typedef void (*xpower_mode_change_callback_t)(xpower_mode_t old_mode, xpower_mode_t new_mode);
typedef void (*xpower_low_battery_callback_t)(float voltage);
typedef void (*xpower_wakeup_callback_t)(xpower_wakeup_source_t source);

int xpower_init(const xpower_config_t* config);
int xpower_deinit(void);
int xpower_set_mode(xpower_mode_t mode);
xpower_mode_t xpower_get_mode(void);
int xpower_enable_domain(xpower_domain_t domain);
int xpower_disable_domain(xpower_domain_t domain);
uint8_t xpower_is_domain_enabled(xpower_domain_t domain);
int xpower_set_cpu_frequency(uint32_t frequency_mhz);
uint32_t xpower_get_cpu_frequency(void);
int xpower_set_voltage(xpower_domain_t domain, float voltage_v);
float xpower_get_voltage(xpower_domain_t domain);
int xpower_get_status(xpower_status_t* status);
int xpower_configure_wakeup_source(xpower_wakeup_source_t source, uint8_t enable);
int xpower_enter_sleep_mode(uint32_t duration_ms);
int xpower_wake_from_sleep(void);
int xpower_set_mode_change_callback(xpower_mode_change_callback_t callback);
int xpower_set_low_battery_callback(xpower_low_battery_callback_t callback);
int xpower_set_wakeup_callback(xpower_wakeup_callback_t callback);
int xpower_get_stats(xpower_stats_t* stats);
int xpower_reset_stats(void);
float xpower_estimate_battery_life_hours(float battery_capacity_mah);

#endif // XPOWER_MGMT_H