#include <Arduino.h>
#include <Servo.h>
int latch=7, data=8,cl=4;
int pos = 90;
int step = 1;
Servo head;
Servo rArm;
Servo lArm;
int led = 0, ledStep = 1;
void setup() {
  head.attach(9);
  rArm.attach(10);
  lArm.attach(11);
  pinMode(latch, OUTPUT);
  pinMode(cl, OUTPUT);
  pinMode(data, OUTPUT);
}
void loop() {
    head.write(pos);
    rArm.write(pos); 
    lArm.write(pos);
    pos+=step;
    if(pos==180){
      mouth(100);
      step*=-1;
    }
    if(pos==90){
      mouth(100);
    }
    
    if(pos==0){
      mouth(100);
      step*=-1;
    }
    registerWrite(led, HIGH);
    delay(20);
    if (led!=0){
      registerWrite(led-1,LOW);
    }
    if (led!=8){
      registerWrite(led+1,LOW);
    }
    delay(20);
    led+=ledStep;
    if(led==8)ledStep*=-1;
    if(led==0)ledStep*=-1;
    delay(10);
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
