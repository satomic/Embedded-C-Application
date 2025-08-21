#ifndef XMODBUS_PROTOCOL_H
#define XMODBUS_PROTOCOL_H

#include <stdint.h>

typedef enum {
    XMODBUS_MODE_RTU = 0,
    XMODBUS_MODE_ASCII = 1,
    XMODBUS_MODE_TCP = 2
} xmodbus_mode_t;

typedef enum {
    XMODBUS_ROLE_MASTER = 0,
    XMODBUS_ROLE_SLAVE = 1
} xmodbus_role_t;

typedef enum {
    XMODBUS_FUNC_READ_COILS = 0x01,
    XMODBUS_FUNC_READ_DISCRETE_INPUTS = 0x02,
    XMODBUS_FUNC_READ_HOLDING_REGISTERS = 0x03,
    XMODBUS_FUNC_READ_INPUT_REGISTERS = 0x04,
    XMODBUS_FUNC_WRITE_SINGLE_COIL = 0x05,
    XMODBUS_FUNC_WRITE_SINGLE_REGISTER = 0x06,
    XMODBUS_FUNC_WRITE_MULTIPLE_COILS = 0x0F,
    XMODBUS_FUNC_WRITE_MULTIPLE_REGISTERS = 0x10
} xmodbus_function_t;

typedef enum {
    XMODBUS_STATUS_OK = 0,
    XMODBUS_STATUS_TIMEOUT = 1,
    XMODBUS_STATUS_CRC_ERROR = 2,
    XMODBUS_STATUS_ILLEGAL_FUNCTION = 3,
    XMODBUS_STATUS_ILLEGAL_DATA_ADDRESS = 4,
    XMODBUS_STATUS_ILLEGAL_DATA_VALUE = 5,
    XMODBUS_STATUS_SLAVE_DEVICE_FAILURE = 6
} xmodbus_status_t;

typedef struct {
    uint8_t slave_address;
    xmodbus_function_t function_code;
    uint16_t start_address;
    uint16_t quantity;
    uint8_t* data;
    uint16_t data_length;
    uint32_t timeout_ms;
} xmodbus_request_t;

typedef struct {
    uint8_t slave_address;
    xmodbus_function_t function_code;
    uint8_t* data;
    uint16_t data_length;
    xmodbus_status_t status;
} xmodbus_response_t;

typedef struct {
    uint32_t uart_instance;
    xmodbus_mode_t mode;
    xmodbus_role_t role;
    uint8_t device_address;
    uint32_t response_timeout_ms;
    uint32_t frame_delay_ms;
    uint8_t enable_crc_check;
} xmodbus_config_t;

typedef struct {
    uint32_t requests_sent;
    uint32_t responses_received;
    uint32_t timeout_errors;
    uint32_t crc_errors;
    uint32_t exception_responses;
    uint32_t broadcast_messages;
} xmodbus_stats_t;

typedef xmodbus_status_t (*xmodbus_read_coils_callback_t)(uint16_t address, uint16_t quantity, uint8_t* data);
typedef xmodbus_status_t (*xmodbus_read_registers_callback_t)(uint16_t address, uint16_t quantity, uint16_t* data);
typedef xmodbus_status_t (*xmodbus_write_coils_callback_t)(uint16_t address, uint16_t quantity, const uint8_t* data);
typedef xmodbus_status_t (*xmodbus_write_registers_callback_t)(uint16_t address, uint16_t quantity, const uint16_t* data);

int xmodbus_init(const xmodbus_config_t* config);
int xmodbus_deinit(void);
xmodbus_status_t xmodbus_master_request(const xmodbus_request_t* request, xmodbus_response_t* response);
xmodbus_status_t xmodbus_read_coils(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, uint8_t* coils);
xmodbus_status_t xmodbus_read_discrete_inputs(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, uint8_t* inputs);
xmodbus_status_t xmodbus_read_holding_registers(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, uint16_t* registers);
xmodbus_status_t xmodbus_read_input_registers(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, uint16_t* registers);
xmodbus_status_t xmodbus_write_single_coil(uint8_t slave_addr, uint16_t address, uint8_t value);
xmodbus_status_t xmodbus_write_single_register(uint8_t slave_addr, uint16_t address, uint16_t value);
xmodbus_status_t xmodbus_write_multiple_coils(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, const uint8_t* coils);
xmodbus_status_t xmodbus_write_multiple_registers(uint8_t slave_addr, uint16_t start_addr, uint16_t quantity, const uint16_t* registers);
int xmodbus_slave_set_coils_callback(xmodbus_read_coils_callback_t read_cb, xmodbus_write_coils_callback_t write_cb);
int xmodbus_slave_set_registers_callback(xmodbus_read_registers_callback_t read_cb, xmodbus_write_registers_callback_t write_cb);
int xmodbus_process_slave_requests(void);
int xmodbus_get_stats(xmodbus_stats_t* stats);
int xmodbus_reset_stats(void);

#endif // XMODBUS_PROTOCOL_H