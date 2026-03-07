#include <stdio.h>
#include "driver/uart.h"
#include "driver/gpio.h"

#define TXD_PIN GPIO_NUM_1
#define RXD_PIN GPIO_NUM_3
#define UART_PORT UART_NUM_0
#define UART_BAUD_RATE 115200
#define BUF_SIZE 1024

void app_main(void) {
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (true) {
        int len = uart_read_bytes(UART_PORT, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        uart_write_bytes(UART_PORT, (const char *) data, len);
        if (len) data[len] = '\0';
    }
}
