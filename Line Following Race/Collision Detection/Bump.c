//// Bump.c
//// Runs on MSP432
//// Provide low-level functions that interface bump switches the robot.
//// Daniel Valvano and Jonathan Valvano
//// July 11, 2019
//
///* This example accompanies the book
//   "Embedded Systems: Introduction to Robotics,
//   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
// For more information about my classes, my research, and my books, see
// http://users.ece.utexas.edu/~valvano/
//
//Simplified BSD License (FreeBSD License)
//Copyright (c) 2019, Jonathan Valvano, All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification,
//are permitted provided that the following conditions are met:
//
//1. Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//2. Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
//LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//The views and conclusions contained in the software and documentation are
//those of the authors and should not be interpreted as representing official
//policies, either expressed or implied, of the FreeBSD Project.
//*/
//
//// Negative logic bump sensors
//// P4.7 Bump5, left side of robot
//// P4.6 Bump4
//// P4.5 Bump3
//// P4.3 Bump2
//// P4.2 Bump1
//// P4.0 Bump0, right side of robot
//
//#include <stdint.h>
//#include "msp.h"
//// Initialize Bump sensors
//// Make six Port 4 pins inputs
//// Activate interface pullup
//// pins 7,6,5,3,2,0
//volatile uint8_t result;
//void Bump_Init(void){
//    // write this as part of Lab 10
//    result = 0;
//    P4->SEL0 &= ~0xED;
//    P4->SEL1 &= ~0xED; // Configure P4.0, P4.2, P4.3, P4.5, P4.6, P4.7 as GPIO
//    P4->DIR &= ~0xED;  // Make ports input
//    P4->REN |= 0xED;   // Enable pull resistors
//    P4->IES |= 0xED;   // Make ports falling edge event
//    P4->IFG &= ~0xED;  // clear flags (reduce possibility of extra interrupt)
//    P4->IE |= 0xED;    // arm interrupt on ports
//    P4->OUT |= 0xED;   // Ports are pull-up
//    NVIC->IP[9] = (NVIC->IP[9]&0x00FFFFFF)|0x40000000; // priority 2
//    NVIC->ISER[1] = 0x00000040;        // enable interrupt 38 in NVIC
//}
//// Read current state of 6 switches
//// Returns a 6-bit positive logic result (0 to 63)
//// bit 5 Bump5
//// bit 4 Bump4
//// bit 3 Bump3
//// bit 2 Bump2
//// bit 1 Bump1
//// bit 0 Bump0
//uint8_t Bump_Read(void){
//    // write this as part of Lab 10
//    // 0b543-21-0
//    result = ~P4->IN&0x01; // 0b-------0
//    result |= (~P4->IN&0x0C)>>1; // 0b-----210
//    result |= (~P4->IN&0xE0)>>2; // 0b--543210
//    return result; // replace this line
//}
//// we do not care about critical section/race conditions
//// triggered on touch, falling edge
//void PORT4_IRQHandler(void){
//    // write this as part of Lab 14
//    uint8_t status;
//    status = P4->IV;  // 2*(n+1) where n is highest priority
//    switch(status){
//            case 0x01:          // 0b00000001
//                P2->OUT = 0x01; // Red LED
//                break;
//            case 0x02:          // 0b00000010
//                P2->OUT = 0x02; // Green LED
//                break;
//            case 0x03:          // 0b00000011
//                P2->OUT = 0x02; // Green LED
//                break;
//            case 0x04:          // 0b00000100
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x05:          // 0b00000101
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x06:          // 0b00000110
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x07:          // 0b00000111
//                P2->OUT = 0x02; // Green LED
//                break;
//            case 0x08:          // 0b00001000
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x09:          // 0b00001001
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x0A:          // 0b00001010
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x0B:          // 0b00001011
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x0C:          // 0b00001100
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x0D:          // 0b00001101
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x0E:          // 0b00001110
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x0F:          // 0b00001111
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x10:          // 0b00010000
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x11:          // 0b00010001
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x12:          // 0b00010010
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x13:          // 0b00010011
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x14:          // 0b00010100
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x15:          // 0b00010101
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x16:          // 0b00010110
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x17:          // 0b00010111
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x18:          // 0b00011000
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x19:          // 0b00011001
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x1A:          // 0b00011010
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x1B:          // 0b00011011
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x1C:          // 0b00011100
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x1D:          // 0b00011101
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x1E:          // 0b00011110
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x1F:          // 0b00011111
//                P2->OUT = 0x03; // Yellow LED
//                break;
//            case 0x20:          // 0b00100000
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x21:          // 0b00100001
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x22:          // 0b00100010
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x23:          // 0b00100011
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x24:          // 0b00100100
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x25:          // 0b00100101
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x26:          // 0b00100110
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x27:          // 0b00100111
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x28:          // 0b00101000
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x29:          // 0b00101001
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x2A:          // 0b00101010
//                P2->OUT = 0x06; // Pink LED
//                break;
//            case 0x2B:          // 0b00101011
//                P2->OUT = 0x06; // Pink LED
//                break;
//            case 0x2C:          // 0b00101100
//                P2->OUT = 0x06; // Blue LED
//                break;
//            case 0x2D:          // 0b00101101
//                P2->OUT = 0x06; // Blue LED
//                break;
//            case 0x2E:          // 0b00101110
//                P2->OUT = 0x06; // Blue LED
//                break;
//            case 0x2F:          // 0b00101111
//                P2->OUT = 0x06; // Yellow LED
//                break;
//            case 0x30:          // 0b00110000
//                P2->OUT = 0x06; // Sky Blue LED
//                break;
//            case 0x31:          // 0b00111001
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x32:          // 0b00111010
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x33:          // 0b00111011
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x34:          // 0b00111100
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x35:          // 0b00111101
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x36:          // 0b00111110
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x37:          // 0b00111111
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x38:          // 0b00111000
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x39:          // 0b00111001
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x3A:          // 0b00111010
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x3B:          // 0b00111011
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x3C:          // 0b00111100
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x3D:          // 0b00111101
//                P2->OUT = 0x05; // Pink LED
//                break;
//            case 0x3E:          // 0b00111110
//                P2->OUT = 0x04; // Blue LED
//                break;
//            case 0x3F:          // 0b00111111
//                P2->OUT = 0x04; // Blue LED
//                break;
//            default:
//                P2->OUT &= ~0xFF; // LED off
//                break;
//        }
//
//}
//
