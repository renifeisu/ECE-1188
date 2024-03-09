# About
For this project, we will design a robot with the ability to follow a line and compete against
our classmates in a race.

| Module | Contributor |
| :--- | :--- |
| Motor Drivers | Cara Buck |
| Collision Detection | Beryl Sin |   
| Finite State Machine | Aiden Iannetti |   

# Motor Drivers
We will use SysTick timers to control the motor drivers. Our design will be modified such that the motors are controlled by the Timer A hardware module being used to generate PWM signals. (See Module 13)

> [!NOTE]
> The Motor Drivers folder contains a main file from Lab 13 for reference, a PWM.c file, a Motor.c file, and a main.c file. The motor functions were implemented using PWM functions. The main.c file includes a third version of a working FSM for the line follower that was eventually used in the race.

# Collision Detection
The robot’s ability to detect collisions will be improved by making use of edge-triggered interrupts on the bump sensors.
(See Module 14)

> [!NOTE]
> The Collision Detection folder contains bump.c code that was modified iteratively throughout the duration of the first project. The main.c file in this folder has a back-up FSM logic that was not used in the race.

# Finite State Machine
We will recreate a new FSM controller that leverages our modifications and is robust to conditions and scenarios our robot will encounter.
(See Module 7)

> [!NOTE]
> The Finite State Machine folder contains a main.c file with the original FSM implementation that had some issues. There is also a version of the reflectance.c file that modifies the Reflectance_Read() function to decode the 8-bit output to a 5-bit number instead.

# Other
> [!NOTE]
> The other folders contain files that were automatically generated when creating/running the project. Files outside the folders encompassed the updated versions of our modifications and were used in the race on Thursday. 
