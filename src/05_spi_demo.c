#include "freertos/FreeRTOS.h"
#include "driver/spi_master.h"
#include "esp_system.h"
#include <string.h>

void app_main(void) {
    spi_bus_config_t buscfg = {
        .miso_io_num = 19,
        .mosi_io_num = 23,
        .sclk_io_num = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 8
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = 5,
        .queue_size = 1,
    };

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    spi_device_handle_t device;
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &device));

    uint8_t counter = 0;
    while (true) {
        spi_transaction_t tr;
        memset(&tr, 0, sizeof(tr));
        tr.length = 8;
        tr.tx_buffer = &counter;
        tr.flags = SPI_TRANS_USE_RXDATA;
        spi_device_acquire_bus(device, portMAX_DELAY);
        ESP_ERROR_CHECK(spi_device_polling_transmit(device, &tr));
        spi_device_release_bus(device);

        uint8_t spi_counter = *(uint8_t*) tr.rx_data;
        printf("counter: %d\n", spi_counter);
        counter++;
        vTaskDelay(10);
    }
}
