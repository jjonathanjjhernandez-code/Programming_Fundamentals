// let's see if we can do this servo drive just right!

#include "servo.h"
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
volatile uint16_t eight_bit_tick_counter = 0;
uint16_t timer_s = 0;
volatile bool channel_switch = false; //global variable to check channel ADC1 & ADC2!
volatile uint16_t VRx_value;//ADC1
volatile uint16_t VRy_value;//ADC2
volatile bool vx_ready = false;
volatile bool vy_ready = false;
int main(void) {
  initUSART();
  initServo();
  init_eight_bit_timer();
  initADC0();
  initADCinterrupt();
  stdout = &uart_output;
  DDRB |= (1<<PB1);
  printf("Time to move some servos!");
  while (1) {
    if (eight_bit_tick_counter == 61) {
      timer_s++;
      eight_bit_tick_counter = 0;
    }
    if(vx_ready){
        if(VRx_value <=400){
            if(OCR1A==2000){
            }else{
                OCR1A = OCR1A + 2;
            }
        }else if(VRx_value >= 600){
            if(OCR1A==4000){
            }else{
                OCR1A = OCR1A - 2;
            }            
        }else{
            OCR1A =3000;
        }
        vx_ready = false;
    }
  }
  return 0;
}
ISR(TIMER0_COMPA_vect) { // gotta use the COMPA since we are using register A
  eight_bit_tick_counter++;
}
//Note to self if we are to EVER use a component that needs a different voltage supply from that of the other component ALWAYS ALWAYS
//reference your MCU ground pin to that external power supply whatever it might be!

//Also we need to figure out how to allow nice and smooth pulses!

ISR(ADC_vect){//&&Vector #: 22   &&Program Address:0x002A
//Interrupt Vector:ADC----ADC Conversion Complete
        if(channel_switch){//if true start with ADC2 else ADC1
            VRy_value = ADC;
            ADMUX = (0b11110000 & ADMUX) | (0b00000001);
            ADCSRA |= (1<<ADSC);
            vy_ready = true;
            channel_switch = !channel_switch;
        }else{
            VRx_value = ADC;
            ADMUX = (0b11110000 & ADMUX) | (0b00000010);
            ADCSRA |= (1<<ADSC);
            vx_ready = true;
            channel_switch = !channel_switch;
        }
}