#ifndef XRING_BUFFER_H
#define XRING_BUFFER_H

#include <stdint.h>

typedef enum {
    XRING_BUFFER_OK = 0,
    XRING_BUFFER_FULL = 1,
    XRING_BUFFER_EMPTY = 2,
    XRING_BUFFER_INVALID_PARAM = 3,
    XRING_BUFFER_OVERFLOW = 4
} xring_buffer_status_t;

typedef enum {
    XRING_BUFFER_MODE_NORMAL = 0,
    XRING_BUFFER_MODE_OVERWRITE = 1
} xring_buffer_mode_t;

typedef struct {
    uint8_t* buffer;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    xring_buffer_mode_t mode;
    uint8_t thread_safe;
} xring_buffer_t;

typedef struct {
    uint32_t total_size;
    uint32_t used_size;
    uint32_t free_size;
    uint32_t peak_usage;
    uint32_t overflow_count;
    uint32_t underflow_count;
} xring_buffer_stats_t;

xring_buffer_status_t xring_buffer_init(xring_buffer_t* rb, uint8_t* buffer, uint32_t size, xring_buffer_mode_t mode);
xring_buffer_status_t xring_buffer_deinit(xring_buffer_t* rb);
xring_buffer_status_t xring_buffer_put(xring_buffer_t* rb, uint8_t data);
xring_buffer_status_t xring_buffer_get(xring_buffer_t* rb, uint8_t* data);
xring_buffer_status_t xring_buffer_put_multiple(xring_buffer_t* rb, const uint8_t* data, uint32_t length, uint32_t* written);
xring_buffer_status_t xring_buffer_get_multiple(xring_buffer_t* rb, uint8_t* data, uint32_t length, uint32_t* read);
xring_buffer_status_t xring_buffer_peek(xring_buffer_t* rb, uint8_t* data, uint32_t offset);
xring_buffer_status_t xring_buffer_peek_multiple(xring_buffer_t* rb, uint8_t* data, uint32_t offset, uint32_t length);
uint32_t xring_buffer_get_count(const xring_buffer_t* rb);
uint32_t xring_buffer_get_free_space(const xring_buffer_t* rb);
uint8_t xring_buffer_is_empty(const xring_buffer_t* rb);
uint8_t xring_buffer_is_full(const xring_buffer_t* rb);
xring_buffer_status_t xring_buffer_flush(xring_buffer_t* rb);
xring_buffer_status_t xring_buffer_get_stats(const xring_buffer_t* rb, xring_buffer_stats_t* stats);
xring_buffer_status_t xring_buffer_reset_stats(xring_buffer_t* rb);

#endif // XRING_BUFFER_H