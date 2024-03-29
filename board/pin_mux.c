/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: MIMXRT1062xxxxA
package_id: MIMXRT1062DVL6A
mcu_data: ksdk2_0
processor_version: 12.0.1
pin_labels:
- {pin_num: E3, pin_signal: GPIO_EMC_00, label: NINA_CLK, identifier: SEMC_D0;NINA_CLK}
- {pin_num: F3, pin_signal: GPIO_EMC_01, label: NINA_CS, identifier: SEMC_D1;NINA_CS}
- {pin_num: F4, pin_signal: GPIO_EMC_02, label: NINA_MOSI, identifier: SEMC_D2;NINA_MOSI}
- {pin_num: F2, pin_signal: GPIO_EMC_04, label: MAYA_BT_W_H, identifier: SEMC_D4;MAYA_BT_W_H}
- {pin_num: G4, pin_signal: GPIO_EMC_03, label: NINA_MISO, identifier: SEMC_D3;NINA_MISO}
- {pin_num: C2, pin_signal: GPIO_EMC_09, label: MAYA_WLAN_W_D, identifier: SEMC_A0;MAYA_WLAN_W_D}
- {pin_num: A6, pin_signal: GPIO_EMC_13, label: NINA_TX, identifier: SEMC_A4;NINA_TX}
- {pin_num: B6, pin_signal: GPIO_EMC_14, label: NINA_RX, identifier: SEMC_A5;NINA_RX}
- {pin_num: B1, pin_signal: GPIO_EMC_15, label: NINA_CTS, identifier: SEMC_A6;NINA_CTS}
- {pin_num: A5, pin_signal: GPIO_EMC_16, label: NINA_RTS, identifier: SEMC_A7;NINA_RTS}
- {pin_num: A4, pin_signal: GPIO_EMC_17, label: NINA_GPIO1, identifier: SEMC_A8;NINA_GPIO1}
- {pin_num: B2, pin_signal: GPIO_EMC_18, label: MAYA_WLAN_RESET, identifier: SEMC_A9;MAYA_WLAN_RESET}
- {pin_num: B4, pin_signal: GPIO_EMC_19, label: NINA_GPIO3, identifier: SEMC_A11;NINA_GPIO3}
- {pin_num: A3, pin_signal: GPIO_EMC_20, label: NINA_GPIO2, identifier: SEMC_A12;NINA_GPIO2}
- {pin_num: C1, pin_signal: GPIO_EMC_21, label: MAYA_BT_W_D, identifier: SEMC_BA0;MAYA_BT_W_D}
- {pin_num: F1, pin_signal: GPIO_EMC_22, label: NINA_RST, identifier: SEMC_BA1;NINA_RST}
- {pin_num: D3, pin_signal: GPIO_EMC_24, label: NINA_SW1, identifier: SEMC_CAS;NINA_SW1}
- {pin_num: D2, pin_signal: GPIO_EMC_25, label: MAYA_TX, identifier: SEMC_RAS;MAYA_TX}
- {pin_num: B3, pin_signal: GPIO_EMC_26, label: MAYA_RX, identifier: SEMC_CLK;MAYA_RX}
- {pin_num: A2, pin_signal: GPIO_EMC_27, label: MAYA_BT_RESET, identifier: SEMC_CKE;MAYA_BT_RESET}
- {pin_num: D1, pin_signal: GPIO_EMC_28, label: MAYA_WLAN_W_H, identifier: SEMC_WE;MAYA_WLAN_W_H}
- {pin_num: E1, pin_signal: GPIO_EMC_29, label: MAYA_RTS, identifier: SEMC_CS0;MAYA_RTS}
- {pin_num: C6, pin_signal: GPIO_EMC_30, label: MAYA_CTS, identifier: SEMC_D8;MAYA_CTS}
- {pin_num: C5, pin_signal: GPIO_EMC_31, label: NINA_SW2, identifier: SEMC_D9;NINA_SW2}
- {pin_num: C4, pin_signal: GPIO_EMC_33, label: NINA_UART_MUX, identifier: SEMC_D11;SEL_MUX_AX_UART;NINA_UART_MUX}
- {pin_num: C3, pin_signal: GPIO_EMC_36, label: ANT_BXX_UART_MUX, identifier: SEMC_D14;SEL_MUX_AX;ANT_BXX_UART_MUX}
- {pin_num: A11, pin_signal: GPIO_B1_00, label: USER_LED_01, identifier: LCDIF_D12;USER_LED_02;USER_LED_01}
- {pin_num: B11, pin_signal: GPIO_B1_01, label: MCU_SW1, identifier: LCDIF_D13;MCU_SW1}
- {pin_num: C11, pin_signal: GPIO_B1_02, label: MCU_SW2, identifier: LCDIF_D14;MCU_SW2}
- {pin_num: D13, pin_signal: GPIO_B1_12, label: ANT_BXX_SW1, identifier: SD_CD_SW;ANT_BXX_SW1}
- {pin_num: C14, pin_signal: GPIO_B1_14, label: MCU_SW3, identifier: SD0_VSELECT;MCU_SW3}
- {pin_num: B14, pin_signal: GPIO_B1_15, label: USER_LED_02, identifier: BACKLIGHT_CTL;USER_LED_02}
- {pin_num: M14, pin_signal: GPIO_AD_B0_00, label: ANT_BXX_SW2, identifier: ANT_BXX_SW2}
- {pin_num: J11, pin_signal: GPIO_AD_B1_00, label: ANT_BXX_CTS, identifier: I2C_SCL_FXOS8700CQ;CSI_I2C_SCL;ANT_BXX_CTS}
- {pin_num: K11, pin_signal: GPIO_AD_B1_01, label: ANT_BXX_RTS, identifier: I2C_SDA_FXOS8700CQ;CSI_I2C_SDA;ANT_BXX_RTS}
- {pin_num: L11, pin_signal: GPIO_AD_B1_02, label: ANT_BXX_TX, identifier: SPDIF_OUT;ANT_BXX_TX}
- {pin_num: M12, pin_signal: GPIO_AD_B1_03, label: ANT_BXX_RX, identifier: SPDIF_IN;ANT_BXX_RX}
- {pin_num: H13, pin_signal: GPIO_AD_B1_08, label: ANT_BXX_GPIO3, identifier: CSI_D9;ANT_BXX_GPIO3}
- {pin_num: M13, pin_signal: GPIO_AD_B1_09, label: ANT_BXX_RST, identifier: CSI_D8;ANT_BXX_RST;ANT_BXX}
- {pin_num: L13, pin_signal: GPIO_AD_B1_10, label: ANT_BXX_GPIO1, identifier: CSI_D7;ANT_BXX_GPIO1}
- {pin_num: J13, pin_signal: GPIO_AD_B1_11, label: ANT_BXX_GPIO2, identifier: CSI_D6;ANT_BXX_GPIO2}
- {pin_num: H12, pin_signal: GPIO_AD_B1_12, label: ANT_BXX_CS, identifier: CSI_D5;ANT_BX_CS;ANT_BXX_CS}
- {pin_num: H11, pin_signal: GPIO_AD_B1_13, label: ANT_BXX_MISO, identifier: CSI_D4;ANT_BXX_MISO}
- {pin_num: G12, pin_signal: GPIO_AD_B1_14, label: ANT_BXX_MOSI, identifier: CSI_D3;ANT_BXX_MOSI}
- {pin_num: J14, pin_signal: GPIO_AD_B1_15, label: ANT_BXX_CLK, identifier: CSI_D2;ANT_BXX_CLK}
- {pin_num: L5, pin_signal: GPIO_SD_B1_00, label: MAYA_PDN, identifier: FlexSPI_D3_B;MAYA_PDN}
- {pin_num: L6, pin_signal: WAKEUP, label: USER_BUTTON, identifier: SD_PWREN;USER_BUTTON}
- {pin_num: L14, pin_signal: GPIO_AD_B0_13, label: UART1_RXD, identifier: UART1_RXD}
- {pin_num: K14, pin_signal: GPIO_AD_B0_12, label: UART1_TXD, identifier: UART1_TXD}
- {pin_num: A7, pin_signal: GPIO_EMC_40, label: ENET_MDC, identifier: ENET_MDC}
- {pin_num: C7, pin_signal: GPIO_EMC_41, label: ENET_MDIO, identifier: ENET_MDIO}
- {pin_num: B13, pin_signal: GPIO_B1_10, label: ENET_TX_CLK, identifier: ENET_TX_CLK}
- {pin_num: E12, pin_signal: GPIO_B1_04, label: ENET_RXD0, identifier: ENET_RXD0}
- {pin_num: D12, pin_signal: GPIO_B1_05, label: ENET_RXD1, identifier: ENET_RXD1}
- {pin_num: C12, pin_signal: GPIO_B1_06, label: ENET_CRS_DV, identifier: ENET_CRS_DV}
- {pin_num: C13, pin_signal: GPIO_B1_11, label: ENET_RXER, identifier: ENET_RXER}
- {pin_num: B12, pin_signal: GPIO_B1_07, label: ENET_TXD0, identifier: ENET_TXD0}
- {pin_num: A12, pin_signal: GPIO_B1_08, label: ENET_TXD1, identifier: ENET_TXD1}
- {pin_num: A13, pin_signal: GPIO_B1_09, label: ENET_TXEN, identifier: ENET_TXEN}
- {pin_num: F14, pin_signal: GPIO_AD_B0_09, label: ENET_RST, identifier: ENET_RST}
- {pin_num: G13, pin_signal: GPIO_AD_B0_10, label: INT1_COMBO, identifier: INT1_COMBO}
- {pin_num: D14, pin_signal: GPIO_B1_13, label: WDOG_B, identifier: WDOG_B}
- {pin_num: K7, pin_signal: PMIC_ON_REQ, label: PMIC_ON_REQ, identifier: PMIC_ON_REQ}
- {pin_num: J3, pin_signal: GPIO_SD_B0_01, label: SD1_CLK, identifier: SD1_CLK}
- {pin_num: J4, pin_signal: GPIO_SD_B0_00, label: SD1_CMD, identifier: SD1_CMD}
- {pin_num: J1, pin_signal: GPIO_SD_B0_02, label: SD1_D0, identifier: SD1_D0}
- {pin_num: K1, pin_signal: GPIO_SD_B0_03, label: SD1_D1, identifier: SD1_D1}
- {pin_num: H2, pin_signal: GPIO_SD_B0_04, label: SD1_D2, identifier: SD1_D2}
- {pin_num: J2, pin_signal: GPIO_SD_B0_05, label: SD1_D3, identifier: SD1_D3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L14, peripheral: LPUART1, signal: RX, pin_signal: GPIO_AD_B0_13, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Down_100K_Ohm,
    pull_keeper_select: Keeper, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_100, drive_strength: R0_6, slew_rate: Slow}
  - {pin_num: K14, peripheral: LPUART1, signal: TX, pin_signal: GPIO_AD_B0_12, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Down_100K_Ohm,
    pull_keeper_select: Keeper, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_100, drive_strength: R0_6, slew_rate: Slow}
  - {pin_num: A7, peripheral: ENET, signal: enet_mdc, pin_signal: GPIO_EMC_40, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: C7, peripheral: ENET, signal: enet_mdio, pin_signal: GPIO_EMC_41, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Enable, speed: MHZ_50, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: B13, peripheral: ENET, signal: enet_ref_clk, pin_signal: GPIO_B1_10, software_input_on: Enable, hysteresis_enable: Disable, pull_up_down_config: Pull_Down_100K_Ohm,
    pull_keeper_select: Keeper, pull_keeper_enable: Disable, open_drain: Disable, speed: MHZ_50, drive_strength: R0_6, slew_rate: Fast}
  - {pin_num: E12, peripheral: ENET, signal: 'enet_rx_data, 0', pin_signal: GPIO_B1_04, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: D12, peripheral: ENET, signal: 'enet_rx_data, 1', pin_signal: GPIO_B1_05, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: C12, peripheral: ENET, signal: enet_rx_en, pin_signal: GPIO_B1_06, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: C13, peripheral: ENET, signal: enet_rx_er, pin_signal: GPIO_B1_11, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: B12, peripheral: ENET, signal: 'enet_tx_data, 0', pin_signal: GPIO_B1_07, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: A12, peripheral: ENET, signal: 'enet_tx_data, 1', pin_signal: GPIO_B1_08, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: A13, peripheral: ENET, signal: enet_tx_en, pin_signal: GPIO_B1_09, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_200, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: F14, peripheral: GPIO1, signal: 'gpio_io, 09', pin_signal: GPIO_AD_B0_09, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Up_100K_Ohm,
    pull_keeper_select: Pull, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_100, drive_strength: R0_5, slew_rate: Fast}
  - {pin_num: J3, peripheral: USDHC1, signal: usdhc_clk, pin_signal: GPIO_SD_B0_01}
  - {pin_num: J4, peripheral: USDHC1, signal: usdhc_cmd, pin_signal: GPIO_SD_B0_00}
  - {pin_num: J1, peripheral: USDHC1, signal: 'usdhc_data, 0', pin_signal: GPIO_SD_B0_02}
  - {pin_num: K1, peripheral: USDHC1, signal: 'usdhc_data, 1', pin_signal: GPIO_SD_B0_03}
  - {pin_num: H2, peripheral: USDHC1, signal: 'usdhc_data, 2', pin_signal: GPIO_SD_B0_04}
  - {pin_num: J2, peripheral: USDHC1, signal: 'usdhc_data, 3', pin_signal: GPIO_SD_B0_05}
  - {pin_num: J11, peripheral: LPUART2, signal: CTS_B, pin_signal: GPIO_AD_B1_00, identifier: ANT_BXX_CTS}
  - {pin_num: K11, peripheral: LPUART2, signal: RTS_B, pin_signal: GPIO_AD_B1_01, identifier: ANT_BXX_RTS}
  - {pin_num: M12, peripheral: LPUART2, signal: RX, pin_signal: GPIO_AD_B1_03, identifier: ANT_BXX_RX}
  - {pin_num: L11, peripheral: LPUART2, signal: TX, pin_signal: GPIO_AD_B1_02, identifier: ANT_BXX_TX}
  - {pin_num: H12, peripheral: LPSPI3, signal: PCS0, pin_signal: GPIO_AD_B1_12, identifier: ANT_BXX_CS, direction: OUTPUT}
  - {pin_num: J14, peripheral: LPSPI3, signal: SCK, pin_signal: GPIO_AD_B1_15, identifier: ANT_BXX_CLK}
  - {pin_num: H11, peripheral: LPSPI3, signal: SDI, pin_signal: GPIO_AD_B1_13, identifier: ANT_BXX_MISO}
  - {pin_num: G12, peripheral: LPSPI3, signal: SDO, pin_signal: GPIO_AD_B1_14, identifier: ANT_BXX_MOSI}
  - {pin_num: M13, peripheral: GPIO1, signal: 'gpio_io, 25', pin_signal: GPIO_AD_B1_09, identifier: ANT_BXX_RST, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: D13, peripheral: GPIO7, signal: 'gpio_io, 28', pin_signal: GPIO_B1_12, identifier: ANT_BXX_SW1, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: M14, peripheral: GPIO1, signal: 'gpio_io, 00', pin_signal: GPIO_AD_B0_00, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: L13, peripheral: GPIO1, signal: 'gpio_io, 26', pin_signal: GPIO_AD_B1_10, identifier: ANT_BXX_GPIO1, direction: OUTPUT, open_drain: Enable}
  - {pin_num: J13, peripheral: GPIO1, signal: 'gpio_io, 27', pin_signal: GPIO_AD_B1_11, identifier: ANT_BXX_GPIO2, direction: OUTPUT, open_drain: Enable}
  - {pin_num: H13, peripheral: GPIO1, signal: 'gpio_io, 24', pin_signal: GPIO_AD_B1_08, identifier: ANT_BXX_GPIO3, direction: OUTPUT, open_drain: Enable}
  - {pin_num: C3, peripheral: GPIO3, signal: 'gpio_io, 22', pin_signal: GPIO_EMC_36, identifier: ANT_BXX_UART_MUX, direction: OUTPUT}
  - {pin_num: L5, peripheral: GPIO3, signal: 'gpio_io, 00', pin_signal: GPIO_SD_B1_00, identifier: MAYA_PDN, direction: OUTPUT}
  - {pin_num: F2, peripheral: GPIO4, signal: 'gpio_io, 04', pin_signal: GPIO_EMC_04, identifier: MAYA_BT_W_H, direction: INPUT}
  - {pin_num: C1, peripheral: GPIO4, signal: 'gpio_io, 21', pin_signal: GPIO_EMC_21, identifier: MAYA_BT_W_D, direction: OUTPUT}
  - {pin_num: A2, peripheral: GPIO4, signal: 'gpio_io, 27', pin_signal: GPIO_EMC_27, identifier: MAYA_BT_RESET, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: D1, peripheral: GPIO4, signal: 'gpio_io, 28', pin_signal: GPIO_EMC_28, identifier: MAYA_WLAN_W_H, direction: INPUT}
  - {pin_num: C2, peripheral: GPIO4, signal: 'gpio_io, 09', pin_signal: GPIO_EMC_09, identifier: MAYA_WLAN_W_D, direction: OUTPUT}
  - {pin_num: B2, peripheral: GPIO4, signal: 'gpio_io, 18', pin_signal: GPIO_EMC_18, identifier: MAYA_WLAN_RESET, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: D2, peripheral: LPUART6, signal: TX, pin_signal: GPIO_EMC_25, identifier: MAYA_TX}
  - {pin_num: B3, peripheral: LPUART6, signal: RX, pin_signal: GPIO_EMC_26, identifier: MAYA_RX}
  - {pin_num: E1, peripheral: LPUART6, signal: RTS_B, pin_signal: GPIO_EMC_29, identifier: MAYA_RTS}
  - {pin_num: C6, peripheral: LPUART6, signal: CTS_B, pin_signal: GPIO_EMC_30, identifier: MAYA_CTS}
  - {pin_num: B1, peripheral: LPUART3, signal: CTS_B, pin_signal: GPIO_EMC_15, identifier: NINA_CTS}
  - {pin_num: A5, peripheral: LPUART3, signal: RTS_B, pin_signal: GPIO_EMC_16, identifier: NINA_RTS}
  - {pin_num: B6, peripheral: LPUART3, signal: RX, pin_signal: GPIO_EMC_14, identifier: NINA_RX}
  - {pin_num: A6, peripheral: LPUART3, signal: TX, pin_signal: GPIO_EMC_13, identifier: NINA_TX}
  - {pin_num: F3, peripheral: LPSPI2, signal: PCS0, pin_signal: GPIO_EMC_01, identifier: NINA_CS}
  - {pin_num: E3, peripheral: LPSPI2, signal: SCK, pin_signal: GPIO_EMC_00, identifier: NINA_CLK}
  - {pin_num: G4, peripheral: GPIO4, signal: 'gpio_io, 03', pin_signal: GPIO_EMC_03, identifier: NINA_MISO, direction: INPUT, pull_keeper_enable: Enable}
  - {pin_num: F4, peripheral: GPIO4, signal: 'gpio_io, 02', pin_signal: GPIO_EMC_02, identifier: NINA_MOSI, direction: INPUT, pull_keeper_enable: Enable}
  - {pin_num: F1, peripheral: GPIO4, signal: 'gpio_io, 22', pin_signal: GPIO_EMC_22, identifier: NINA_RST, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: D3, peripheral: GPIO4, signal: 'gpio_io, 24', pin_signal: GPIO_EMC_24, identifier: NINA_SW1, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: C5, peripheral: GPIO4, signal: 'gpio_io, 31', pin_signal: GPIO_EMC_31, identifier: NINA_SW2, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Up_47K_Ohm,
    open_drain: Enable}
  - {pin_num: A4, peripheral: GPIO4, signal: 'gpio_io, 17', pin_signal: GPIO_EMC_17, identifier: NINA_GPIO1, direction: INPUT, pull_up_down_config: Pull_Up_47K_Ohm}
  - {pin_num: A3, peripheral: GPIO4, signal: 'gpio_io, 20', pin_signal: GPIO_EMC_20, identifier: NINA_GPIO2, direction: INPUT, pull_up_down_config: Pull_Up_47K_Ohm}
  - {pin_num: B4, peripheral: GPIO4, signal: 'gpio_io, 19', pin_signal: GPIO_EMC_19, identifier: NINA_GPIO3, direction: INPUT, pull_up_down_config: Pull_Up_47K_Ohm}
  - {pin_num: C4, peripheral: GPIO3, signal: 'gpio_io, 19', pin_signal: GPIO_EMC_33, identifier: NINA_UART_MUX, direction: OUTPUT}
  - {pin_num: B11, peripheral: GPIO7, signal: 'gpio_io, 17', pin_signal: GPIO_B1_01, identifier: MCU_SW1, direction: INPUT, software_input_on: Disable, pull_up_down_config: Pull_Up_47K_Ohm,
    pull_keeper_select: Pull}
  - {pin_num: C11, peripheral: GPIO7, signal: 'gpio_io, 18', pin_signal: GPIO_B1_02, identifier: MCU_SW2, direction: INPUT, software_input_on: Disable, pull_up_down_config: Pull_Up_47K_Ohm,
    pull_keeper_select: Pull}
  - {pin_num: C14, peripheral: GPIO7, signal: 'gpio_io, 30', pin_signal: GPIO_B1_14, identifier: MCU_SW3, direction: INPUT, software_input_on: Disable, pull_up_down_config: Pull_Up_47K_Ohm,
    pull_keeper_select: Pull}
  - {pin_num: A11, peripheral: GPIO2, signal: 'gpio_io, 16', pin_signal: GPIO_B1_00, identifier: USER_LED_01, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: B14, peripheral: GPIO2, signal: 'gpio_io, 31', pin_signal: GPIO_B1_15, identifier: USER_LED_02, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: L6, peripheral: GPIO5, signal: 'gpio_io, 00', pin_signal: WAKEUP, identifier: USER_BUTTON, direction: INPUT, pull_up_down_config: Pull_Up_47K_Ohm}
  - {pin_num: K7, peripheral: SNVS, signal: snvs_pmic_on_req, pin_signal: PMIC_ON_REQ}
  - {pin_num: D14, peripheral: WDOG1, signal: wdog_b, pin_signal: GPIO_B1_13}
  - {pin_num: G13, peripheral: GPIO1, signal: 'gpio_io, 10', pin_signal: GPIO_AD_B0_10, direction: INPUT, gpio_interrupt: kGPIO_IntFallingEdge, pull_up_down_config: Pull_Up_47K_Ohm,
    pull_keeper_select: Pull}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           
  CLOCK_EnableClock(kCLOCK_IomuxcSnvs);       

  /* GPIO configuration of ANT_BXX_SW2 on GPIO_AD_B0_00 (pin M14) */
  gpio_pin_config_t ANT_BXX_SW2_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B0_00 (pin M14) */
  GPIO_PinInit(GPIO1, 0U, &ANT_BXX_SW2_config);

  /* GPIO configuration of INT1_COMBO on GPIO_AD_B0_10 (pin G13) */
  gpio_pin_config_t INT1_COMBO_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_IntFallingEdge
  };
  /* Initialize GPIO functionality on GPIO_AD_B0_10 (pin G13) */
  GPIO_PinInit(GPIO1, 10U, &INT1_COMBO_config);
  /* Enable GPIO pin interrupt on GPIO_AD_B0_10 (pin G13) */
  GPIO_PortEnableInterrupts(GPIO1, 1U << 10U);

  /* GPIO configuration of ANT_BXX_GPIO3 on GPIO_AD_B1_08 (pin H13) */
  gpio_pin_config_t ANT_BXX_GPIO3_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B1_08 (pin H13) */
  GPIO_PinInit(GPIO1, 24U, &ANT_BXX_GPIO3_config);

  /* GPIO configuration of ANT_BXX_RST on GPIO_AD_B1_09 (pin M13) */
  gpio_pin_config_t ANT_BXX_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B1_09 (pin M13) */
  GPIO_PinInit(GPIO1, 25U, &ANT_BXX_RST_config);

  /* GPIO configuration of ANT_BXX_GPIO1 on GPIO_AD_B1_10 (pin L13) */
  gpio_pin_config_t ANT_BXX_GPIO1_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B1_10 (pin L13) */
  GPIO_PinInit(GPIO1, 26U, &ANT_BXX_GPIO1_config);

  /* GPIO configuration of ANT_BXX_GPIO2 on GPIO_AD_B1_11 (pin J13) */
  gpio_pin_config_t ANT_BXX_GPIO2_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B1_11 (pin J13) */
  GPIO_PinInit(GPIO1, 27U, &ANT_BXX_GPIO2_config);

  /* GPIO configuration of USER_LED_01 on GPIO_B1_00 (pin A11) */
  gpio_pin_config_t USER_LED_01_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_00 (pin A11) */
  GPIO_PinInit(GPIO2, 16U, &USER_LED_01_config);

  /* GPIO configuration of USER_LED_02 on GPIO_B1_15 (pin B14) */
  gpio_pin_config_t USER_LED_02_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_15 (pin B14) */
  GPIO_PinInit(GPIO2, 31U, &USER_LED_02_config);

  /* GPIO configuration of MAYA_PDN on GPIO_SD_B1_00 (pin L5) */
  gpio_pin_config_t MAYA_PDN_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_SD_B1_00 (pin L5) */
  GPIO_PinInit(GPIO3, 0U, &MAYA_PDN_config);

  /* GPIO configuration of NINA_UART_MUX on GPIO_EMC_33 (pin C4) */
  gpio_pin_config_t NINA_UART_MUX_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_33 (pin C4) */
  GPIO_PinInit(GPIO3, 19U, &NINA_UART_MUX_config);

  /* GPIO configuration of ANT_BXX_UART_MUX on GPIO_EMC_36 (pin C3) */
  gpio_pin_config_t ANT_BXX_UART_MUX_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_36 (pin C3) */
  GPIO_PinInit(GPIO3, 22U, &ANT_BXX_UART_MUX_config);

  /* GPIO configuration of NINA_MOSI on GPIO_EMC_02 (pin F4) */
  gpio_pin_config_t NINA_MOSI_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_02 (pin F4) */
  GPIO_PinInit(GPIO4, 2U, &NINA_MOSI_config);

  /* GPIO configuration of NINA_MISO on GPIO_EMC_03 (pin G4) */
  gpio_pin_config_t NINA_MISO_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_03 (pin G4) */
  GPIO_PinInit(GPIO4, 3U, &NINA_MISO_config);

  /* GPIO configuration of MAYA_BT_W_H on GPIO_EMC_04 (pin F2) */
  gpio_pin_config_t MAYA_BT_W_H_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_04 (pin F2) */
  GPIO_PinInit(GPIO4, 4U, &MAYA_BT_W_H_config);

  /* GPIO configuration of MAYA_WLAN_W_D on GPIO_EMC_09 (pin C2) */
  gpio_pin_config_t MAYA_WLAN_W_D_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_09 (pin C2) */
  GPIO_PinInit(GPIO4, 9U, &MAYA_WLAN_W_D_config);

  /* GPIO configuration of NINA_GPIO1 on GPIO_EMC_17 (pin A4) */
  gpio_pin_config_t NINA_GPIO1_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_17 (pin A4) */
  GPIO_PinInit(GPIO4, 17U, &NINA_GPIO1_config);

  /* GPIO configuration of MAYA_WLAN_RESET on GPIO_EMC_18 (pin B2) */
  gpio_pin_config_t MAYA_WLAN_RESET_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_18 (pin B2) */
  GPIO_PinInit(GPIO4, 18U, &MAYA_WLAN_RESET_config);

  /* GPIO configuration of NINA_GPIO3 on GPIO_EMC_19 (pin B4) */
  gpio_pin_config_t NINA_GPIO3_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_19 (pin B4) */
  GPIO_PinInit(GPIO4, 19U, &NINA_GPIO3_config);

  /* GPIO configuration of NINA_GPIO2 on GPIO_EMC_20 (pin A3) */
  gpio_pin_config_t NINA_GPIO2_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_20 (pin A3) */
  GPIO_PinInit(GPIO4, 20U, &NINA_GPIO2_config);

  /* GPIO configuration of MAYA_BT_W_D on GPIO_EMC_21 (pin C1) */
  gpio_pin_config_t MAYA_BT_W_D_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_21 (pin C1) */
  GPIO_PinInit(GPIO4, 21U, &MAYA_BT_W_D_config);

  /* GPIO configuration of NINA_RST on GPIO_EMC_22 (pin F1) */
  gpio_pin_config_t NINA_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_22 (pin F1) */
  GPIO_PinInit(GPIO4, 22U, &NINA_RST_config);

  /* GPIO configuration of NINA_SW1 on GPIO_EMC_24 (pin D3) */
  gpio_pin_config_t NINA_SW1_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_24 (pin D3) */
  GPIO_PinInit(GPIO4, 24U, &NINA_SW1_config);

  /* GPIO configuration of MAYA_BT_RESET on GPIO_EMC_27 (pin A2) */
  gpio_pin_config_t MAYA_BT_RESET_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_27 (pin A2) */
  GPIO_PinInit(GPIO4, 27U, &MAYA_BT_RESET_config);

  /* GPIO configuration of MAYA_WLAN_W_H on GPIO_EMC_28 (pin D1) */
  gpio_pin_config_t MAYA_WLAN_W_H_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_28 (pin D1) */
  GPIO_PinInit(GPIO4, 28U, &MAYA_WLAN_W_H_config);

  /* GPIO configuration of NINA_SW2 on GPIO_EMC_31 (pin C5) */
  gpio_pin_config_t NINA_SW2_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_EMC_31 (pin C5) */
  GPIO_PinInit(GPIO4, 31U, &NINA_SW2_config);

  /* GPIO configuration of USER_BUTTON on WAKEUP (pin L6) */
  gpio_pin_config_t USER_BUTTON_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on WAKEUP (pin L6) */
  GPIO_PinInit(GPIO5, 0U, &USER_BUTTON_config);

  /* GPIO configuration of MCU_SW1 on GPIO_B1_01 (pin B11) */
  gpio_pin_config_t MCU_SW1_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_01 (pin B11) */
  GPIO_PinInit(GPIO7, 17U, &MCU_SW1_config);

  /* GPIO configuration of MCU_SW2 on GPIO_B1_02 (pin C11) */
  gpio_pin_config_t MCU_SW2_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_02 (pin C11) */
  GPIO_PinInit(GPIO7, 18U, &MCU_SW2_config);

  /* GPIO configuration of ANT_BXX_SW1 on GPIO_B1_12 (pin D13) */
  gpio_pin_config_t ANT_BXX_SW1_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_12 (pin D13) */
  GPIO_PinInit(GPIO7, 28U, &ANT_BXX_SW1_config);

  /* GPIO configuration of MCU_SW3 on GPIO_B1_14 (pin C14) */
  gpio_pin_config_t MCU_SW3_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_B1_14 (pin C14) */
  GPIO_PinInit(GPIO7, 30U, &MCU_SW3_config);

  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_GPIO1_IO00, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_LPUART2_CTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_LPUART2_RTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_LPUART2_TX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_LPUART2_RX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_LPSPI3_PCS0, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_LPSPI3_SDI, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_LPSPI3_SDO, 0U); 
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 4)
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_LPSPI3_SCK, 0U); 
#endif
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_GPIO2_IO16, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_GPIO2_IO17, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_GPIO2_IO18, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_ENET_RX_DATA00, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_ENET_RX_DATA01, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_ENET_RX_EN, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_ENET_TX_DATA00, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_ENET_TX_DATA01, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_ENET_TX_EN, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_ENET_REF_CLK, 1U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_ENET_RX_ER, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_GPIO2_IO28, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_WDOG1_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_GPIO2_IO30, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_GPIO2_IO31, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_00_LPSPI2_SCK, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_01_LPSPI2_PCS0, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_02_GPIO4_IO02, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_03_GPIO4_IO03, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_04_GPIO4_IO04, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_09_GPIO4_IO09, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_13_LPUART3_TX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_14_LPUART3_RX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_15_LPUART3_CTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_16_LPUART3_RTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_17_GPIO4_IO17, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_18_GPIO4_IO18, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_19_GPIO4_IO19, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_20_GPIO4_IO20, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_21_GPIO4_IO21, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_22_GPIO4_IO22, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_24_GPIO4_IO24, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_25_LPUART6_TX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_26_LPUART6_RX, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_27_GPIO4_IO27, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_28_GPIO4_IO28, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_29_LPUART6_RTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_30_LPUART6_CTS_B, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_31_GPIO4_IO31, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_GPIO3_IO19, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_GPIO3_IO22, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_ENET_MDC, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_ENET_MDIO, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3, 0U); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00, 0U); 
  IOMUXC_GPR->GPR26 = ((IOMUXC_GPR->GPR26 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR26_GPIO_MUX1_GPIO_SEL(0x00U) 
    );
  IOMUXC_GPR->GPR27 = ((IOMUXC_GPR->GPR27 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR27_GPIO_MUX2_GPIO_SEL(0x50060000U) 
    );
  IOMUXC_GPR->GPR28 = ((IOMUXC_GPR->GPR28 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR28_GPIO_MUX3_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR28_GPIO_MUX3_GPIO_SEL(0x00U) 
    );
  IOMUXC_GPR->GPR29 = ((IOMUXC_GPR->GPR29 &
    (~(BOARD_INITPINS_IOMUXC_GPR_GPR29_GPIO_MUX4_GPIO_SEL_MASK))) 
      | IOMUXC_GPR_GPR29_GPIO_MUX4_GPIO_SEL(0x00U) 
    );
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 4)
  IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_ON_REQ_SNVS_PMIC_ON_REQ, 0U); 
#else
  IOMUXC_SetPinMux(IOMUXC_SNVS_PMIC_ON_REQ_SNVS_LP_PMIC_ON_REQ, 0U); 
#endif
  IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00, 0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_00_GPIO1_IO00, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0xB0A9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10, 0x70B1U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0x10B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0x10B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0x18B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26, 0x18B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27, 0x18B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_GPIO2_IO17, 0x70B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_GPIO2_IO18, 0x70B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_04_ENET_RX_DATA00, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_ENET_RX_DATA01, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_ENET_RX_EN, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_ENET_TX_DATA00, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_08_ENET_TX_DATA01, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_ENET_TX_EN, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_ENET_REF_CLK, 0x31U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_ENET_RX_ER, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_12_GPIO2_IO28, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_14_GPIO2_IO30, 0x70B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_02_GPIO4_IO02, 0x10B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_03_GPIO4_IO03, 0x10B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_17_GPIO4_IO17, 0x50B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_19_GPIO4_IO19, 0x50B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_20_GPIO4_IO20, 0x50B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_22_GPIO4_IO22, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_24_GPIO4_IO24, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_31_GPIO4_IO31, 0x58B0U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_ENET_MDC, 0xB0E9U); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_ENET_MDIO, 0xB829U); 
  IOMUXC_SetPinConfig(IOMUXC_SNVS_WAKEUP_GPIO5_IO00, 0x0170A0U); 
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
