# Internal Modules CMakeLists.txt

# HAL (Hardware Abstraction Layer) modules
add_library(xgpio_hal STATIC hal/xgpio_hal.c)
target_include_directories(xgpio_hal PUBLIC .)

add_library(xspi_hal INTERFACE)
target_include_directories(xspi_hal INTERFACE .)

add_library(xi2c_hal INTERFACE)
target_include_directories(xi2c_hal INTERFACE .)

add_library(xuart_hal INTERFACE)
target_include_directories(xuart_hal INTERFACE .)

# Sensor modules
add_library(xtemp_sensor INTERFACE)
target_include_directories(xtemp_sensor INTERFACE .)
target_link_libraries(xtemp_sensor INTERFACE xi2c_hal)

add_library(xaccel_sensor INTERFACE)
target_include_directories(xaccel_sensor INTERFACE .)
target_link_libraries(xaccel_sensor INTERFACE xi2c_hal)

add_library(xgyro_sensor INTERFACE)
target_include_directories(xgyro_sensor INTERFACE .)
target_link_libraries(xgyro_sensor INTERFACE xspi_hal)

# Memory management modules
add_library(xmem_pool INTERFACE)
target_include_directories(xmem_pool INTERFACE .)

add_library(xring_buffer INTERFACE)
target_include_directories(xring_buffer INTERFACE .)

add_library(xdma_manager INTERFACE)
target_include_directories(xdma_manager INTERFACE .)

# Protocol modules
add_library(xcan_protocol INTERFACE)
target_include_directories(xcan_protocol INTERFACE .)

add_library(xmodbus_protocol INTERFACE)
target_include_directories(xmodbus_protocol INTERFACE .)
target_link_libraries(xmodbus_protocol INTERFACE xuart_hal)

add_library(xproprietary_protocol INTERFACE)
target_include_directories(xproprietary_protocol INTERFACE .)

# Scheduler modules
add_library(xrtos_scheduler INTERFACE)
target_include_directories(xrtos_scheduler INTERFACE .)

add_library(xhw_timer INTERFACE)
target_include_directories(xhw_timer INTERFACE .)

add_library(xsoft_timer INTERFACE)
target_include_directories(xsoft_timer INTERFACE .)

# Display module
add_library(xlcd_display INTERFACE)
target_include_directories(xlcd_display INTERFACE .)
target_link_libraries(xlcd_display INTERFACE xspi_hal xgpio_hal)

# Power management module
add_library(xpower_mgmt INTERFACE)
target_include_directories(xpower_mgmt INTERFACE .)

# Crypto module
add_library(xcrypto_engine INTERFACE)
target_include_directories(xcrypto_engine INTERFACE .)

# Install headers
install(DIRECTORY hal/ DESTINATION include/internal_modules/hal
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY sensors/ DESTINATION include/internal_modules/sensors
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY memory/ DESTINATION include/internal_modules/memory
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY protocols/ DESTINATION include/internal_modules/protocols
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY scheduler/ DESTINATION include/internal_modules/scheduler
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY display/ DESTINATION include/internal_modules/display
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY power/ DESTINATION include/internal_modules/power
    FILES_MATCHING PATTERN "*.h")
install(DIRECTORY crypto/ DESTINATION include/internal_modules/crypto
    FILES_MATCHING PATTERN "*.h")