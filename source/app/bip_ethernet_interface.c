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

#include <app/bip_ethernet_interface.h>
#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/netifapi.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/dns.h"
#include "netif/ethernet.h"
#include "netif/etharp.h"
#include "enet_ethernetif.h"
#include "lwip/apps/mdns.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_phy.h"

#include "fsl_phyksz8041.h"
#include "fsl_enet_mdio.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include <app/bip_configuration.h>

/*Just to use the wlan copy of tcp/ip thread initialization, where it also checks if it is already initialized*/
#include <wm_net.h>

#include <app/bip_otp_fuses.h>

static mdio_handle_t mdioHandle = {.ops = &ENET_MDIO_OPS};
static phy_handle_t phyHandle   = {.phyAddr = ENET_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &ENET_PHY_OPS};
static struct netif ethernet_netif;

static volatile bool enet_is_up = false;

void  BOARD_ENET_INT_IRQ_HANDLER(void)
{
    GPIO_PortClearInterruptFlags(BOARD_INITPINS_INT1_COMBO_GPIO, 1U << BOARD_INITPINS_INT1_COMBO_GPIO_PIN);
    PRINTF("ENET link up interrupt\n");
    enet_is_up = true;
    SDK_ISR_EXIT_BARRIER;
}

static void BOARD_InitModuleClock(void)
{
    const clock_enet_pll_config_t config = {.enableClkOutput = true, .enableClkOutput25M = false, .loopDivider = 1};
    CLOCK_InitEnetPll(&config);
}

static void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i) {
        __asm("NOP"); /* delay */
    }
}

static void http_srv_txt(struct mdns_service *service, void *txt_userdata)
{
    mdns_resp_add_service_txtitem(service, "path=/", 6);
}

static void ethernet_netif_init(void *arg)
{
	LWIP_UNUSED_ARG(arg);

    ip4_addr_t netif_ipaddr, netif_netmask, netif_gw, dns1, dns2;
    ethernetif_config_t enet_config = {
        .phyHandle  = &phyHandle,
        .macAddress = configMAC_ADDR,
    };

    memcpy(enet_config.macAddress, get_mac_addr_array_from_OTP(), NETIF_MAX_HWADDR_LEN);

    uint8_t has_gateway = 1;

    mdioHandle.resource.csrClock_Hz = ENET_CLOCK_FREQ;

    if (get_configuration()->enetUseDHCP) {
        IP4_ADDR(&netif_ipaddr, 0, 0, 0, 0);
        IP4_ADDR(&netif_netmask, 0, 0, 0, 0);
        IP4_ADDR(&netif_gw, 0, 0, 0, 0);

        net_ipv4stack_init();

        netifapi_netif_add(&ethernet_netif, &netif_ipaddr, &netif_netmask, (has_gateway) ? &netif_gw : NULL, &enet_config,
                           ENET_NETIF_INIT_FN, tcpip_input);

#if ETHERNET_DEFAULT_NETIF == 1
        netifapi_netif_set_default(&ethernet_netif);
#endif
        netifapi_netif_set_up(&ethernet_netif);

        if (dhcp_start(&ethernet_netif) != ERR_OK) {
            PRINTF("Failed to initialize dhcp for ethernet netif");
            __BKPT(0);
        }

    } else {

        netif_ipaddr = get_configuration()->enetIp;
        netif_netmask = get_configuration()->enetMask;
        netif_gw = get_configuration()->enetGW;
        dns1 = get_configuration()->enetDns1;
        dns2 = get_configuration()->enetDns2;

        net_ipv4stack_init();

        netifapi_netif_add(&ethernet_netif, &netif_ipaddr, &netif_netmask, (has_gateway) ? &netif_gw : NULL, &enet_config,
                           ENET_NETIF_INIT_FN, tcpip_input);

#if ETHERNET_DEFAULT_NETIF == 1
        netifapi_netif_set_default(&ethernet_netif);
#endif
        netifapi_netif_set_up(&ethernet_netif);

        dns_setserver(0, &dns1);
        dns_setserver(1, &dns2);

    }

#if ENABLE_MDNS_FOR_ETHERNET_NETIF == 1
    LOCK_TCPIP_CORE();
    mdns_resp_init();
    mdns_resp_add_netif(&ethernet_netif, MDNS_HOSTNAME);
    mdns_resp_add_service(&ethernet_netif, MDNS_HOSTNAME, "_http", DNSSD_PROTO_TCP, 80, http_srv_txt, NULL);
    UNLOCK_TCPIP_CORE();
#endif

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" Ethernet interface initialized\r\n");
    PRINTF("************************************************\r\n");
    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&netif_ipaddr)[0], ((u8_t *)&netif_ipaddr)[1],
           ((u8_t *)&netif_ipaddr)[2], ((u8_t *)&netif_ipaddr)[3]);
    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&netif_netmask)[0], ((u8_t *)&netif_netmask)[1],
           ((u8_t *)&netif_netmask)[2], ((u8_t *)&netif_netmask)[3]);
    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&netif_gw)[0], ((u8_t *)&netif_gw)[1],
           ((u8_t *)&netif_gw)[2], ((u8_t *)&netif_gw)[3]);
    PRINTF("************************************************\r\n");

    vTaskDelete(NULL);
}

int ethernet_init(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    BOARD_InitModuleClock();
    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

    GPIO_PinInit(BOARD_INITPINS_ENET_RST_GPIO, BOARD_INITPINS_ENET_RST_PIN, &gpio_config);
    //Apply Reset
    GPIO_WritePinOutput(BOARD_INITPINS_ENET_RST_GPIO, BOARD_INITPINS_ENET_RST_PIN, 0);
    delay();
    GPIO_WritePinOutput(BOARD_INITPINS_ENET_RST_GPIO, BOARD_INITPINS_ENET_RST_PIN, 1);

    EnableIRQ(BOARD_ENET_INT_IRQ);
    GPIO_PortEnableInterrupts(BOARD_INITPINS_INT1_COMBO_GPIO, 1U << BOARD_INITPINS_INT1_COMBO_GPIO_PIN);

    /* Initialize lwIP from thread */
    if (sys_thread_new(ENET_INIT_TASK_NAME, ethernet_netif_init, NULL, ENET_INIT_TASK_STACK_SIZE,
                       ENET_INIT_TASK_PRIORITY) == NULL) {
        LWIP_ASSERT(ENET_INIT_TASK_NAME, 0);
    }

    return 0;
}

void update_configuration_wth_enet_DHCP_data(void)
{

    if (!get_configuration()->enetUseDHCP) {
        return;
    }

	taskENTER_CRITICAL();
	get_configuration()->enetDns1 = *dns_getserver(0);
	get_configuration()->enetDns2 = *dns_getserver(1);
	get_configuration()->enetIp = ethernet_netif.ip_addr;
	get_configuration()->enetMask = ethernet_netif.netmask;
	get_configuration()->enetGW = ethernet_netif.gw;
	taskEXIT_CRITICAL();

}

#endif
