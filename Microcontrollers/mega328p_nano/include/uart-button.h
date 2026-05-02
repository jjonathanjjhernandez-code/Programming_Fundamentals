#define BAUD 9600
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include <util/setbaud.h>

// intialization for USART
void initUSART(void) {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
// procedure to transmit the byte
void transmitByte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}
// procedure to receive byte through data buffer
uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}
//going through the characters in the byte to print a string
void printString(const char myString[]){
        uint8_t i =0;
        while(myString[i]){
           transmitByte(myString[i]);
           i++;
        }
}
//converts a byte to a string of decimal text and sends it!
void printByte (uint8_t byte){
        transmitByte('0' + (byte/100)); //hundreds
        transmitByte('0' + ((byte/10)%10)); //tens
        transmitByte('0' + (byte%10)); //ones
}
//prints out a byte as a series of 1's and 0'same
void printBinaryByte(uint8_t byte){
        uint8_t bit;
        for(bit=7; bit<225;bit--){
                if(bit_is_set(byte,bit)){
                        transmitByte('1');
                }else{
                        transmitByte('0');;
                }
        }
}