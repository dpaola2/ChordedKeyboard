/*

Chorded Keyboard (a la Doug Engelbart's 1968 demo)
Dave Paola, started Aug 1, 2013

Connect the five buttons to pins 2 - 6, as outlined here:
http://www.arduino.cc/en/Tutorial/Pushbutton

You MUST use this guide: http://mitchtech.net/arduino-usb-hid-keyboard/
(don't forget to put the board into DFU mode by bridging the GND and RESET pin headers)
and this library: https://github.com/SFE-Chris/UNO-HIDKeyboard-Library

*/

// meaningful constants
byte SC_A = 0x04;              byte SC_SPACE = 0x2c;            byte MOD_SHIFT = 0xf1;
byte SC_B = 0x05;              byte SC_ENTER = 0x28;            byte MOD_ALT = 0xf2;
byte SC_C = 0x06;              byte SC_BCKSPC = 0x2a;           byte MOD_CTRL = 0xf0;
byte SC_D = 0x07;              byte SC_TAB = 0x2b;
byte SC_E = 0x08;              byte SC_ESCAPE = 0x29;
byte SC_F = 0x09;              byte SC_ESC = 0x29;
byte SC_G = 0x0a;              byte SC_RIGHT_ARROW = 0xef;
byte SC_H = 0x0b;              byte SC_LEFT_ARROW = 0x50;
byte SC_I = 0x0c;              byte SC_DOWN_ARROW = 0x51;
byte SC_J = 0x0d;              byte SC_UP_ARROW = 0x52;
byte SC_K = 0x0e;              
byte SC_L = 0x0f;              
byte SC_M = 0x10;              
byte SC_N = 0x11;              
byte SC_O = 0x12;              
byte SC_P = 0x13;              
byte SC_Q = 0x14;              
byte SC_R = 0x15;              
byte SC_S = 0x16;              
byte SC_T = 0x17;              
byte SC_U = 0x18;              
byte SC_V = 0x19;              
byte SC_W = 0x1a;              
byte SC_X = 0x1b;              
byte SC_Y = 0x1c;              
byte SC_Z = 0x1d;        

uint8_t buf[8] = { 0 };	/* Keyboard report buffer */

#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20

char alphabet[] = {
  'invalid',
 'a',
 'b',
'c',
'd',
'e',
'f',
'g',
'h',
'i',
'j',
'k',
'l',
'm',
'n',
'o',
'p',
'q',
'r',
's',
't',
'u',
'v',
'w',
'x',
'y',
'z',
' '
};

// set pin numbers:
const int firstButtonPin = 2;
const int secondButtonPin = 3;
const int thirdButtonPin = 4;
const int fourthButtonPin = 5;
const int fifthButtonPin = 6;

const int ledPin =  13;      // the number of the LED pin

// variables will change:
int firstButtonState = 0;         // variable for reading the pushbutton status
int secondButtonState = 0;
int thirdButtonState = 0;
int fourthButtonState = 0;
int fifthButtonState = 0;

// states
int priorState = 0;
int curState = 0;

void setup() {
  delay(6000); // wait for keyboard driver to boot
  Serial.end();
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(firstButtonPin, INPUT);     
  pinMode(secondButtonPin, INPUT);
  pinMode(thirdButtonPin, INPUT);
  pinMode(fourthButtonPin, INPUT);
  pinMode(fifthButtonPin, INPUT);
  //Serial.println("done with setup");
}

void loop(){
  // figure out the new state
  priorState = curState;
  curState = readPins();
  
  if (curState != priorState) {
    // things have changed, update the states! 
    //printStatus();
    if (curState == 0) {
      // emit the priorState
      char message[] = {
        alphabet[priorState]
      };
      emit(message);
    } else {
      curState = priorState | curState;        
    }
  }
}

int readPins() {
  // read the state of the pushbutton value:
  firstButtonState = digitalRead(firstButtonPin) * 1;
  secondButtonState = digitalRead(secondButtonPin) * 2;
  thirdButtonState = digitalRead(thirdButtonPin) * 4;
  fourthButtonState = digitalRead(fourthButtonPin) * 8;
  fifthButtonState = digitalRead(fifthButtonPin) * 16;
  
  return firstButtonState + secondButtonState + thirdButtonState + fourthButtonState + fifthButtonState;
}

void printStatus() {
  Serial.print(priorState);
  Serial.print(" -> ");
  Serial.println(curState);
}

void emit(char * message) {
    char *chp = message;
    //delay(25);
    while (*chp) {
	    
	if ((*chp >= 'a') && (*chp <= 'z')) {
	    buf[2] = *chp - 'a' + 4;
	} else if ((*chp >= 'A') && (*chp <= 'Z')) {
	    buf[0] = KEY_LEFT_SHIFT;	/* Caps */
	    buf[2] = *chp - 'A' + 4;
	} else {
	    switch (*chp) {
	    case ' ':
	    	buf[2] = 0x2c;	// Space
		break;
	    case '+':
	       buf[2] = 128;	// Volume up
	       break;
	    case '-':
	       buf[2] = 129;	// Volume down
	       break;
	    default:
	        /* Character not handled. To do: add rest of chars from HUT1_11.pdf */
		buf[2] = 0;	// Period
		break;
	    }
	}

	Serial.write(buf, 8);	// Send keypress
	buf[0] = 0;
	buf[2] = 0;
	Serial.write(buf, 8);	// Release key
	chp++;  
    }
}

