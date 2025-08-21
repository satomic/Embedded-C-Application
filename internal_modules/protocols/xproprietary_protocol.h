#ifndef XPROPRIETARY_PROTOCOL_H
#define XPROPRIETARY_PROTOCOL_H

#include <stdint.h>

#define XPROP_MAX_PAYLOAD_SIZE 256
#define XPROP_HEADER_SIZE 8

typedef enum {
    XPROP_PACKET_TYPE_DATA = 0x01,
    XPROP_PACKET_TYPE_ACK = 0x02,
    XPROP_PACKET_TYPE_NACK = 0x03,
    XPROP_PACKET_TYPE_HEARTBEAT = 0x04,
    XPROP_PACKET_TYPE_CONFIG = 0x05,
    XPROP_PACKET_TYPE_STATUS = 0x06,
    XPROP_PACKET_TYPE_COMMAND = 0x07,
    XPROP_PACKET_TYPE_RESPONSE = 0x08
} xprop_packet_type_t;

typedef enum {
    XPROP_PRIORITY_LOW = 0,
    XPROP_PRIORITY_NORMAL = 1,
    XPROP_PRIORITY_HIGH = 2,
    XPROP_PRIORITY_CRITICAL = 3
} xprop_priority_t;

typedef enum {
    XPROP_STATUS_OK = 0,
    XPROP_STATUS_TIMEOUT = 1,
    XPROP_STATUS_CHECKSUM_ERROR = 2,
    XPROP_STATUS_BUFFER_OVERFLOW = 3,
    XPROP_STATUS_INVALID_PACKET = 4,
    XPROP_STATUS_SEQUENCE_ERROR = 5,
    XPROP_STATUS_BUSY = 6
} xprop_status_t;

typedef struct {
    uint16_t start_marker;
    uint8_t packet_type;
    uint8_t priority;
    uint16_t source_id;
    uint16_t dest_id;
    uint16_t sequence_num;
    uint16_t payload_length;
    uint8_t payload[XPROP_MAX_PAYLOAD_SIZE];
    uint16_t checksum;
} __attribute__((packed)) xprop_packet_t;

typedef struct {
    uint32_t interface_instance;
    uint16_t device_id;
    uint32_t heartbeat_interval_ms;
    uint32_t ack_timeout_ms;
    uint8_t max_retries;
    uint8_t enable_encryption;
    uint8_t encryption_key[16];
} xprop_config_t;

typedef struct {
    uint32_t packets_sent;
    uint32_t packets_received;
    uint32_t packets_dropped;
    uint32_t checksum_errors;
    uint32_t timeout_errors;
    uint32_t retransmissions;
    uint32_t bytes_transmitted;
    uint32_t bytes_received;
} xprop_stats_t;

typedef void (*xprop_rx_callback_t)(const xprop_packet_t* packet);
typedef void (*xprop_tx_complete_callback_t)(uint16_t sequence_num, xprop_status_t status);
typedef void (*xprop_error_callback_t)(xprop_status_t error, uint32_t error_data);

int xprop_init(const xprop_config_t* config);
int xprop_deinit(void);
xprop_status_t xprop_send_packet(uint16_t dest_id, xprop_packet_type_t type, xprop_priority_t priority, 
                                const uint8_t* payload, uint16_t payload_len);
xprop_status_t xprop_send_data(uint16_t dest_id, const uint8_t* data, uint16_t length);
xprop_status_t xprop_send_command(uint16_t dest_id, uint8_t command_id, const uint8_t* params, uint16_t param_len);
xprop_status_t xprop_send_response(uint16_t dest_id, uint16_t sequence_num, const uint8_t* response_data, uint16_t length);
xprop_status_t xprop_send_ack(uint16_t dest_id, uint16_t sequence_num);
xprop_status_t xprop_send_nack(uint16_t dest_id, uint16_t sequence_num, uint8_t error_code);
int xprop_process_received_data(const uint8_t* data, uint16_t length);
int xprop_set_rx_callback(xprop_rx_callback_t callback);
int xprop_set_tx_complete_callback(xprop_tx_complete_callback_t callback);
int xprop_set_error_callback(xprop_error_callback_t callback);
int xprop_enable_heartbeat(uint8_t enable);
int xprop_get_stats(xprop_stats_t* stats);
int xprop_reset_stats(void);
uint16_t xprop_get_next_sequence_number(void);
xprop_status_t xprop_validate_packet(const xprop_packet_t* packet);

#endif // XPROPRIETARY_PROTOCOL_H