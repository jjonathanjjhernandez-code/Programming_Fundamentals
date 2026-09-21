#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

static const char *TAG = "ESP2_RX";

#define THRES_HIGH 3000
#define THRES_LOW  1000
#define MOT_A_L GPIO_NUM_13
#define MOT_A_R GPIO_NUM_12
#define PIN_11 GPIO_NUM_12
#define PIN_10 GPIO_NUM_10

static void gpio_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << MOT_A_L) | (1ULL << MOT_A_R),//
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    // known starting state — both low until first valid reading arrives
    gpio_set_level(MOT_A_L, 0);
    gpio_set_level(MOT_A_R, 0);
}

static void wifi_init(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE)); // must match ESP1's channel
}

// Fires whenever a packet arrives — this IS the reaction, no polling task needed
static void on_data_recv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len) {
    if (len != sizeof(int)) {
        ESP_LOGW(TAG, "Unexpected packet size: %d bytes", len);
        return;
    }

    int adc_value;
    memcpy(&adc_value, data, sizeof(adc_value));

    if (adc_value > THRES_HIGH) {
        gpio_set_level(MOT_A_R, 1);
        gpio_set_level(MOT_A_L, 0);
        ESP_LOGI(TAG, "Value %d > HIGH thresh — PIN11=1, PIN10=0", adc_value);
    } else if (adc_value < THRES_LOW) {
        gpio_set_level(MOT_A_R, 0);
        gpio_set_level(MOT_A_L, 1);
        ESP_LOGI(TAG, "Value %d < LOW thresh — PIN11=0, PIN10=1", adc_value);
    }
    else{
        gpio_set_level(MOT_A_R, 1);
        gpio_set_level(MOT_A_L, 1);
        ESP_LOGI(TAG, "Value %d — PIN11=1, PIN10=1", adc_value);
    }
}

static void espnow_init(void) {
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(on_data_recv));
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    gpio_init();
    wifi_init();
    espnow_init();

    ESP_LOGI(TAG, "ESP2 ready — waiting for ESP-NOW packets");
}