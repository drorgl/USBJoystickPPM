#include "hidjoystickrptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt, RCState *rcs) :
	joyEvents(evt),
	oldHat(0xDE),
	oldButtons(0) {
	for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
		oldPad[i] = 0xD;
	
	joyEvents->rcState = rcs;
}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
		if (buf[i] != oldPad[i]) {
			match = false;
			break;
		}

	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
	}

	uint8_t hat = (buf[5] & 0xF);

	// Calling Hat Switch event handler
	if (hat != oldHat && joyEvents) {
		joyEvents->OnHatSwitch(hat);
		oldHat = hat;
	}

	uint16_t buttons = (0x0000 | buf[6]);
	buttons <<= 4;
	buttons |= (buf[5] >> 4);
	uint16_t changes = (buttons ^ oldButtons);

	// Calling Button Event Handler for every button changed
	if (changes) {
		for (uint8_t i = 0; i < 0x0C; i++) {
			uint16_t mask = (0x0001 << i);

			if (((mask & changes) > 0) && joyEvents) {
				if ((buttons & mask) > 0)
					joyEvents->OnButtonDn(i + 1);
				else
					joyEvents->OnButtonUp(i + 1);
			}
		}
		oldButtons = buttons;
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
	//Serial.print("X1: ");
	//PrintHex<uint8_t >(evt->X, 0x80);
	rcState->roll = map(evt->X, 0, 255, rcState->MIN_VALUE, rcState->MAX_VALUE);
	
	//Serial.print("\tY1: ");
	//PrintHex<uint8_t >(evt->Y, 0x80);
	rcState->pitch = map(evt->Y, 0, 255, rcState->MIN_VALUE, rcState->MAX_VALUE);

	//Serial.print("\tX2: ");
	//PrintHex<uint8_t >(evt->Z1, 0x80);
	

	//Serial.print("\tY2: ");
	//PrintHex<uint8_t >(evt->Z2, 0x80);
	rcState->throttle = map(evt->Z2, 0, 255, rcState->MAX_VALUE,rcState->MIN_VALUE);

	//Serial.print("\tRz: ");
	//PrintHex<uint8_t >(evt->Rz, 0x80);
	rcState->yaw = map(evt->Rz, 0, 255, rcState->MIN_VALUE, rcState->MAX_VALUE);
	//Serial.println("");

	rcState->data_updated();
}

void JoystickEvents::OnHatSwitch(uint8_t hat) {
	//rcState->hat_position = (HAT_POSITION) hat;
	rcState->hat_changed((HAT_POSITION) hat);
	//Serial.print("Hat Switch: ");
	//
	//PrintBin<uint8_t>(hat, 0);
	//
	//Serial.print(" ");
	//Serial.print(hat);
	//
	//Serial.print(" ");
	//PrintHex<uint8_t >(hat, 0x80);
	//
	//Serial.println("");
}

void JoystickEvents::OnButtonUp(uint8_t but_id) {
	rcState->button_state[but_id] = false;
	rcState->button_state_change_time[but_id] = abs(abs(millis()) - abs(rcState->button_state_changed[but_id]));
	rcState->button_state_changed[but_id] = millis();
	rcState->button_changed(but_id);

	//Serial.print("Up: ");
	//Serial.println(but_id, DEC);
}

void JoystickEvents::OnButtonDn(uint8_t but_id) {
	rcState->button_state[but_id] = true;
	rcState->button_state_change_time[but_id] = abs(abs(millis()) - abs(rcState->button_state_changed[but_id]));
	rcState->button_state_changed[but_id] = millis();
	rcState->button_changed(but_id);

	//Serial.print("Dn: ");
	//Serial.println(but_id, DEC);
}