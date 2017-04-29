//this programm will put out a PPM signal

//////////////////////CONFIGURATION///////////////////////////////
#define chanel_number 8  //set the number of chanels
#define default_servo_value 1500  //set the default servo value
#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 200  //set the pulse length
#define onState 0  //set polarity of the pulses: 1 is positive, 0 is negative
//#define sigPin 10  //set PPM signal output pin on the arduino
uint8_t sigPin;
//////////////////////////////////////////////////////////////////


/*this array holds the servo values for the ppm signal
change theese values in your code (usually servo values move between 1000 and 2000)*/
volatile int ppm[chanel_number];



#define PPM_COMPARE           OCR1A
#define PPM_COMPARE_ENABLE    OCIE1A
#define PPM_INT_VECTOR        TIMER1_COMPA_vect
#define SERVO_TIMER_CNT       TCNT1


//#define PPM_COMPARE           OCR1B
//#define PPM_COMPARE_ENABLE    OCIE1B
//#define PPM_INT_VECTOR        TIMER1_COMPB_vect
//#define SERVO_TIMER_CNT       TCNT1



void setup_ppm(uint8_t pin) {
	sigPin = pin;
	//initiallize default ppm values
	for (int i = 0; i<chanel_number; i++) {
		ppm[i] = default_servo_value;
	}

	pinMode(sigPin, OUTPUT);
	digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)

	cli();
	TCCR1A = 0; // set entire TCCR1 register to 0
	TCCR1B = 0;

	PPM_COMPARE = 10;  // compare match register, change this
	TCCR1B |= (1 << WGM12);  // turn on CTC mode
	TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
	TIMSK1 |= (1 << PPM_COMPARE_ENABLE); // enable timer compare interrupt
	sei();
}

//void loop() {
//	//put main code here
//	//static int val = 1;
//
//	//ppm[0] = ppm[0] + val;
//	//if (ppm[0] >= 2000) { val = -1; }
//	//if (ppm[0] <= 1000) { val = 1; }
//	//delay(10);
//}

volatile bool pause_ppm = false;
volatile bool ppm_paused = false;

ISR(PPM_INT_VECTOR) {  //leave this alone
	static volatile boolean state = true;
	static volatile byte cur_chan_numb;
	static volatile unsigned int calc_rest;

	if (cur_chan_numb == 99) {
		if (pause_ppm) {
			ppm_paused = true;
			return;
		}
		else {
			ppm_paused = false;
			cur_chan_numb = 0;
		}
	}

	TCNT1 = 0;
	cli();
	if (state) {  //start pulse
		digitalWrite(sigPin, onState);
		PPM_COMPARE = PPM_PulseLen * 2;
		state = false;
	}
	else {  //end pulse and calculate when to start the next pulse
		

		digitalWrite(sigPin, !onState);
		state = true;

		if (cur_chan_numb >= chanel_number) {
			cur_chan_numb = 0;
			if (pause_ppm) {
				cur_chan_numb = 99;
			}
			calc_rest = calc_rest + PPM_PulseLen;// 
			PPM_COMPARE = (PPM_FrLen - calc_rest) * 2;
			calc_rest = 0;
		}
		else {
			PPM_COMPARE = (ppm[cur_chan_numb] - PPM_PulseLen) * 2;
			calc_rest = calc_rest + ppm[cur_chan_numb];
			cur_chan_numb++;
		}
	}
	sei();
}
