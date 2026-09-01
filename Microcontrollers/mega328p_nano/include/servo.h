//a header for servo.c just to clean some stuff up!
#include "uart-printf-scanf.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

void initServo(void) {//servo configuration but we are using a 16-bit timer!
  TCCR1A |= (1 << COM1A1); // everytime the time interval is done the OC1A/OC1B
                           // pin stops pulsing based on compare match!

  // waveform generation settings
  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  TCCR1A |= (1 << WGM11);
  //

  TCCR1B |= (1 << CS11); // we are doing 16MHz/8 ~=2MHz which is close to .5us
                         // as our counter to determine then the ticks....
  ICR1 = 40000; // we do our desired frequency operation say 128Hz(MG90S 9G Micro Servo  has
                // operating range of 20ms) and thus                 
                // that divided by 0.5us gives us roughly 40000 ticks that the
                // chip needs to count
  // now this here is the counter for the time interval{period} of the pulses
  // but it is now time to configure our pulses

  OCR1A = 3000; // this should ALWAYS be measured in ticks and is super
                // dependent on the pre-scaler you decide to choose!{our range is from 1ms to 2ms}
}



void init_eight_bit_timer(void) {//just a regular old 8-bit timer for the seconds counting!
  TCCR0B =
      (1 << CS02) |
      (1 << CS00); // clck 16MHz/1024 prescaler....should result in 15625 ticks
                   // but register is 8 bits so 15625/255 roughly results in
                   // counting the register 255...61 times to count a second
  TCCR0A = (1 << WGM01); // CTC for OCR0A comparasion!
  OCR0A = 255; // although this a 8-bit prescaler/1024 we are slightly off....by
               // less
  TIFR0 = (1 << OCF0B) | (1 << OCF0A) |
          (1 << TOV0); // i guess this plays as a security feature basically
                       // once a corresponding enable bit like OCIE0B or OCIE0A
                       // is enabled it allows compare match execution
  TIMSK0 = (1 << OCIE0A); // enabling time 0 output compare match interrupt
  sei();
}

// As for the setup we will place VRx on A1(PC1) & VRy on A2(PC2)
// For the digital input of the swithch(basde on the KY-023 dual axis joystick) we will place that on PD3
void initADC0(void){
    ADMUX |= (1<<REFS0);//Configuration 01: AVCC with external capacitor at AREF pin
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//Configuration of 111: Division factor of the internal: clk source/128
    ADCSRA |= (1<<ADEN);// enable the ADC logic block
}

void initADCinterrupt(void){
    ADCSRA |= (1<<ADIE);//enable the global interrupts specifically the I-bit in the status register of the MCU!
    //ADCMUX----MUX3:0 Analog Channel Selection Bits
    ADMUX = (0b11110000 & ADMUX) | (0b00000001);
    ADCSRA |= (1<<ADSC);//enable the ADC conversion!
    sei();//enable global interrupts!
}