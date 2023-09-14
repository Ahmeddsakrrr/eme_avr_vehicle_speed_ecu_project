# EME - Egypt Makes Electronics

## Team GUCALEX - CLASS 3 - SEITECH

### Team Members

- Hossam Elwahsh - [![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=flat&logo=github&logoColor=white)](https://github.com/HossamElwahsh) [![LinkedIn](https://img.shields.io/badge/linkedin-%230077B5.svg?style=flat&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/hossam-elwahsh/)
- Mahmoud Abdrabo - [![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=flat&logo=github&logoColor=white)](https://github.com/Mahmoud-Abdrabo)
- Ahmed Sakr - [![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=flat&logo=github&logoColor=white)](https://github.com/Ahmeddsakrrr)
- MennaTullah Ahmed - [![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=flat&logo=github&logoColor=white)](https://github.com/Menna-Ahmed)

### AVR-Based Project

### Vehicle speed control ECU

#### Project Description

> Project controls Vehicle ECU to control gears, set and remember speed limit, along with extra features

### Hardware

- 1x ATmega32 Kit (Vehicle Control ECU)
  - LCD to show car dashboard/settings
  - Keypad for user input
        
    > Keypad Layout
    > * 1 | 2 | 3 | P
    > * 4 | 5 | 6 | R 
    > * 7 | 8 | 9 | N 
    > * X | 0 | K | D
    >
    > X : Exit
     
  - LDR to detect Day/Night for automatic car front lights
  - Potentiometer to simulate KL15 Car Switch (OFF - ACC - ON)
  - Potentiometer to simulate car accelerator pedal
  - 1x LED (Red) car interior light
  - 2x LED car front lights
  - SPI communication


- 1x Atmega32 Kit (Data retention ECU)
  - EEPROM retaining last used speed limit value
  - SPI communication
   
### Features
- KL15 Car switch
  - `OFF position:` car is turned off
  - `ACC position:` minor lights are on (interior), ***battery watchdog*** enabled, engine OFF
  - `ON position:` Engine is running, car dashboard is up, systems and front lights (if at night) are ON
- Battery Watchdog Feature
  - If car is left for `10 seconds` on (ACC) key position it will automatically shut off lights and go to sleep mode
- User defined Speed limit option to limit max car speed (default 220)
- Car max speed on reverse: `30 km/hr`
- Car max speed on drive: `220 km/hr`
- Automatic car gear system - auto switches D1 to D7
- Configurable app settings like min-max speeds / transmission gears count / delays etc. can be updated from `app_config.h` file

### Future Improvements
- Adding Persistent Odometer
 
### Video Uploading...