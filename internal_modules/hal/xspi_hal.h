#ifndef XSPI_HAL_H
#define XSPI_HAL_H

#include <stdint.h>

typedef enum {
    XSPI_MODE_0 = 0,  // CPOL=0, CPHA=0
    XSPI_MODE_1 = 1,  // CPOL=0, CPHA=1
    XSPI_MODE_2 = 2,  // CPOL=1, CPHA=0
    XSPI_MODE_3 = 3   // CPOL=1, CPHA=1
} xspi_mode_t;

typedef enum {
    XSPI_BITORDER_MSB = 0,
    XSPI_BITORDER_LSB = 1
} xspi_bitorder_t;

typedef enum {
    XSPI_CS_ACTIVE_LOW = 0,
    XSPI_CS_ACTIVE_HIGH = 1
} xspi_cs_polarity_t;

typedef struct {
    uint32_t instance;
    uint32_t clock_freq;
    xspi_mode_t mode;
    xspi_bitorder_t bit_order;
    xspi_cs_polarity_t cs_polarity;
    uint8_t data_width;
} xspi_config_t;

typedef struct {
    uint8_t* tx_buffer;
    uint8_t* rx_buffer;
    uint32_t length;
    uint32_t cs_pin;
    uint32_t timeout_ms;
} xspi_transfer_t;

int xspi_init(uint32_t instance, const xspi_config_t* config);
int xspi_deinit(uint32_t instance);
int xspi_transfer(uint32_t instance, const xspi_transfer_t* transfer);
int xspi_transmit(uint32_t instance, const uint8_t* data, uint32_t length, uint32_t cs_pin, uint32_t timeout_ms);
int xspi_receive(uint32_t instance, uint8_t* data, uint32_t length, uint32_t cs_pin, uint32_t timeout_ms);
int xspi_transmit_receive(uint32_t instance, const uint8_t* tx_data, uint8_t* rx_data, uint32_t length, uint32_t cs_pin, uint32_t timeout_ms);
int xspi_set_cs(uint32_t instance, uint32_t cs_pin, uint8_t active);
int xspi_get_status(uint32_t instance);
int xspi_abort_transfer(uint32_t instance);
int xspi_flush_buffers(uint32_t instance);

#endif // XSPI_HAL_H