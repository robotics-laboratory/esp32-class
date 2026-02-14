### UNCOMMENT ONE LINE BELOW:
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/01_gpio_blink_button.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/02_gpio_button_isr.c)
# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/03_ledc_pwm_simple.c)

idf_component_register(SRCS ${app_sources})
