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
#include <app/bip_nina_gpios.h>
#include "board.h"
#include "pin_mux.h"
#include <wm_os.h>


typedef enum {
    NINA_BUTTONS_RESET,
	NINA_BUTTONS_SWITCH_1,
    NINA_BUTTONS_SWITCH_2
} nina_buttons_t;


static void push_nina_button(nina_buttons_t button)
{

    GPIO_Type *button_gpio_type;
    int button_gpio_pin;

    if (get_configuration()->useOnboardNina) {
        switch (button) {
            case NINA_BUTTONS_RESET:
                button_gpio_type = BOARD_INITPINS_NINA_RST_GPIO;
                button_gpio_pin = BOARD_INITPINS_NINA_RST_GPIO_PIN;
                break;
            case NINA_BUTTONS_SWITCH_1:
                button_gpio_type = BOARD_INITPINS_NINA_SW1_GPIO;
                button_gpio_pin = BOARD_INITPINS_NINA_SW1_GPIO_PIN;
                break;
            case NINA_BUTTONS_SWITCH_2:
                button_gpio_type = BOARD_INITPINS_NINA_SW2_GPIO;
                button_gpio_pin = BOARD_INITPINS_NINA_SW2_GPIO_PIN;
                break;
        }
    } else {
        switch (button) {
            case NINA_BUTTONS_RESET:
                button_gpio_type = BOARD_INITPINS_ANT_BXX_RST_GPIO;
                button_gpio_pin = BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN;
                break;
            case NINA_BUTTONS_SWITCH_1:
                button_gpio_type = BOARD_INITPINS_ANT_BXX_SW1_GPIO;
                button_gpio_pin = BOARD_INITPINS_ANT_BXX_SW1_GPIO_PIN;
                break;
            case NINA_BUTTONS_SWITCH_2:
                button_gpio_type = BOARD_INITPINS_ANT_BXX_SW2_GPIO;
                button_gpio_pin = BOARD_INITPINS_ANT_BXX_SW2_GPIO_PIN;
                break;
        }
    }

    GPIO_PinWrite(button_gpio_type, button_gpio_pin, 0U);
    os_thread_sleep(os_msec_to_ticks(100));
    GPIO_PinWrite(button_gpio_type, button_gpio_pin, 1U);
}

void nina_apply_reset(void)
{
    push_nina_button(NINA_BUTTONS_RESET);
}

void nina_apply_sw1(void)
{
    push_nina_button(NINA_BUTTONS_SWITCH_1);
}

void nina_apply_sw2(void)
{
    push_nina_button(NINA_BUTTONS_SWITCH_2);
}
