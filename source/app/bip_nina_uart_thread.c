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

#include <app/bip_configuration.h>
#include <app/bip_measurements_queue.h>
#include <app/bip_nina_uart_thread.h>

static void uart_task(void *pvParameters);

static uint8_t background_buffer[MEASUREMENT_MESSAGE_LENGTH];
static uint8_t recv_buffer[MEASUREMENT_MESSAGE_LENGTH];

static lpuart_rtos_handle_t handle;
static struct _lpuart_handle t_handle;

static lpuart_rtos_config_t lpuart_config = {
    .baudrate    = 115200,
    .parity      = kLPUART_ParityDisabled,
    .stopbits    = kLPUART_OneStopBit,
    .buffer      = background_buffer,
    .buffer_size = sizeof(background_buffer),
    .enableRxRTS = true,
    .enableTxCTS = true,
};

void create_nina_uart_thread(void)
{
    if (get_configuration()->useOnboardNina) {
        GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 1U);
        lpuart_config.srcclk = ONBOARD_NINA_UART_CLK_FREQ;
        lpuart_config.base   = ONBOARD_NINA_UART;
        NVIC_SetPriority(ONBOARD_NINA_UART_IRQn, 5);
    } else {
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_RST_GPIO, BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN, 1U);
        lpuart_config.srcclk = ANT_B10_UART_CLK_FREQ;
        lpuart_config.base   = ANT_B10_UART;
        NVIC_SetPriority(ANT_B10_UART_IRQn, 5);
    }

    if (xTaskCreate(uart_task, NINA_UART_TASK_NAME, NINA_UART_TASK_STACK_SIZE, NULL, NINA_UART_TASK_PRIORITY,
            NULL) != pdPASS) {
        PRINTF("NINA uart Task creation failed!.\r\n");
        while (1)
            ;
    }
}

bool nina_send_at(uint8_t* cmd, uint32_t len)
{
    int ret;
    PRINTF("bip_nina_send_at: %s\n", cmd);
    ret = LPUART_RTOS_Send(&handle, cmd, len);
}

static void uart_task(void *pvParameters)
{
    int error;
    size_t n = 0;
    uint8_t *current_byte_pointer = recv_buffer;
    memset(recv_buffer, 0, sizeof(recv_buffer));

    if (kStatus_Success != LPUART_RTOS_Init(&handle, &t_handle, &lpuart_config)) {
        vTaskSuspend(NULL);
    }

    do {
        error = LPUART_RTOS_Receive(&handle, current_byte_pointer, 1, &n);
        if (error == kStatus_LPUART_RxHardwareOverrun) {
            vTaskSuspend(NULL);
        }
        if (error == kStatus_LPUART_RxRingBufferOverrun) {
            vTaskSuspend(NULL);
        }
        if (n > 0) {
            if (((*current_byte_pointer) == (uint8_t)'\n') ||
                (current_byte_pointer - recv_buffer == MEASUREMENT_MESSAGE_LENGTH - 1)) {
                if (current_byte_pointer - recv_buffer > 2) {
                    add_measurement_to_queue((measurement_t *) recv_buffer);
                }
                memset(recv_buffer, 0, sizeof(recv_buffer));
                current_byte_pointer = recv_buffer;
            } else {
                current_byte_pointer++;
            }
        }
    } while (1);

    LPUART_RTOS_Deinit(&handle);
    vTaskSuspend(NULL);
}
