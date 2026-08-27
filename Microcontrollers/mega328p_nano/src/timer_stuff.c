//checking out timer capabilities for an AVR328p
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart-printf.h"
FILE uart_output =
    FDEV_SETUP_STREAM(UART_transmit_char, NULL, _FDEV_SETUP_WRITE);
volatile uint16_t eight_bit_tick_counter = 0;
static inline void initTimer1(void){
    //let's see if we can use a simple 8-bit timer...mayber Timer0
    //we will a normal operation and will be using OCR0A as compare value i believe....
    //meanining COM0A1 and COM0A0 will be ZERO!
    TCCR0B = (1<<CS02) | (1<<CS00);//clck 16MHz/1024 prescaler....should result in 15625 ticks but register is 8 bits so 15625/255 roughly results in counting the register 255...61 times to count a second
    TCCR0A = (1<<WGM01);//CTC for OCR0A comparasion!
    OCR0A = 255;//although this a 8-bit prescaler/1024 we are slightly off....by less
    TIFR0 = (1<<OCF0B)|(1<<OCF0A)|(1<<TOV0);//i guess this plays as a security feature basically once a corresponding enable bit like OCIE0B or OCIE0A is enabled it allows compare match execution
    TIMSK0 = (1<<OCIE0A);//enabling time 0 output compare match interrupt
    sei();
}

int main(void){
  stdout = &uart_output; // define the output using the FILE type as mentioned above
  //not only that i believe you are only able to declare wherever you plan to conduct your printf....or just in the main function
    //char byte;
    uint16_t timer_sec=0;
    uint16_t timer_min=0;
    initUSART();
    initTimer1();
    printf("Here we go again!\n");
    while(1){
        if(eight_bit_tick_counter==61){
            if((timer_sec%60==0)&&(timer_sec!=0)){
                timer_min++;
                timer_sec=0;
            }
        printf("Time: %"PRIu16" : %"PRIu16"\n",timer_min,timer_sec);
        timer_sec++;
        eight_bit_tick_counter=0;        
    }
    }
    return 0;
}
ISR(TIMER0_COMPA_vect){//gotta use the COMPA since we are using register A
eight_bit_tick_counter++;
}