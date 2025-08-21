#ifndef XGPIO_HAL_H
#define XGPIO_HAL_H

#include <stdint.h>

typedef enum {
    XGPIO_PIN_LOW = 0,
    XGPIO_PIN_HIGH = 1
} xgpio_pin_state_t;

typedef enum {
    XGPIO_MODE_INPUT = 0,
    XGPIO_MODE_OUTPUT = 1,
    XGPIO_MODE_ALTERNATE = 2,
    XGPIO_MODE_ANALOG = 3
} xgpio_pin_mode_t;

typedef enum {
    XGPIO_PULL_NONE = 0,
    XGPIO_PULL_UP = 1,
    XGPIO_PULL_DOWN = 2
} xgpio_pull_t;

typedef enum {
    XGPIO_IRQ_RISING = 0x01,
    XGPIO_IRQ_FALLING = 0x02,
    XGPIO_IRQ_BOTH = 0x03
} xgpio_irq_mode_t;

typedef struct {
    uint32_t port;
    uint32_t pin;
    xgpio_pin_mode_t mode;
    xgpio_pull_t pull;
} xgpio_config_t;

typedef void (*xgpio_irq_callback_t)(uint32_t port, uint32_t pin);

int xgpio_init_pin(uint32_t port, uint32_t pin, const xgpio_config_t* config);
int xgpio_deinit_pin(uint32_t port, uint32_t pin);
int xgpio_write_pin(uint32_t port, uint32_t pin, xgpio_pin_state_t state);
xgpio_pin_state_t xgpio_read_pin(uint32_t port, uint32_t pin);
int xgpio_toggle_pin(uint32_t port, uint32_t pin);
int xgpio_configure_irq(uint32_t port, uint32_t pin, xgpio_irq_mode_t mode, xgpio_irq_callback_t callback);
int xgpio_enable_irq(uint32_t port, uint32_t pin);
int xgpio_disable_irq(uint32_t port, uint32_t pin);
uint32_t xgpio_read_port(uint32_t port);
int xgpio_write_port(uint32_t port, uint32_t value, uint32_t mask);

#endif // XGPIO_HAL_H