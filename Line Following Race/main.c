#include <stdint.h>
// #include "msp.h"
// #include "../inc/Clock.h"
// #include "../inc/LaunchPad.h"
// #include "../inc/TExaS.h"

// #include "..\inc\bump.h"
// #include "..\inc\Reflectance.c"
// #include "..\inc\SysTickInts.c"
// #include "..\inc\CortexM.h"
// #include "..\inc\LaunchPad.h"
// #include "..\inc\FlashProgram.h"


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

/*#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/CortexM.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/SysTickInts.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/Clock.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/bump.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/Reflectance.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/LaunchPad.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/PWM.h"
#include "/Users/carabuck/Downloads/tirslk_max_1_00_00/inc/Motor.h"*/



// Linked data structure
struct State {
  uint32_t LM;                // Left Motor Speed
  uint32_t RM;              // Right Motor Speed
  uint32_t delay;           // delay time
  const struct State *next[12];
};
typedef const struct State State_t;

//#define Center     &fsm[0]
#define Left       &fsm[1]
//#define Hard_Left  &fsm[2]
//#define Right      &fsm[3]
#define Right &fsm[0]
//#define Stop       &fsm[5]
//#define Center_LL  &fsm[6]
//#define Center_LR  &fsm[7]
//#define Turn_LL    &fsm[8]
//#define Turn_LR    &fsm[9]
//#define Center_LL2 &fsm[10]
//#define CenterLR2  &fsm[11]


//Motor speed values are in percentages
/*State_t fsm[12]={
  {100, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center}},       //Center
  {30, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Left }},           //Left
  {0, 100, 500, { Center_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Left }},  //Hard Left
  {100, 30, 500, { Center_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Right }},         //Right
  {100, 0, 500, { Center_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Right }},            //Hard Right
  {0, 0, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Stop }},                   //stop
  {100, 100, 500, { Turn_LR, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center_LL }},  //Center Lost Left
  {100, 100, 500, { Turn_LL, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Center_LR }},  //Center Lost Right
  {0, 100, 500, { Center_LL2, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Turn_LL }},     //Turn Lost Left
  {100, 0, 500, { CenterLR2, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Turn_LR }},      //Turn Lost Right
  {100, 100, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Right }},   //Center Lost Left 2
  {100, 100, 500, { Stop, Center, Right, Hard_Right, Left, Hard_Left, Hard_Right, Hard_Left, Hard_Left }}      //Center Lost Right 2
};
*/

State_t fsm[2]={

 {100, 100, 500, { Right, Left }},        //Right
 {30, 100, 500, { Left, Right }}          //Left

};

State_t *Spt;  // pointer to the current state
uint8_t Input;
uint32_t LM_out;
uint32_t RM_out;
uint32_t count;
uint32_t delay_out;

void SysTick_Handler(void){ // every 1ms

    Input = Reflectance_Read(1000);    // read sensors
    if(Input == 0xFF)
    {
        Motor_Stop();
        P2->OUT = 0x01; // Red LED
    }
    else if(Input == 0x18)
    {
        Motor_Forward(1000,1000);
        P2->OUT = 0x02; // Green LED
    }
    else if(Input <=0x02)
    {
        Motor_Left(1000, 0);
        P2->OUT = 0x03; // Yellow LED
    }
    else if(Input <= 0x0F)
    {
        Motor_Forward(1000, 500);
        P2->OUT = 0x04; // Blue LED
    }
    else if(Input == 0x40 | 0x80 | 0xC0)
    {
        Motor_Right(0, 1000);
        P2->OUT = 0x05; // Pink LED
    }
    else
    {
        Motor_Forward(500,1000);
        P2->OUT = 0x06; // Sky Blue LED
    }

}



int main(void){
    count = 0;
  Clock_Init48MHz();
  LaunchPad_Init();
  SysTick_Init(4800000,2);
  EnableInterrupts();
  Reflectance_Init();
  EnableInterrupts();
  Motor_Init();
  Bump_Init();
  Input = 0;
  Input = Reflectance_Read(1000);    // read sensors

  //Spt = Right;

  while(1){
    /*LM_out = Spt->LM;            // set output from FSM
    RM_out = Spt->RM;
    delay_out = Spt->delay;
    Motor_Forward(LM_out/100 * 500, RM_out/100 * 500);
    */
   // PORT4_IRQHandler();
    WaitForInterrupt();

     /*Input = Reflectance_Read(1000);    // read sensors

     if(Input == 0x00)
     {
         Motor_Stop();
     }
     else if(Input <= 0xF)
     {
         Motor_Left(1000, 0);
     }
     else
     {
         Motor_Right(0, 1000);
     }*/





  }
}
