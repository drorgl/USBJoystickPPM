#include "FrSkyAccessor.h"
#include "LEDDisplay.h"
#include "LCDDisplay.h"
#include "PPMGenerator.h"
#include "hidjoystickrptparser.h"
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include "hidjoystickrptparser.h"

RCState rcs;

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents, &rcs);

#define PPM_PIN 9

PPMGenerator ppm_gen;

FrSkyAccessor frsky_accessor;
//LEDDisplay led_display;
LCDDisplay lcd_display;

void setup()
{
	frsky_accessor.setup();
	//led_display.setup();
	lcd_display.setup();

	Serial.begin(115200);
#if !defined(__MIPSEL__)
	while (!Serial)
		; // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
	Serial.println("Start");

	auto usb_init = Usb.Init();
	Serial.print("Init");
	Serial.println(usb_init);
	if (usb_init == -1)
	{
		Serial.println("OSC did not start.");
		//led_display.display_oerr();
		lcd_display.display_oerr();
		delay(2000);
	}

	delay(200);
	if (!Hid.SetReportParser(0, &Joy))
	{
		ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);
		//led_display.display_herr();
		lcd_display.display_herr();
		delay(2000);
	}

	rcs.init();
	ppm_gen.init(PPM_PIN);
}

bool is_connected = true;

int update_now = 0;

void loop()
{
	update_now++;

	ppm_gen.pause();
	Usb.Task();
	frsky_accessor.loop();

	if (Usb.getUsbTaskState() == USB_STATE_RUNNING)
	{
		if (is_connected == true)
		{
			//already connected, do nothing
		}
		else
		{
			is_connected = true;
			rcs.is_connected = true;
			Serial.println("joystick connected");
			lcd_display.display_joystick_connected();
			delay(200);
			lcd_display.clear();
		}
	}
	else
	{

		if (is_connected == false)
		{
			//already disconnected, do nothing
		}
		else
		{
			is_connected = false;
			rcs.is_connected = false;
			Serial.println("joystick disconnected");
			lcd_display.display_joystick_disconnected();
			delay(200);
		}
	}

	if (update_now > 15)
	{
		if (is_connected)
		{
			lcd_display.display(rcs.flight_mode_code, rcs.channel5, (byte)rcs.camera_mode, rcs.auto_center);
			lcd_display.print_all(&rcs);
			lcd_display.display_rx_rssi(frsky_accessor.link_down);
			lcd_display.display_tx_rssi(frsky_accessor.link_up);
		}
		update_now = 0;
	}

	ppm_gen.resume();

	rcs.data_updated();
	ppm_gen.set_value(0, rcs.roll);
	ppm_gen.set_value(1, rcs.pitch);
	ppm_gen.set_value(2, rcs.throttle);
	ppm_gen.set_value(3, rcs.yaw);
	ppm_gen.set_value(4, (rcs.channel5) ? rcs.MAX_VALUE : rcs.MIN_VALUE);
	ppm_gen.set_value(5, rcs.flight_mode);
	ppm_gen.set_value(6, rcs.camera_pitch);
	ppm_gen.set_value(7, rcs.camera_yaw);
	delay(10);

	if (is_connected)
	{
		//led_display.display(rcs.flight_mode_code, rcs.channel5, (byte)rcs.camera_mode, rcs.auto_center);
	}
}
