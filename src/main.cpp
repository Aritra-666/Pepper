#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "movements.h"
#define SERVOMIN 150
#define SERVOMAX 600

//Limits of hip servos 

#define HIPMAX 135 
#define HIPMIN 60


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int8_t AngErr[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //ignoring for now

int frameDelay = 200;

int angleToPWM(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServoAngle(uint8_t channel, int angle){

  int adjusted = constrain(angle + AngErr[channel], 0, 180);

  if(channel%2 == 0) 
    pwm.setPWM(channel, 0, angleToPWM(map(adjusted,0,180,HIPMIN,HIPMAX)));
  else
    pwm.setPWM(channel, 0, angleToPWM(180-adjusted));
    

}

void robotDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    delay(5);
  }
}

void setup() {
  Serial.begin(115200);
    Wire.begin();
    pwm.begin();
    pwm.setPWMFreq(50);

}

void loop() {
  Serial.println("REST");
  runRestPose();
  delay(2000);
 
  Serial.println("STAND");
  runStandPose();
  delay(2000);
 
  Serial.println("WALK FWD");
  runWalkPose();
  delay(1000);
 
  Serial.println("WALK BACK");
  runWalkBackward();
  delay(1000);
 
  // Serial.println("TURN LEFT");
  // runTurnLeft();
  // delay(1000);
 
  // Serial.println("TURN RIGHT");
  // runTurnRight();
  // delay(1000);
 
  Serial.println("WAVE");
  runWavePose();
  delay(1000);
 
  Serial.println("DANCE");
  runDancePose();
  delay(1000);
 
  Serial.println("SWIM");
  runSwimPose();
  delay(1000);
 
  Serial.println("POINT");
  runPointPose();
  delay(1000);
 
  Serial.println("PUSHUP");
  runPushupPose();
  delay(1000);
 
  Serial.println("BOW");
  runBowPose();
  delay(1000);
 
  Serial.println("CUTE");
  runCutePose();
  delay(1000);
 
  Serial.println("FREAKY");
  runFreakyPose();
  delay(1000);
 
  Serial.println("WORM");
  runWormPose();
  delay(1000);
 
  Serial.println("SHAKE");
  runShakePose();
  delay(1000);
 
  Serial.println("SHRUG");
  runShrugPose();
  delay(1000);
 
  Serial.println("DEAD");
  runDeadPose();
  delay(1000);
 
  Serial.println("CRAB");
  runCrabPose();
  delay(1000);
 
  Serial.println("FIGHT");
  runFightPose();
  delay(1000);
 
  Serial.println("PUNCH");
  runPunchPose();
  delay(1000);
 
  Serial.println("KICK");
  runKickPose();
  delay(1000);
 
  Serial.println("DIZZY");
  runDizzyPose();
  delay(1000);
 
  Serial.println("FALL");
  runFallPose();
  delay(1000);
 
  Serial.println("GLITCH");
  runGlitchPose();
  delay(1000);
 
}
 
