//#include <stdint.h>
//#include "msp.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\CortexM.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\SysTickInts.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\Clock.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\bump.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\Reflectance.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\FlashProgram.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\LaunchPad.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\PWM.h"
//#include "C:\ti\tirslk_max_1_00_02\inc\Motor.h"
//
//uint8_t input_handler(uint8_t);
//void output_handler(uint32_t);
//
//// Linked data structure
//struct State {
//  uint32_t state;
//  uint32_t delay;           // delay time
//  const struct State *next[4];
//};
//typedef const struct State State_t;
//
//#define Center          &fsm[0]
//#define BackCenter      &fsm[1]
//#define LeftLoop        &fsm[2]
//#define LeftCheck       &fsm[3]
//#define LeftStraight    &fsm[4]
//#define LeftRight       &fsm[5]
//#define LeftLeft        &fsm[6]
//#define RightLoop       &fsm[7]
//#define RightCheck      &fsm[8]
//#define RightStraight   &fsm[9]
//#define RightRight      &fsm[10]
//#define RightLeft       &fsm[11]
//#define Right           &fsm[12]
//#define Left            &fsm[13]
//#define BackLeft        &fsm[14]
//#define BackRight       &fsm[15]
//// stop 0x00
//// forward 0x01
//// forward left 0x02
//// forward right 0x03
//// backward 0x04
//// backward left 0x05
//// backward right 0x06
//State_t fsm[16]={
//                 {0x01, 500, {BackCenter, Left, Right, Center}}, // Center
//                 {0x04, 500, {BackCenter, LeftLoop, LeftLoop, LeftLoop}}, // BackCenter
//                 {0x02, 500, {LeftCheck, Left, Right, Center}}, // LeftLoop
//                 {0x02, 500, {LeftCheck, LeftLeft, LeftRight, LeftStraight}}, // LeftCheck
//                 {0x01, 500, {RightLoop, LeftLeft, LeftRight, LeftStraight}}, // LeftStraight
//                 {0x03, 500, {RightLoop, LeftLeft, LeftRight, LeftStraight}}, // LeftRight
//                 {0x02, 500, {RightLoop, LeftLeft, LeftRight, LeftStraight}}, // LeftLeft
//                 {0x03, 500, {RightCheck, Left, Right, Center}}, // RightLoop
//                 {0x03, 500, {RightCheck, RightLeft, RightRight, RightStraight}}, // RightCheck
//                 {0x01, 500, {LeftLoop, RightLeft, RightRight, RightStraight}}, // RightStraight
//                 {0x03, 500, {LeftLoop, RightLeft, RightRight, RightStraight}}, // RightRight
//                 {0x02, 500, {LeftLoop, RightLeft, RightRight, RightStraight}}, // RightLeft
//                 {0x03, 500, {BackRight, Left, Right, Center}}, // Right
//                 {0x02, 500, {BackLeft, Left, Right, Center}}, // Left
//                 {0x05, 500, {BackLeft, RightLoop, RightLoop, RightLoop}}, // BackLeft
//                 {0x06, 500, {BackRight, LeftLoop, LeftLoop, LeftLoop}} // BackRIght
//};
//State_t *Spt;
//
//volatile uint32_t Time, MainCount, Output;
//volatile uint8_t line_sensor, bump_sensor, Input;
//void SysTick_Handler(void){ // every 1ms
//    Reflectance_Start();
//    if(Time % 10 == 0){
//        line_sensor = ~(Reflectance_End());
//        Input = input_handler(line_sensor);
//        bump_sensor = Bump_Read()&0x3F;
//    }
//    Time = Time + 1;
//}
//
//
//int main(void){
//    Clock_Init48MHz();
//    LaunchPad_Init();
//    SysTick_Init(48000, 2);
//    EnableInterrupts();
//    Reflectance_Init();
//    Motor_Init();
//    Bump_Init();
//    Spt = Center;
//    while(1){
//        WaitForInterrupt();
//        Output = Spt->state;
//        output_handler(Output);
//        Clock_Delay1ms(Spt->delay);
//        Spt = Spt->next[Input];
//        MainCount++;
//    }
//}
//
//// stop 0x00
//// forward 0x01
//// forward left 0x02
//// forward right 0x03
//// backward 0x04
//// backward left 0x05
//// backward right 0x06
//
//void output_handler(uint32_t Output){
//    switch(Output){
//        case 0x01:
//            // forward
//            LaunchPad_LED(1);
//            P2->OUT = 0x01; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // go forward
//            Motor_Forward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//        case 0x21:
//            // forward left
//            LaunchPad_LED(1);
//            P2->OUT = 0x00; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // turn left
//            Motor_Left(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(1000);
//            // go forward
//            Motor_Forward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//        case 0x03:
//            // forward right
//            LaunchPad_LED(0);
//            P2->OUT = 0x01; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // turn right
//            Motor_Right(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(1000);
//            // go forward
//            Motor_Forward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//        case 0x04:
//            // backward
//            LaunchPad_LED(1);
//            P2->OUT = 0x00; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // go back
//            Motor_Backward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//        case 0x05:
//            // backward left
//            LaunchPad_LED(1);
//            P2->OUT = 0x00; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // go backward
//            Motor_Backward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // turn right
//            Motor_Right(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(1000);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//        case 0x06:
//            // backward right
//            LaunchPad_LED(0);
//            P2->OUT = 0x01; // Red LED
//            // stop
//            Motor_Stop();
//            Clock_Delay1ms(100);
//            // go backward
//            Motor_Backward(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(500);
//            // turn left
//            Motor_Left(0.5*7500, 0.5*7500);
//            Clock_Delay1ms(1000);
//            // finish
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//        default:
//            Motor_Stop();
//            LaunchPad_LED(0);
//            P2->OUT = 0x00; // Red LED
//            break;
//    }
//}
//
//// line sensor handler
//uint8_t input_handler(uint8_t Input){
//    // 0x00 none
//    // 0x01 center
//    // 0x02 left
//    // 0x03 right
//    uint8_t decoded;
//    switch(Input){
//        case 0b00001000:
//        case 0b00010000:
//        case 0b00011000:
//        case 0b00011100:
//        case 0b00111100:
//        case 0b00111110:
//        case 0b01111110:
//        case 0b11111110:
//        case 0b11111111:
//            decoded = 0x01;
//            break;
//        case 0b00100000:
//        case 0b00110000:
//        case 0b01000000:
//        case 0b01010000:
//        case 0b01100000:
//        case 0b01110000:
//        case 0b10000000:
//        case 0b10010000:
//        case 0b10100000:
//        case 0b10110000:
//        case 0b11000000:
//        case 0b11010000:
//        case 0b11110000:
//            decoded = 0x02;
//            break;
//        case 0b00000001:
//        case 0b00000010:
//        case 0b00000011:
//        case 0b00000100:
//        case 0b00000101:
//        case 0b00000110:
//        case 0b00000111:
//        case 0b00001001:
//        case 0b00001010:
//        case 0b00001011:
//        case 0b00001100:
//        case 0b00001101:
//        case 0b00001110:
//        case 0b00001111:
//            decoded = 0x03;
//            break;
//        default:
//            decoded = 0x00;
//            break;
//    }
//    return decoded;
//}
