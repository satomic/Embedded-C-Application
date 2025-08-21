#ifndef XMEM_POOL_H
#define XMEM_POOL_H

#include <stdint.h>

typedef enum {
    XMEM_POOL_STATUS_OK = 0,
    XMEM_POOL_STATUS_FULL = 1,
    XMEM_POOL_STATUS_EMPTY = 2,
    XMEM_POOL_STATUS_INVALID_PARAM = 3,
    XMEM_POOL_STATUS_CORRUPTION = 4
} xmem_pool_status_t;

typedef struct {
    void* pool_start;
    uint32_t block_size;
    uint32_t block_count;
    uint32_t alignment;
    uint8_t enable_debug;
    uint8_t enable_poison;
} xmem_pool_config_t;

typedef struct {
    uint32_t total_blocks;
    uint32_t free_blocks;
    uint32_t used_blocks;
    uint32_t peak_usage;
    uint32_t allocation_count;
    uint32_t deallocation_count;
    uint32_t corruption_count;
} xmem_pool_stats_t;

typedef void* xmem_pool_handle_t;

xmem_pool_handle_t xmem_pool_create(const xmem_pool_config_t* config);
xmem_pool_status_t xmem_pool_destroy(xmem_pool_handle_t pool);
void* xmem_pool_alloc(xmem_pool_handle_t pool);
xmem_pool_status_t xmem_pool_free(xmem_pool_handle_t pool, void* ptr);
xmem_pool_status_t xmem_pool_get_stats(xmem_pool_handle_t pool, xmem_pool_stats_t* stats);
xmem_pool_status_t xmem_pool_reset(xmem_pool_handle_t pool);
uint8_t xmem_pool_is_valid_pointer(xmem_pool_handle_t pool, void* ptr);
xmem_pool_status_t xmem_pool_check_integrity(xmem_pool_handle_t pool);
uint32_t xmem_pool_get_free_count(xmem_pool_handle_t pool);
uint32_t xmem_pool_get_used_count(xmem_pool_handle_t pool);
void* xmem_pool_alloc_aligned(xmem_pool_handle_t pool, uint32_t alignment);
xmem_pool_status_t xmem_pool_defragment(xmem_pool_handle_t pool);

#endif // XMEM_POOL_H