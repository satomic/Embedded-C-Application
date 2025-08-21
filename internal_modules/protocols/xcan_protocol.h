#ifndef XCAN_PROTOCOL_H
#define XCAN_PROTOCOL_H

#include <stdint.h>

typedef enum {
    XCAN_BITRATE_125K = 125000,
    XCAN_BITRATE_250K = 250000,
    XCAN_BITRATE_500K = 500000,
    XCAN_BITRATE_1M = 1000000
} xcan_bitrate_t;

typedef enum {
    XCAN_FRAME_STANDARD = 0,
    XCAN_FRAME_EXTENDED = 1
} xcan_frame_type_t;

typedef enum {
    XCAN_FRAME_DATA = 0,
    XCAN_FRAME_REMOTE = 1
} xcan_frame_format_t;

typedef enum {
    XCAN_MODE_NORMAL = 0,
    XCAN_MODE_LOOPBACK = 1,
    XCAN_MODE_SILENT = 2,
    XCAN_MODE_SILENT_LOOPBACK = 3
} xcan_mode_t;

typedef struct {
    uint32_t id;
    xcan_frame_type_t type;
    xcan_frame_format_t format;
    uint8_t dlc;
    uint8_t data[8];
    uint32_t timestamp;
} xcan_frame_t;

typedef struct {
    uint32_t id;
    uint32_t mask;
    xcan_frame_type_t type;
    uint8_t fifo_assignment;
} xcan_filter_t;

typedef struct {
    uint32_t instance;
    xcan_bitrate_t bitrate;
    xcan_mode_t mode;
    uint8_t enable_brs;
    uint32_t data_bitrate;
    uint8_t auto_retransmission;
    uint8_t time_triggered_mode;
} xcan_config_t;

typedef struct {
    uint32_t tx_frames;
    uint32_t rx_frames;
    uint32_t tx_errors;
    uint32_t rx_errors;
    uint32_t bus_off_count;
    uint32_t error_warning_count;
    uint32_t error_passive_count;
} xcan_stats_t;

typedef void (*xcan_rx_callback_t)(uint32_t instance, const xcan_frame_t* frame);
typedef void (*xcan_tx_callback_t)(uint32_t instance, uint32_t mailbox);
typedef void (*xcan_error_callback_t)(uint32_t instance, uint32_t error_code);

int xcan_init(uint32_t instance, const xcan_config_t* config);
int xcan_deinit(uint32_t instance);
int xcan_start(uint32_t instance);
int xcan_stop(uint32_t instance);
int xcan_transmit(uint32_t instance, const xcan_frame_t* frame, uint32_t timeout_ms);
int xcan_transmit_async(uint32_t instance, const xcan_frame_t* frame, uint32_t mailbox);
int xcan_receive(uint32_t instance, xcan_frame_t* frame, uint32_t timeout_ms);
int xcan_add_filter(uint32_t instance, const xcan_filter_t* filter);
int xcan_remove_filter(uint32_t instance, uint32_t filter_id);
int xcan_set_rx_callback(uint32_t instance, xcan_rx_callback_t callback);
int xcan_set_tx_callback(uint32_t instance, xcan_tx_callback_t callback);
int xcan_set_error_callback(uint32_t instance, xcan_error_callback_t callback);
int xcan_get_stats(uint32_t instance, xcan_stats_t* stats);
int xcan_reset_stats(uint32_t instance);
uint8_t xcan_is_bus_off(uint32_t instance);
uint32_t xcan_get_error_count(uint32_t instance);
int xcan_abort_transmission(uint32_t instance, uint32_t mailbox);

#endif // XCAN_PROTOCOL_H