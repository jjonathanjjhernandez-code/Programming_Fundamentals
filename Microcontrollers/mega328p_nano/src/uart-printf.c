#include "uart-printf.h"
FILE uart_output = FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
int main(void){
    initUSART();
    DDRD |= (1<<PD3); //enabling LED output!
    PORTD |= (1<<PD5);//enabling pullup resistor for digital reading of button switch 
    bool ledon = false;
    stdout = &uart_output;
    while(1){
        puts("Hello world!");
        _delay_ms(1000);
    }
    return 0;
}
/*Example of ISR BUtton!

*/
