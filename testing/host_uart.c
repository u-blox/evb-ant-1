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

#include "host_uart.h"
#include <wm_os.h>
#include <app/bip_version.h>

static void host_uart_task(void *pvParameters);

static char startup_message[] = "+STARTUP EVB-ANT-1 v" FIRMWARE_VERSION_STR "\r\n";
static uint8_t background_buffer[30];
static uint8_t recv_buffer[30];

static lpuart_rtos_handle_t handle;
static struct _lpuart_handle t_handle;

static lpuart_rtos_config_t lpuart_config = {
    .baudrate    = 115200,
    .parity      = kLPUART_ParityDisabled,
    .stopbits    = kLPUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
    .enableRxRTS = false,
    .enableTxCTS = false,
};

void create_host_uart_thread(void)
{

    lpuart_config.srcclk = COMMAND_UART_CLK_FREQ;
    lpuart_config.base   = COMMAND_UART;
    NVIC_SetPriority(COMMAND_UART_IRQn, 5);

    if (xTaskCreate(host_uart_task, CMD_LISTERNER_TASK_NAME, CMD_LISTENER_TASK_STACK_SIZE, NULL, CMD_LISTENER_TASK_PRIORITY,
                    NULL) != pdPASS) {
        PRINTF("Command parser Task creation failed!.\r\n");
        while (1)
            ;
    }
}

static void host_uart_task(void *pvParameters)
{
    int error;
    size_t n = 0;
    uint8_t *current_byte_pointer = recv_buffer;
    memset(recv_buffer, 0, sizeof(recv_buffer));


    if (kStatus_Success != LPUART_RTOS_Init(&handle, &t_handle, &lpuart_config)) {
        vTaskSuspend(NULL);
    }

    LPUART_RTOS_Send(&handle, startup_message, strlen(startup_message));

    do {
        error = LPUART_RTOS_Receive(&handle, current_byte_pointer, 1, &n);
        if (error == kStatus_LPUART_RxHardwareOverrun) {
            vTaskSuspend(NULL);
        }
        if (error == kStatus_LPUART_RxRingBufferOverrun) {
            vTaskSuspend(NULL);
        }
        if (n > 0) {
            if ((*current_byte_pointer) == (uint8_t)'\n') {
                if (current_byte_pointer - recv_buffer > 2) {

                    uint8_t response_length;
                    char *response = parse_command(recv_buffer, (current_byte_pointer - recv_buffer) + 1, &response_length);
                    LPUART_RTOS_Send(&handle, response, response_length);

                }
                current_byte_pointer = recv_buffer;
            } else {
                current_byte_pointer++;
                if (current_byte_pointer - recv_buffer >= sizeof(recv_buffer)) {
                    current_byte_pointer  = recv_buffer;
                }
            }
        }
    } while (1);

    LPUART_RTOS_Deinit(&handle);
    vTaskSuspend(NULL);
}
