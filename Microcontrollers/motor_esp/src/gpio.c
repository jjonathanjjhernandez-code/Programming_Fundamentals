/*
Let's see if we can establish some common ground....
The ESP32 chip features 34 physical GPIO pins. Each pin can be used as a general-purpose I/O, or be connected to an internal peripheral signal.
Through IO MUX, RTC IO MUX, and the GPIO matrix, peripheral input signals can be from any IO pins, and peripheral output signals can be routed to any IO pins.
Together these modules provide highly configurable I/O.
{of course depending on your dev board and chip you need to know where and what these are mapped out to!}


[IO Configuration]
An IO can be used in two ways:
    --As a simple GPIO input to read the level on the pin, or as a simple GPIO output to output the desired level on the pin
    --As a peripheral signal input/output
IDF peripheral drivers always take case of the necessary IO configurations that need to be applied onto the pins, so that they can be used as the peripheral signal inputs or outputs.
This means the users usually only need to be responsible for configuring the IOs as simple inputs or outputs.
gpio_config() is an all-in-one API that can be used to configure the I/O mode, internal pull-up/pull-down resistors, etc, for pins, including the ones reused by the USB PHY.

In some applications, an IO pin can serve dual purposes. For example,the IO, which outputs a LEDC PWM signal, can also act as a GPIO input to generate interrupts or GPIO ETM events.
Careful handling on the configuration step is necessary for such dual use of IO pins cases. gpio_config is an API that overwrites all the current configurations, so it must be called to set the pin mode to
gpio_mode_t::GPIO_MODE_INPUT before calling the LEDC driver API which connects the output signal to the pin. As an alternative, if no other configuration is needed other than making the pin input enabled, gpio_input_enable() can 
be the one to call at any time to achieve the same purpose.

*/
#include "driver/gpio.h"
#include <stdio.h>