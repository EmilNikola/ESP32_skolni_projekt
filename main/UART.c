#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_log.h"

#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <time.h>

#include "rand.c"
#include "temp.c"
/**
 * This is an example which echos any data it receives on configured UART back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: configured UART
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below (See Kconfig)
 */

#define ECHO_TEST_TXD (43)
#define ECHO_TEST_RXD (44)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

//#define CONFIG_ESP_CONSOLE_ROM_SERIAL_PORT_NUM 0
#define ECHO_UART_PORT_NUM      (CONFIG_ESP_CONSOLE_ROM_SERIAL_PORT_NUM)
#define ECHO_UART_BAUD_RATE     (CONFIG_ESP_CONSOLE_UART_BAUDRATE)
#define ECHO_TASK_STACK_SIZE    (CONFIG_MAIN_TASK_STACK_SIZE)

#define BUF_SIZE (1024)
struct tm timeinfo;
static uint16_t LED_Period;
static const char *TAG_UART = "UART";
static const char *TAG_UNIX_TIME = "UNIX_TIME";

static void echo_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;

    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        // Write data back to the UART
        //uart_write_bytes(ECHO_UART_PORT_NUM, (const char *) data, len);
        if (len) 
        {
            int len = strlen((char*)data);
            if( len > 4  && strncmp ((char*)data,"PER:", 4) == 0)
            {
                LED_Period = atoi((char*)(data + 4)) * 100;
                printf ("Perioda ledky je %d ms\n", LED_Period);
            }
            if( len >= 8  && strncmp ((char*)data,"UNIXTIME?", 8) == 0)
            {
                time_t now;
                unsigned long epochTime = time(&now); 
                ESP_LOGI("UNIX_TIME", "%ld", epochTime);

            }
            if( len >= 6  && strncmp ((char*)data,"RANDOM?", 6) == 0)
            {
                random_number();
            }
            if( len >= 6  && strncmp ((char*)data,"TEMPERATURE?", 11) == 0)
            {
                teplota_rizek();
            }      
        }
    }
}
