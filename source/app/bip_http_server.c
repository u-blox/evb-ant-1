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

#include "lwip/opt.h"

#if LWIP_SOCKET
#include "lwip/sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "fsl_wdog.h"

#include "httpsrv.h"

#include <app/bip_http_server.h>

#include <app/bip_configuration.h>
#include <app/bip_nina_gpios.h>
#include <app/bip_nina_uart_thread.h>
#include <app/bip_version.h>

static void cgi_urldecode(char *url);
static int cgi_reboot(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_nina_reset(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_nina_sw1(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_nina_sw2(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_nina_at_cmd(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_firmware_version(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT *param);
static int cgi_configuration(HTTPSRV_CGI_REQ_STRUCT *param);
static int ssi_config(HTTPSRV_SSI_PARAM_STRUCT *param);
static bool cgi_get_varval(char *var_str, char *var_name, char *var_val, uint32_t length);


/* FS data.*/
extern const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[];

/*
 * Authentication users
 */
static const HTTPSRV_AUTH_USER_STRUCT users[] = {
    {AUTH_USERNAME, AUTH_PASSWORD}, {NULL, NULL} /* Array terminator */
};

/*
 * Authentication information.
 */
static const HTTPSRV_AUTH_REALM_STRUCT auth_realms[] = {
    {"Please use uid:admin pass:admin to login", "/auth.html", HTTPSRV_AUTH_BASIC, users},
    {NULL, NULL, HTTPSRV_AUTH_INVALID, NULL} /* Array terminator */
};

char cgi_data[CGI_DATA_LENGTH_MAX + 1];

const HTTPSRV_CGI_LINK_STRUCT cgi_lnk_tbl[] = {
    {"rtcdata", cgi_rtc_data},
    {"get", cgi_configuration},
    {"post", cgi_configuration},
    {"reboot", cgi_reboot},
    {"nina_reset", cgi_nina_reset},
    {"nina_sw1", cgi_nina_sw1},
    {"nina_sw2", cgi_nina_sw2},
    {"at_cmd", cgi_nina_at_cmd},
	{"get_version", cgi_firmware_version},
    {0, 0} // DO NOT REMOVE - last item - end of table
};

const HTTPSRV_SSI_LINK_STRUCT ssi_lnk_tbl[] = {{"config", ssi_config}, {0, 0}};

static int cgi_reboot(HTTPSRV_CGI_REQ_STRUCT *param)
{
	WDOG_TriggerSystemSoftwareReset(WDOG1);
    return 0;
}

static int cgi_nina_reset(HTTPSRV_CGI_REQ_STRUCT *param)
{
    nina_apply_reset();
    return 0;
}

static int cgi_nina_sw1(HTTPSRV_CGI_REQ_STRUCT *param)
{
    nina_apply_sw1();
    return 0;
}

static int cgi_nina_sw2(HTTPSRV_CGI_REQ_STRUCT *param)
{
    nina_apply_sw2();
    return 0;
}

static int cgi_nina_at_cmd(HTTPSRV_CGI_REQ_STRUCT *param)
{
    PRINTF("cgi_nina_at_cmd\n");

    if (param->request_method == HTTPSRV_REQ_POST) {
        uint32_t length = 0;
        uint32_t read;
        char buffer[sizeof("command=") + CGI_DATA_LENGTH_MAX] = {0};

        length = param->content_length;
        read   = HTTPSRV_cgi_read(param->ses_handle, buffer, (length > sizeof(buffer)) ? sizeof(buffer) : length);

        if (read > 0) {
            cgi_get_varval(buffer, "command", cgi_data, sizeof(cgi_data));
            cgi_urldecode(cgi_data);

            nina_send_at(cgi_data, strlen(cgi_data));
        }
    }

    return 0;
}

static int cgi_firmware_version(HTTPSRV_CGI_REQ_STRUCT *param){
    HTTPSRV_CGI_RES_STRUCT response;
    char str[] = FIRMWARE_VERSION_STR;

    if (param->request_method != HTTPSRV_REQ_GET) {
        return (0);
    }

    response.ses_handle     = param->ses_handle;
    response.content_type   = HTTPSRV_CONTENT_TYPE_PLAIN;
    response.status_code    = HTTPSRV_CODE_OK;
    response.data           = str;
    response.data_length    = strlen(str);
    response.content_length = response.data_length;

    HTTPSRV_cgi_write(&response);
    return (response.content_length);
}

static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT *param)
{
#define BUFF_SIZE sizeof("00\n00\n00\n")
    HTTPSRV_CGI_RES_STRUCT response;
    uint32_t time;
    uint32_t min;
    uint32_t hour;
    uint32_t sec;

    char str[BUFF_SIZE];
    uint32_t length = 0;

    if (param->request_method != HTTPSRV_REQ_GET) {
        return (0);
    }

    time = sys_now();

    sec  = time / 1000;
    min  = sec / 60;
    hour = min / 60;
    min %= 60;
    sec %= 60;

    response.ses_handle   = param->ses_handle;
    response.content_type = HTTPSRV_CONTENT_TYPE_PLAIN;
    response.status_code  = HTTPSRV_CODE_OK;
    /*
    ** When the keep-alive is used we have to calculate a correct content length
    ** so the receiver knows when to ACK the data and continue with a next request.
    ** Please see RFC2616 section 4.4 for further details.
    */

    /* Calculate content length while saving it to buffer */
    length                  = snprintf(str, BUFF_SIZE, "%ld\n%ld\n%ld\n", hour, min, sec);
    response.data           = str;
    response.data_length    = length;
    response.content_length = response.data_length;
    /* Send response */
    HTTPSRV_cgi_write(&response);
    return (response.content_length);
}

static int cgi_configuration(HTTPSRV_CGI_REQ_STRUCT *param)
{
    HTTPSRV_CGI_RES_STRUCT response = {0};

    response.ses_handle  = param->ses_handle;
    response.status_code = HTTPSRV_CODE_OK;

    if (param->request_method == HTTPSRV_REQ_GET) {

        stringify_configuration(cgi_data, sizeof(cgi_data));
        char *c;
        /* Replace '+' with spaces. */
        while ((c = strchr(cgi_data, '+')) != NULL) {
            *c = ' ';
        }
        response.content_type   = HTTPSRV_CONTENT_TYPE_PLAIN;
        response.data           = cgi_data;
        response.data_length    = strlen(cgi_data);
        response.content_length = response.data_length;
        HTTPSRV_cgi_write(&response);
    } else if (param->request_method == HTTPSRV_REQ_POST) {
        uint32_t length = 0;
        uint32_t read;
        char buffer[sizeof("post_input = ") + CGI_DATA_LENGTH_MAX] = {0};

        length = param->content_length;
        read   = HTTPSRV_cgi_read(param->ses_handle, buffer, (length > sizeof(buffer)) ? sizeof(buffer) : length);

        if (read > 0) {
            cgi_get_varval(buffer, "post_input", cgi_data, sizeof(cgi_data));
            cgi_urldecode(cgi_data);

            parse_json_configuration(cgi_data);
        }

        /* Write the response using chunked transmission coding. */
        response.content_type = HTTPSRV_CONTENT_TYPE_HTML;
        /* Set content length to -1 to indicate unknown content length. */
        response.content_length = -1;
        response.data           = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">";
        response.data_length    = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data        = "<html><head><title>POST successfull!</title>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data        = "<meta http-equiv=\"refresh\" content=\"0; url=cgi.html\"></head><body></body></html>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data_length = 0;
        HTTPSRV_cgi_write(&response);
    }

    return (response.content_length);
}

static bool cgi_get_varval(char *src, char *var_name, char *dst, uint32_t length)
{
    char *name;
    bool result;
    uint32_t index;
    uint32_t n_length;

    result = false;
    dst[0] = 0;
    name   = src;

    n_length = strlen(var_name);

    while ((name != NULL) && ((name = strstr(name, var_name)) != NULL)) {
        if (name[n_length] == '=') {
            name += n_length + 1;

            index = strcspn(name, "&");
            if (index >= length) {
                index = length - 1;
            }
            strncpy(dst, name, index);
            dst[index] = '\0';
            result     = true;
            break;
        } else {
            name = strchr(name, '&');
        }
    }

    return (result);
}

static int ssi_config(HTTPSRV_SSI_PARAM_STRUCT *param)
{
    char *string_value = NULL;
    int int_value      = -1;
    char str[16];

    if (strcmp(param->com_param, "SERVER_STACK_SIZE") == 0) {
        int_value = HTTPSRV_CFG_SERVER_STACK_SIZE;
    } else if (strcmp(param->com_param, "HTTP_SESSION_STACK_SIZE") == 0) {
        int_value = HTTPSRV_CFG_HTTP_SESSION_STACK_SIZE;
    } else if (strcmp(param->com_param, "HTTPS_SESSION_STACK_SIZE") == 0) {
        int_value = HTTPSRV_CFG_HTTPS_SESSION_STACK_SIZE;
    } else if (strcmp(param->com_param, "DEFAULT_PRIORITY") == 0) {
        int_value = HTTPSRV_CFG_DEFAULT_PRIORITY;
    } else if (strcmp(param->com_param, "DEFAULT_HTTP_PORT") == 0) {
        int_value = HTTPSRV_CFG_DEFAULT_HTTP_PORT;
    } else if (strcmp(param->com_param, "DEFAULT_HTTPS_PORT") == 0) {
        int_value = HTTPSRV_CFG_DEFAULT_HTTPS_PORT;
    } else if (strcmp(param->com_param, "DEFAULT_INDEX_PAGE") == 0) {
        string_value = HTTPSRV_CFG_DEFAULT_INDEX_PAGE;
    } else if (strcmp(param->com_param, "CACHE_MAXAGE") == 0) {
        int_value = HTTPSRV_CFG_CACHE_MAXAGE;
    } else if (strcmp(param->com_param, "DEFAULT_SES_CNT") == 0) {
        int_value = HTTPSRV_CFG_DEFAULT_SES_CNT;
    } else if (strcmp(param->com_param, "SES_BUFFER_SIZE") == 0) {
        int_value = HTTPSRV_CFG_SES_BUFFER_SIZE;
    } else if (strcmp(param->com_param, "DEFAULT_URL_LEN") == 0) {
        int_value = HTTPSRV_CFG_DEFAULT_URL_LEN;
    } else if (strcmp(param->com_param, "MAX_SCRIPT_LN") == 0) {
        int_value = HTTPSRV_CFG_MAX_SCRIPT_LN;
    } else if (strcmp(param->com_param, "KEEPALIVE_ENABLED") == 0) {
        int_value = HTTPSRV_CFG_KEEPALIVE_ENABLED;
    } else if (strcmp(param->com_param, "KEEPALIVE_TIMEOUT") == 0) {
        int_value = HTTPSRV_CFG_KEEPALIVE_TIMEOUT;
    } else if (strcmp(param->com_param, "SES_TIMEOUT") == 0) {
        int_value = HTTPSRV_CFG_SES_TIMEOUT;
    } else if (strcmp(param->com_param, "SEND_TIMEOUT") == 0) {
        int_value = HTTPSRV_CFG_SEND_TIMEOUT;
    } else if (strcmp(param->com_param, "RECEIVE_TIMEOUT") == 0) {
        int_value = HTTPSRV_CFG_RECEIVE_TIMEOUT;
    } else if (strcmp(param->com_param, "WEBSOCKET_ENABLED") == 0) {
        int_value = HTTPSRV_CFG_WEBSOCKET_ENABLED;
    } else if (strcmp(param->com_param, "WOLFSSL_ENABLE") == 0) {
        int_value = HTTPSRV_CFG_WOLFSSL_ENABLE;
    } else if (strcmp(param->com_param, "MBEDTLS_ENABLE") == 0) {
        int_value = HTTPSRV_CFG_MBEDTLS_ENABLE;
    }

    if (string_value != NULL) {
        HTTPSRV_ssi_write(param->ses_handle, string_value, strlen(string_value));
    } else {
        sprintf(str, "%d", int_value);
        HTTPSRV_ssi_write(param->ses_handle, str, strlen(str));
    }

    return (0);
}

/* Decode URL encoded string in place. */
static void cgi_urldecode(char *url)
{
    char *src = url;
    char *dst = url;

    while (*src != '\0') {
        if ((*src == '%') && (isxdigit((unsigned char) * (src + 1))) && (isxdigit((unsigned char) * (src + 2)))) {
            *src       = *(src + 1);
            *(src + 1) = *(src + 2);
            *(src + 2) = '\0';
            *dst++     = strtol(src, NULL, 16);
            src += 3;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}


/*!
 * @brief Initializes server.
 */
static void http_server_socket_init(void)
{
    HTTPSRV_PARAM_STRUCT params;
    uint32_t httpsrv_handle;

    /* Init Fs*/
    HTTPSRV_FS_init(httpsrv_fs_data);

    /* Init HTTPSRV parameters.*/
    memset(&params, 0, sizeof(params));
    params.root_dir    = "";
    params.index_page  = "/index.html";
    params.auth_table  = auth_realms;
    params.cgi_lnk_tbl = cgi_lnk_tbl;
    params.ssi_lnk_tbl = ssi_lnk_tbl;

    /* Init HTTP Server.*/
    httpsrv_handle = HTTPSRV_init(&params);
    if (httpsrv_handle == 0) {
        LWIP_PLATFORM_DIAG(("HTTPSRV_init() is Failed"));
    }
}

/*!
 * @brief The main function containing server thread.
 */
static void http_main_thread(void *arg)
{
    LWIP_UNUSED_ARG(arg);

    http_server_socket_init();

    vTaskDelete(NULL);
}

/*!
 * @brief Main function.
 */
int create_http_server_thread(void)
{
    /* create server thread in RTOS */
    if (!sys_thread_new(HTTP_SRV_INIT_TASK_NAME, http_main_thread, NULL, HTTP_SRV_INIT_TASK_STACK_SIZE,
                        HTTP_SRV_INIT_TASK_PRIORITY)) {
        LWIP_ASSERT("http server: Task creation failed.", 0);
    }

    return 0;
}

#endif // LWIP_SOCKET

