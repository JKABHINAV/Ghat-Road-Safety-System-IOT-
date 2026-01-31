#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "sensors.h"
#include "buzzer_control.h"
#include "web_server.h"

int vehicle_count = 0;
int status_A = 0;
int status_B = 0;

// Correcting the counting error using Edge Detection
int last_A = 1;
int last_B = 1;

void wifi_init_softap(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "Ghat_Safety_System",
            .ssid_len = strlen("Ghat_Safety_System"),
            .password = "12345678",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("\n========================================\n");
    printf("WIFI ACCESS POINT STARTED\n");
    printf("SSID: Ghat_Safety_System\n");
    printf("Web URL: http://192.168.4.1\n");
    printf("========================================\n");
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init_softap();
    init_sensors();
    init_buzzers();
    start_webserver();

    while (1) {
        int read_A = gpio_get_level(IR_A);
        int read_B = gpio_get_level(IR_B);

        status_A = (read_A == 0);
        status_B = (read_B == 0);

        // Hardware Logic: Side A alerts Side B, and vice-versa
        gpio_set_level(BUZZER_B, status_A);
        gpio_set_level(BUZZER_A, status_B);

        // ACCURATE COUNTING LOGIC (Edge Detection)
        // Increment only when state switches from 1 (Clear) to 0 (Object)
        if (read_A == 0 && last_A == 1) {
            vehicle_count++;
            printf("Vehicle detected on Side A. Total: %d\n", vehicle_count);
        }
        if (read_B == 0 && last_B == 1) {
            vehicle_count++;
            printf("Vehicle detected on Side B. Total: %d\n", vehicle_count);
        }

        last_A = read_A;
        last_B = read_B;

        vTaskDelay(pdMS_TO_TICKS(50)); // Polling at 50ms for high accuracy
    }
}
