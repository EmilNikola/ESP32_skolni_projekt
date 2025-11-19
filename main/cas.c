
#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_netif_sntp.h"
#include "lwip/ip_addr.h"
#include "esp_sntp.h"

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 48
#endif

static const char *TAG_TIME = "TIME";
void obtain_time(void);

void print_time_periodically(void *pvParameters)
{
    char strftime_buf[64];
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGI("cas", "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time();
        // update 'now' variable with current time
        time(&now);
    }
    while (1) {
        setenv("TZ", "CST-1", 1);
        tzset();
        time(&now);
        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
        ESP_LOGI(TAG_TIME, " %s", strftime_buf);
        vTaskDelay(pdMS_TO_TICKS(5000)); // print every 5 seconds
    }
}

void obtain_time(void)
{
    //ESP_ERROR_CHECK(example_connect());
    ESP_LOGI(TAG_TIME, "Initializing and starting SNTP");

    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(CONFIG_SNTP_TIME_SERVER);

    esp_netif_sntp_init(&config);

    // wait for time to be set

    int retry = 0;
    const int retry_count = 15;
    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count) {
        ESP_LOGI(TAG_TIME, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    }
}

