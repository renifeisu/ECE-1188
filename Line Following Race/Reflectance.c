#include <stdint.h>
#include "msp432.h"
#include "C:\ti\tirslk_max_1_00_02\inc\Clock.h"

// ------------Reflectance_Init------------
// Initialize the GPIO pins associated with the QTR-8RC
// reflectance sensor.  Infrared illumination LEDs are
// initially off.
// Input: none
// Output: none
void Reflectance_Init(void){
    // write this as part of Lab 6
    // P5.3: Even IR LEDS
    P5->SEL0 &= ~0x08;
    P5->SEL1 &= ~0x08;    // Configure P5.3 as GPIO
    P5->DIR |= 0x08;      // Make P5.3 out
    P5->OUT &= ~0x08;     // LED off
    // P9.2: Odd IR LEDs
    P9->SEL0 &= ~0x04;
    P9->SEL1 &= ~0x04;    // Configure P9.2 as GPIO
    P9->DIR |= 0x04;      // Make P9.2 out
    P9->OUT &= ~0x04;     // LED off

    // P7.0: input
    P7->SEL0 &= ~0xFF;
    P7->SEL1 &= ~0xFF;    // Configure P7.0 as GPIO
    P7->DIR &= ~0xFF;     // Make P7.0 in

}

// ------------Reflectance_Read------------
// Read the eight sensors
// Turn on the 8 IR LEDs
// Pulse the 8 sensors high for 10 us
// Make the sensor pins input
// wait t us
// Read sensors
// Turn off the 8 IR LEDs
// Input: time to wait in usec
// Output: sensor readings
// Assumes: Reflectance_Init() has been called
uint8_t Reflectance_Read(uint32_t time){
uint8_t result;
    // write this as part of Lab 6
  result = 0; // replace this line
  P5->OUT |= 0x08;       // LED on
  P9->OUT |= 0x04;
  P7->DIR |= 0xFF;
  P7->OUT |= 0xFF;       // Initiate charge to capacitor
  Clock_Delay1us(10);    // wait 10 us
  P7->DIR &= ~0xFF;      // Make sensor line ports in
  Clock_Delay1us(time);  // wait time us
  result = P7->IN&0xFF; // convert P7.0 input to digital
  P5->OUT &= ~0x08;       // LED off
  P9->OUT &= ~0x04;
  return result;
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
    int w[] = {-33400,-23800,-14300,-4800,4800,14300,23800,33400};
    int total = 0, sum = 0;
    float d = 0;
    int i;
    for(i = 0; i < 8; i++)
    {
        if(data & 1 == 1)
        {
            total += w[i];
            sum ++;
        }
        data = data >> 1;
    }
    if(sum > 0)
    {
        d = (float)total / sum;
    }
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
volatile uint8_t result;
void Reflectance_Start(void){
    // write this as part of Lab 10
    result = 0;
    P5->OUT |= 0x08;       // LED on
    P9->OUT |= 0x04;
    P7->DIR |= 0xFF;
    P7->OUT |= 0xFF;       // Initiate charge to capacitor
    Clock_Delay1us(10);    // wait 10 us
    P7->DIR &= ~0xFF;      // Make sensor line ports in
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
    // Read the 8-bit sensor result
    Clock_Delay1us(1000);
    result = P7->IN&0xFF;
    P5->OUT &= ~0x08;       // LED off
    P9->OUT &= ~0x04;
    return result;
}


