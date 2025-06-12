#ifndef __INCLUDE_ESP32_AKRI_H__
#define __INCLUDE_ESP32_AKRI_H__

#include "esp_http_server.h"

int akri_server_start();

int akri_server_end();

int akri_set_update_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_info_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_temp_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_onboard_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_handler_generic(const char *uri,
			     httpd_method_t method,
			     esp_err_t (*handler)(httpd_req_t *req));
#endif
