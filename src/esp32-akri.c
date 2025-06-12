#include "esp32-akri.h"

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "esp_http_server.h"

/* Akri server handle */
httpd_handle_t akri_server = NULL;

/* predefined /update uri */
httpd_uri_t uri_update = {
    .uri      = "/update",
    .method   = HTTP_POST,
    .user_ctx = NULL
};

/* predefined /info uri */
httpd_uri_t uri_info = {
    .uri      = "/info",
    .method   = HTTP_GET,
    .user_ctx = NULL
};

/* predefined /temp uri */
httpd_uri_t uri_temp = {
    .uri      = "/temp",
    .method   = HTTP_GET,
    .user_ctx = NULL
};

/* predefined /temp uri */
httpd_uri_t uri_onboard = {
    .uri      = "/onboard",
    .method   = HTTP_GET,
    .user_ctx = NULL
};

#define MAX_NEW_URIS 10

static struct {
	unsigned short int curr_idx;
	httpd_uri_t configs[MAX_NEW_URIS];
} upcoming_uris_buf = { 0 };

int akri_server_start() {
	if (akri_server)
		return -1;

	httpd_config_t config = HTTPD_DEFAULT_CONFIG();

	/* Start the httpd server */
	return (int) httpd_start(&akri_server, &config);
}

int akri_server_end() {
	if (akri_server)
		httpd_stop(akri_server);

	akri_server = NULL;
	upcoming_uris_buf.curr_idx = 0;
	memset(upcoming_uris_buf.configs, 0,
	       sizeof(upcoming_uris_buf.configs));
	return (int) ESP_OK;
}

int akri_set_update_handler(esp_err_t (*handler)(httpd_req_t *req)) {
	if (NULL == akri_server || NULL == handler)
		return -1;

	uri_update.handler = handler;
	httpd_register_uri_handler(akri_server, &uri_update);
	return (int) ESP_OK;
}

int akri_set_info_handler(esp_err_t (*handler)(httpd_req_t *req)) {
	if (NULL == akri_server || NULL == handler)
		return -1;

	uri_info.handler = handler;
	httpd_register_uri_handler(akri_server, &uri_info);
	return (int) ESP_OK;
}

int akri_set_temp_handler(esp_err_t (*handler)(httpd_req_t *req)) {
	if (NULL == akri_server || NULL == handler)
		return -1;

	uri_temp.handler = handler;
	httpd_register_uri_handler(akri_server, &uri_temp);
	return (int) ESP_OK;
}

int akri_set_onboard_handler(esp_err_t (*handler)(httpd_req_t *req)) {
	if (NULL == akri_server || NULL == handler)
		return -1;

	uri_onboard.handler = handler;
	httpd_register_uri_handler(akri_server, &uri_onboard);
	return (int) ESP_OK;
}

int akri_set_handler_generic(const char *uri,
			     httpd_method_t method,
			     esp_err_t (*handler)(httpd_req_t *req)) {
	if (NULL == akri_server)
		return -1;
	if (!uri || !handler)
		return -1;
	if (upcoming_uris_buf.curr_idx >= MAX_NEW_URIS)
		return -1;

	httpd_uri_t *new_uri = &upcoming_uris_buf.configs[upcoming_uris_buf.curr_idx];
	new_uri->uri      = uri;
	new_uri->method   = method;
	new_uri->handler  = handler;
	new_uri->user_ctx = NULL;

	httpd_register_uri_handler(akri_server, new_uri);
	++upcoming_uris_buf.curr_idx;

	return (int) ESP_OK;
}
