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

#ifndef BIP_HTTP_SERVER_H
#define BIP_HTTP_SERVER_H

#include <app/bip_tasks.h>


#define CGI_DATA_LENGTH_MAX (500)

#define AUTH_USERNAME   "admin"
#define AUTH_PASSWORD   "admin"

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG LWIP_DBG_ON
#endif
#ifndef HTTPD_STACKSIZE
#define HTTPD_STACKSIZE HTTP_SRV_TASK_STACK_SIZE
#endif
#ifndef HTTPD_PRIORITY
#define HTTPD_PRIORITY HTTP_SRV_TASK_PRIORITY
#endif
#ifndef DEBUG_WS
#define DEBUG_WS 0
#endif


/**
 * Initializes the task that handles the http server functionality
 */
int create_http_server_thread(void);


#endif
