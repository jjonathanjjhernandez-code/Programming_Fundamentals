/*
hey just want to put some functionalaties in here if other files need them!
*/
#include <avr/io.h>     //defines all the PORTS and DDRs
#include <util/delay.h> //provides the function _delay_ms() function
#ifndef BLINKLED_REG_H
#define BLINKLED_REG_H
#endif
//enumeration states for LEDs!
typedef enum direction{
  FORWARD,
  BACKWARD
} led_state;

void POVDisplayD(uint8_t oneByte, led_state ledstate) { // function to register output value for portD/bit
  switch (ledstate)
  {
  case (FORWARD):
  PORTD  = PORTD | oneByte;
  _delay_ms(20);  
    break;
  case(BACKWARD):
  PORTD = PORTD & ~(oneByte);
  _delay_ms(20);
  break;
  }
}

void POVDisplayB(uint8_t oneByte, led_state ledstate) { // function to register output value for portB/bit
  switch (ledstate)
  {
  case (FORWARD):
  PORTB  = PORTB | oneByte;
  _delay_ms(20);  
    break;
  case(BACKWARD):
  PORTB = PORTB & ~(oneByte);
  _delay_ms(20);
  break;
  }
}

void POVDisplayC(uint8_t oneByte, led_state ledstate) { // function to register output value for portD/bit
  switch (ledstate)
  {
  case (FORWARD):
  PORTC  = PORTC | oneByte;
  _delay_ms(20);  
    break;
  case(BACKWARD):
  PORTC = PORTC & ~(oneByte);
  _delay_ms(20);
  break;
  }
}
/*a << b
--where a is the integer value to be shifted
--b specifies how many positions to shift the bits*/
uint8_t onebitShifter(uint8_t shift) {
  return (0b00000001 << shift);
}
