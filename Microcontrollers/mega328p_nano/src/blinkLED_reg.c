#include "blinkLED_reg.h"
// LedS!
// D2-D6 = 0b 1111 1100 <--- equivalent to 0xFC i think in hex....
// ALSO these are your PINS but on PORT D!

// Now for the extra stuff!!!
// LED INPUT indicator <---A0 = PC0....will turn on if button has been pushed
// Button INPUT <--- D13 = PB5...use PINx to let you know if the button has been
// pressed(possibly implement an interrupt!)

// xtra LEDS!
// D8-D10 <---PB0-PB2

int main(void) {
  // DDRD |=(1<<PD3);
  DDRD |= (0b11111100); // initial leds
  DDRB |= (0b00000011); // xtra leds
  DDRC |= (0b00000001); // led button indicator

  while (1) {
//===========Phase One==============//
    for (int i = 2; i < 8; i++) {
        POVDisplayD(onebitShifter(i),FORWARD);
    }    
    for(int j=0;j < 2;j++){
        POVDisplayB(onebitShifter(j),FORWARD);
    }
    _delay_ms(1000);
    for(int j = 1;j >=0;j--){
        POVDisplayB(onebitShifter(j),BACKWARD);
    }
    for (int i = 7; i >= 2; i--) {
        POVDisplayD(onebitShifter(i),BACKWARD);
    }
    _delay_ms(3000);
//===========Phase One==============//


  }
  return 0;
}