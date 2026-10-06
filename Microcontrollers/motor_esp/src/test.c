#include <stdio.h>
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

static const char *TAG = "chip_info";

void app_main(void)
{
    esp_chip_info_t info;
    esp_chip_info(&info);

    const char *model_str;
    switch (info.model) {
        case CHIP_ESP32:   model_str = "ESP32";   break;
        case CHIP_ESP32S2: model_str = "ESP32-S2"; break;
        case CHIP_ESP32S3: model_str = "ESP32-S3"; break;
        case CHIP_ESP32C3: model_str = "ESP32-C3"; break;
        case CHIP_ESP32C2: model_str = "ESP32-C2"; break;
        case CHIP_ESP32C6: model_str = "ESP32-C6"; break;
        case CHIP_ESP32H2: model_str = "ESP32-H2"; break;
        default:           model_str = "Unknown";  break;
    }

    ESP_LOGI(TAG, "Chip model: %s (%d), cores: %d, revision: v%d.%d",
             model_str, info.model, info.cores,
             info.revision / 100, info.revision % 100);

    ESP_LOGI(TAG, "Features: %s%s%s",
             (info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi " : "",
             (info.features & CHIP_FEATURE_BLE) ? "BLE " : "",
             (info.features & CHIP_FEATURE_BT) ? "BT Classic " : "");

    uint32_t flash_size;
    if (esp_flash_get_size(NULL, &flash_size) == ESP_OK) {
        ESP_LOGI(TAG, "Flash size: %lu MB", flash_size / (1024 * 1024));
    } else {
        ESP_LOGE(TAG, "Failed to get flash size");
    }
}