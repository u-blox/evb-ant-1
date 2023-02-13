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
#include <app/bip_measurements_queue.h>
#include <app/bip_position_engine_link.h>
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"


static void measurements_relay_thread(void *arg)
{
    static char message_buffer[MEASUREMENT_MESSAGE_LENGTH];
    memset(message_buffer, 0, sizeof(message_buffer));
    struct netconn *conn;
    struct netbuf *buf;
    ip_addr_t addr;
    char *data;

    int i;

    if (!ipaddr_aton(get_configuration()->posEngIp, &addr)) {
        PRINTF("Failed to convert %s to ip\r\n", get_configuration()->posEngIp);
        PRINTF("Executing a DNS query\n");
        if (netconn_gethostbyname(get_configuration()->posEngIp, &addr) != ERR_OK) {
            PRINTF("DNS query failed\n");
        }
    }

    while (1) {

        /* create a new connection */
        conn = netconn_new(NETCONN_UDP);
        if (!conn) {
            PRINTF("Failed to create network connection\r\n");
            __BKPT(0);
        }

        /* connect the connection to the remote host */
        if (netconn_connect(conn, &addr, get_configuration()->posEngPort) != ERR_OK) {
            PRINTF("failed to connect to udp server\r\n");
            __BKPT(0);
        }

        while (1) {

            /* create a new netbuf */
            buf = netbuf_new();
            if (!buf) {
                PRINTF("Failed to create network buffer\r\n");
                __BKPT(0);
            }

            if (get_measurement_from_queue((measurement_t *)message_buffer) == 0) {

                size_t message_length =  strlen(message_buffer);
                data = netbuf_alloc(buf, message_length);
                memcpy(data, message_buffer, message_length);
                if (!data) {
                    PRINTF("Failed to allocate memory for the udp payload\r\n");
                    __BKPT(0);
                }

                if (netconn_send(conn, buf) != ERR_OK) {
                    netbuf_delete(buf);
                    break;
                }
            }
            netbuf_delete(buf);
        }

        /* deallocate connection and netbuf */
        netconn_delete(conn);
    }
}

void position_engine_link_init(void)
{
    sys_thread_new(POSENG_TASK_NAME, measurements_relay_thread, NULL, POSENG_TASK_STACK_SIZE, POSENG_TASK_PRIORITY);
}
