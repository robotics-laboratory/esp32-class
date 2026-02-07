#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN 2
#define BUTTON_PIN 0

bool blink_enabled = true;
bool led_state = false;

void app_main(void) {
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&led_config));
    
    gpio_config_t btn_config = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&btn_config));

    while (true) {
        bool pressed = !gpio_get_level(BUTTON_PIN);

        if (pressed) {
            led_state = !led_state;
            gpio_set_level(LED_PIN, led_state);
        } else {
            gpio_set_level(LED_PIN, 0);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
