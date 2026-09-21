#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_adc/adc_oneshot.h"

static const char *TAG = "ESP1_TX";

//both ESPs need to be on the same channel!!!! by default they go to channel!
//target ESP!!!     I (330) MAC_READ: STA MAC Address: 44:1D:64:F8:0C:74
// >>> Replace with ESP2's actual STA MAC address from step 1 <
static uint8_t peer_mac[6] = {0x44, 0x1D, 0x64, 0xF8, 0x0C, 0x74};

static adc_oneshot_unit_handle_t adc1_handle;

static void espnow_send_cb(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
    // optional: log send success/failure for debugging
    if (status != ESP_NOW_SEND_SUCCESS) {
        ESP_LOGW(TAG, "Send failed");
    }
}

static void wifi_init(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE)); //force both ESPs to be in channel One
}

static void espnow_init(void) {
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(espnow_send_cb));

    esp_now_peer_info_t peer_info = {0};
    memcpy(peer_info.peer_addr, peer_mac, 6);
    peer_info.channel = 0;      // 0 = use current WiFi channel
    peer_info.encrypt = false;  // set true + configure keys if you want encryption
    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info));
}

static void adc_init(void) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc1_handle));

    adc_oneshot_chan_cfg_t chan_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    //this is pin VP??? basically ADC1_0 look for the pinouts!
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &chan_config));
}

void adc_send_task(void *pvParameters) {
    int adc_value;
    int last_sent_value = -1;
    const int CHANGE_THRESHOLD = 20; // tune based on your noise floor

    while (1) {
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &adc_value));

            esp_err_t result = esp_now_send(peer_mac, (uint8_t *)&adc_value, sizeof(adc_value));
        if(result != ESP_OK) {
            ESP_LOGW(TAG, "ADC read failed: %s", esp_err_to_name(result));
            //vTaskDelay(pdMS_TO_TICKS(10));
            continue; // skip this cycle, try again next loop
        }
        
        vTaskDelay(pdMS_TO_TICKS(10)); // ~66Hz poll rate
    }
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init();
    espnow_init();
    adc_init();

    xTaskCreate(adc_send_task, "adc_send_task", 4096, NULL, 3, NULL);
}