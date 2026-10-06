# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

# idf_component_register(SRCS ${app_sources}) #this appears to be a simple grab....basically compiles everything in sight!
idf_component_register(
    #SRCS "./motor_stuff/esp_1/mac_address.c"
    SRCS "./motor_stuff/pwm-api-module/pwm.c"
    INCLUDE_DIRS "." "motor_stuff/pwm-api-module"
#    REQUIRES esp_wifi nvs_flash esp_netif esp_event driver freertos log esp_adc
    REQUIRES esp_wifi nvs_flash esp_netif esp_event driver freertos log
)
#just a little run down......
# SRC focuses on target files you GENUINELY want to compile!
# INCLUDE_DIRS ????
# REQUIRES basically look at the included header files and whatnot and see the folder its under like the ones you see here!