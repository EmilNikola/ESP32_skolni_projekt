#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32S2 Skolni Projekt");
    ESP_LOGI(TAG, "Chip info:");
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "Model: %s", CONFIG_IDF_TARGET);
    ESP_LOGI(TAG, "Cores: %d", chip_info.cores);
    ESP_LOGI(TAG, "Silicon revision: %d", chip_info.revision);
    ESP_LOGI(TAG, "Free heap: %ld bytes", esp_get_free_heap_size());
    
    ESP_LOGI(TAG, "Starting main loop...");
    
    while (1) {
        ESP_LOGI(TAG, "Hello from ESP32S2!");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
