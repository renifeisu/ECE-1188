# About
For this project, we will design a robot with the ability to follow a line and compete against
our classmates in a race.

# Motor Drivers
We will use SysTick timers to control the motor drivers. Our design will be modified such that the motors are controlled by the Timer A hardware module being used to generate PWM signals. (See Module 13)

# Collision Detection
The robot’s ability to detect collisions will be improved by making use of edge-triggered interrupts on the bump sensors.
(See Module 14)

# Finite State Machine
We will recreate a new FSM controller that leverages our modifications and is robust to conditions and scenarios our robot will encounter.
(See Module 7)