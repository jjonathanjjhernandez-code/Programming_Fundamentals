#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>
#include <stdio.h>
/*
Now using our knowledge from the gpio file.c let's see if we can use the associated L298N Dual H-Bridge Motor Driver for a simple
DC motor!

here are the combos 
We have inputs 1,2,3,4 in that order where 1 and 2 are for motor A and 3 & 4 are for motor B
let's do this!

so as of now we will be using the pins on the ESP32-DEVKIT 1/ FCC ID: 2B77-ESP32-32
Pins:
    --D12
    --D13

    1.If both pins output high nothing happens!
    2.If either or well, you get clock wise or counterclockwise!
    */
#define MOT_1_L GPIO_NUM_13
#define MOT_1_R GPIO_NUM_12

static const char *TAG = "MOTOR_DRIVE";
void app_main(void){
        gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << MOT_1_L) | (1ULL << MOT_1_R),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    esp_err_t config_result = gpio_config(&io_conf);
    //safety standard with the ESPs!!! Basically checks out your structure to see if gpio_config() can even run!
    if(config_result != ESP_OK){
        ESP_LOGE(TAG,"GPIO config failed!\nHere's the message %s", esp_err_to_name(config_result));
        return;
    }
    ESP_LOGI(TAG,"Driving now!");
    gpio_set_level(MOT_1_L,1);
    gpio_set_level(MOT_1_R,0);
    while(1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}