/**
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   
 *                                   Camera ESP
 *  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
 * 
 * Data Tranmission through Bluetooth of ESP32-S3 WROOM
 * 
 * [Component Knowledge]
 * ESP32-S3's integrated Bluetooth function Bluetooth is a short-distance communication system, which can be divided into two types, namely Bluetooth Low Energy(BLE)
 * and classic Bluetooth. There are two modes for simple data transmission: master mode and slave mode
 * 
 * 
 * 
 * [Master Mode]
 * In this mode, works are done in the master device and it can connect with a slave device. And we can search and select slave devices nearby to connect with. When a device initiates
 * connection equest in master mode, it requires information of the other Bluetooth devices including their address and pairing passkey. After finishing pairing, it can connect with them directly.
 * 
 * [Slave Mode]
 * The Bluetooth Module in slave mode can only accpet connection request from a host computer, but cannot initiate a connection request. After connecting with a host device, it can send data to or recieve from host device.
 * Bluetooth devices can make data interaction with each other, as one is in master mode and the other in slave mode. When they are making data interaction, the Bluetooth device in master mode searchs and selects devices nearby to connect to.
 * When establishing connection, they can exchange data. When mobile phones exchange data with ESP32-S3, they are usually in master mode and ESP32-S3 in slave mode.
 *
 * Essentially we will have a mobile device and the esp32 to interact with one another via bluetooth.....no pcbs as of now,but perhaps we can incorporate that later....
 * With regards to the Bluetooth API based off the espressif documentation

    *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
                                    Bluetooth API
    *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
    This section provides the API reference for Bluetooth components supported in ESP-IDF. ESP-IDF supports two host stacks: Bluedroid and NimBLE
        --Bluedroid(default stack): Supports both Bluetooth Classic and Bluetooth LE....Recommended for applications that require both technologies
        --NimBLE: A lighweight stack for Bluetooth LE only. Ideal for resource-oriented applications due to smaller code size and memory usage



[Controller and Hardware Connect Interactivity]
bluetooth/hci/controller_hci_uart_esp32: demonstrates how to configure the Bluetooth LE Controller;s HCI to communicate over UART on ESP32, enabling communication with an external Bluetooth host stack.        

**/
#include "esp_bt.h"
void app_main() {}