#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define LED_PIN 12
#define BUTTON_PIN 0
#define DEBOUNCE_TIME_MS 200

bool led_state = false;
volatile bool button_pressed = false;
volatile uint64_t last_interrupt_time = 0;

static void IRAM_ATTR button_isr_handler(void* arg) {
    uint64_t now = esp_timer_get_time();
    if ((now - last_interrupt_time) < (DEBOUNCE_TIME_MS * 1000)) return;
    last_interrupt_time = now;
    int level = gpio_get_level(BUTTON_PIN);
    if (level == 0) button_pressed = true;
}

void app_main(void) {
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&led_config));

    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_ERROR_CHECK(gpio_config(&button_config));

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    while (true) {
        if (button_pressed) {
            button_pressed = false;
            led_state = !led_state;
            gpio_set_level(LED_PIN, led_state);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
