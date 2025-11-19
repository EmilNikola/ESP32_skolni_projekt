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


#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_netif_sntp.h"
#include "lwip/ip_addr.h"
#include "esp_sntp.h"

#include "esp_mac.h"

#include "driver/uart.h"

#include "driver/temperature_sensor.h"

#include "driver/dac_cosine.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_check.h"

#include "led.c"
#include "wifi.c"
#include "cas.c"
#include "UART.c"
#include "MAC.c"
#include "dac_cosine.c"


void app_main(void)
{
    //disables all tags
    esp_log_level_set("*", ESP_LOG_NONE);
    //allows only tasks specified by me
    esp_log_level_set("MAC", ESP_LOG_INFO);
    esp_log_level_set("WIFI", ESP_LOG_INFO);
    esp_log_level_set("LED", ESP_LOG_INFO);
    esp_log_level_set("TIME", ESP_LOG_INFO);
    esp_log_level_set("UART", ESP_LOG_INFO);
    esp_log_level_set("TEMP", ESP_LOG_INFO);
    esp_log_level_set("RANDOM", ESP_LOG_INFO);
    esp_log_level_set("UNIX_TIME", ESP_LOG_INFO);

    //reads MAC adress at start
    mac(); 
    //connects to wifi
    wifi_con();

    //makes the LED blink
    xTaskCreate( blink_led, "LED", 2048, NULL, 1, NULL ); 
    //starts time synchronization and periodic time printing
    xTaskCreate(print_time_periodically, "time_task", 2048, NULL, 1, NULL);
    //handles user input
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 1, NULL);

    //generates wave on pin 17 and 18
    cosine();
}
