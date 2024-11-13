file(GLOB AKRI_SRCS "src/*.c")

idf_component_register(SRCS ${AKRI_SRCS} INCLUDE_DIRS "src" "include"
		       REQUIRES esp_netif esp_event esp_http_server)
