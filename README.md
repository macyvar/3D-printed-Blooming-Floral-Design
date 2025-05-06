# 3D-printed-Blooming-Floral-Design
A 3D-printed flower that opens and closes using a servo controlled by a TM4C123 microcontroller. Supports manual (button) and automatic (light sensor) modes using PWM, GPIO, and SPI. Built for ECE 425 to combine embedded systems with creative mechanical design.

# Introduction
This project fulfills the final project requirement for the following classes at California State University, Northridge (CSUN):
- ECE 425: Microprocessor Systems

Performed By:
- Macy Varga
- Vedi Vartani

Professor:
- Aaron Nanas

Click on 'ECE425 Final Project Report (1).pdf' to view the report that contains additional details

Click on '3D Print Floral Design.pptx' to view the presentation for presentation slides

Video Demonstrations:
- Manual Mode: [Link](https://www.youtube.com/shorts/sJubQrR22dA)
- Automatic Mode: [Link](https://www.youtube.com/shorts/-aOCNeL3odc)

# Project Goals
- Demonstrate embedded systems concepts
    - Apply course topics like GPIO, PWM, SPI, and interrupt handling in a hands-on project
- Create responsive motion control
    - Design a system where a servo motor drives smooth, repeatable blooming action for a 3D-printed flower
- Support multiple input modes
    - Implement both manual (button) and automatic (light sensor) controls for triggering the flower’s motion
- Integrate mechanical and electrical design
    - Convert servo rotation into vertical motion through a custom mechanical assembly, coordinated with embedded control logic
- Develop modular, maintainable code
    -  Organize code into reusable drivers for timing, motor control, input, and communication peripherals
- Build and test a working prototype
    - Fabricate the parts, wire the system, debug, and demonstrate consistent, functional performance
# Video Demonstration
- Button Control Demo: [Link]
- Motion Sensor Control Demo: [Link]


# Project Description
Implemented in C on the TM4C123 microcontroller platform, this project integrates embedded systems and mechanical design to control a 3D-printed blooming flower. The project achieves the following:

- Designed and built a 3D-printed flower with realistic blooming motion using a servo motor and a custom mechanical linkage
  -A linear actuator mechanism was developed to convert the servo’s rotary motion into vertical displacement of a central axle
  - Petals open as the axle rises and close as it lowers, mimicking natural blooming

- Implemented dual control modes on the microcontroller:
    - Manual Mode (PMOD BTN):
      - GPIO pins PA2–PA5 read button input using interrupt-driven event handling
      - Each button press sets a predefined servo position (e.g., fully closed, half bloom, fully open)
    - Automatic Mode (PMOD ALS):
      - Light sensor data is read via SPI using SSI2 (PB4–PB6)
      - The servo opens the flower when ambient light exceeds a threshold (e.g., from a flashlight or sunlight)
      - Ambient light level is also displayed on EduBase LEDs by outputting the top 4 bits of the 8-bit sensor value

- PWM control implemented using Module 1 Generator 3 (PF2, M1PWM6) for the servo motor
  - PWM signal frequency: 50 Hz
  - Duty cycle range mapped from approximately 553 μs (closed position) to 2425 μs (fully open)
  - Servo positions are calibrated using clock tick values (e.g., 1875 for closed, 3590 for open)

- Utilized system-level timing via the SysTick timer for delay and event pacing
  - Blocking delay functions in microseconds and milliseconds support consistent timing for sensor polling and motor response

- Modular codebase includes:
  - 'main.c': Core logic for control flow
  - 'PWM1_3.c:' PWM initialization and control
  - 'GPIO.c': LED output and button setup
  - 'SysTick_Delay.c': System timing functions
  - 'PMOD_BTN_Interrupt.c' and 'SSI2.c': Peripheral drivers for button and SPI communication
 
- Designed all mechanical components using Rhino 3D
  - Includes a housing for the servo, the central axle, a shaft-and-piston mechanism, and a structural base
  - Addressed fabrication challenges related to print tolerances and material constraints
  - Future improvements could include an integrated electronics enclosure and high-resolution resin printing for finer petal detail

 # Block Diagram
 ![Image](https://github.com/user-attachments/assets/d2e53a00-e8b3-41da-88ea-2a3454e62eb6)

 # Parts
 | Part | QTY | Proce $ | Link|
 | --- | --- | --- | --- |
 | Tivia C Series TM4C123G LaunchPad | 1 | 16.99 per unit | [Product Link](https://www.ti.com/tool/EK-TM4C123GXL)
 | USB-A to Micro-USB Cable | 1 | 8.24 per unit | [Product Link](https://www.amazon.com/Amazon-Basics-Charging-Transfer-Gold-Plated/dp/B07232M876?th=1)
 | PMOD ALS (Ambient Light Sensor) | 1 | 12.99 per unit | [Product Link](https://digilent.com/shop/pmod-als-ambient-light-sensor/?srsltid=AfmBOoo0kxgvVAwQuc-BNFxNm-8LzqFudKycYnibmbCsAVFQNEUlxlfY)
 | PMOD BTN Module | 1 | 7.99 per unit | [Product Link](https://digilent.com/shop/pmod-btn-4-user-pushbuttons/)
 | HS-485HB Servo | 1 | 19.99 per unit | [Product Link](https://www.servocity.com/hs-485hb-servo/)

 # PMOD BTN Pinout
 | PMOD BTN Pin | TM4C123G Launchpad Pin | 
 | --- | --- |
 | BTN0 | PA2
 | BTN1 | PA3
 | BTN2 | PA4
 | Pin 5 (GND) | GND
 | Pin 6 (VCC) | VCC (3.3v)

 # PMOD ALS Pinout
 | PMOD ALS Pin | TM4C123G Launchpad Pin | 
 | --- | --- |
 | Pin 1 (CS) | PB5
 | Pin 2 (Not Connected) | Not Connected
 | Pin 3 (MISO) | PB6
 | Pin 4 (SCLK) | PB4
 | Pin 5 (GND) | GND
 | Pin 6 (VCC) | VCC (3.3v)

 # HS-485HB Servo Pinout
 | HS-485HB Servo | TM4C123G Launchpad Pin | 
 | --- | --- |
 | Servo PWM Input Signal (Yellow Wire) | PF2
 | Servo VCC (Red Wire) | 5V
 | Servo GND (Black Wire) | GND
 
 # 3D Design
![Image](https://github.com/user-attachments/assets/3b287ff7-df22-49b9-ad22-7f59f2f394b7)
![Image](https://github.com/user-attachments/assets/607cbd0c-fd04-499a-b422-ddad21d295f2)
![Image](https://github.com/user-attachments/assets/b4c5e71d-284b-4ea3-a8d8-961f65828251)
