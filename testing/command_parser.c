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

#include "command_parser.h"
#include <string.h>
#include <stdio.h>

static char response[50];

static const supported_command_t commands_registry[] = {
    {"AT+BASICTEST", dummy_test},
    {"AT+USERLEDS=1", user_leds_on},
    {"AT+USERLEDS=0", user_leds_off},
    {"AT+MAYATEST", maya_functionality_test},
    {"AT+TESTANTB10SIGNALS", ant_b10_signals_test},
    {"AT+NINAUARTTEST", nina_uart_test},
    {"AT+MACADDR=", store_mac_addr},
    {"AT+NINABOOTMODE=", nina_boot_mode},
	{"AT+ANTB10BOOTMODE=", antb10_boot_mode},
    {"AT+MAYAUARTTEST", maya_uart_test},
    {"AT+UNIQUEID", unique_id_test},
    {"AT+MAYABUILTINMAC", maya_mac_addr_test},
	{"AT+MCUSWITCHTEST", sw1_button_test}
};

char *parse_command(char *in_str, unsigned int in_length, uint8_t *out_length)
{
    unsigned int num_of_commands = sizeof(commands_registry) / sizeof(commands_registry[0]);

    int i;

    for (i = 0; i < num_of_commands; i++) {
        if (strstr(in_str, commands_registry[i].name) == in_str) {
            commands_registry[i].callback(&in_str[strlen(commands_registry[i].name)], response, out_length);
            return response;
        }
    }

    sprintf(response, "UNKNOWN_COMMAND\r\n");
    *out_length =  strlen(response);
    return response;
}
