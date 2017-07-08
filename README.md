# USB Joystick to PPM

This project enables a USB Joystick to control FrSky DHT Module, the project was designed around a PXN Pro 2113 USB Joystick from https://www.aliexpress.com/item/PXN-PRO-2113-Wired-4-Axles-Flying-Game-arcade-Joystick-Controller-Professional-Gaming-Gamepad-Flight-Stick/32747923688.html

Buttons 7-12 for flight mode

Additional buttons implementation incomplete.

## Configuration

``` USBJoystickPPM.ino
#define PPM_PIN 9
```

``` RCState.h
const int MAX_VALUE = 2000; //max ppm value
const int MIN_VALUE = 1000; //min ppm value
const int FAIL_SAFE_VALUE = 950; //failsafe is set when communication with USB Joystick is lost (disconnected)
```

## Credits
TM1637 driver - https://github.com/avishorp/TM1637
LCD Driver - https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/
FrSky Library - https://github.com/sgofferj/arduino-frsky - incomplete
ArduinoRCLib PPM Library - http://sourceforge.net/p/arduinorclib/






