#include <stdint.h>
#include "msp432.h"
#include "C:\ti\tirslk_max_1_00_02\inc\Clock.h"

void Reflectance_Init(void){

    // CTRL EVEN -> Pin 5.3
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08;  // 5.3 as GPIO
    P5->DIR |= 0x08;    // 5.3 as OUTPUT
    P5->OUT &= ~0x08;   // turn LEDs off

    // CTRL ODD -> Pin 9.2
    P9->SEL0 &= ~0x04;
    P9->SEL1 &= ~0x04;  // 9.2 as GPIO
    P9->DIR |= 0x04;    // 9.2 as OUTPUT
    P9->OUT &= ~0x04;   // turn LEDs off

    // QTRX module
    P7->SEL0 &= ~0x00;
    P7->SEL1 &= ~0x00;    // 7.0-7.7 as GPIO
    P7->DIR &= ~0x00;     // 7.0-7.7 as INPUT
}


uint8_t Reflectance_Read(uint32_t time){

    uint8_t result;
    P5->OUT |= 0x08;      // turn on the 4 even IR LEDs
    P9->OUT |=0x04;       // turn on the 4 odd  IR LEDs

    P7->DIR = 0xFF;       // make P7.7-P7.0 output
    P7->OUT = 0xFF;       // charge the 8 capacitors

    Clock_Delay1us(10);   // wait 10us for charging to complete

    P7->DIR = 0x00;       // change the directionality of the sensor line ports to make them inputs

    Clock_Delay1us(time); // wait for time microseconds

    result = P7->IN;      // read the binary interpretations of the sensor line voltages

    P5->OUT &= ~0x08;     // turn off the 4 even IR LEDs
    P9->OUT &= ~0x04;     // turn off the 4 odd  IR LEDs

    //Need to make output 5 bits instead of 8 bit
    result = ~result;
    uint8_t temp = result;
    temp = temp >> 1;
    temp &= 0x2A;
    result |= temp; ////////
    temp = result;
    temp = temp >> 1;
    temp |= 0xFB;
    result |= 0x04;
    result &= temp; ////////
    temp = result;
    temp = temp >> 2;
    temp |= 0xF7;
    result |= 0x08;
    result &= temp; ////////
    temp = result;
    temp = temp >> 3;
    temp |= 0xEF;
    result |= 0x10;
    result &= temp; ////////
    result &= 0x1F;

    return result;        // return the 8-bit value that represents the state of the sensors
}

// ------------Reflectance_Center------------
// Read the two center sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: 0 (off road), 1 off to left, 2 off to right, 3 on road
// (Left,Right) Sensors
// 1,1          both sensors   on line
// 0,1          just right     off to left
// 1,0          left left      off to right
// 0,0          neither        lost
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Center(uint32_t time){
    // write this as part of Lab 6
  return 0; // replace this line
}


// Perform sensor integration
// Input: data is 8-bit result from line sensor
// Output: position in 0.1mm relative to center of line
int32_t Reflectance_Position(uint8_t data){
    // write this as part of Lab 6
    int32_t top_sum = 0;
    int32_t bottom_sum = 0;
    int32_t wi[8] = {-33400,-23800,-14300,-4800,4800,14300,23800,33400};
    int32_t i;
    for(i = 0; i<8; i++){
        uint8_t data2 = data >> i;
        data2 &= 0x01;
        top_sum += (data2*wi[7-i]);
        bottom_sum += data2;
    }
    int32_t d = top_sum/bottom_sum;

 return d; // replace this line
}


// ------------Reflectance_Start------------
// Begin the process of reading the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// Input: none
// Output: none
// Assumes: Reflectance_Init() has been called
void Reflectance_Start(void){
    // write this as part of Lab 10
}


// ------------Reflectance_End------------
// Finish reading the eight sensors
// Read sensors
// Turn off the 8 IR LEDs
// Input: none
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
// Assumes: Reflectance_Start() was called 1 ms ago
uint8_t Reflectance_End(void){
    // write this as part of Lab 10
 return 0; // replace this line
}

