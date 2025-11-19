/* Prototype for the DAC cosine task so other modules can start it */
#ifndef DAC_COSINE_EXAMPLE_H
#define DAC_COSINE_EXAMPLE_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * Task which runs the DAC cosine example. Create with `xTaskCreate(dac_cosine_task, ...)`.
 * The task sets up two DAC cosine channels and an ADC monitor task, then deletes itself.
 */
void dac_cosine_task(void *arg);

#endif // DAC_COSINE_EXAMPLE_H
