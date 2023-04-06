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

#include <stdint.h>
#include <stdio.h>

#ifndef FUNCTIONAL_TESTS_H
#define FUNCTIONAL_TESTS_H


#define TEST_TP31_SCK_PIN   31
#define TEST_TP33_CS_PIN    28
#define TEST_TP39_TX_PIN    19
#define TEST_TP40_RX_PIN    18
#define TEST_TP35_RTS_PIN   16
#define TEST_TP37_CTS_PIN   17
#define TEST_TP7_MISO_PIN   29
#define TEST_TP12_MOSI_PIN  30
#define TEST_TP34_GPIO1_PIN 26
#define TEST_TP32_GPIO2_PIN 27
#define TEST_TP21_GPIO3_PIN 24
#define TEST_TP38_RST_PIN   25
#define TEST_TP9_SW1_PIN    28
#define TEST_TP36_SW2_PIN   0
#define TEST_TP71_MCUSW_PIN 17

#define TEST_TP31_SCK_GPIO      GPIO1
#define TEST_TP33_CS_GPIO       GPIO1
#define TEST_TP39_TX_GPIO       GPIO1
#define TEST_TP40_RX_GPIO       GPIO1
#define TEST_TP35_RTS_GPIO      GPIO1
#define TEST_TP37_CTS_GPIO      GPIO1
#define TEST_TP7_MISO_GPIO      GPIO1
#define TEST_TP12_MOSI_GPIO     GPIO1
#define TEST_TP34_GPIO1_GPIO    GPIO1
#define TEST_TP32_GPIO2_GPIO    GPIO1
#define TEST_TP21_GPIO3_GPIO    GPIO1
#define TEST_TP38_RST_GPIO      GPIO1
#define TEST_TP9_SW1_GPIO       GPIO7
#define TEST_TP36_SW2_GPIO      GPIO1
#define TEST_TP71_MCUSW_PORT 	GPIO7

#define BT_OP(ogf, ocf)                         ((ocf) | ((ogf) << 10))
#define BT_OGF_VS                               0x3f

#define RETURN_OK(out_buff_p,out_len_p)    do {sprintf(out_buff_p,"OK\r\n"); *out_len_p = 4; return;} while(0)
#define RETURN_FAIL(out_buff_p,out_len_p)  do {sprintf(out_buff_p,"FAIL\r\n"); *out_len_p = 6; return;} while(0)

typedef void (*command_callback_t) (const char *, char *, uint8_t *);

/**
 * All the functional test functions
 */
void dummy_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void user_leds_on(const char *payload, char *outputBuffer, uint8_t *outputLength);

void user_leds_off(const char *payload, char *outputBuffer, uint8_t *outputLength);

void maya_functionality_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void ant_b10_signals_test(const char *payload,  char *outputBuffer, uint8_t *outputLength);

void nina_uart_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void store_mac_addr(const char *payload, char *outputBuffer, uint8_t *outputLength);

void nina_boot_mode(const char *payload, char *outputBuffer, uint8_t *outputLength);

void antb10_boot_mode(const char *payload, char *outputBuffer, uint8_t *outputLength);

void maya_uart_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void unique_id_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void maya_mac_addr_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void sw1_button_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void ethernet_diagnostics_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void toggle_wdog_pin_test(const char *payload, char *outputBuffer, uint8_t *outputLength);

void general_gpio_set(const char *payload, char *outputBuffer, uint8_t *outputLength);

void general_gpio_get(const char *payload, char *outputBuffer, uint8_t *outputLength);

#endif
