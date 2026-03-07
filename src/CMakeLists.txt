### UNCOMMENT ONE LINE BELOW:
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/01_gpio_blink_button.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/02_gpio_button_isr.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/03_ledc_pwm_simple.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/04_pcnt_encoder.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/05_spi_demo.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/06_uart_demo.c)

idf_component_register(SRCS ${app_sources})
