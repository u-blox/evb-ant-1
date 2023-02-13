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

#ifndef BIP_CONFIGURATION_H_
#define BIP_CONFIGURATION_H_

#include <inttypes.h>
#include <stddef.h>
#include <utils/utils_crc.h>
#include "lwip/ip_addr.h"


/*The field names for the json text*/
#define WIFIEN_NAME         "wifien"
#define SSID_NAME           "ssid"
#define PASSWORD_NAME       "password"
#define ENETEN_NAME         "eneten"
#define ENETIP_NAME         "enetip"
#define ENETMASK_NAME       "enetmask"
#define ENETGW_NAME         "enetgw"
#define POSENGIP_NAME       "posengip"
#define POSENGPORT_NAME     "posengport"
#define ENETUSEDHCP_NAME    "enetuseDHCP"
#define WIFIIP_NAME         "wifiip"
#define WIFIMASK_NAME       "wifimask"
#define WIFIGW_NAME         "wifigw"
#define WIFIUSEDHCP_NAME    "wifiuseDHCP"
#define WIFIDNS_1           "wifidns1"
#define WIFIDNS_2           "wifidns2"
#define ENETDNS_1           "enetdns1"
#define ENETDNS_2           "enetdns2"
#define USEONBOARDNINA      "onboardNina"
#define WIFI_RSSI_NAME      "wifirssi"

#define HARDCODED_ENET_IP   "192.168.1.102"
#define HARDCODED_ENET_MASK "255.255.255.0"
#define HARDCODED_ENET_GW   "192.168.1.1"

/**
 * The struct that holds all of the configuration data.
 * Also used as scheme for the flash memory storage
 */
typedef struct Configuration {
    char ssid[32];
    char password[64];
    ip4_addr_t enetIp;
    ip4_addr_t enetMask;
    ip4_addr_t enetGW;
    char posEngIp[20];
    uint16_t posEngPort;
    uint8_t wifiEnabled;
    uint8_t enetUseDHCP;
    ip4_addr_t wifiIp;
    ip4_addr_t wifiMask;
    ip4_addr_t wifiGW;
    ip4_addr_t wifiDns1;
    ip4_addr_t wifiDns2;
    ip4_addr_t enetDns1;
    ip4_addr_t enetDns2;
    uint8_t wifiUseDHCP;
    uint8_t enetEnabled;
    uint8_t useOnboardNina;
    uint8_t _padding;
    /* Do NOT add any other field after this line */
    crc conf_crc;

} Configuration_t;

/**
 * Populates the static configuration object with the data stored in flash
 * Data validity is checked using Cyclic Redundancy Check. If found invalid,
 * configuration falls back to the hard-coded default values.
 * If this function is called while button SW1 is pressed, the saved configuration is
 * overwritten with the default values
 */
void load_configuration_from_flash(void);

/**
 * Accepts a json string containing new configuration data.
 * The data are stored to the static configuration object and also in flash memory
 */
int parse_json_configuration(char *conf_str_buf);

/**
 * Returns a pointer to the static configuration object
 * It is safe to use it for read purposes
 * If caller uses it to write to the configuration (only to the volatile object),
 * it is probably safer to do so inside a critical section
 */
Configuration_t *get_configuration(void);

/**
 * Serializes the configuration object to a json string.
 * The string is written to the supplied buffer,
 * without exceeding the total buffer length
 */
void stringify_configuration(char *buf, size_t buffer_length);

#endif /* CONFIGURATION_H_ */
