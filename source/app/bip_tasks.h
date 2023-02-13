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

#ifndef BIP_TASKS_H_
#define BIP_TASKS_H_

#include "FreeRTOSConfig.h"

/*
 * Definitions for all created tasks
 * Each task is assigned a priority from 0 to ( configMAX_PRIORITIES - 1 )
 * Low priority numbers denote low priority tasks. The idle task has priority zero (tskIDLE_PRIORITY)
 */

#define WIFI_TASK_NAME                  "wifi_task"
#define WIFI_TASK_STACK_SIZE            (800)
#define WIFI_TASK_PRIORITY              (15)

/*
 * temporary lwIP initialization thread
 * next tcp ip thread is initialized
 * with stack size 768 and priorty 2
 */
#define ENET_INIT_TASK_NAME             "enet_init"
#define ENET_INIT_TASK_STACK_SIZE       (1024)
#define ENET_INIT_TASK_PRIORITY         (1)

#define NINA_UART_TASK_NAME             "nina_task"
#define NINA_UART_TASK_STACK_SIZE       (228)
#define NINA_UART_TASK_PRIORITY         (17)

#define POSENG_TASK_NAME                "poseng_task"
#define POSENG_TASK_STACK_SIZE          (400)
#define POSENG_TASK_PRIORITY            (1)

/* Http server initialization task. */
#define HTTP_SRV_INIT_TASK_NAME         "httpsrv_init"
#define HTTP_SRV_INIT_TASK_STACK_SIZE   (400)
#define HTTP_SRV_INIT_TASK_PRIORITY     (1)

#define GEN_PURPOSE_TASK_NAME           "genprp_task"
#define GEN_PURPOSE_TASK_STACK_SIZE     (configMINIMAL_STACK_SIZE + 64)
#define GEN_PURPOSE_TASK_PRIORITY       (17)

#define CMD_LISTERNER_TASK_NAME         "cmd_listener"
#define CMD_LISTENER_TASK_STACK_SIZE    (configMINIMAL_STACK_SIZE + 100)
#define CMD_LISTENER_TASK_PRIORITY      (17)

#endif /* EVB_TASKS_H_ */
