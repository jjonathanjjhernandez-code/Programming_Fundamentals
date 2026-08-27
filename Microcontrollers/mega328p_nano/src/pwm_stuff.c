#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart-printf.h"
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
volatile uint16_t eight_bit_tick_counter = 0;
//going to some PWM LED!
void initPWM(void){
    //initiating FAST PWM mode!
    TCCR0A = (1<<WGM01) | (1<<WGM00) | (1<<COM0A1); //then conducting non-inverting mode...not sure what that means!
    TCCR0B = (1<<CS00);//choosing the I/O clock with no prescaler wonder what this means or does????
    OCR0A = 127;//maybe 50% duty cycle???
    TIMSK0 = (1<<OCIE0A);//enabling output compare match interrupt to produce PWM!
    DDRD |= (1<<PD6);//which should be pin6 set as output maybe??
}

int main(void){
stdout = &uart_output;
initUSART();
initPWM();
printf("Helo!\nTurning your LED on & OFF!\n");
while(1){
    }
    return 0;
}
