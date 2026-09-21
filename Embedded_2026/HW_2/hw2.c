/*
Question 1
a) Timer_A is using a 300kHz clock signal. What is the timer's period if the continous mode is used?
Everytime you divide by a input divider, what you get back are what is called the tick periods, how long one timer count takes, but you are going to use
a multitude of these to make your total frequency count looking something like this....
T = 65536*ID/f_clk--------65536 since Timer_A is a 16-bit timer thus.....
    --Input Divider = 1
        Timer Period = 218.45ms
    --Input Divider = 2
        Timer Period = 436.91ms
    --Input Dvider = 4
        Timer Period = 873.813ms
    --Input Divder = 8
        Timer Period = 1.74s
b) Timer_A is using a 300kHz clock signal. We're aiming at a timer period of 0.5 seconds using the up mode. Find suitable values
of TACCR0 and ID(Input divider). Give all the possible solutions

As for the calculation of upmode.....
T = (TACCR0+1)*ID/f_clk
If we desire a time based on 0.5 seconds, this is completely dependent on the clock divider that we use to relate the number of ticks the peripheral
has to count to make 0.5 seconds....
    --Input Divider = 1
        Timer Period = 3.33us
        TACCR0 ~= 150150
    --Input Divider = 2
        Timer Period = 6.67us
        TACCR0 ~= 74962
    --Input Divider = 4
        Timer Period = 13.33us
        TACCR0 ~= 37509
    --Input Divder = 8
        Timer Period = 26.67us
        TACCR0 ~= 18747
However, take note that Timer_A is a 16-bit timer with its max capacity being 65536 bits, thus Divider 1 and Divider 2 are not possible for this frequency selection

Question 2
a)Timer_A is using ACLK configured to a 16 kHZ crystal. What is the timer period if the continous mode is used? Give the answer for all the values of ID
Using the Auxillary clock is just fine and can be passed directingly into the timer OR be divided using 2,4,8 using the ID bits
    --ACLK passed to Timer
        Timer Period = 4.096s
    --ACLK divided by 2
        Timer Period = 8.096s
    --ACLK divided by 4
        Timer Period = 16.384s
    --ACLK divided by 8
        Timer Period = 32.768s

b) Timer_A is using a 5MHz clock signal. Can we configure the timer to directly generate a delay of 0.5 seconds? Show your analysis
To answer the question this task can not be done directly(the tick counts are too big for the 16 bit timer), a couple loopholes are in place, but it is very much possible.    
Using our 8 divider we can get 5MHz to 625000 ticks, if we want 0.5 seconds
    we'd need.....0.5/(1/625000) ~= 312500 ticks
    now we are only capable of getting maximum 65536, so if we enable an interrupt to conduct an ISR to increment uint8_t variable we can most defenitely get 0.5 seconds
    since 312500/65536 ~= 4.7, meaning if we go to our main loop, we can say if(count >= 5) {printf("0.5 delay!\r\n")}...however time can drift....
    if we want a smoother number we can get a pre-scale divider of 2 that way our tick ratio is rouhglyl...1250000/65536 ~= 19.07 times for a 0.5 second delay!

Questio 3
a)Two clock technologies used in MCU are the crystal oscillator and the RC oscillator. For each of them, comment on:
    --Startup Speed (after the clock has been disabled for a while)
    --Accuracy
    --Stability with respect to temperature and voltage variations
    --Price
    1.In terms of speed the oscillator might take some clock cycles to start up since the internal circuitry might need a moment to adjust the parameters you placed.
    As for the RC oscillator which may be a crystal??? Starts up as soon as you hit it with some voltage!
    2.Now as for accuracy most if not all oscillators give a very nice, stable reference(if provided with the right voltage range!) for the entirety of the time it is on. As for
    RC crystal it is completly dependent on the parasitics of the crystal and the value of the components you placed to aid it such as the load capacitors and the dampening resistor.
    3.Both oscillator and RC crystal have variations to temp. and voltage variations, and is entirely dependent of one used. But as long as an oscillator has a constant nominal voltage
    it should work, as for the crystal those voltage variations are dependent on its properties and the components along side with it.
    Oscillator is stable whereas RC varies with temp and voltage
    4.Oscillators are just a little more pricey than that of crystals

Question 4
a)Why does embedded programming use 'extension' to C?
It appears that extensions are additional features provided by the associated compilers like GCC Extensions to optimize your code for specific hardware architectures. These
extensions help reduce the size of the compiled program , improve performance, and enable access to hardware-specific instructions not available in Standard C
    --Accessing special registers and instructions
    --declaring interrupt service routines
    --memory placement and types
    --optimization and control
b)What is the downside of extensions regarding code portability?
They are entirely dependent on the compiler you are using!! Not all compilers are equal...meaning if your MCU is not compactible with the compiler, it might do more harm than good!
    --Code using extensions is tied to one compiler and typically meaning one architecture
c)What is an instrinic function?
An intrisinc function is a function-like construct built into the compiler that gets translated directly into specific machine instructions instead being a call to library code.
It gives C access to processor instructions with no assembly

d)In MSP430, interrupts are enabled/disabled by writing to the bit called GIE in the status register.
Why use functions like these.....
_enable_interrupts();
_disable_interrupts();
it is just easier to do!
    --GIE is not accessed like a normal variable since it is part of the CPU status register, which is not reachable from our memory-mapped peripherals
    --The instrinsic function maps to the exact instruction
    --On MSP430 there is a specific rule that the instruction following EINT executes before a pending interrupt is serviced, the instrsinc function takes care of that
    --Readability and portability across MSP430 toolchains 

Question 5
a)How many bits is an integer(int) in the C language?
Minimum size being 16-bits
b)Why does embedded programming use data types like (uint_8t, int_8t etc...)
Mainly to know just how many bits you can store in a varibles...
    --int8_t -128 - 127 data
    --uint8_t 0-255 data
    etc
c)A programmer wrote a software delay loop that counts the variable(unsigned int counter) from 0 up to 45000 to create a small delay. If the user wishes to double the delay,
can they simply increase the upperbound to 90000?
no , not really highest value is 65536 BUT they can reset the counter then continue counting to 90000, but the questionn is how long will that take????
d)If the code contains a delay loop and we noticed that no delay is being created at run-time. What should we suspect during debugging?
    --bound is too small
    --loop condition or variable type problems(these are things the compiler will probably highlight)
    --compiler optimized loop(....i guess make the variables volatile if need be....)
*/
