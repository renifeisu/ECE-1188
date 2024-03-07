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
//#include <stdio.h>
//#include "msp.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\Clock.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\PWM.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\Motor.h"
//
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
//
//void b_center(void){
//    // any center/random bumper triggers
//    LaunchPad_LED(1);
//    P2->OUT = 0x01; // Red LED
//    // stop
//    Motor_Stop();
//    Clock_Delay1ms(500);
//    // go back
//    Motor_Backward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // turn 180
//    Motor_Left(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(4000);
//    // go forward
//    Motor_Forward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // finish
//    Motor_Stop();
//    LaunchPad_LED(0);
//    P2->OUT = 0x04; // Red LED
//}
//
//void b_left(void){
//    // left bumper triggers
//    LaunchPad_LED(1);
//    P2->OUT = 0x02; // Green LED
//    // stop
//    Motor_Stop();
//    Clock_Delay1ms(500);
//    // go back
//    Motor_Backward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // turn right
//    Motor_Right(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(2000);
//    // go forward
//    Motor_Forward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // finish
//    Motor_Stop();
//    LaunchPad_LED(0);
//    P2->OUT = 0x04; // Red LED
//}
//
//void b_right(void){
//    // right bumper triggered
//    LaunchPad_LED(1);
//    P2->OUT = 0x03; // Yellow LED
//    // stop
//    Motor_Stop();
//    Clock_Delay1ms(500); //1s
//    // go back
//    Motor_Backward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // turn left
//    Motor_Left(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(2000);
//    // go forward
//    Motor_Forward(0.5*7500, 0.5*7500);
//    Clock_Delay1ms(500);
//    // finish
//    Motor_Stop();
//    LaunchPad_LED(0);
//    P2->OUT = 0x04; // Red LED
//}
//
//void b_none(void){
//    LaunchPad_LED(0);
//    P2->OUT = 0x04; // Blue LED
//}
//// PORT4_IRQHandler
//// we do not care about critical section/race conditions
//// triggered on touch, falling edge
//volatile uint8_t triggered = 0;
//void PORT4_IRQHandler(void){
//    // write this as part of Lab 14
//    uint32_t status;
//    status = P4->IV;  // 2*(n+1) where n is highest priority
//    printf("Interrupt Vector: %02X\n", status);
//    switch(status){
//        case 0x02:
//        case 0x06:
//            b_right();
//            break;
//        case 0x0E:
//        case 0x10:
//            b_left();
//            break;
//        case 0x08:
//        case 0x0C:
//            b_center();
//            break;
//        default:
//            b_none();
//            break;
//
//    }
//    triggered = 1;
//    P4->IFG &= ~0xED; // Clear flag
//    Clock_Delay1ms(500); // Delay for 500ms
//    triggered = 0;
//}
