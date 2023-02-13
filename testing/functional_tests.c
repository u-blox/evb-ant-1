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

#include "fsl_gpio.h"
#include "functional_tests.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"
#include "fsl_lpuart_freertos.h"
#include "fsl_lpuart.h"
#include <wm_os.h>
#include <app/bip_general_purpose_thread.h>
#include <app/bip_nina_uart_thread.h>
#include <app/bip_otp_fuses.h>
#include <app/bip_wifi_setup.h>

static UART_HANDLE_DEFINE(s_controllerHciUartHandle);

void dummy_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    RETURN_OK(outputBuffer, outputLength);
}

void user_leds_on(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    if ( general_purpose_task_handle != NULL ) {
        vTaskSuspend(general_purpose_task_handle);
    }
    GPIO_PinWrite(BOARD_INITPINS_USER_LED_01_GPIO, BOARD_INITPINS_USER_LED_01_GPIO_PIN, 0U);
    GPIO_PinWrite(BOARD_INITPINS_USER_LED_02_GPIO, BOARD_INITPINS_USER_LED_02_GPIO_PIN, 0U);

    RETURN_OK(outputBuffer, outputLength);
}

void user_leds_off(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    if ( general_purpose_task_handle != NULL ) {
        vTaskResume(general_purpose_task_handle);
    }
    GPIO_PinWrite(BOARD_INITPINS_USER_LED_01_GPIO, BOARD_INITPINS_USER_LED_01_GPIO_PIN, 1U);
    GPIO_PinWrite(BOARD_INITPINS_USER_LED_02_GPIO, BOARD_INITPINS_USER_LED_02_GPIO_PIN, 1U);

    RETURN_OK(outputBuffer, outputLength);
}

void maya_functionality_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    if (wifi_is_initialized()) {
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }
}

bool verify_ant_b10_gpio_pattern(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g)
{

    GPIO_PinWrite(TEST_TP21_GPIO3_GPIO, TEST_TP21_GPIO3_PIN,    a);
    GPIO_PinWrite(TEST_TP33_CS_GPIO, TEST_TP33_CS_PIN,          b);
    GPIO_PinWrite(TEST_TP7_MISO_GPIO, TEST_TP7_MISO_PIN,        c);
    GPIO_PinWrite(TEST_TP37_CTS_GPIO, TEST_TP37_CTS_PIN,        d);
    GPIO_PinWrite(TEST_TP35_RTS_GPIO, TEST_TP35_RTS_PIN,        e);
    GPIO_PinWrite(TEST_TP39_TX_GPIO, TEST_TP39_TX_PIN,          f);
    GPIO_PinWrite(TEST_TP34_GPIO1_GPIO, TEST_TP34_GPIO1_PIN,    g);

    if ((GPIO_PinRead(TEST_TP38_RST_GPIO, TEST_TP38_RST_PIN) !=     a) ||
        (GPIO_PinRead(TEST_TP40_RX_GPIO, TEST_TP40_RX_PIN) !=       b) ||
        (GPIO_PinRead(TEST_TP36_SW2_GPIO, TEST_TP36_SW2_PIN) !=     c) ||
        (GPIO_PinRead(TEST_TP31_SCK_GPIO, TEST_TP31_SCK_PIN) !=     d) ||
        (GPIO_PinRead(TEST_TP32_GPIO2_GPIO, TEST_TP32_GPIO2_PIN) != e) ||
        (GPIO_PinRead(TEST_TP12_MOSI_GPIO, TEST_TP12_MOSI_PIN) !=   f) ||
        (GPIO_PinRead(TEST_TP9_SW1_GPIO, TEST_TP9_SW1_PIN) !=       g)) {
        return false;
    } else {
        return true;
    }
}

/*      ant_b10_signals_test checks the ANT-B10 signals
 *      The tests requires connection between the following test points
 *      TP21 - TP38
 *      TP33 - TP40
 *      TP7  - TP36
 *      TP37 - TP31
 *      TP35 - TP32
 *      TP39 - TP12
 *      TP34 - TP9
 *
 *      The pins that correspond to the left column of test points are set as output and
 *      the pins that correspond to the right column of test points as inputs,
 *      in order to read the values of the left.
 */

void ant_b10_signals_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    bool result = false;

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_GPIO1_IO31, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_GPIO1_IO18, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_GPIO1_IO19, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_GPIO1_IO29, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_GPIO1_IO30, 0U);

    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0x10B0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26, 0x10B0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27, 0x10B0U);

    gpio_pin_config_t InputConfig = {
        .direction = kGPIO_DigitalInput,
        .outputLogic = 0U,
        .interruptMode = kGPIO_NoIntmode
    };

    gpio_pin_config_t OutputConfig = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 0U,
        .interruptMode = kGPIO_NoIntmode
    };

    // Configure output GPIOs
    GPIO_PinInit(TEST_TP21_GPIO3_GPIO, TEST_TP21_GPIO3_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP33_CS_GPIO, TEST_TP33_CS_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP7_MISO_GPIO, TEST_TP7_MISO_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP37_CTS_GPIO, TEST_TP37_CTS_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP35_RTS_GPIO, TEST_TP35_RTS_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP39_TX_GPIO, TEST_TP39_TX_PIN, &OutputConfig);
    GPIO_PinInit(TEST_TP34_GPIO1_GPIO, TEST_TP34_GPIO1_PIN, &OutputConfig);

    // Configure input GPIOs
    GPIO_PinInit(TEST_TP38_RST_GPIO, TEST_TP38_RST_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP40_RX_GPIO, TEST_TP40_RX_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP36_SW2_GPIO, TEST_TP36_SW2_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP31_SCK_GPIO, TEST_TP31_SCK_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP32_GPIO2_GPIO, TEST_TP32_GPIO2_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP12_MOSI_GPIO, TEST_TP12_MOSI_PIN, &InputConfig);
    GPIO_PinInit(TEST_TP9_SW1_GPIO, TEST_TP9_SW1_PIN, &InputConfig);

    if ((verify_ant_b10_gpio_pattern(0, 0, 0, 0, 0, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 0, 0, 0, 0, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 0, 0, 0, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 1, 0, 0, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 1, 1, 0, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 1, 1, 1, 0, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 1, 1, 1, 1, 0))  &&
        (verify_ant_b10_gpio_pattern(1, 1, 1, 1, 1, 1, 1))) {
        result = true;
    }


    BOARD_InitPins();


    if (result) {
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }
}


void nina_uart_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    uint8_t txbuff[]   = "AT\r\n";
    uint8_t rxchar;
    status_t result;

    lpuart_config_t config = {
        .baudRate_Bps = 115200U,
        .parityMode = kLPUART_ParityDisabled,
        .dataBitsCount = kLPUART_EightDataBits,
        .isMsb = false,
        .stopBitCount = kLPUART_OneStopBit,
        .enableRxRTS = true,
        .enableTxCTS = true,
        .enableTx = true,
        .enableRx = true
    };

    GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 1U);
    vTaskDelay(1);
    LPUART_Init(ONBOARD_NINA_UART, &config, ONBOARD_NINA_UART_CLK_FREQ);
    LPUART_WriteBlocking(ONBOARD_NINA_UART, txbuff, sizeof(txbuff) - 1);
    result = LPUART_ReadBlocking(ONBOARD_NINA_UART, &rxchar, 1);
    LPUART_Deinit(ONBOARD_NINA_UART);

    if (result == kStatus_Success) {
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }

}

uint64_t parse_mac_addr_str(const char *s)
{

    uint64_t value = 0;
    int i;

    for (i = 0; i < 12; i++) {
        uint8_t temp = 0;
        char c = s[i];
        if ((c >= '0') && (c <= '9')) {
            temp = c - '0';
        } else if ((c >= 'A') && (c <= 'F')) {
            temp = c + 10 - 'A';
        } else if ((c >= 'a') && (c <= 'f')) {
            temp = c + 10 - 'a';
        }
        value = (value << 4) | temp;
    }

    return value;
}


#define ENABLE_IRREVERSIBLE_WRITE_TO_OTP 1

//Expects mac address in the form "AABBCCDDEEFF"
void store_mac_addr(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    uint64_t mac = parse_mac_addr_str(payload);
    uint32_t mac0 = mac & 0xffffffff;
    uint32_t mac1 = (mac >> 32) & 0x0000ffff;
    uint32_t mac0_test, mac1_test;


    OCOTP_Init(OCOTP, OCOTP_FREQ_HZ);
#if ENABLE_IRREVERSIBLE_WRITE_TO_OTP
    OCOTP_WriteFuseShadowRegister(OCOTP, MAC_0, mac0);
    OCOTP_WriteFuseShadowRegister(OCOTP, MAC_1, mac1);
#endif
    OCOTP_ReadFuseShadowRegisterExt(OCOTP, MAC_0, &mac0_test, 1);
    OCOTP_ReadFuseShadowRegisterExt(OCOTP, MAC_1, &mac1_test, 1);
    OCOTP_Deinit(OCOTP);

    if ((mac0 == mac0_test) && (mac1 == mac1_test)) {
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }

}


void nina_boot_mode(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    if (*payload == '1') {
        GPIO_PinWrite(BOARD_INITPINS_NINA_UART_MUX_GPIO, BOARD_INITPINS_NINA_UART_MUX_GPIO_PIN, 1U);
        GPIO_PinWrite(BOARD_INITPINS_NINA_SW2_GPIO, BOARD_INITPINS_NINA_SW2_GPIO_PIN, 0U);
        GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 0U);
        vTaskDelay(50);
        GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 1U);
        vTaskDelay(200);
        GPIO_PinWrite(BOARD_INITPINS_NINA_SW2_GPIO, BOARD_INITPINS_NINA_SW2_GPIO_PIN, 1U);
        RETURN_OK(outputBuffer, outputLength);
    } else if (*payload == '0') {
        GPIO_PinWrite(BOARD_INITPINS_NINA_UART_MUX_GPIO, BOARD_INITPINS_NINA_UART_MUX_GPIO_PIN, 0U);
        GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 0U);
        vTaskDelay(50);
        GPIO_PinWrite(BOARD_INITPINS_NINA_RST_GPIO, BOARD_INITPINS_NINA_RST_GPIO_PIN, 1U);
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }

}

void antb10_boot_mode(const char *payload, char *outputBuffer, uint8_t *outputLength)
{

    if (*payload == '1') {
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_UART_MUX_GPIO, BOARD_INITPINS_ANT_BXX_UART_MUX_GPIO_PIN, 1U);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_SW2_GPIO, BOARD_INITPINS_ANT_BXX_SW2_GPIO_PIN, 0U);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_RST_GPIO, BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN, 0U);
        vTaskDelay(50);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_RST_GPIO, BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN, 1U);
        vTaskDelay(200);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_SW2_GPIO, BOARD_INITPINS_ANT_BXX_SW2_GPIO_PIN, 1U);
        RETURN_OK(outputBuffer, outputLength);
    } else if (*payload == '0') {
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_UART_MUX_GPIO, BOARD_INITPINS_ANT_BXX_UART_MUX_GPIO_PIN, 0U);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_RST_GPIO, BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN, 0U);
        vTaskDelay(50);
        GPIO_PinWrite(BOARD_INITPINS_ANT_BXX_RST_GPIO, BOARD_INITPINS_ANT_BXX_RST_GPIO_PIN, 1U);
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }

}

void maya_uart_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    uint16_t *opcode;
    uint8_t  *param_len;
    static hal_uart_config_t config;
    uint8_t sendingBuffer[8];
    uint8_t recvBuffer[8];
    hal_uart_status_t error;
    bool result = false;

    memset(sendingBuffer, 0, sizeof(sendingBuffer));
    memset(recvBuffer, 0, sizeof(recvBuffer));
    memset(&config, 0, sizeof(config));
#if (defined(WIFI_IW416_BOARD_AW_AM457_USD) || defined(WIFI_IW416_BOARD_AW_AM510_USD) || defined(WIFI_IW416_BOARD_AW_AM510MA) || \
     defined(WIFI_IW416_BOARD_MURATA_1XK_USD) || defined(WIFI_IW416_BOARD_MURATA_1XK_M2) || \
     defined(WIFI_88W8987_BOARD_MURATA_1ZM_USD) || defined (WIFI_88W8987_BOARD_MURATA_1ZM_M2))
    /*delay to make sure controller is ready to receive command*/
    os_thread_sleep(os_msec_to_ticks(100));
#endif

    /* Set the HCI-UART Configuration parameters */
    config.srcClock_Hz  = BOARD_BT_UART_CLK_FREQ;
    config.parityMode   = kHAL_UartParityDisabled;
    config.stopBitCount = kHAL_UartOneStopBit;
    config.enableRx     = 1;
    config.enableTx     = 1;
    config.instance     = BOARD_BT_UART_INSTANCE;
    config.enableRxRTS  = 1u;
    config.enableTxCTS  = 1u;
#if (defined(HAL_UART_ADAPTER_FIFO) && (HAL_UART_ADAPTER_FIFO > 0u))
    config.txFifoWatermark = 0U;
    config.rxFifoWatermark = 0U;
#endif
    config.baudRate_Bps = BOARD_BT_UART_BAUDRATE; //  MAYA W161 use baud rate 115200,
    /* Initialize UART with Adapter */
    error = HAL_UartInit
            (
                (hal_uart_handle_t)s_controllerHciUartHandle,
                &config
            );

    if (kStatus_HAL_UartSuccess != error) {
        RETURN_FAIL(outputBuffer, outputLength);
    }

    sendingBuffer[0] = 0x01;
    opcode = (uint16_t *)&sendingBuffer[1];
    param_len = &sendingBuffer[3];
    *opcode                                   = (uint16_t)BT_OP(BT_OGF_VS, 0x09);
    *param_len                                = sizeof(config.baudRate_Bps);
    *((uint32_t *)(&sendingBuffer[4]))        = config.baudRate_Bps;

    /*delay to make sure controller is ready to receive command*/
    os_thread_sleep(os_msec_to_ticks(100));
    error = HAL_UartSendBlocking((hal_uart_handle_t)s_controllerHciUartHandle, &sendingBuffer[0], 8);
    os_thread_sleep(os_msec_to_ticks(100));
    if (kStatus_HAL_UartSuccess == error) {
        error = HAL_UartReceiveBlocking((hal_uart_handle_t)s_controllerHciUartHandle, &recvBuffer[0], 7);
        if (kStatus_HAL_UartSuccess == error && (0 != recvBuffer[0])) {
            result = true;
        }
    }

    os_thread_sleep(os_msec_to_ticks(100));
    error = HAL_UartDeinit((hal_uart_handle_t)s_controllerHciUartHandle);
    assert(kStatus_HAL_UartSuccess == error);

    if (result) {
        RETURN_OK(outputBuffer, outputLength);
    } else {
        RETURN_FAIL(outputBuffer, outputLength);
    }
}

void unique_id_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    unsigned long long id = get_unique_id_from_OTP();
    unsigned int idMSB = id >> 32;
    unsigned int idLSB = id & 0x00000000FFFFFFFF;
    sprintf(outputBuffer, "0x%08X%08X\r\n", idMSB, idLSB);
    *outputLength = strlen(outputBuffer);
}

void maya_mac_addr_test(const char *payload, char *outputBuffer, uint8_t *outputLength)
{
    unsigned char *mac = wifi_get_mac_addr();
    sprintf(outputBuffer, "%02X%02X%02X%02X%02X%02X\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    *outputLength = strlen(outputBuffer);
}

void sw1_button_test(const char *payload, char *outputBuffer, uint8_t *outputLength){
	unsigned int timeout_ms = 2000;
	unsigned int count = 0;
	bool success = false;
	while(count < timeout_ms){
		if (GPIO_PinRead(TEST_TP71_MCUSW_PORT, TEST_TP71_MCUSW_PIN) == 0){
			success = true;
			break;
		}
		vTaskDelay(1);
		count++;
	}
	if (success) {
		RETURN_OK(outputBuffer, outputLength);
	} else {
		RETURN_FAIL(outputBuffer, outputLength);
	}
}
