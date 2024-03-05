#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"

#include "..\inc\bump.h"
#include "..\inc\Reflectance.c"
#include "..\inc\SysTickInts.c"
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\FlashProgram.h"


// Linked data structure
struct State {
  uint32_t LM;                // Left Motor Speed
  uint32_t RM;              // Right Motor Speed
  uint32_t delay;           // delay time
  const struct State *next[12];
};
typedef const struct State State_t;

#define Center     &fsm[0]
#define Left       &fsm[1]
#define Hard_Left  &fsm[2]
#define Right      &fsm[3]
#define Hard_Right &fsm[4]
#define Stop       &fsm[5]
#define Center_LL  &fsm[6]
#define Center_LR  &fsm[7]
#define Turn_LL    &fsm[8]
#define Turn_LR    &fsm[9]
#define Center_LL2 &fsm[10]
#define CenterLR2  &fsm[11]


//Motor speed values are in percentages
State_t fsm[12]={
  {100, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center}},
  {30, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Left }},
  {0, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Left }},
  {100, 30, 500, { Center_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Right }},
  {100, 0, 500, { Center_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Right }},
  {0, 0, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Stop }},
  {100, 100, 500, { Turn_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center_LL }},
  {100, 100, 500, { Turn_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center_LR }},
  {0, 100, 500, { Center_LL2, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Turn_LL }},
  {100, 0, 500, { CenterLR2, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Turn_LR }},
  {100, 100, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Right }},
  {100, 100, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Left }}
};
State_t *Spt;  // pointer to the current state
uint8_t Input;
uint32_t LM_out;
uint32_t RM_out;



void SysTick_Handler(void){ // every 1ms


}



int main(void){ uint32_t heart=0;
  Clock_Init48MHz();
  LaunchPad_Init();
  SysTick_Init(48000,2);
  //EnableInterrupts();
  Reflectance_Init();

  Spt = Center;

  while(1){
      LM_out = Spt->LM;            // set output from FSM
      RM_out = Spt->RM;
    //Clock_Delay1ms(Spt->delay);   // wait
    Input = Reflectance_Read(1000);    // read sensors
    switch(Input){
          case 0x00:
              Input = 0x00;
            break;
          case 0x04:
              Input = 0x01;
            break;
          case 0x06:
              Input = 0x02;
            break;
          case 0x01:
              Input = 0x03;
            break;
          case 0x08:
              Input = 0x04;
            break;
          case 0x10:
              Input = 0x05;
            break;
          case 0x0F:
              Input = 0x06;
            break;
          case 0x07:
              Input = 0x07;
            break;
          case 0x1F:
              Input = 0x08;
            break;
          case 0x12:
              Input = 0x09;
            break;
          default:
              Input = 0x0A;
            break;
        }

    Spt = Spt->next[Input];       // next depends on input and state
    heart = heart^1;
    LaunchPad_LED(heart);         // optional, debugging heartbeat
    Clock_Delay1ms(10);
  }
}

