idf_component_register(SRCS "UART.c" "cas.c" "led.c" "station_example_main.c"
                    PRIV_REQUIRES esp_wifi bootloader_support  nvs_flash driver esp_driver_tsens
                    esp_driver_dac esp_adc esp_driver_dac esp_adc
                    INCLUDE_DIRS ".")
