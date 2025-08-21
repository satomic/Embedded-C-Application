#ifndef XUART_HAL_H
#define XUART_HAL_H

#include <stdint.h>

typedef enum {
    XUART_BAUDRATE_9600 = 9600,
    XUART_BAUDRATE_19200 = 19200,
    XUART_BAUDRATE_38400 = 38400,
    XUART_BAUDRATE_57600 = 57600,
    XUART_BAUDRATE_115200 = 115200,
    XUART_BAUDRATE_230400 = 230400,
    XUART_BAUDRATE_460800 = 460800,
    XUART_BAUDRATE_921600 = 921600
} xuart_baudrate_t;

typedef enum {
    XUART_DATABITS_7 = 7,
    XUART_DATABITS_8 = 8,
    XUART_DATABITS_9 = 9
} xuart_databits_t;

typedef enum {
    XUART_PARITY_NONE = 0,
    XUART_PARITY_EVEN = 1,
    XUART_PARITY_ODD = 2
} xuart_parity_t;

typedef enum {
    XUART_STOPBITS_1 = 1,
    XUART_STOPBITS_2 = 2
} xuart_stopbits_t;

typedef enum {
    XUART_FLOWCTRL_NONE = 0,
    XUART_FLOWCTRL_RTS_CTS = 1,
    XUART_FLOWCTRL_XON_XOFF = 2
} xuart_flowctrl_t;

typedef struct {
    uint32_t instance;
    xuart_baudrate_t baudrate;
    xuart_databits_t databits;
    xuart_parity_t parity;
    xuart_stopbits_t stopbits;
    xuart_flowctrl_t flow_control;
    uint32_t rx_buffer_size;
    uint32_t tx_buffer_size;
} xuart_config_t;

typedef void (*xuart_rx_callback_t)(uint32_t instance, uint8_t* data, uint32_t length);
typedef void (*xuart_tx_callback_t)(uint32_t instance);
typedef void (*xuart_error_callback_t)(uint32_t instance, uint32_t error_flags);

int xuart_init(uint32_t instance, const xuart_config_t* config);
int xuart_deinit(uint32_t instance);
int xuart_transmit(uint32_t instance, const uint8_t* data, uint32_t length, uint32_t timeout_ms);
int xuart_receive(uint32_t instance, uint8_t* data, uint32_t length, uint32_t timeout_ms);
int xuart_transmit_async(uint32_t instance, const uint8_t* data, uint32_t length);
int xuart_receive_async(uint32_t instance, uint8_t* data, uint32_t length);
int xuart_abort_transmit(uint32_t instance);
int xuart_abort_receive(uint32_t instance);
uint32_t xuart_get_rx_count(uint32_t instance);
uint32_t xuart_get_tx_count(uint32_t instance);
int xuart_set_rx_callback(uint32_t instance, xuart_rx_callback_t callback);
int xuart_set_tx_callback(uint32_t instance, xuart_tx_callback_t callback);
int xuart_set_error_callback(uint32_t instance, xuart_error_callback_t callback);
int xuart_flush_rx_buffer(uint32_t instance);
int xuart_flush_tx_buffer(uint32_t instance);
int xuart_set_break(uint32_t instance, uint8_t enable);
uint32_t xuart_get_status(uint32_t instance);

#endif // XUART_HAL_H