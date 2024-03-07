#include <stdint.h>
#include "msp.h"
#include "C:\ti\tirslk_max_1_00_02\inc\CortexM.h"
#include "C:\ti\tirslk_max_1_00_02\inc\SysTickInts.h"
#include "C:\ti\tirslk_max_1_00_02\inc\Clock.h"
#include "C:\ti\tirslk_max_1_00_02\inc\bump.h"
#include "C:\ti\tirslk_max_1_00_02\inc\Reflectance.h"
#include "C:\ti\tirslk_max_1_00_02\inc\FlashProgram.h"
#include "C:\ti\tirslk_max_1_00_02\inc\LaunchPad.h"
#include "C:\ti\tirslk_max_1_00_02\inc\PWM.h"
#include "C:\ti\tirslk_max_1_00_02\inc\Motor.h"

void input_handler(uint8_t);
//uint8_t bump_handler(void);

// Linked data structure
struct State {
  uint32_t LM;                // Left Motor Speed
  uint32_t RM;              // Right Motor Speed
  uint32_t delay;           // delay time
  const struct State *next[15];
};
typedef const struct State State_t;

#define Center     &fsm[0]
#define BackCenter &fsm[1]
#define Leftloop   &fsm[2]
#define Leftcheck  &fsm[3]
#define Leftstraight &fsm[4]
#define Leftright &fsm[5]
#define Leftleft &fsm[6]
#define Rightloop &fsm[7]
#define Rightcheck &fsm[8]
#define Rightstraight &fsm[9]
#define Rightright &fsm[10]
#define Rightleft   &fsm[11]
#define Right   &fsm[12]
#define Left    &fsm[13]
#define Backleft    &fsm[14]

volatile uint32_t Time, MainCount;
volatile uint8_t line_sensor, bump_sensor, decoded=0;
void SysTick_Handler(void){ // every 1ms
    Reflectance_Start();
    if(Time % 10 == 0){
        line_sensor = ~(Reflectance_End());
        bump_sensor = Bump_Read()&0x3F;
    }
    Time = Time + 1;
}


int main(void){
    Clock_Init48MHz();
    LaunchPad_Init();
    SysTick_Init(48000, 2);
    EnableInterrupts();
    Reflectance_Init();
    Motor_Init();
    Bump_Init();
    uint8_t status;
    while(1){
        decoded +=1;
        status = P4->IV;
        WaitForInterrupt();
        //decoded = bump_handler();
        MainCount++;
    }
}


// line sensor handler
void input_handler(uint8_t Input){
    // 0x00 none
    // 0x01 center
    // 0x02 left
    // 0x03 right
    uint8_t decoded;
    switch(Input){
        case 0b00001000:
        case 0b00010000:
        case 0b00011000:
        case 0b00011100:
        case 0b00111100:
        case 0b00111110:
        case 0b01111110:
        case 0b11111110:
        case 0b11111111:
            decoded = 0x01;
            break;
        case 0b00100000:
        case 0b00110000:
        case 0b01000000:
        case 0b01010000:
        case 0b01100000:
        case 0b01110000:
        case 0b10000000:
        case 0b10010000:
        case 0b10100000:
        case 0b10110000:
        case 0b11000000:
        case 0b11010000:
        case 0b11110000:
            decoded = 0x02;
            break;
        case 0b00000001:
        case 0b00000010:
        case 0b00000011:
        case 0b00000100:
        case 0b00000101:
        case 0b00000110:
        case 0b00000111:
        case 0b00001001:
        case 0b00001010:
        case 0b00001011:
        case 0b00001100:
        case 0b00001101:
        case 0b00001110:
        case 0b00001111:
            decoded = 0x03;
            break;
        default:
            decoded = 0x00;
            break;
    }
}
