#include <stdio.h>
#include "esp_random.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "bootloader_random.h"

static const char *TAG_RANDOM = "RANDOM";

 void random_number(void) {
    bootloader_random_enable();

    uint32_t high = esp_random();
    uint32_t low = esp_random();
    uint64_t num = ((uint64_t)high << 32) | low;
    ESP_LOGI(TAG_RANDOM, " Random number: 0x%016llX", num);

    bootloader_random_disable();
}
    

