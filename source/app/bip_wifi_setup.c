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

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "wlan_bt_fw.h"
#include "wlan.h"
#include "wifi.h"
#include "wm_net.h"
#include <wm_os.h>

#include "fsl_sdmmc_host.h"
#include "fsl_gpio.h"
#include "lwip/tcpip.h"

#include "fsl_common.h"

#include <app/bip_configuration.h>
#include <app/bip_wifi_setup.h>

static struct wlan_network sta_network;
static struct wlan_network user_defined_network;
static int connect_to_user_network = 1;
static int sta_network_available = 0;

static char firstResult             = 0;
static TaskHandle_t xInitTaskNotify = NULL;
static TaskHandle_t xJoinTaskNotify = NULL;

static TaskHandle_t xKnownNetworksUpdatedNotify = NULL;

static int wifi_initialization_result = -1;

static unsigned char wifi_mac_addr[6];
static int network_added = 0;


static int __scan_cb(unsigned int count)
{
    struct wlan_scan_result res;
    int i;
    int err;

    if (count == 0) {
        PRINTF("No networks found!\r\n");
        return 0;
    }

    PRINTF("%d network%s found:\r\n", count, count == 1 ? "" : "s");

    for (i = 0; i < count; i++) {
        err = wlan_get_scan_result(i, &res);
        if (err) {
            PRINTF("Error: can't get scan res %d\r\n", i);
            continue;
        }

        if (!strcmp(res.ssid, get_configuration()->ssid)) {
            sta_network_available = 1;
            connect_to_user_network = 0;
        }

        print_mac(res.bssid);

        if (res.ssid[0]) {
            PRINTF(" \"%s\"\r\n", res.ssid);
        } else {
            PRINTF(" (hidden) \r\n");
        }

        PRINTF("\tchannel: %d\r\n", res.channel);
        PRINTF("\trssi: -%d dBm\r\n", res.rssi);
        PRINTF("\tsecurity: ");
        if (res.wep) {
            PRINTF("WEP ");
        }
        if (res.wpa && res.wpa2) {
            PRINTF("WPA/WPA2 Mixed ");
        } else {
            if (res.wpa) {
                PRINTF("WPA ");
            }
            if (res.wpa2) {
                PRINTF("WPA2 ");
            }
            if (res.wpa3_sae) {
                PRINTF("WPA3 SAE ");
            }
            if (res.wpa2_entp) {
                PRINTF("WPA2 Enterprise");
            }
        }
        if (!(res.wep || res.wpa || res.wpa2 || res.wpa3_sae || res.wpa2_entp)) {
            PRINTF("OPEN ");
        }
        PRINTF("\r\n");

        PRINTF("\tWMM: %s\r\n", res.wmm ? "YES" : "NO");
    }

    firstResult = 1;
    return 0;
}

static void scan(void)
{
    if (wlan_scan(__scan_cb)) {
        PRINTF("Error: scan request failed\r\n");
    } else {
        PRINTF("Scan scheduled...\r\n");
    }
}

static void conToAp(void)
{
    int ret;

    if (connect_to_user_network) {
        PRINTF("Connecting to %s .....", user_defined_network.ssid);
        ret = wlan_connect(user_defined_network.name);
    } else {
        PRINTF("Connecting to %s .....", sta_network.ssid);
        ret = wlan_connect(sta_network.name);
    }

    if (ret != WM_SUCCESS) {
        PRINTF("Failed to connect %d\r\n", ret);
    }
}

/* Callback Function passed to WLAN Connection Manager. The callback function
 * gets called when there are WLAN Events that need to be handled by the
 * application.
 */
static int wlan_event_callback(enum wlan_event_reason reason, void *data)
{
    PRINTF("app_cb: WLAN: received event %d\r\n", reason);

    switch (reason) {
        case WLAN_REASON_INITIALIZED:
            PRINTF("app_cb: WLAN initialized\r\n");
            int ret;

            /* Print WLAN FW Version */
            wlan_version_extended();

            if (!network_added) {
                uint8_t network_name_len = 0;
                uint8_t ssid_len         = 0;
                uint8_t psk_len          = 0;
                memset(&sta_network, 0, sizeof(struct wlan_network));

                network_name_len = (strlen("sta_network") < WLAN_NETWORK_NAME_MAX_LENGTH) ?
                                   (strlen("sta_network") + 1) :
                                   WLAN_NETWORK_NAME_MAX_LENGTH;
                strncpy(sta_network.name, "sta_network", network_name_len);

                char *ssid = get_configuration()->ssid;
                char *passw = get_configuration()->password;

                ssid_len = (strlen(ssid) <= IEEEtypes_SSID_SIZE) ? strlen(ssid) : IEEEtypes_SSID_SIZE;
                memcpy(sta_network.ssid, (const char *)ssid, ssid_len);


                if (get_configuration()->wifiUseDHCP) {

                    sta_network.ip.ipv4.addr_type = ADDR_TYPE_DHCP;

                } else {

                    sta_network.ip.ipv4.addr_type = ADDR_TYPE_STATIC;

                    sta_network.ip.ipv4.address = get_configuration()->wifiIp.addr;
                    sta_network.ip.ipv4.netmask = get_configuration()->wifiMask.addr;
                    sta_network.ip.ipv4.gw = get_configuration()->wifiGW.addr;
                    sta_network.ip.ipv4.dns1 = get_configuration()->wifiDns1.addr;
                    sta_network.ip.ipv4.dns2 = get_configuration()->wifiDns2.addr;

                }

                sta_network.ssid_specific     = 1;

                if (strlen(passw)) {
                    sta_network.security.type = WLAN_SECURITY_WILDCARD;
                    psk_len = (strlen(passw) <= (WLAN_PSK_MAX_LENGTH - 1)) ? strlen(passw) :
                              (WLAN_PSK_MAX_LENGTH - 1);
                    strncpy(sta_network.security.psk, passw, psk_len);
                    sta_network.security.psk_len = psk_len;
                } else {
                    sta_network.security.type = WLAN_SECURITY_NONE;
                }

                ret = wlan_add_network(&sta_network);

                if (ret != 0) {
                    PRINTF(" Failed to add network %d\r\n", ret);
                    return 0;
                }
                network_added = 1;

            }

            if (xInitTaskNotify != NULL) {
                xTaskNotify(xInitTaskNotify, WM_SUCCESS, eSetValueWithOverwrite);
                xInitTaskNotify = NULL;
            }

            break;
        case WLAN_REASON_INITIALIZATION_FAILED:
            PRINTF("app_cb: WLAN: initialization failed\r\n");

            if (xInitTaskNotify != NULL) {
                xTaskNotify(xInitTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xInitTaskNotify = NULL;
            }

            break;
        case WLAN_REASON_ADDRESS_SUCCESS:
            PRINTF("network mgr: DHCP new lease\r\n");
            break;
        case WLAN_REASON_ADDRESS_FAILED:
            PRINTF("app_cb: failed to obtain an IP address\r\n");
            break;
        case WLAN_REASON_USER_DISCONNECT:
            PRINTF("app_cb: disconnected\r\n");
            break;
        case WLAN_REASON_LINK_LOST:
            PRINTF("app_cb: WLAN: link lost\r\n");
            break;
        case WLAN_REASON_SUCCESS:
            PRINTF("Connected to [%s]\r\n", sta_network.ssid);
                wlan_store_dhcp_data_to_conf();
            if (xJoinTaskNotify != NULL) {
                xTaskNotify(xJoinTaskNotify, WM_SUCCESS, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_AUTH_SUCCESS:
            PRINTF("WLAN: authentication successful\r\n");
            break;
        case WLAN_REASON_CONNECT_FAILED:
            PRINTF("[!] WLAN: connect failed\r\n");
            if (xJoinTaskNotify != NULL) {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_NETWORK_NOT_FOUND:
            PRINTF("[!] WLAN: network not found\r\n");
            if (xJoinTaskNotify != NULL) {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_NETWORK_AUTH_FAILED:
            PRINTF("[!] Network Auth failed\r\n");
            if (xJoinTaskNotify != NULL) {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        default:
            PRINTF("app_cb: WLAN: Unknown Event: %d\r\n", reason);
    }
    return 0;
}

static void wifiTaskMain(void *param)
{
    int32_t result = 0;
    ip4_addr_t ip;

    /* Undo reset maya */
    GPIO_PinWrite(BOARD_INITPINS_MAYA_PDN_GPIO, BOARD_INITPINS_MAYA_PDN_GPIO_PIN, 0U);
    os_thread_sleep(os_msec_to_ticks(100));
    GPIO_PinWrite(BOARD_INITPINS_MAYA_PDN_GPIO, BOARD_INITPINS_MAYA_PDN_GPIO_PIN, 1U);
    os_thread_sleep(os_msec_to_ticks(5));


    PRINTF("Initialize WLAN Driver\r\n");
    wifi_initialization_result = wlan_init(wlan_fw_bin, wlan_fw_bin_len);
    if (WM_SUCCESS != wifi_initialization_result) {
        PRINTF("Wlan initialization failed");
    }

    wlan_get_mac_address(wifi_mac_addr);

    if (!(get_configuration()->wifiEnabled)) {
        vTaskDelete(NULL);
    }

    xInitTaskNotify = xTaskGetCurrentTaskHandle();
    result          = wlan_start(wlan_event_callback);
    if (WM_SUCCESS != result) {
        PRINTF("Couldn't start wlan\r\n");
    }


    if (WM_SUCCESS == ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) {
        while (!sta_network_available) {
            firstResult = 0;
            scan();
            while (!firstResult) {
                os_thread_sleep(os_msec_to_ticks(500));
            }

            if (sta_network_available) {

                xJoinTaskNotify = xTaskGetCurrentTaskHandle();
                conToAp();

                if (WM_SUCCESS == ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) {
                    /* create any other thread to be executed using the wifi functionality here */
                    vTaskDelete(NULL);
                } else {
                    PRINTF("Connection Failed! \r\n");
                    vTaskDelete(NULL);
                }
            } else {
                os_thread_sleep(os_msec_to_ticks(5000));
            }
        }
    } else {
        PRINTF("Wlan initialization failed");
    }

}

int create_wifi_thread(void)
{
    BaseType_t result = 0;

    PRINTF("Creating Wifi Thread\r\n");

    result = xTaskCreate(wifiTaskMain, WIFI_TASK_NAME, WIFI_TASK_STACK_SIZE, NULL, WIFI_TASK_PRIORITY, NULL);
    assert(pdPASS == result);

    return result;
}

void wlan_store_dhcp_data_to_conf()
{
    struct wlan_ip_config ip_addr;
    wlan_get_address(&ip_addr);
    PRINTF("Address acquired: %s\r\n", ipaddr_ntoa((const ip_addr_t *)&ip_addr.ipv4.address));

	taskENTER_CRITICAL();
	get_configuration()->wifiIp.addr = ip_addr.ipv4.address;
	get_configuration()->wifiMask.addr = ip_addr.ipv4.netmask;
	get_configuration()->wifiGW.addr = ip_addr.ipv4.gw;
	get_configuration()->wifiDns1.addr = ip_addr.ipv4.dns1;
	get_configuration()->wifiDns2.addr = ip_addr.ipv4.dns2;
	taskEXIT_CRITICAL();
}

bool wifi_is_initialized()
{
    return (WM_SUCCESS == wifi_initialization_result);
}

unsigned char *wifi_get_mac_addr()
{
    return wifi_mac_addr;
}
