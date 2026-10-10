# SERVO TESTER

A servo tester is basically a device someone can use to check whether their servo motors work or not and this can be very essential as it can help you to check your servo motors before having to write new code just to run a single servo.
Most of the servo need 1ms to 2ms pulse so that it moves from 0 to 180 degrees respectively.

Here is a normal view of servo tester:
![SERVO TESTER NORMAL VIEW](assets/PREVIEW.PNG)

Exploded View:

![SERVO TESTER EXPLODED VIEW](assets/exploded%20vieww.PNG)

## WORKING / SCHEMATIC

The main component here is Arduino Nano I chose this specially because this servo tester also has a 0.91 inch display module.
The display shows stats like speed, angle, mode, etc.
It also feature a potentiometer to control different things based on the mode selected
It also has two buttons one is for resetting to original position and other is for switching between sweep and manual mode.

### The servo tester has 4 modes which are:
- Manual Mode : As the name suggests here you control the servo manually by using the potentiometer. In this potentiometer controls the position of servo.
- Sweep : In this the servo moves from the minimum position to maximum position it can attain between 1ms to 2ms pulses which in most cases is between 0 to 180 degrees. In this the potentiometer controls the speed of sweep of servo.
- Calibration : I added this mode because if someone chose to have a different kind of potentiometer then the readings may become incorrect, which is why in calibration mode you can make your servo tester adapt to your potentiometer. In this the potentiometer is used for setting the maximum and minimum position.
It can be selected by pressing the two buttons simultaneously.
- RESET : In this the servo moves to the initial position and stays like that.

## Bill of Materials

| Component | Quantity | 
|-----------|----------|
| Arduino Nano | 1 |
| Arduino Data Cable | 1 |
| 0.91" OLED Display Module | 1 |
| Push Button | 2 |
| Toggle Switch | 1 |
| PCB | 1 |
| Male connector pins | 11 |
| Top enclosure | 1 |
| Middle Enclosure | 1 |
| Bottom Panel | 1 |
| 6-12V DC Power Source | 1 |
| Servo Motor (SG90) | 1 |
| 4x1.5mm magnets | 2 |
| Diodes | 2 |

## Wiring / Schematic
An overview of what the PCB is like.

[![View PCB on KiCanvas](https://hack.club/pcb-badge)](https://kicanvas.org/?repo=https://github.com/VX7FAR/Servo-Tester/tree/main/PCB)

Circuit:

![CIRCUIT](assets/circuit.png)

PCB:

![PCB TRACES](assets/PCB%20tracing.png)

PCB 3D Model:

![PCB 3D MODEL](assets/PCB.png)

## Things to keep in mind when using the repository:
- The CAD folder contains CAD model for each part individually as well as step and f3d original files.
- The firmware was made using platformIO which is a vs code extension so you will have to load the directory where platform.ini file is. If you are using arduino IDE then you can directly copy the code `from src/main.cpp` and header is in `include/animation.h`.
- The libraries are mainly for controlling the display and they are `Adafruit_SSD1306.h` and `Adafruit_GFX.h`.
- `PCB` folder contains everything related to PCB like gerber file (`PCB-gerber.zip`), kicad files and also the 3D model of PCB (`servo tester.step`).
- `assets` folder contains things that are not really important for making the project but I kept them for having a bit easy while working and writing the README. You can freely ignore that folder if you want to.

## Things to keep in mind when using the project:
- To run the servos you will have to use an external power source which will be connected on top left of the PCB by two connector pins
- When running the servo make sure to connect the servo then power them up as there is a direct connection between ground to vcc of servo power source
