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

#ifndef HOST_UART_H_
#define HOST_UART_H_

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
#include "command_parser.h"
#include <app/bip_tasks.h>

#define COMMAND_UART            LPUART1
#define COMMAND_UART_IRQn       LPUART1_IRQn
#define COMMAND_UART_CLK_FREQ   BOARD_DebugConsoleSrcFreq()


/**
 * Creates the task that handles the UART connection with the testing PC
 */
void create_host_uart_thread(void);

#endif /* HOST_UART_H_ */
