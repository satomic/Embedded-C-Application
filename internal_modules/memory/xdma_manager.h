#ifndef XDMA_MANAGER_H
#define XDMA_MANAGER_H

#include <stdint.h>

typedef enum {
    XDMA_STATUS_IDLE = 0,
    XDMA_STATUS_BUSY = 1,
    XDMA_STATUS_COMPLETE = 2,
    XDMA_STATUS_ERROR = 3,
    XDMA_STATUS_ABORTED = 4
} xdma_status_t;

typedef enum {
    XDMA_PRIORITY_LOW = 0,
    XDMA_PRIORITY_MEDIUM = 1,
    XDMA_PRIORITY_HIGH = 2,
    XDMA_PRIORITY_VERY_HIGH = 3
} xdma_priority_t;

typedef enum {
    XDMA_WIDTH_8BIT = 0,
    XDMA_WIDTH_16BIT = 1,
    XDMA_WIDTH_32BIT = 2,
    XDMA_WIDTH_64BIT = 3
} xdma_width_t;

typedef enum {
    XDMA_MODE_NORMAL = 0,
    XDMA_MODE_CIRCULAR = 1,
    XDMA_MODE_DOUBLE_BUFFER = 2
} xdma_mode_t;

typedef struct {
    void* src_addr;
    void* dst_addr;
    uint32_t length;
    xdma_width_t data_width;
    xdma_mode_t mode;
    xdma_priority_t priority;
    uint8_t src_increment;
    uint8_t dst_increment;
    uint32_t burst_size;
} xdma_transfer_config_t;

typedef struct {
    uint32_t total_transfers;
    uint32_t successful_transfers;
    uint32_t failed_transfers;
    uint32_t bytes_transferred;
    uint32_t average_transfer_time_us;
    uint32_t peak_bandwidth_mbps;
} xdma_stats_t;

typedef void (*xdma_complete_callback_t)(uint32_t channel, xdma_status_t status);
typedef void (*xdma_error_callback_t)(uint32_t channel, uint32_t error_code);

int xdma_init(void);
int xdma_deinit(void);
int xdma_allocate_channel(uint32_t* channel, xdma_priority_t priority);
int xdma_release_channel(uint32_t channel);
int xdma_configure_transfer(uint32_t channel, const xdma_transfer_config_t* config);
int xdma_start_transfer(uint32_t channel);
int xdma_stop_transfer(uint32_t channel);
int xdma_abort_transfer(uint32_t channel);
xdma_status_t xdma_get_transfer_status(uint32_t channel);
uint32_t xdma_get_remaining_bytes(uint32_t channel);
int xdma_set_complete_callback(uint32_t channel, xdma_complete_callback_t callback);
int xdma_set_error_callback(uint32_t channel, xdma_error_callback_t callback);
int xdma_get_stats(uint32_t channel, xdma_stats_t* stats);
int xdma_reset_stats(uint32_t channel);
uint8_t xdma_is_channel_available(uint32_t channel);
int xdma_get_available_channels(uint32_t* channels, uint32_t max_channels);

#endif // XDMA_MANAGER_H