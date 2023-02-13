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

#ifndef BIP_NINA_UART_THREAD_H
#define BIP_NINA_UART_THREAD_H

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include <app/bip_tasks.h>


#define ANT_B10_UART            LPUART2
#define ANT_B10_UART_IRQn       LPUART2_IRQn
#define ANT_B10_UART_CLK_FREQ   BOARD_DebugConsoleSrcFreq()

#define ONBOARD_NINA_UART           LPUART3
#define ONBOARD_NINA_UART_IRQn      LPUART3_IRQn
#define ONBOARD_NINA_UART_CLK_FREQ  BOARD_DebugConsoleSrcFreq()

#define uart_task_PRIORITY (configMAX_PRIORITIES - 1)


/**
 * Creates the task that is responsible to handle the UART connection to the NINA module
 * Every time that a complete message arrives, it is pushed to the measurements queue
 */
void create_nina_uart_thread(void);

bool nina_send_at(uint8_t* cmd, uint32_t len);

#endif
