// Based on given bit numbers like 0x00000000,0x00000001,0x00000010....etc we
// are basically going to manipulate bits based on a given byte!
/*
Jonathan Hernandez-Morales
EEL4742C - 003
*/
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
uint8_t data = 0b00000000;
void print_binary(uint8_t byte){
    uint8_t count = 8;
    printf("Data:");
    while (count>0) {
      if (byte % 2 == 0) {
        printf("0");
      } else {
        printf("1");
      }
      byte = byte / 2;
      count--;
    }
//    printf("\nCount = %"PRIu8"\n",count);
    printf("\n");
}
bool bit_checker(uint8_t byte, uint8_t count){//bits are MSB:7-0:LSB
    uint8_t place_holder = byte;
    uint8_t bit = 0;
    bit |= (1<<count);
    place_holder &= (bit);
    if(place_holder==0){
//      printf("Bit: %"PRIu8" is a zero!\n", count);
      return false;
    }
    else{
//      printf("Bit: %"PRIu8" is a one!\n", count);
      return true;
    }
}

/*
//* * * PART A *  *  *
Write Code that performs the three operations on variable data...
1.Set bit 2
2.Clear bit 2
3.Invert bit 2
 uint8_t data = 0b00000000;
 data |= (0b00000010);// set bit 2
 printf("Data:%"PRIu8"\n",data);
 data &= ~(0b00000010);// clear bit 2
 printf("Data:%"PRIu8"\n",data);
 data ^= (0b00000010);// invert bit 2



// * * * Part B * * *
1.Set bit 4 and 5
2.Clear bits 4 and 5
3.Invert bits 4 and 5
4.Set bit 4 and clear bit 5
  data |= (0b00011000);
  print_binary(data);//rotate the bits!
  data &= ~(0b00011000);
  print_binary(data);
  data ^= (0b00011000);
  print_binary(data);
  data &= (0b00001000); 
  print_binary(data);

// * * * Part C * * *
Write an if condition for each of the cases below. Perform each operation independently of each other
1.Check if bit 3 is 1
2.Check if bit 3 is 0
3.Check if bit bits 3, 4 are 1,1
4.Check if bit 3 is 0 and bit 4 is 1
5.Check if bits 3, 4 are 0, 0
  data = (0b00011001);
  if(bit_checker(data,3)){
    printf("Bit 3 is one a 1!\n");
  }else{
    printf("Bit 3 is one a 1!\n");
  }
  data = (0b00010001);
  bit_checker(data,3);
  if(bit_checker(data,3) && bit_checker(data,4)){
    printf("Bits 3 & 4 are a one!\n");
  }else if((bit_checker(data,3)==0) && (bit_checker(data,4)==0)){
    printf("Bits 3 & 4 are a zero!\n");
  }else if((bit_checker(data,3)==0)&& (bit_checker(data,4)==1)){
    printf("Bit 3 is zero while bit 4 is one!\n");
  }else{
    printf("unknown condition!\n");
  }



//Question 2 Part A
SLP: selects sleep mode, value between 0 and 3
CLK: selects clock speed, value betweem 0 and 7
CAP: selects built-in capacitor value, between 0 and 3
IE: interrupt enable bit(1:enable/0:disable)
Write a line of code that configures the module as the following
(Sleep Mode 1)(Clock Speed 5)(Capacitor Value 2)(Interrupts Enabled)
CTL |= (SLP_1) | (CLK_5) | (CAP_2) | (1<<IE);

//Part B
For the operation above, show the masks used and the final value of CTL in binary
Assuming CTL starts off as 0b00000000......
SLP_1 = 0b0100 0000
CLK_5 = 0b0010 1000
CAP_2 = 0b0000 0100
IE =    0b0000 0001
CTL =   0b0110 1101

//Part C
Write a piece of code that changes SLP to 2. The current value of SLP is unknown
CTL &= ~(0b11000000);
CTL |=  (0b10000000)

//Part D
Write a piece of code that changes CLK to 6. The current value of CLK is unknown
CTL &= ~(0b00111000);
CTL |=  (0b00101000);

//Part E
Write an if condition line that check if SLP=2
uint8_t dummy = CTL 
if((dummy&SLP_2)==(SLP_2)){....do something....}

//Part F
Write an if-condition line that checks if CLK=6
uint8_t dummy = CTL 
if((dummy&CLK_6)==(CLK_6)){....do something...}

//Part G
Write an if-condition that checks if the current value of CLK is either of (0,2,4,6)
uint8_t dummy = CTL 
if( ((dummy&CLK_0)==(CLK_0)) | ((dummy&CLK_2)==(CLK_2)) | ((dummy&CLK_4)==(CLK_4)) | ((dummy&CLK_6)==(CLK_6))) {...do something....}



//  * * * * * * *
//  Question 3
//  * * * * * * *
Part A] A memory is byte addressable and has an 18-bit address. All the addresses are valid. What is the total size of the memory? 
Number of addresses = 2^18 = 262144  bytes of memory for addresses(each address being accessed by 1 byte) 
    --Byte Addressable: describes how much data lives at each address location
    --Address Width: is how many bits are in the address itself, determines how many locations exist

  Part B] A memory is byte addressable and has a total size of 17,408 bytes(17kB). What is the smallest address size that can be used for this memory?
logbase2(17000) ~= 14.09
2^14 ~= 16,384 kB
2^15 ~= 32,768 kB
so we stick with the bigger number 15 address bit

//  * * * * * * *
//  Question 4
//  * * * * * * *
Part A] A computer maintains memory alignment. At what addresses can we store a byte variable? What about a 16-bit variable?
Both will be done in a memory address, HOWEVER how it is partitioned inside of it is super dependent on the chip!
      --Alignment means a variable of size N bytes is stored at an address that is a multiple of N
      So basically put anything that goes past 8 bits needs to be separated into two sections of the memory
        1.Byte(8-bit) variable: any address (multiple of 1)
        2.16-bit variable: only even addresses (multiple of 2)

Part B] A computer maintains memory alignment. Show how the variables below are stored in the memory if they have to be stored in the order
they are declared (x,f,y,g,z), starting at address 400.
Show the value at each address (including empty slots)
unsigned char x;  //8 bit variable
short int f;      //16-bit variable
unsigned char y;  
short int g;
unsigned char z;
Assuminh each address is byte accessible....
400 = x
401 = empty (seems like 16-bit address needs even numbers?)
402 = f high byte
403 = f low byte
404 = y
405 = empty
406 = h high byte
407 = h low byte
408 = z
Part C] Repeat the question above knowing that memory should be aligned but the variables can be stored in any order
400 = f high byte
401 = f low byte
402 = h high byte
403 = h low byte
404 = x
405 = y
406 = z

//  * * * * * * *
//  Question 5
//  * * * * * * *
Part A] Explain the Big Endian and the Little Endian configurations
Part B] Show how the data (0x45CD) is stored in address 400(0x0193) in either of the configurations
Big: 
Address: 0x0193
Data:    0x45CD

Little:
Address: 0x0193
Data:    0xDC54
Part C] Which configuration is used in the MSP430? {probably little endian!}

//  * * * * * * *
//  Question 6
//  * * * * * * *
Part A] A MCU memory map allocates the FLASH code space to the address range [0x0500 to 0x0CFF].
What is the code size, in bytes that is supported by this MCU?
 0x0CFF
-0x0500
==========
 0x07FF

Size = Range + 1 = 
  0x07FF 
+ 0x0001 = 0x0800 = (16^2)*(8) = 2048 bytes word of code space

Part B] The vector table contains memory addresses(a vector is a memory address). In a certain MCU
device, the vector table is in the range [0xFFC0 to 0xFFFF]. The memory address is 16-bit. How many
vectors does this vector table support.
 0xFFFF
-0xFFC0
==========
 0x003F
 
 Size = Range + 1
 0x003F
+0x0001 = 0x0040 = (16^1)*(4) =64 bytes....with each vector being 2bytes worth....there are about 32 vectors supported
*/
int main(void) {
  printf("Fair Warning these bits need to be flipped for proper reading!\n");

}