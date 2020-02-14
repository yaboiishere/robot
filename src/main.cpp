#include <Arduino.h>
#include <Servo.h>
int latch=6, data=7,cl=5;
Servo head;  // create servo object to control a servo
Servo rArm;
Servo lArm;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
void setup() {
  head.attach(9);  // attaches the servo on pin 9 to the servo object
  rArm.attach(10);
  lArm.attach(11);
  pinMode(latch, OUTPUT);
  pinMode(cl, OUTPUT);
  pinMode(data, OUTPUT);
}

void loop() {
  for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    head.write(pos);              // tell servo to go to position in variable 'pos'
    rArm.write(pos); 
    lArm.write(pos); 
    delay(10);       // waits 15ms for the servo to reach the position
    if(pos%90==0||!pos)mouth(20);
  }
  mouth(100);
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    head.write(pos);              // tell servo to go to position in variable 'pos'
    rArm.write(pos); 
    lArm.write(pos);            // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
    if(pos%90==0||!pos)mouth(20);
  }
  mouth(100);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    head.write(pos);              // tell servo to go to position in variable 'pos'
    rArm.write(pos); 
    lArm.write(pos);            // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
    if(pos%90==0||!pos)mouth(20);
  }
  mouth(100);
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    head.write(pos);              // tell servo to go to position in variable 'pos'
    rArm.write(pos); 
    lArm.write(pos); 
    delay(10);       // waits 15ms for the servo to reach the position
    if(pos%90==0||!pos)mouth(20);
  }
  mouth(100);
}
void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latch, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);

  // shift the bits out:
  shiftOut(data, cl, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latch, HIGH);

}
void mouth(int timeout){
  int br=0;
  while (br<8){
    /* code */
    registerWrite(br, HIGH);
    delay(timeout);
    if (br!=0){
      /* code */
      registerWrite(br-1,LOW);
    }
    delay(timeout);
    br++;    
  }
  while (br>=0){
    /* code */
    registerWrite(br, HIGH);
    delay(timeout);
    if (br!=8){
      /* code */
      registerWrite(br+1,LOW);
    }
    delay(timeout);
    br--;    
  }
}
//unbreaking vscode git hopefully
