/*
Now to expand on from before!
We are going to test some button preses!
For now we will focus on two pins 
A5(PC5) for input reading and D13(PB5) for indicating States
D13=LED
A5=button input
*/
#include "blinkLED_reg.h"
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
int main(){
    DDRB |= (1<<PB5);//setting LED output for PB5
    PORTC |= (1<<PC5); //enabling pull up resistor
    //remember inputs are naturally placed!
    bool ledon = false;
    while(1){
        if(!(PINC & (1<<PC5))){
            ledon = !ledon;
            _delay_ms(145);
        }
        if(ledon){
            PORTB = PORTB | (1<<PB5);
            _delay_ms(20);
        }else{
           PORTB = PORTB & ~(1<<PB5); 
            _delay_ms(20);
        }
    }
    return 0;
}
/*
cool but this can be improved!
we are going to implement the UART communication for this!
*/