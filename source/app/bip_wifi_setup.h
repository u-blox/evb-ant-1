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

#ifndef BIP_WIFI_SETUP_H
#define BIP_WIFI_SETUP_H

#include <app/bip_tasks.h>


/**
 * Creates the thread that initializes the wifi handling functionality
 */
int create_wifi_thread(void);

/**
 * Updates the configuration data with the actual addresses obtained from DHCP.
 * Does not alter the permanently stored configuration
 */
void wlan_store_dhcp_data_to_conf(void);

/**
 * Checks if The initialization of WiFi was completed successfully
 */
bool wifi_is_initialized(void);

/**
 * Returns a pointer to a 6-byte-length char array containing the MAC address of MAYA module
 */
unsigned char *wifi_get_mac_addr(void);

#endif
