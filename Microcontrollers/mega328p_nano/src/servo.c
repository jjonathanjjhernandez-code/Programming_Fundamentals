//let's see if we can do this servo drive just right!
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart-printf.h"
#include <stdbool.h>
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
bool output_or_not = false;
    //we'll try doing so using the 16-bit timer 1
void initServo(void){
    TCCR1A |= (1<<COM1A1);//everytime the time interval is done the OC1A/OC1B pin stops pulsing based on compare match!
    
    //waveform generation settings
    TCCR1B |= (1<<WGM13) | (1<<WGM12);
    TCCR1A |= (1<<WGM11);
    //

    TCCR1B |= (1<<CS11);// we are doing 16MHz/8 ~=2MHz which is close to .5us as our counter to determine then the ticks.... 
    ICR1 = 15625;// we do our desired frequency operation say 128Hz(DS3218 has operating range of 50-330Hz) and thus 1/128 ~= 7.8125ms and that divided by 0.5us gives us roughly 15625 ticks that the chip needs to count
//now this here is the counter for the time interval{period} of the pulses but it is now time to configure our pulses
    
    OCR1A = 1000;//this should ALWAYS be measured in ticks and is super dependent on the pre-scaler you decide to choose!
}
int main(void){
    initServo();
    stdout = &uart_output;
    if(output_or_not){
        DDRB |= (1<<PB1); //considerded as the OC1A pin on the pinouts!
    }
    DDRB &= ~(1<<PB1);
    while(1){

    }
    return 0;
}
