#ifndef XRTOS_SCHEDULER_H
#define XRTOS_SCHEDULER_H

#include <stdint.h>

typedef enum {
    XRTOS_TASK_READY = 0,
    XRTOS_TASK_RUNNING = 1,
    XRTOS_TASK_BLOCKED = 2,
    XRTOS_TASK_SUSPENDED = 3,
    XRTOS_TASK_DELETED = 4
} xrtos_task_state_t;

typedef enum {
    XRTOS_PRIORITY_IDLE = 0,
    XRTOS_PRIORITY_LOW = 1,
    XRTOS_PRIORITY_NORMAL = 2,
    XRTOS_PRIORITY_HIGH = 3,
    XRTOS_PRIORITY_CRITICAL = 4,
    XRTOS_PRIORITY_MAX = 5
} xrtos_priority_t;

typedef enum {
    XRTOS_SCHED_POLICY_RR = 0,        // Round Robin
    XRTOS_SCHED_POLICY_FIFO = 1,      // First In First Out
    XRTOS_SCHED_POLICY_EDF = 2,       // Earliest Deadline First
    XRTOS_SCHED_POLICY_RM = 3         // Rate Monotonic
} xrtos_sched_policy_t;

typedef void* xrtos_task_handle_t;
typedef void (*xrtos_task_function_t)(void* parameters);

typedef struct {
    char name[16];
    xrtos_task_function_t task_function;
    void* parameters;
    uint32_t stack_size;
    xrtos_priority_t priority;
    uint32_t time_slice_ms;
    uint32_t deadline_ms;
    uint32_t period_ms;
    uint8_t auto_start;
} xrtos_task_config_t;

typedef struct {
    char name[16];
    xrtos_task_state_t state;
    xrtos_priority_t priority;
    uint32_t stack_size;
    uint32_t stack_free;
    uint32_t cpu_usage_percent;
    uint32_t execution_count;
    uint32_t missed_deadlines;
    uint32_t max_execution_time_us;
    uint32_t avg_execution_time_us;
} xrtos_task_info_t;

typedef struct {
    uint32_t total_tasks;
    uint32_t running_tasks;
    uint32_t ready_tasks;
    uint32_t blocked_tasks;
    uint32_t suspended_tasks;
    uint32_t cpu_utilization_percent;
    uint32_t context_switches;
    uint32_t interrupts_processed;
    uint32_t tick_count;
} xrtos_system_stats_t;

int xrtos_init(xrtos_sched_policy_t policy, uint32_t tick_rate_hz);
int xrtos_start_scheduler(void);
int xrtos_stop_scheduler(void);
xrtos_task_handle_t xrtos_create_task(const xrtos_task_config_t* config);
int xrtos_delete_task(xrtos_task_handle_t task);
int xrtos_suspend_task(xrtos_task_handle_t task);
int xrtos_resume_task(xrtos_task_handle_t task);
int xrtos_set_task_priority(xrtos_task_handle_t task, xrtos_priority_t priority);
xrtos_priority_t xrtos_get_task_priority(xrtos_task_handle_t task);
int xrtos_get_task_info(xrtos_task_handle_t task, xrtos_task_info_t* info);
xrtos_task_handle_t xrtos_get_current_task(void);
int xrtos_yield(void);
int xrtos_delay(uint32_t delay_ms);
int xrtos_delay_until(uint32_t* last_wake_time, uint32_t period_ms);
int xrtos_get_system_stats(xrtos_system_stats_t* stats);
uint32_t xrtos_get_tick_count(void);
uint32_t xrtos_get_free_heap_size(void);
int xrtos_enter_critical_section(void);
int xrtos_exit_critical_section(void);

#endif // XRTOS_SCHEDULER_H