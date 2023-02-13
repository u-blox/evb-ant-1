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

#include <stdio.h>
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1062.h"
#include "fsl_debug_console.h"
#include <wm_net.h>
#include <host_uart.h>
#include <app/bip_configuration.h>
#include <app/bip_ethernet_interface.h>
#include <app/bip_general_purpose_thread.h>
#include <app/bip_http_server.h>
#include <app/bip_measurements_queue.h>
#include <app/bip_non_volatile_storage.h>
#include <app/bip_nina_uart_thread.h>
#include <app/bip_position_engine_link.h>
#include <app/bip_wifi_setup.h>

/*
 *   Application entry point.
 */
int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /* initialize flash memory or non volatile storage */
    initialize_flash();
    load_configuration_from_flash();

    /* initialize the tcp/ip thread separately */
    net_ipv4stack_init();

    /* Initialize the wifi interface */
    create_wifi_thread();

    /* Initialize the ethernet interface */
    if (get_configuration()->enetEnabled) {
        ethernet_init();
    }

    /* Initialize the queue that holds the position measurements */
    measurements_queue_init();

    /* Initialize the thread that receives the UART measurements from nina */
    create_nina_uart_thread();

    /* Initialize the thread that relays the measurements found in the queue, to the position engine */
    position_engine_link_init();

    /* Initialize the http server for reading / writing the configuration */
    create_http_server_thread();

    /* Initialize a general purpose thread that checks gpios etc */
    create_general_purpose_thread();

    /* Initialize the thread for the functional testing */
    create_host_uart_thread();

    /* Start the scheduler */
    vTaskStartScheduler();

    /* Will not get here unless a task calls vTaskEndScheduler () */
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while (1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
