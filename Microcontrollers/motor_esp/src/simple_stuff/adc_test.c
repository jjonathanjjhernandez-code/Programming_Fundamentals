
/*
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
                            Analog to Digital Converter
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
{Note since we might be using the wifi channel try to restrict yourself to using just ADC1 unit!!!}
We need to read somewhat aribitrary values given from sensors, and other modules that produce analog signals
 basically any voltage that vary continously.
 However, MCUs operate in the digital domain and the ADC is the bridge between these worlds. Converting the
 continous analog voltage into a discrete digital number that the MCU can process. 
 Just a little recap on the ADC functionality........
    --Resolution: This determines the number of discrete digital values the ADC can produce. It is typically expressed in bits. An N-bit
    ADC can represent 2^N distinct digital levels. ex) 12-bit ADC can do 4096 discrete values.
    A higher resolution means smaller voltage steps can be detected, leading to a more accurate digital representation of the analog signal
    --Sampling Rate: This is the number of times per second the ADC converts the analog input toa digital value.{This focusrs on oneshot??}
    --Input Voltage Ranger: This is the range of analog voltages(0V to 3.3V) that the ADC can convert. Voltages otuside this range may not be
    accurately converted or could even damage the ADC
    --Refrence Voltage(Vref): The ADC compares the input analog voltage to a reference voltage to perform the conversion. The accuracy of the Vref directly
    impacts the accuracy of the conversion.
    Conversion formula: 
    Digital Value(that the MCU sees) = (Input Analog Voltage/ Vref)* (2^n - 1)

 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
                            ESP32 ADC Architecture
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
Most ESP32 variants are equipped with two Successive Approximation Register(SAR) ADCs...
ADC1 and ADC2. However, the availiabilty and channel count can vary

    --ADC UNITS
        --ADC1
        --ADC2
    --Channels: Each ADC has multiple input channels. A channle is typically connected to a specific
    GPIO that can be CONFIGURED as an analog input. The number of avaliable channels varies with different
    ESP32s
    --Resolution: The ADCs on ESP32 variants typically support configurable resolutuions up to 12-bit or 13-bit.
    --Attenutation:The ESP32 ADCS have a confgiurable input attentuation. Attentation allows the ADC  to measure
    voltages higher than its internal reference voltage by scaling them down. Common attenuation levels are:
        --ADC_ATTEN_DB_0: No attenuation(input voltage range typically around 0-1.1V, varies slightly byb chip)
        --ADC_ATTEN_DB_2_5: 2.54dB attentuation (input voltage range typically around 0-1.5V)
        --ADC_ATTEN_DB_6: 6dB attenuation(input voltage range typically aroujnd 0-2.2V)
        --ADC_ATTEN_DB_11: 11dB attentuation(0-3.3V range). This is the most common setting for measuring signals up to
        supply voltage.

 *  *   *   *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
                            ESP-IDF ADC adc_oneshot Driver
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
 Here we provide the adc_oneshot driver for performing single, on demand ADC readings. This is simpler to use than the continous
 mode driver when you only need occassional readings....

    --Initialization Configuration (adc_oneshot_unit_init_cfg_t)
**
typedef struct{
    adc_unit_t unit_id;         //adc unit id...so like either ADC1 or ADC2
    adc_ulp_mode_t ulp_mode;    //wifi stuff??
}adc_oneshot_unit_init_cfg_t;
**
    --Channel Configuration(adc_oneshot_chan_cfg_t)
**
typedef struct{
    adc_atten_t atten;          //adc attenuation
    adc_bandwidth_t bitwdith;   /adc conversion bits
}adc_oneshot_chan_cfg_t;
**

 *  *   *   *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
                                    ADC Calibration
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * *
Rw ADC readings can be affected by variations in the chip's internal refernce voltage and other non-linearities. For accurate
voltage measurements, ADC calibration is essential. ESPIDF providesw an adc_cali component to help compensate for these variations
As of right now we will only be implementing raw ADC values!

Using the KY-023 Module which is essentially a joystick....so this should be able to give use some values!!!

....although this works....super duper slow and not too preceise....we can fix this!!
*/
// we will be using ADC1_0 which is on GPIO36
//#define ADC1_CHANNEL_0 GPIO_NUM_36
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include <driver/gpio.h>
#define ADC_UNIT     ADC_UNIT_1
#define ADC_CHANNEL  ADC_CHANNEL_0
#define ADC_ATTEN    ADC_ATTEN_DB_12
#define ADC_BITWDITH ADC_BITWIDTH_DEFAULT    
static const char *TAG = "ADC_READ";
static adc_oneshot_unit_handle_t adc1_handle;
static void adc_init(void){
    //**adc init**
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1,&adc1_handle)); //includes handle and config struct
    ESP_LOGI(TAG, "ADC1 initialized, handle: %p",adc1_handle);

    //* * adc 1 channel config * *
    adc_oneshot_chan_cfg_t config_channel = {
        .atten = ADC_ATTEN,
        .bitwidth = ADC_BITWDITH,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL, &config_channel));
    ESP_LOGI(TAG, "ADC1 Channel %d confguired, handle: %d",ADC_CHANNEL);
}

void app_main(void){
    adc_init();
    int adc_raw_reading;
    while(1){
        esp_err_t ret =adc_oneshot_read(adc1_handle,ADC_CHANNEL, &adc_raw_reading);
        if(ret == ESP_OK){
            ESP_LOGI(TAG,"ADC1 Channel[%d] Raw Data: %d", ADC_CHANNEL,adc_raw_reading);
        }else if(ret==ESP_ERR_TIMEOUT){
            ESP_LOGW(TAG,"ADC Read Timeout");
        }else{
            ESP_LOGE(TAG,"ADC read fialed with error: %s", esp_err_to_name(ret));
        }
    vTaskDelay(pdMS_TO_TICKS(15));
    }
}