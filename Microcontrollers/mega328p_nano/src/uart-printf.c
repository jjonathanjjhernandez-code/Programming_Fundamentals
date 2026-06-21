#include "uart-printf.h"
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
volatile bool button_press = false; // need to make it volatile type for immediate changes
static uint8_t count = 0;
int main(void) {
  // Interrupt Config
  initUSART();
  EICRA |= (1 << ISC11) | (0 << ISC10); // The falling edge of INT1 generates an interrupt request
  EIMSK |= (1 << INT1); // external pin(1<<PD3) is enabled
  sei();
  // Pin config
  DDRD |= (1 << PD5);  // enabling LED output!
  DDRD &= ~(1 << PD3); // force PD3 bit to be input
  PORTD |= (1 << PD3); // enabling pullup resistor for digital reading of button
                       // switch...ensure PIN is configured wiht INT1_vect
  stdout =
      &uart_output; // define the output using the FILE type as mentioned above
  while (1) {
    if (button_press) {
      button_press = false;
      printf("Hello world!\tCount: %d\n",count); // place characters on the terminal!
        PORTD |= (1 << PD5);
      _delay_ms(100);
    }else{
        PORTD &= ~(1<<PD5);
      }
  }
  return 0;
}
/*Example of ISR BUtton!*/
ISR(INT1_vect) {
  count++;
  button_press = true; // Interrupt Service Routines need to be quick
  // boolean statement toggles are FAST!
}