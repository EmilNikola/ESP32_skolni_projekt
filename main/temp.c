#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"
#include "esp_err.h"

static const char *TAG_TEMP = "TEMP";

/* Module-level handle: if non-NULL the sensor is already configured. */
static temperature_sensor_handle_t s_temp_sensor = NULL;

void teplota_rizek(void)
{
    esp_err_t err;

    /* Configure/install once on first use; subsequent calls reuse the handle. */
    if (s_temp_sensor == NULL) {
        temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
        err = temperature_sensor_install(&temp_sensor_config, &s_temp_sensor);
        if (err != ESP_OK) {
            ESP_LOGI(TAG_TEMP, "temperature_sensor_install failed: %s", esp_err_to_name(err));
            s_temp_sensor = NULL;
            return;
        }
        err = temperature_sensor_enable(s_temp_sensor);
        if (err != ESP_OK) {
            ESP_LOGI(TAG_TEMP, "temperature_sensor_enable failed: %s", esp_err_to_name(err));
            temperature_sensor_uninstall(s_temp_sensor);
            s_temp_sensor = NULL;
            return;
        }
    }

    float tsens_value;
    err = temperature_sensor_get_celsius(s_temp_sensor, &tsens_value);
    if (err != ESP_OK) {
        ESP_LOGI(TAG_TEMP, "temperature_sensor_get_celsius failed: %s", esp_err_to_name(err));
        return;
    }
    float far = (tsens_value * 9.0f / 5.0f) + 32.0f;
    ESP_LOGI(TAG_TEMP, "Je %.01f °C %.01f °F", tsens_value, far);
}