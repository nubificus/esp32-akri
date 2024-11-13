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

int akri_set_temp_handler(esp_err_t (*handler)(httpd_req_t *req));

int akri_set_handler_generic(const char *uri,
                             httpd_method_t method,
                             esp_err_t (*handler)(httpd_req_t *req));
```
Make sure you have connected the device on the internet previously.
