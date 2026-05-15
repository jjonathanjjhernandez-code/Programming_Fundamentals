#include <stdio.h>
#include <avr/interrupt.h>
#include "uart-button.h"
//transmission of character bits into the STDOUT stream
void UART_transmit_char(char c, FILE *stream){
    if(c == '\n'){
        UART_transmit_char('\r',stream);
    }
    loop_until_bit_is_set(UCSR0A,UDRE0);
    UDR0 = c;
}
