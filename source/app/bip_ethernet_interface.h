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

#ifndef BIP_ETHERNET_INTERFACE_H_
#define BIP_ETHERNET_INTERFACE_H_

#include <app/bip_tasks.h>

#define ETHERNET_DEFAULT_NETIF  1

#define ENABLE_MDNS_FOR_ETHERNET_NETIF 0
#define MDNS_HOSTNAME "evb-ant-1" //.local

/* MAC address configuration. */
#define configMAC_ADDR                     \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x11 \
    }

/* Address of PHY interface. */
#define ENET_PHY_ADDRESS BOARD_ENET0_PHY_ADDRESS

/* MDIO operations. */
#define ENET_MDIO_OPS enet_ops

/* PHY operations. */
#define ENET_PHY_OPS phyksz8041_ops

/* ENET clock frequency. */
#define ENET_CLOCK_FREQ CLOCK_GetFreq(kCLOCK_IpgClk)

#ifndef ENET_NETIF_INIT_FN
/*! @brief Network interface initialization function. */
#define ENET_NETIF_INIT_FN ethernetif0_init
#endif /* ENET_NETIF_INIT_FN */

/**
 * Initializes and starts the task that handles the Ethernet network interface
 */
int ethernet_init(void);

/**
 * Stores the dynamically obtained addresses and masks to the local configuration object
 * It is useful to display the actual information to the user
 */
void update_configuration_wth_enet_DHCP_data(void);

#endif /* ETHERNET_INTERFACE_H_ */
