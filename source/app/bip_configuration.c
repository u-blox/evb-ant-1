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

#include <tiny-json.h>
#include <json-maker.h>
#include <app/bip_configuration.h>
#include <app/bip_ethernet_interface.h>
#include <app/bip_non_volatile_storage.h>
#include <app/bip_wifi_setup.h>
#include "wlan.h"

static Configuration_t conf;

static void load_hardcoded_conf(void)
{
    memset(&conf, 0, sizeof(conf));
    conf.enetEnabled = true;
    ipaddr_aton(HARDCODED_ENET_IP, &conf.enetIp);
    ipaddr_aton(HARDCODED_ENET_MASK, &conf.enetMask);
    ipaddr_aton(HARDCODED_ENET_GW, &conf.enetGW);
}

void load_configuration_from_flash(void)
{
    memcpy(&conf, read_from_flash(), sizeof(conf));

    /* Reset configuration, when SW1 button is pressed on boot*/
    if (!GPIO_PinRead(BOARD_INITPINS_MCU_SW1_GPIO, BOARD_INITPINS_MCU_SW1_PIN)) {
        load_hardcoded_conf();
        conf.conf_crc = calculate_crc( (unsigned char const *) &conf, sizeof(conf) - sizeof(conf.conf_crc));
        store_to_flash(0, &conf, sizeof(conf));
    }

    if (calculate_crc( (unsigned char const *) &conf, sizeof(conf) - sizeof(conf.conf_crc)) != conf.conf_crc) {
        load_hardcoded_conf();
    }
}

Configuration_t *get_configuration(void)
{
    return &conf;
}

int parse_json_configuration(char *conf_str_buf)
{
    static json_t mem[50];
    memset(mem, 0, sizeof(mem));
    json_t const *json = json_create( conf_str_buf, mem, sizeof mem / sizeof * mem );

    if ( !json ) {
        return EXIT_FAILURE;
    }

    if (json_getProperty(json, WIFIEN_NAME)) {
        conf.wifiEnabled = json_getBoolean(json_getProperty(json, WIFIEN_NAME));
    }

    if (json_getProperty(json, SSID_NAME) && json_getProperty(json, PASSWORD_NAME)) {
        strcpy(conf.ssid, json_getPropertyValue(json, SSID_NAME));
        strcpy(conf.password, json_getPropertyValue(json, PASSWORD_NAME));
    }

    if (json_getProperty(json, ENETIP_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, ENETIP_NAME), &conf.enetIp)) {
            conf.enetIp.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, ENETMASK_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, ENETMASK_NAME), &conf.enetMask)) {
            conf.enetMask.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, ENETGW_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, ENETGW_NAME), &conf.enetGW)) {
            conf.enetGW.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, POSENGIP_NAME)) {
        strcpy(conf.posEngIp, json_getPropertyValue(json, POSENGIP_NAME));
    }

    if (json_getProperty(json, POSENGPORT_NAME)) {
        conf.posEngPort = json_getInteger(json_getProperty(json, POSENGPORT_NAME));
    }

    if (json_getProperty(json, ENETUSEDHCP_NAME)) {
        conf.enetUseDHCP = json_getBoolean(json_getProperty(json, ENETUSEDHCP_NAME));
    }

    if (json_getProperty(json, WIFIIP_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, WIFIIP_NAME), &conf.wifiIp)) {
            conf.wifiIp.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, WIFIMASK_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, WIFIMASK_NAME), &conf.wifiMask)) {
            conf.wifiMask.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, WIFIGW_NAME)) {
        if (!ipaddr_aton(json_getPropertyValue(json, WIFIGW_NAME), &conf.wifiGW)) {
            conf.wifiGW.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, WIFIUSEDHCP_NAME)) {
        conf.wifiUseDHCP = json_getBoolean(json_getProperty(json, WIFIUSEDHCP_NAME));
    }

    if (json_getProperty(json, WIFIDNS_1)) {
        if (!ipaddr_aton(json_getPropertyValue(json, WIFIDNS_1), &conf.wifiDns1)) {
            conf.wifiDns1.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, WIFIDNS_2)) {
        if (!ipaddr_aton(json_getPropertyValue(json, WIFIDNS_2), &conf.wifiDns2)) {
            conf.wifiDns2.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, ENETDNS_1)) {
        if (!ipaddr_aton(json_getPropertyValue(json, ENETDNS_1), &conf.enetDns1)) {
            conf.enetDns1.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, ENETDNS_2)) {
        if (!ipaddr_aton(json_getPropertyValue(json, ENETDNS_2), &conf.enetDns2)) {
            conf.enetDns2.addr = IPADDR_ANY;
        }
    }

    if (json_getProperty(json, ENETEN_NAME)) {
        conf.enetEnabled = json_getBoolean(json_getProperty(json, ENETEN_NAME));
    }

    if (json_getProperty(json, USEONBOARDNINA)) {
        conf.useOnboardNina = json_getBoolean(json_getProperty(json, USEONBOARDNINA));
    }

    conf.conf_crc = calculate_crc( (unsigned char const *) &conf, sizeof(conf) - sizeof(conf.conf_crc));

    store_to_flash(0, &conf, sizeof(conf));

    return EXIT_SUCCESS;

}

void stringify_configuration(char *buf, size_t buffer_length)
{
    update_configuration_wth_enet_DHCP_data();

    char *p = buf;
    size_t rem = buffer_length;
    char ip_buf[16];

    p = json_objOpen( p, NULL, &rem);

    p = json_bool(p, WIFIEN_NAME, conf.wifiEnabled, &rem);
    p = json_str(p, SSID_NAME, conf.ssid, &rem);
    p = json_str(p, PASSWORD_NAME, conf.password, &rem);
    p = json_str(p, ENETIP_NAME, ipaddr_ntoa_r(&conf.enetIp, ip_buf, 16), &rem);
    p = json_str(p, ENETMASK_NAME, ipaddr_ntoa_r(&conf.enetMask, ip_buf, 16), &rem);
    p = json_str(p, ENETGW_NAME, ipaddr_ntoa_r(&conf.enetGW, ip_buf, 16), &rem);
    p = json_str(p, POSENGIP_NAME, conf.posEngIp, &rem);
    p = json_uint(p, POSENGPORT_NAME, conf.posEngPort, &rem);
    p = json_bool(p, ENETUSEDHCP_NAME, conf.enetUseDHCP, &rem);
    p = json_str(p, WIFIIP_NAME, ipaddr_ntoa_r(&conf.wifiIp, ip_buf, 16), &rem);
    p = json_str(p, WIFIMASK_NAME, ipaddr_ntoa_r(&conf.wifiMask, ip_buf, 16), &rem);
    p = json_str(p, WIFIGW_NAME, ipaddr_ntoa_r(&conf.wifiGW, ip_buf, 16), &rem);
    p = json_bool(p, WIFIUSEDHCP_NAME, conf.wifiUseDHCP, &rem);
    p = json_str(p, WIFIDNS_1, ipaddr_ntoa_r(&conf.wifiDns1, ip_buf, 16), &rem);
    p = json_str(p, WIFIDNS_2, ipaddr_ntoa_r(&conf.wifiDns2, ip_buf, 16), &rem);
    p = json_str(p, ENETDNS_1, ipaddr_ntoa_r(&conf.enetDns1, ip_buf, 16), &rem);
    p = json_str(p, ENETDNS_2, ipaddr_ntoa_r(&conf.enetDns2, ip_buf, 16), &rem);
    p = json_bool(p, ENETEN_NAME, conf.enetEnabled, &rem);
    p = json_bool(p, USEONBOARDNINA, conf.useOnboardNina, &rem);

    short rssi = 0;
    wlan_get_current_rssi(&rssi);
    p = json_int(p, WIFI_RSSI_NAME, (int)rssi, &rem);

    p = json_objClose(p, &rem);
    p = json_end(p, &rem);
}
