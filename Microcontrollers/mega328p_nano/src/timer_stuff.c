//checking out timer capabilities for an AVR328p
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USBAPI.h"
static inline void initTimer1(void){
    //normal mode default....simple counter!
    TCCR1B |= (1 << CS11) | (1 <<CS10);
    //clock speed=1 Mhz /64
    //each tick is 64 microseconds ~= 15.6 per ms
}
int main(void){
    char byte;
    uint16_t timerValue;
    initTimer1();
    while(1){

    }
}