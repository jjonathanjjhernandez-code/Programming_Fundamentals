#include <stdio.h>
#include "uart-button.h"
void UART_transmit_char(char c, FILE *stream){
    if(c == '\n'){
        UART_transmit_char('\r',stream);
    }
    loop_until_bit_is_set(UCSR0A,UDRE0);
    UDR0 = c;
}
void UART_transmit_ISR_char(char c, FILE *stream){
    
}