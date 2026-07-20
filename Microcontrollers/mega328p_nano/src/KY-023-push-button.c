/*
This module consists of two 10kΩ potentiometers perpendicularly placed to control the X and Y axes by changing resistance when 
moving the joystick. A push button is activated when the joystick is pushed down on the Z axis. It has 5 male header pins.

Simply put based on the ADC value we will get from our internal analog-to-digital converter we will be able print up,down,left
and right!

As for the setup we will place VRx on A1(PC1) & VRy on A2(PC2)
For the digital input of the swithch(basde on the KY-023 dual axis joystick) we will place that on PD3
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "uart-printf.h"
#include <inttypes.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
//Define the stream output for the serial output!
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
//Define Global/Voltaile Variables Here!
volatile bool channel_switch = false; //global variable to check channel ADC1 & ADC2!
volatile uint16_t VRx_value;//ADC1
volatile uint16_t VRy_value;//ADC2
volatile bool vx_ready = false;
volatile bool vy_ready = false;
void initADC0(void){
    ADMUX |= (1<<REFS0);//Configuration 01: AVCC with external capacitor at AREF pin
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//Configuration of 111: Division factor of the internal: clk source/128
    ADCSRA |= (1<<ADEN);// enable the ADC logic block
}

void initADCinterrupt(void){
    ADCSRA |= (1<<ADIE);//enable the global interrupts specifically the I-bit in the status register of the MCU!
    //ADCMUX----MUX3:0 Analog Channel Selection Bits
    ADMUX = (0b11110000 & ADMUX) | (0b00000001);
    ADCSRA |= (1<<ADSC);//enable the ADC conversion!
    sei();//enable global interrupts!
}

int main(void){
    DDRD &= ~(1<<PD3);
    PORTD &= ~(1<<PD3);//forces PD3 pin on port D to be an input
    initADC0();
    initUSART();
    initADCinterrupt();
    stdout = &uart_output; // define the output using the FILE type as mentioned above
    while(1){
        if(vy_ready){
            if((VRy_value<=450)||(VRy_value>=550)){
                printf("VRy: %"PRIu16"\tVRx: %"PRIu16"\n",VRy_value,VRx_value);
            }
            vy_ready = false;
            _delay_ms(10);
        }
        if(vx_ready){
            if((VRx_value>=550)||(VRx_value<=450)){
                printf("VRy: %"PRIu16"\tVRx: %"PRIu16"\n",VRy_value,VRx_value);
            }
            vx_ready = false;
            _delay_ms(10);
        }
    }
    return 0;
}
ISR(ADC_vect){//&&Vector #: 22   &&Program Address:0x002A
//Interrupt Vector:ADC----ADC Conversion Complete
        if(channel_switch){//if true start with ADC2 else ADC1
            VRy_value = ADC;
            ADMUX = (0b11110000 & ADMUX) | (0b00000001);
            ADCSRA |= (1<<ADSC);
            vy_ready = true;
            channel_switch = !channel_switch;
        }else{
            VRx_value = ADC;
            ADMUX = (0b11110000 & ADMUX) | (0b00000010);
            ADCSRA |= (1<<ADSC);
            vx_ready = true;
            channel_switch = !channel_switch;
        }
}