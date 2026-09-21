#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>
#include <stdio.h>

/**
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
                                            GPIO PINS
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
*   *

 Interactions with the coding of the eps32 can be a little tricky so let's how
we can configure just a simple GPIO input and/or output using the espidf
 framework, here are the following Pin Configuration Modes
    --Input Mode: The GPIO pin is configured to sense the voltage level applied
to it by an external component. The ESP32 reads whether the pin High or Low.
    This is used for buttons, switches, or receiving signals from other digital
devices.
    --Output Mode: The pin is configured to drive its voltage level High or Low,
controlled by the ESP32's software. This is used to control LEDS, activate
relays (usually via a transistor), or send signals to other digital devices

|    Mode           |                   gpio_mode_t Value               |
Description                     | Common Use Input               GPIO_MODE_INPUT
Configures the pin to sense the voltage level          Buttons, switches,
receiving signals etc. applied to it externally.(Either High or Low)
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Output(Push-Pull)      GPIO_MODE_OUTPUT Configures the pin to actively drive
its voltage        Controlling LEDS, relays, extra stuff! level High(VCC) or
lOw(gnd) )
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Input & Output(Push-Pull)  GPIO_MODE_INPUT_OUTPUT Configures the pin to be
capable of both input      Bidirectional communication lines where the device
might need to and push-pull output. Direction can be swtiched          both send
and receive on the same pin
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Disable                    GPIO_MODE_DISABLE Disables the GPIO functionality
for the pin.          Default state, or when a pin is not used as GPIO or is
dedicated to an analog function This is often the default state. The pin's state
might controlled by other peripherals via IO MUX
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
*   * I/O MUX and GPIO Matrix
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
*   * Modern MCUs have many internal peripherals(UART,SPI,I2C, Timers, ADC,
etc), that need to connect to the physical pins of the chip. Instead of having
fixed pins for every single peripheral funciton, the ESP 32 uses a flexible
routing system.
    --1. I/O Mux(Input/Output Multiplexer): Each physical pin has a primary
peripheral function assigned to it by default(e.g, a specific pin might default
to being TXD0 for UART0). The I/O MUX allows selecting this primary funciton
    --2. GPIO Matrix: Provides a more powerful, crossbar-like switch. It allows
routing almost any internal peripheral signal(input or output) to almost any
GPIO pin, overriding the default I/O Mux funciton if necessary. It also routes
    simple GPIO input/output signals when a pin is configured for basic GPIO
use. Meaning you got a lot of options!! Just remember to configure your pins!

 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
*   * GPIO Configuration Structure: gpio_config_t
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
*   * 1. Most GPIO configurationis done using the gpio_config_t structure, which
is then passed to the gpio_config() funciton.
    **
    typedef struct{
        uint64_t pin_bit_mask;           //GPIO pin like (1ULL<<GPIO_NUM_1) or
something like that gpio_mode_t mode;               //set  input/ ouptut /
open-drain  / output+open-drian gpio_pullup_t pull_up_en;       //gpio pull-up
        gpio_pulldown_t pull_down_en;   //gpio pull-down
        gpio_int_type_t intr_type;      //gpio interrupt type
        } gpio_config_t;
    Ex)
        --pin_bit_mask: (1ULL<<GPIO_NUM_4) | (1ULL << GPIO_NUM_5)
        --mode: GPIO_MODE_DISABLE, GPIO_MODE_INPUT, GPIO_MODE_OUTPUT,
        GPIO_MODE_OUTPUT_OD, GPIO_MODE_INPUT_OUTPUT, GPIO_MODE_INPUT_OUTPUT_OD.
        --pull_up_en: GPIO_PULLUP_ENABLE, GPIO_PULLUP_DISABLE
        --pull_down_en: GPIO_PULLDOWN_ENABLE, GPIO_PULLDOWN_DISABLE
        --intr_type: GPIO_INTR_DISABLE (default), GPIO_INTR_POSEDGE,
GPIO_INTR_NEGEDGE, GPIO_INTR_ANYEDGE, GPIO_INTR_LOW_LEVEL, GPIO_INTR_HIGH_LEVEL
2.
Next we are to apply the configuration using gpio_config()
esp_err_t gpio_config(const gpio_config_t *pGPIOCONFIG);
    --Applies the settings defined in the gpio_config_t structure pointed to by
pGPIOConfig to the pins specified in the pin_bit_mask.
    --Returns ESP_OK on success, or an error code on failure.

    */

#define LED_PIN GPIO_NUM_32 // should be D15 on the dev board??
static const char *TAG = "GPIO_EX";
void app_main(void) {
    ESP_LOGI(TAG,"logging stuff!");
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
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
    ESP_LOGI(TAG,"GPIO %d configured as an output!!",LED_PIN); 
    while (1) {
        gpio_set_level(LED_PIN,1);
        vTaskDelay(pdMS_TO_TICKS(1000));//the esp needs this to not crash!
        gpio_set_level(LED_PIN,0);
        vTaskDelay(pdMS_TO_TICKS(1000));//also seems like the time is in ms!
  }
}