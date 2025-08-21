#ifndef XI2C_HAL_H
#define XI2C_HAL_H

#include <stdint.h>

typedef enum {
    XI2C_SPEED_STANDARD = 100000,   // 100 kHz
    XI2C_SPEED_FAST = 400000,       // 400 kHz
    XI2C_SPEED_FAST_PLUS = 1000000, // 1 MHz
    XI2C_SPEED_HIGH = 3400000       // 3.4 MHz
} xi2c_speed_t;

typedef enum {
    XI2C_ADDR_7BIT = 0,
    XI2C_ADDR_10BIT = 1
} xi2c_addr_mode_t;

typedef enum {
    XI2C_STATUS_IDLE = 0,
    XI2C_STATUS_BUSY = 1,
    XI2C_STATUS_ERROR = 2,
    XI2C_STATUS_TIMEOUT = 3
} xi2c_status_t;

typedef struct {
    uint32_t instance;
    xi2c_speed_t clock_speed;
    xi2c_addr_mode_t addr_mode;
    uint8_t own_address;
    uint32_t timeout_ms;
} xi2c_config_t;

typedef struct {
    uint16_t device_addr;
    uint8_t* data;
    uint32_t length;
    uint32_t timeout_ms;
} xi2c_transfer_t;

int xi2c_init(uint32_t instance, const xi2c_config_t* config);
int xi2c_deinit(uint32_t instance);
int xi2c_master_transmit(uint32_t instance, uint16_t dev_addr, const uint8_t* data, uint32_t length, uint32_t timeout_ms);
int xi2c_master_receive(uint32_t instance, uint16_t dev_addr, uint8_t* data, uint32_t length, uint32_t timeout_ms);
int xi2c_mem_write(uint32_t instance, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, const uint8_t* data, uint32_t length, uint32_t timeout_ms);
int xi2c_mem_read(uint32_t instance, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t* data, uint32_t length, uint32_t timeout_ms);
xi2c_status_t xi2c_get_status(uint32_t instance);
int xi2c_abort_transfer(uint32_t instance);
int xi2c_scan_bus(uint32_t instance, uint8_t* found_addresses, uint8_t max_addresses);
int xi2c_is_device_ready(uint32_t instance, uint16_t dev_addr, uint32_t trials, uint32_t timeout_ms);
int xi2c_enable_clock_stretching(uint32_t instance, uint8_t enable);

#endif // XI2C_HAL_H