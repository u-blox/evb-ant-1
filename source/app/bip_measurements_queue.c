/*
 * Copyright 2023 u-blox
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <app/bip_measurements_queue.h>

static QueueHandle_t measurements_queue = NULL;

int measurements_queue_init(void)
{
    measurements_queue = xQueueCreate(MEASUREMENTS_QUEUE_LENGTH, sizeof(measurement_t));

    if (measurements_queue != NULL) {
        vQueueAddToRegistry(measurements_queue, "measQ");
        return 0;
    }

    return 1;
}

void add_measurement_to_queue(measurement_t *m)
{
    xQueueSend(measurements_queue, m, 0);
}

int get_measurement_from_queue(measurement_t *m_out)
{
    if (xQueueReceive(measurements_queue, m_out, portMAX_DELAY) != pdTRUE) {
        return 1;
    }

    return 0;
}
