#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include <stdio.h>


#include "driver/gpio.h"

#include "led_strip.h"
#include "sdkconfig.h"

#include "lwip/err.h"
#include "lwip/sys.h"


static led_strip_handle_t led_strip;  
static uint16_t LED_Period = 500;

static const char *TAG_LED = "LED";

static void configure_led(void)
{
    ESP_LOGI(TAG_LED, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = 45,
        .max_leds = 1, // at least one LED on board
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}

void blink_led(void *pvParameters)
{
    uint8_t s_led_state = 0;
    configure_led();
    while (1){
    /* If the addressable LED is enabled */
    if (s_led_state) {
        /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
        led_strip_set_pixel(led_strip, 0, 16, 16, 16);
        /* Refresh the strip to send data */
        led_strip_refresh(led_strip);
    } else {
        /* Set all LED off to clear all pixels */
        led_strip_clear(led_strip);
    }
       // ESP_LOGI(LED, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");

        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(LED_Period/ portTICK_PERIOD_MS); //tohle se bude menit k zmene blikani
    }
}                                                 
