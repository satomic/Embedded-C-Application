#ifndef XLCD_DISPLAY_H
#define XLCD_DISPLAY_H

#include <stdint.h>

typedef enum {
    XLCD_COLOR_DEPTH_1BIT = 1,
    XLCD_COLOR_DEPTH_8BIT = 8,
    XLCD_COLOR_DEPTH_16BIT = 16,
    XLCD_COLOR_DEPTH_24BIT = 24
} xlcd_color_depth_t;

typedef enum {
    XLCD_ROTATION_0 = 0,
    XLCD_ROTATION_90 = 1,
    XLCD_ROTATION_180 = 2,
    XLCD_ROTATION_270 = 3
} xlcd_rotation_t;

typedef enum {
    XLCD_FONT_SMALL = 0,
    XLCD_FONT_MEDIUM = 1,
    XLCD_FONT_LARGE = 2,
    XLCD_FONT_CUSTOM = 3
} xlcd_font_size_t;

typedef struct {
    uint16_t x;
    uint16_t y;
} xlcd_point_t;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} xlcd_rect_t;

typedef struct {
    uint32_t spi_instance;
    uint32_t cs_pin;
    uint32_t dc_pin;
    uint32_t reset_pin;
    uint32_t backlight_pin;
    uint16_t width;
    uint16_t height;
    xlcd_color_depth_t color_depth;
    xlcd_rotation_t rotation;
    uint8_t mirror_x;
    uint8_t mirror_y;
} xlcd_config_t;

typedef uint32_t xlcd_color_t;

int xlcd_init(const xlcd_config_t* config);
int xlcd_deinit(void);
int xlcd_clear_screen(xlcd_color_t color);
int xlcd_set_pixel(uint16_t x, uint16_t y, xlcd_color_t color);
xlcd_color_t xlcd_get_pixel(uint16_t x, uint16_t y);
int xlcd_draw_line(xlcd_point_t start, xlcd_point_t end, xlcd_color_t color, uint8_t thickness);
int xlcd_draw_rectangle(xlcd_rect_t rect, xlcd_color_t color, uint8_t filled);
int xlcd_draw_circle(xlcd_point_t center, uint16_t radius, xlcd_color_t color, uint8_t filled);
int xlcd_draw_text(xlcd_point_t position, const char* text, xlcd_font_size_t font, xlcd_color_t color);
int xlcd_draw_bitmap(xlcd_point_t position, const uint8_t* bitmap, uint16_t width, uint16_t height);
int xlcd_set_backlight(uint8_t brightness_percent);
uint8_t xlcd_get_backlight(void);
int xlcd_set_contrast(uint8_t contrast_percent);
int xlcd_set_rotation(xlcd_rotation_t rotation);
xlcd_rotation_t xlcd_get_rotation(void);
int xlcd_copy_region(xlcd_rect_t src, xlcd_point_t dst);
int xlcd_scroll_region(xlcd_rect_t region, int16_t dx, int16_t dy);
int xlcd_invert_region(xlcd_rect_t region);
int xlcd_get_display_info(uint16_t* width, uint16_t* height, xlcd_color_depth_t* depth);

#endif // XLCD_DISPLAY_H