#include <Arduino.h>
#include <Servo.h>
int latch=7, data=8,cl=4;
int pos = 90, step = 1;
int led = 0, ledStep = 1;
int rLed=3, gLed=5, bLed=6;
int Colors[6][3] ={
  {153,0,204},
  {102,0,102},
  {255, 255, 0},
  {51,153,0},
  {0, 255, 255},
  {204,102,0}
};
Servo head;
Servo rArm;
Servo lArm;
void setup() {
  head.attach(9);
  rArm.attach(10);
  lArm.attach(11);
  pinMode(latch, OUTPUT);
  pinMode(cl, OUTPUT);
  pinMode(data, OUTPUT);
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
void _RGB_color(int rVal, int gVal, int bVal){
  analogWrite(rLed, rVal);
  analogWrite(gLed, gVal);
  analogWrite(bLed, bVal);
}
void RGB_color(int red, int green, int blue) {
  int r=0,g=0,b=0;
  while ( r != red || g != green || b != blue ) {
    if ( r < red ) r += 1;
    if ( r > red ) r -= 1;

    if ( g < green ) g += 1;
    if ( g > green ) g -= 1;

    if ( b < blue ) b += 1;
    if ( b > blue ) b -= 1;

    _RGB_color(r,g,b);
    delay(10);
  }
}
//unbreaking vscode git hopefully
void loop() {
  //servo code start
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
  //servo code end
  //matrix bitshifter code start
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
  //matrix bitshifter code end
  //rgb eyes code start
  int ran = rand()%6;
  _RGB_color(Colors[ran][0],Colors[ran][1],Colors[ran][2]);
  //rgb eyes code end
  delay(10);
}
