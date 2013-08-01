/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int firstButtonPin = 2;     // the number of the pushbutton pin
const int secondButtonPin = 3;
const int thirdButtonPin = 4;
const int fourthButtonPin = 5;
const int fifthButtonPin = 6;

const int ledPin =  13;      // the number of the LED pin
const int alphabet[] = {'invalid', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

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
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(firstButtonPin, INPUT);     
  pinMode(secondButtonPin, INPUT);
  pinMode(thirdButtonPin, INPUT);
  pinMode(fourthButtonPin, INPUT);
  pinMode(fifthButtonPin, INPUT);
  Serial.println("done with setup");
}

void loop(){
  // figure out the new state
  priorState = curState;
  curState = readPins();
  
  if (curState != priorState) {
    // things have changed, update the states! 
    printStatus();
    if (curState == 0) {
      // emit the priorState
      emit();
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

void emit() {
 Serial.print("Emitting value: ");
 
 Serial.println((char)alphabet[priorState]); 
}

