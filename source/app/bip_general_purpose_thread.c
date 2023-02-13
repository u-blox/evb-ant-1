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

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include <app/bip_general_purpose_thread.h>
#include "board.h"
#include "pin_mux.h"
#include <wm_os.h>

#include "wlan.h"

TaskHandle_t general_purpose_task_handle = NULL;

static void general_purpose_task(void *pvParameters)
{
    while (1) {
        if (is_sta_connected()) {
            GPIO_PinWrite(BOARD_INITPINS_USER_LED_01_GPIO, BOARD_INITPINS_USER_LED_01_GPIO_PIN, 0U);
        } else {
            GPIO_PinWrite(BOARD_INITPINS_USER_LED_01_GPIO, BOARD_INITPINS_USER_LED_01_GPIO_PIN, 1U);
        }

        os_thread_sleep(os_msec_to_ticks(1000));
    }

}

void create_general_purpose_thread(void)
{
    xTaskCreate(general_purpose_task, GEN_PURPOSE_TASK_NAME, GEN_PURPOSE_TASK_STACK_SIZE, NULL, GEN_PURPOSE_TASK_PRIORITY,
                &general_purpose_task_handle);
    configASSERT( general_purpose_task_handle );
}
