#include "uart-button.h"
#include <avr/interrupt.h>
#include <stdio.h>

// transmission of character bits into the STDOUT stream
void UART_transmit_char(char c, FILE *stream) {
  if (c == '\n') {
    UART_transmit_char('\r', stream);
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}
// character input based on the terminal end
int UART_input_char(char c,
                    FILE *stream) { // basically put all of the characters into
                                    // the STDIN stream for compilation!
  UART_transmit_char(c,stream);
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}