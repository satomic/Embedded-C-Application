#ifndef XSOFT_TIMER_H
#define XSOFT_TIMER_H

#include <stdint.h>

typedef enum {
    XSOFT_TIMER_ONE_SHOT = 0,
    XSOFT_TIMER_PERIODIC = 1
} xsoft_timer_type_t;

typedef enum {
    XSOFT_TIMER_STATUS_INACTIVE = 0,
    XSOFT_TIMER_STATUS_ACTIVE = 1,
    XSOFT_TIMER_STATUS_EXPIRED = 2
} xsoft_timer_status_t;

typedef void* xsoft_timer_handle_t;
typedef void (*xsoft_timer_callback_t)(xsoft_timer_handle_t timer, void* user_data);

typedef struct {
    char name[16];
    xsoft_timer_type_t type;
    uint32_t period_ms;
    xsoft_timer_callback_t callback;
    void* user_data;
    uint8_t auto_start;
} xsoft_timer_config_t;

typedef struct {
    char name[16];
    xsoft_timer_type_t type;
    xsoft_timer_status_t status;
    uint32_t period_ms;
    uint32_t remaining_ms;
    uint32_t expiry_count;
    uint32_t creation_time;
    uint32_t last_expiry_time;
} xsoft_timer_info_t;

typedef struct {
    uint32_t total_timers;
    uint32_t active_timers;
    uint32_t expired_timers;
    uint32_t total_expirations;
    uint32_t max_jitter_ms;
    uint32_t avg_jitter_ms;
    uint32_t timer_task_cpu_usage;
} xsoft_timer_stats_t;

int xsoft_timer_init(uint32_t max_timers, uint32_t tick_period_ms);
int xsoft_timer_deinit(void);
xsoft_timer_handle_t xsoft_timer_create(const xsoft_timer_config_t* config);
int xsoft_timer_delete(xsoft_timer_handle_t timer);
int xsoft_timer_start(xsoft_timer_handle_t timer);
int xsoft_timer_stop(xsoft_timer_handle_t timer);
int xsoft_timer_restart(xsoft_timer_handle_t timer);
int xsoft_timer_set_period(xsoft_timer_handle_t timer, uint32_t period_ms);
uint32_t xsoft_timer_get_period(xsoft_timer_handle_t timer);
uint32_t xsoft_timer_get_remaining_time(xsoft_timer_handle_t timer);
xsoft_timer_status_t xsoft_timer_get_status(xsoft_timer_handle_t timer);
int xsoft_timer_get_info(xsoft_timer_handle_t timer, xsoft_timer_info_t* info);
int xsoft_timer_reset(xsoft_timer_handle_t timer);
int xsoft_timer_change_callback(xsoft_timer_handle_t timer, xsoft_timer_callback_t callback, void* user_data);
int xsoft_timer_process_timers(void);
uint32_t xsoft_timer_get_next_expiry_time(void);
int xsoft_timer_get_stats(xsoft_timer_stats_t* stats);
int xsoft_timer_reset_stats(void);
uint32_t xsoft_timer_get_system_time_ms(void);
xsoft_timer_handle_t xsoft_timer_find_by_name(const char* name);

#endif // XSOFT_TIMER_H