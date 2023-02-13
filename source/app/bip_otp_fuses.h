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

#ifndef BIP_OTP_FUSES_H_
#define BIP_OTP_FUSES_H_


#include "clock_config.h"
#include "fsl_ocotp.h"
#include "fsl_debug_console.h"

#define OCOTP_FREQ_HZ (CLOCK_GetFreq(kCLOCK_IpgClk))
#define UNIQUE_ID_ADDR_0    0x01
#define UNIQUE_ID_ADDR_1    0x02
#define UNIQUE_ID_ADDR_1_MAYBE  0x03
#define MAC_0   0x22
#define MAC_1   0x23
#define MAC_2   0x24

/**
 *	Get the MAC address generated from the OTP fuses as a pointer to a 6-byte array
 *	If there is a non-zero MAC address burned in the dedicated MAC fuses, it is preferred.
 *	Otherwise the MAC address is generated from the unique id found in the fuses
 */
unsigned char *get_mac_addr_array_from_OTP(void);

/**
 * Get the MAC address found in the dedicated OTP fuses as a 64-bit integer
 */
unsigned long long get_mac_from_OTP(void);

/**
 * Get the unique id found in the dedicated OTP fuses as a 64-bit integer
 */
unsigned long long get_unique_id_from_OTP(void);

#endif /* OTP_FUSES_H_ */
