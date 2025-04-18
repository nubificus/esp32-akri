# esp32-akri
ESP32 Component for managing the akri-related http endpoints of the device

## How to use
```
cd <path-to-your-esp-idf-project>
mkdir -p components
cd components
git clone https://github.com/nubificus/esp32-akri.git
```
Add the component to your project by simply adding the following line inside `idf_component_register()` of `<path-to-your-esp-idf-project>/main/CMakeLists.txt`:
```
REQUIRES esp32-akri
```
E.g:
```
idf_component_register(SRCS "test.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp32-akri)
```

Afterwards, you can include the component's header file:
```c
#include "esp32-akri.h"
```

## API Reference
```c
int akri_server_start();

int akri_server_end();

int akri_set_update_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_info_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_onboard_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_temp_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_handler_generic(const char *uri,
                             httpd_method_t method,
                             esp_err_t (*handler)(httpd_req_t *req));
```
Make sure you have connected the device on the internet previously.

## Endpoints

The exported endpoints from esp32-akri are:
 - `/info`
 - `/onboard`
 - `/update`

### `/info`
By sending a GET request to `/info`, one can retrieve information about the device (device type, firmware version, firmware type etc) in JSON format.

### `/update`
On the other side, the update should be initialized through a POST request. More specifically, the body of the request should include the IP address of the OTA agent in the form: "ip: A.B.C.D". The handler then will extract the IP from the request and initialize a TLS (secure) connection between the device and the Agent. If the authentication succeeds, the device will receive the new firmware.
