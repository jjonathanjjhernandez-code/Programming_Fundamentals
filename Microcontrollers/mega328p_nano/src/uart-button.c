#include "uart-button.h"
int main(void) {
  DDRB |= (1 << PB5);  // setting LED output for PB5
  PORTC |= (1 << PC5); // enabling pull up resistor
  // remember inputs are naturally placed!
  bool ledon = false;
  bool bossbutton = true;
  initUSART(); // NEW STUFF!
  transmitByte('0');
  while (1) {
    if (!(PINC & (1 << PC5))) {//pin input checkup
      ledon = !ledon;
      _delay_ms(145);
    }
    if (ledon) {
      PORTB = PORTB | (1 << PB5);//toggle on
      if (bossbutton) {
        transmitByte('X');
        bossbutton = !bossbutton;
      }
      _delay_ms(20);
    } else {
      bossbutton = !bossbutton;
      PORTB = PORTB & ~(1 << PB5);//toggle off
      //    transmitByte('0');
      _delay_ms(20);
    }
  }
  return 0;
}
// check out digital_input.txt for the FULL context of what is going on!