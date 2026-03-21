#pragma once

#include <Arduino.h>

enum ServoName : uint8_t {
  R1 = 0,  // Front-right hip
  R2 = 1,  // Front-right knee
  L1 = 2,  // Front-left hip
  L2 = 3,  // Front-left knee
  R3 = 4,  // Back-right hip
  R4 = 5,  // Back-right knee
  L3 = 6,  // Back-left hip
  L4 = 7   // Back-left knee
};

const String ServoNames[] = {"R1","R2","L1","L2","R3","R4","L3","L4"};

inline int servoNameToIndex(const String& servo) {
  if (servo == "R1") return R1;
  if (servo == "R2") return R2;
  if (servo == "L1") return L1;
  if (servo == "L2") return L2;
  if (servo == "R3") return R3;
  if (servo == "R4") return R4;
  if (servo == "L3") return L3;
  if (servo == "L4") return L4;
  return -1;
}

extern int frameDelay;
extern void setServoAngle(uint8_t channel, int angle);
extern void robotDelay(unsigned long ms);

inline void setServoAngleBack(uint8_t channel, int angle) {
  setServoAngle(channel, 180 - angle);
}
#define SF(ch, ang) setServoAngle(ch, ang)
#define SB(ch, ang) setServoAngleBack(ch, ang)

#define WALK_STEPS 12

void runRestPose();
void runStandPose();
void runWavePose();
void runDancePose();
void runSwimPose();
void runPointPose();
void runPushupPose();
void runBowPose();
void runCutePose();
void runFreakyPose();
void runWormPose();
void runShakePose();
void runShrugPose();
void runDeadPose();
void runCrabPose();
void runWalkPose();
void runWalkBackward();
void runTurnLeft();
void runTurnRight();
void runFightPose();
void runPunchPose();
void runKickPose();
void runDizzyPose();
void runFallPose();
void runGlitchPose();


inline void runRestPose() {
  Serial.println(F("REST"));
  SF(R1, 90); SF(R2, 90);
  SF(L1, 90); SB(L2, 90);
  SB(R3, 90); SB(R4, 90);
  SB(L3, 90); SF(L4, 90);
}

inline void runStandPose() {
  SF(R1, 90); SF(R2, 0);
  SF(L1, 90); SB(L2, 0);
  SB(R3, 90); SB(R4, 0);
  SB(L3, 90); SF(L4, 0);
}

inline void runWavePose() {
  Serial.println(F("WAVE"));
  runStandPose();
  SF(L4,30);
  robotDelay(200);
  SF(R1, 150); SF(R2, 180);           
  robotDelay(300);
  for (int i = 0; i < 4; i++) {
    SF(R1, 150); robotDelay(300);      
    SF(R1, 100);  robotDelay(300);      
  }
  runStandPose();
}

inline void runDancePose() {
  Serial.println(F("DANCE"));
  runStandPose();
  robotDelay(200);
  for (int i = 0; i < 5; i++) {
    SF(R2, 60);  SF(L4, 60);
    SF(R1, 120); SB(L3, 60);
    robotDelay(300);
    SF(R2, 0);   SF(L4, 0);
    robotDelay(200);
    SB(L2, 60);  SB(R4, 60);
    SF(L1, 120); SB(R3, 60);
    robotDelay(300);
    SF(L2, 0);   SB(R4, 0);
    robotDelay(200);
  }
  runStandPose();
}

inline void runSwimPose() {
  Serial.println(F("SWIM"));
  runStandPose();
  robotDelay(200);
  for (int i = 0; i < 4; i++) {
    SF(R1, 150); SF(L1, 150); SF(R2, 60); SF(L2, 60);
    SB(R3, 30);  SB(L3, 30);  SB(R4, 60); SB(L4, 60);
    robotDelay(400);
    SF(R1, 30);  SF(L1, 30);  SF(R2, 0); SF(L2, 0);
    SB(R3, 150); SB(L3, 150); SB(R4, 0); SB(L4, 0);
    robotDelay(400);
  }
  runStandPose();
}

inline void runPointPose() {
  Serial.println(F("POINT"));
  runStandPose();
  robotDelay(200);
  SF(R1, 150); SF(R2, 0);             
  robotDelay(2000);
  runStandPose();
}

inline void runPushupPose() {
  Serial.println(F("PUSHUP"));
  runStandPose();
  robotDelay(200);
  SF(R1, 120); SF(L1, 60);            
  SF(R2, 0);   SB(L2, 0);              
  robotDelay(400);
  for (int i = 0; i < 4; i++) {
    SF(R2, 120); SB(L2, 120);          
    robotDelay(500);
    SF(R2, 0);   SB(L2, 0);            
    robotDelay(500);
  }
  runStandPose();
}

inline void runBowPose() {
  Serial.println(F("BOW"));
  runStandPose();
  robotDelay(200);
  SF(R1, 150); SF(L1, 30);             
  robotDelay(200);
  SF(R2, 180); SB(L2, 180);            
  robotDelay(3000);
  runStandPose();
}

inline void runCutePose() {
  Serial.println(F("CUTE"));
  runStandPose();
  robotDelay(200);
  SF(R2, 120); SB(L2, 120);
  SF(R1, 150); SF(L1, 30);
  robotDelay(300);
  for (int i = 0; i < 5; i++) {
    SB(R3, 120); SB(L3, 60); robotDelay(300);
    SB(R3, 60);  SB(L3, 120); robotDelay(300);
  }
  runStandPose();
}

inline void runFreakyPose() {
  Serial.println(F("FREAKY"));
  runStandPose();
  robotDelay(200);
  SF(R1, 150); SF(R2, 90);
  SF(L1, 30);  SB(L2, 0);
  SB(R3, 30);  SB(R4, 90);
  SB(L3, 150); SF(L4, 0);
  robotDelay(300);
  for (int i = 0; i < 3; i++) {
    SF(R2, 0);   SF(L4, 90);  robotDelay(300);
    SF(R2, 90);  SB(L4, 0);   robotDelay(300);
  }
  runStandPose();
}

inline void runWormPose() {
  Serial.println(F("WORM"));
  runStandPose();
  robotDelay(200);
  for (int i = 0; i < 5; i++) {
    SF(R2, 120); SB(L2, 120);
    SB(R4, 0);   SF(L4, 0);
    robotDelay(300);
    SF(R2, 0);   SB(L2, 0);
    SB(R4, 120); SF(L4, 120);
    robotDelay(300);
  }
  runStandPose();
}

inline void runShakePose() {
  Serial.println(F("SHAKE"));
  runStandPose();
  robotDelay(200);
  // shake whole body by rocking hips side to side
  for (int i = 0; i < 5; i++) {
    SF(R1, 120); SF(L1, 120);
    SB(R3, 60);  SB(L3, 60);
    robotDelay(200);
    SF(R1, 60);  SF(L1, 60);
    SB(R3, 120); SB(L3, 120);
    robotDelay(200);
  }
  runStandPose();
}

inline void runShrugPose() {
  Serial.println(F("SHRUG"));
  runStandPose();
  robotDelay(200);
  SF(R2, 90); SB(L2, 90);
  SB(R4, 90); SF(L4, 90);
  robotDelay(1000);
  SF(R2, 0);  SB(L2, 0);
  SB(R4, 0);  SF(L4, 0);
  robotDelay(500);
  runStandPose();
}

inline void runDeadPose() {
  Serial.println(F("DEAD"));
  runStandPose();
  robotDelay(200);
  SF(R1, 150); SF(L1, 30);
  SB(R3, 30);  SB(L3, 150);
  robotDelay(300);
  SF(R2, 180); SB(L2, 180);
  SB(R4, 180); SF(L4, 180);
}

inline void runCrabPose() {
  Serial.println(F("CRAB"));
  runStandPose();
  robotDelay(200);
  SF(R1, 150); SF(L1, 30);
  SB(R3, 30);  SB(L3, 150);
  SF(R2, 0);   SB(L2, 0);
  SB(R4, 0);   SF(L4, 0);
  robotDelay(300);
  for (int i = 0; i < 5; i++) {
    // step right
    SF(R2, 60);  SB(R4, 60);
    SF(R1, 120); SB(R3, 60);
    robotDelay(300);
    SF(R2, 0);   SB(R4, 0);
    robotDelay(200);
    // step left
    SB(L2, 60);  SF(L4, 60);
    SF(L1, 60);  SB(L3, 120);
    robotDelay(300);
    SB(L2, 0);   SF(L4, 0);
    robotDelay(200);
  }
  runStandPose();
}


inline void runWalkPose() {
  Serial.println(F("WALK FWD"));
  runStandPose();
  robotDelay(frameDelay);
 
  for (int i = 0; i < WALK_STEPS; i++) {

    SF(R2, 90);                       
    robotDelay(frameDelay);
    SF(R1, 150);                       
    SF(L1, 80); SB(R3, 80); SB(L3, 80);
    robotDelay(frameDelay);
    SF(R2, 0);                     
    robotDelay(frameDelay);
    SF(L4, 90);                         
    robotDelay(frameDelay);
    SB(L3, 150);                        
    SF(R1, 95); SF(L1, 85); SB(R3, 85); 
    robotDelay(frameDelay);
    SF(L4, 0);                       
    robotDelay(frameDelay); 
    SB(L2, 90);                    
    robotDelay(frameDelay);
    SB(L1, 150);                         
    SF(R1, 80); SB(R3, 80); SB(L3, 80); 
    robotDelay(frameDelay);
    SB(L2, 0);                           
    robotDelay(frameDelay);
    SB(R4, 90);                          
    robotDelay(frameDelay);
    SF(R3, 150);                     
    SF(R1, 95); SF(L1, 95); SB(L3, 85);
    robotDelay(frameDelay);
    SB(R4, 0);                         
    robotDelay(frameDelay);
  }
 
  runStandPose();
}



inline void runWalkBackward() {
  Serial.println(F("WALK BACK"));

 
  runStandPose();
  robotDelay(frameDelay);
 
  for (int i = 0; i < WALK_STEPS; i++) {

    SF(R2, 90);
    robotDelay(frameDelay);
    SF(R1, 30);                           
    SB(L1, 100); SF(R3, 100); SB(L3, 100); 
    robotDelay(frameDelay);
    SF(R2, 0);                            
    robotDelay(frameDelay);
    SF(L4, 90);                       
    robotDelay(frameDelay);
    SB(L3, 30);                           
    SF(R1, 85); SB(L1, 95); SF(R3, 95);  
    robotDelay(frameDelay);
    SF(L4, 0);                           
    robotDelay(frameDelay);
    SB(L2, 90);                          
    robotDelay(frameDelay);
    SB(L1, 30);                           
    SF(R1, 100); SF(R3, 100); SB(L3, 100); 
    robotDelay(frameDelay);
    SB(L2, 0);                        
    robotDelay(frameDelay);
    SB(R4, 90);                         
    robotDelay(frameDelay);
    SF(R3, 30);                          
    SF(R1, 85); SB(L1, 85); SF(L3, 95); 
    robotDelay(frameDelay);
    SB(R4, 0);                         
    robotDelay(frameDelay);
  }
 
  runStandPose();
}
 
// inline void runTurnLeft() {
//   Serial.println(F("TURN LEFT"));
//   runStandPose();
//   robotDelay(frameDelay);
 
//   for (int i = 0; i < WALK_STEPS; i++) {
//     SF(R2, 90);                          
//     robotDelay(frameDelay);
//     SF(R1, 150);                         
//     robotDelay(frameDelay);
//     SF(R2, 0);                            
//     robotDelay(frameDelay);
//     SB(R4, 90);                      
//     robotDelay(frameDelay);
//     SB(R3, 30);                       
//     robotDelay(frameDelay);
//     SB(R4, 0);                       
//     robotDelay(frameDelay);
//     SF(L2, 90);                          
//     robotDelay(frameDelay);
//     SF(L1, 30);                         
//     robotDelay(frameDelay);
//     SF(L2, 0);                          
//     robotDelay(frameDelay);
//     SB(L4, 90);                         
//     robotDelay(frameDelay);
//     SB(L3, 150);                         
//     robotDelay(frameDelay);
//     SB(L4, 0);                         
//     robotDelay(frameDelay);
//   }
 
//   runStandPose();
// }
 
// inline void runTurnRight() {
//   Serial.println(F("TURN RIGHT"));
//   runStandPose();
//   robotDelay(frameDelay);
 
//   for (int i = 0; i < WALK_STEPS; i++) {

//     SF(L2, 90);                           
//     robotDelay(frameDelay);
//     SF(L1, 150);                         
//     robotDelay(frameDelay);
//     SF(L2, 0);                          
//     robotDelay(frameDelay);
//     SB(L4, 90);                      
//     robotDelay(frameDelay);
//     SB(L3, 30);                        
//     robotDelay(frameDelay);
//     SB(L4, 0);                        
//     robotDelay(frameDelay);
//     SF(R2, 90);                          
//     robotDelay(frameDelay);
//     SF(R1, 30);                         
//     robotDelay(frameDelay);
//     SF(R2, 0);                           
//     robotDelay(frameDelay);
//     SB(R4, 90);                          
//     robotDelay(frameDelay);
//     SB(R3, 150);                          
//     robotDelay(frameDelay);
//     SB(R4, 0);                         
//     robotDelay(frameDelay);
//   }
 
//   runStandPose();
// }
 

inline void runFightPose() {
  Serial.println(F("FIGHT"));
  runStandPose();
  robotDelay(200);
  // Front legs raise up aggressively
  SF(R1, 160); SF(L1, 20);
  SF(R2, 20);  SF(L2, 160);
  // Back legs widen for stability
  SB(R3, 110); SB(L3, 70);
  SB(R4, 30);  SB(L4, 150);
  robotDelay(2000);
  runStandPose();
}

// Throws a quick right jab — front-right leg punches forward then retracts
inline void runPunchPose() {
  Serial.println(F("PUNCH"));
  runStandPose();
  robotDelay(200);
  // Wind up
  SF(R1, 160); SF(R2, 160);
  robotDelay(150);
  // Punch — snap forward fast
  SF(R1, 30);  SF(R2, 30);
  robotDelay(120);
  // Retract
  SF(R1, 160); SF(R2, 160);
  robotDelay(120);
  // Second punch
  SF(R1, 30);  SF(R2, 30);
  robotDelay(120);
  SF(R1, 160); SF(R2, 160);
  robotDelay(200);
  runStandPose();
}

// Snaps the back-right leg out like a karate kick then returns
inline void runKickPose() {
  Serial.println(F("KICK"));
  runStandPose();
  robotDelay(200);
  // Shift weight to left side
  SF(L1, 30);  SF(L2, 150);
  SB(L3, 30);  SB(L4, 150);
  robotDelay(300);
  // Chamber the kick
  SB(R3, 160); SB(R4, 160);
  robotDelay(200);
  // Extend kick
  SB(R3, 10);  SB(R4, 10);
  robotDelay(180);
  // Retract
  SB(R3, 160); SB(R4, 160);
  robotDelay(150);
  // Second kick
  SB(R3, 10);  SB(R4, 10);
  robotDelay(180);
  SB(R3, 160); SB(R4, 160);
  robotDelay(200);
  runStandPose();
}

// ======================================================================
// SILLY POSES
// ======================================================================

// Rocks side to side like dizzy, legs swaying left and right
inline void runDizzyPose() {
  Serial.println(F("DIZZY"));
  runStandPose();
  robotDelay(200);
  for (int i = 0; i < 5; i++) {
    // Lean left
    SF(R1, 160); SF(R2, 30);
    SF(L1, 70);  SF(L2, 110);
    SB(R3, 160); SB(L3, 70);
    robotDelay(250);
    // Lean right
    SF(R1, 110); SF(R2, 70);
    SF(L1, 20);  SF(L2, 150);
    SB(R3, 110); SB(L3, 20);
    robotDelay(250);
  }
  runStandPose();
}

// Tips dramatically to the right then slowly recovers upright
inline void runFallPose() {
  Serial.println(F("FALL"));
  runStandPose();
  robotDelay(300);
  // Start tipping
  SF(R1, 100); SF(R2, 80);
  SF(L1, 80);  SF(L2, 100);
  SB(R3, 100); SB(R4, 80);
  SB(L3, 80);  SB(L4, 100);
  robotDelay(200);
  // Full collapse to right
  SF(R1, 60);  SF(R2, 160);
  SF(L1, 60);  SF(L2, 160);
  SB(R3, 60);  SB(R4, 160);
  SB(L3, 60);  SB(L4, 160);
  robotDelay(600);
  // Slowly struggle back up
  SF(R1, 90);  SF(R2, 90);
  SF(L1, 90);  SF(L2, 90);
  SB(R3, 90);  SB(R4, 90);
  SB(L3, 90);  SB(L4, 90);
  robotDelay(400);
  runStandPose();
}

// Rapid random twitching like a malfunctioning robot
inline void runGlitchPose() {
  Serial.println(F("GLITCH"));
  for (int i = 0; i < 8; i++) {
    // Twitch 1
    SF(R1, 20);  SF(R2, 160);
    SF(L1, 160); SF(L2, 20);
    SB(R3, 20);  SB(R4, 160);
    SB(L3, 160); SB(L4, 20);
    robotDelay(60);
    // Twitch 2
    SF(R1, 160); SF(R2, 20);
    SF(L1, 20);  SF(L2, 160);
    SB(R3, 160); SB(R4, 20);
    SB(L3, 20);  SB(L4, 160);
    robotDelay(60);
    // Twitch 3 — all neutral
    for (int j = 0; j < 8; j++) setServoAngle(j, 90);
    robotDelay(50);
    // Twitch 4 — diagonal
    SF(R1, 30);  SF(R2, 30);
    SF(L1, 150); SF(L2, 150);
    SB(R3, 150); SB(R4, 150);
    SB(L3, 30);  SB(L4, 30);
    robotDelay(70);
  }
  runStandPose();
}