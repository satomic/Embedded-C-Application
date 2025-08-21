#include "xgpio_hal.h"
#include <stdlib.h>

#define XGPIO_MAX_PORTS 8
#define XGPIO_MAX_PINS 16

static volatile uint32_t* gpio_base_addresses[XGPIO_MAX_PORTS] = {0};
static xgpio_irq_callback_t irq_callbacks[XGPIO_MAX_PORTS][XGPIO_MAX_PINS] = {0};

// Simulated register offsets
#define XGPIO_DATA_OFFSET     0x00
#define XGPIO_TRI_OFFSET      0x04
#define XGPIO_PULL_OFFSET     0x08
#define XGPIO_IRQ_EN_OFFSET   0x0C
#define XGPIO_IRQ_MODE_OFFSET 0x10

static int xgpio_validate_port_pin(uint32_t port, uint32_t pin) {
    if (port >= XGPIO_MAX_PORTS || pin >= XGPIO_MAX_PINS) {
        return -1;
    }
    return 0;
}

int xgpio_init_pin(uint32_t port, uint32_t pin, const xgpio_config_t* config) {
    if (xgpio_validate_port_pin(port, pin) != 0 || config == NULL) {
        return -1;
    }
    
    // Simulate hardware register configuration
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) {
        // Simulate memory mapping for port
        gpio_base_addresses[port] = (volatile uint32_t*)malloc(0x100);
        base = gpio_base_addresses[port];
    }
    
    // Configure pin mode
    uint32_t tri_reg = base[XGPIO_TRI_OFFSET / 4];
    if (config->mode == XGPIO_MODE_OUTPUT) {
        tri_reg &= ~(1U << pin);
    } else {
        tri_reg |= (1U << pin);
    }
    base[XGPIO_TRI_OFFSET / 4] = tri_reg;
    
    // Configure pull resistor
    uint32_t pull_reg = base[XGPIO_PULL_OFFSET / 4];
    pull_reg &= ~(3U << (pin * 2));
    pull_reg |= (config->pull << (pin * 2));
    base[XGPIO_PULL_OFFSET / 4] = pull_reg;
    
    return 0;
}

int xgpio_deinit_pin(uint32_t port, uint32_t pin) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    irq_callbacks[port][pin] = NULL;
    return 0;
}

int xgpio_write_pin(uint32_t port, uint32_t pin, xgpio_pin_state_t state) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return -1;
    
    uint32_t data_reg = base[XGPIO_DATA_OFFSET / 4];
    if (state == XGPIO_PIN_HIGH) {
        data_reg |= (1U << pin);
    } else {
        data_reg &= ~(1U << pin);
    }
    base[XGPIO_DATA_OFFSET / 4] = data_reg;
    
    return 0;
}

xgpio_pin_state_t xgpio_read_pin(uint32_t port, uint32_t pin) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return XGPIO_PIN_LOW;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return XGPIO_PIN_LOW;
    
    uint32_t data_reg = base[XGPIO_DATA_OFFSET / 4];
    return (data_reg & (1U << pin)) ? XGPIO_PIN_HIGH : XGPIO_PIN_LOW;
}

int xgpio_toggle_pin(uint32_t port, uint32_t pin) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    xgpio_pin_state_t current_state = xgpio_read_pin(port, pin);
    xgpio_pin_state_t new_state = (current_state == XGPIO_PIN_HIGH) ? XGPIO_PIN_LOW : XGPIO_PIN_HIGH;
    return xgpio_write_pin(port, pin, new_state);
}

int xgpio_configure_irq(uint32_t port, uint32_t pin, xgpio_irq_mode_t mode, xgpio_irq_callback_t callback) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return -1;
    
    irq_callbacks[port][pin] = callback;
    
    uint32_t irq_mode_reg = base[XGPIO_IRQ_MODE_OFFSET / 4];
    irq_mode_reg &= ~(3U << (pin * 2));
    irq_mode_reg |= (mode << (pin * 2));
    base[XGPIO_IRQ_MODE_OFFSET / 4] = irq_mode_reg;
    
    return 0;
}

int xgpio_enable_irq(uint32_t port, uint32_t pin) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return -1;
    
    uint32_t irq_en_reg = base[XGPIO_IRQ_EN_OFFSET / 4];
    irq_en_reg |= (1U << pin);
    base[XGPIO_IRQ_EN_OFFSET / 4] = irq_en_reg;
    
    return 0;
}

int xgpio_disable_irq(uint32_t port, uint32_t pin) {
    if (xgpio_validate_port_pin(port, pin) != 0) {
        return -1;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return -1;
    
    uint32_t irq_en_reg = base[XGPIO_IRQ_EN_OFFSET / 4];
    irq_en_reg &= ~(1U << pin);
    base[XGPIO_IRQ_EN_OFFSET / 4] = irq_en_reg;
    
    return 0;
}

uint32_t xgpio_read_port(uint32_t port) {
    if (port >= XGPIO_MAX_PORTS) {
        return 0;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return 0;
    
    return base[XGPIO_DATA_OFFSET / 4];
}

int xgpio_write_port(uint32_t port, uint32_t value, uint32_t mask) {
    if (port >= XGPIO_MAX_PORTS) {
        return -1;
    }
    
    volatile uint32_t* base = gpio_base_addresses[port];
    if (base == NULL) return -1;
    
    uint32_t current = base[XGPIO_DATA_OFFSET / 4];
    current = (current & ~mask) | (value & mask);
    base[XGPIO_DATA_OFFSET / 4] = current;
    
    return 0;
}