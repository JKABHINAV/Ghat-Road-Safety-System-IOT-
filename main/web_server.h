#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "esp_http_server.h"

extern int vehicle_count;
extern int status_A;
extern int status_B;

static esp_err_t get_handler(httpd_req_t *req) {
    char response[1200];
    snprintf(response, sizeof(response),
             "<html><head><meta http-equiv='refresh' content='1'>"
             "<style>body{font-family:sans-serif; background:#121212; color:white; text-align:center;}"
             ".flex{display:flex; justify-content:center; gap:20px; margin-top:50px;}"
             ".card{padding:40px; border-radius:15px; width:150px; font-weight:bold; border:2px solid #444;}"
             ".danger{background:#ff3333; box-shadow: 0 0 15px #ff3333;}"
             ".safe{background:#222; color:#555;}"
             ".count{font-size:80px; color:#3498db; margin:20px; font-weight:bold;}"
             "</style></head><body>"
             "<h1>GHAT ROAD SAFETY SYSTEM</h1>"
             "<div class='flex'>"
             "<div class='card %s'>SIDE A<br>%s</div>"
             "<div class='card %s'>SIDE B<br>%s</div>"
             "</div>"
             "<div>TOTAL VEHICLES</div><div class='count'>%d</div>"
             "</body></html>",
             status_A ? "danger" : "safe", status_A ? "DANGER" : "CLEAR",
             status_B ? "danger" : "safe", status_B ? "DANGER" : "CLEAR",
             vehicle_count);
    httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static void start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t uri_get = { .uri = "/", .method = HTTP_GET, .handler = get_handler };
        httpd_register_uri_handler(server, &uri_get);
    }
}
#endif
