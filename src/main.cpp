#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>
#include "faces.h"
#include "movements.h"


#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_MOSI     23
#define OLED_CLK      18
#define OLED_DC       17
#define OLED_CS        5
#define OLED_RESET    16

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define SERVOMIN 150
#define SERVOMAX 600
#define HIPMIN    60
#define HIPMAX   140

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int8_t AngErr[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
int    frameDelay = 150;

int angleToPWM(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setServoAngle(uint8_t channel, int angle) {
  int adjusted = constrain(angle + AngErr[channel], 0, 180);
  if (channel % 2 == 0)
    pwm.setPWM(channel, 0, angleToPWM(map(adjusted, 0, 180, HIPMIN, HIPMAX)));
  else
    pwm.setPWM(channel, 0, angleToPWM(180 - adjusted));
}

const char* ssid        = "";
const char* password    = "";
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic  = "Pepper/control";

WiFiClient   espClient;
PubSubClient client(espClient);


struct FaceEntry {
  const char* name;
  void (*animate)();
};

const FaceEntry faces[] = {
  { "idle",           animIdle          },
  { "idle_blink",     animIdleBlink     },
  { "walk",           animWalk          },
  { "rest",           animRest          },
  { "dance",          animDance         },
  { "wave",           animWave          },
  { "happy",          animHappy         },
  { "talk_happy",     animTalkHappy     },
  { "sad",            animSad           },
  { "talk_sad",       animTalkSad       },
  { "angry",          animAngry         },
  { "talk_angry",     animTalkAngry     },
  { "surprised",      animSurprised     },
  { "talk_surprised", animTalkSurprised },
  { "sleepy",         animSleepy        },
  { "talk_sleepy",    animTalkSleepy    },
  { "love",           animLove          },
  { "talk_love",      animTalkLove      },
  { "excited",        animExcited       },
  { "talk_excited",   animTalkExcited   },
  { "confused",       animConfused      },
  { "talk_confused",  animTalkConfused  },
  { "thinking",       animThinking      },
  { "talk_thinking",  animTalkThinking  },
  { "dead",           animDead          },
  { "point",          animPoint         },
  { "shrug",          animShrug         },
};
const uint8_t FACE_COUNT = sizeof(faces) / sizeof(faces[0]);

struct MoveEntry {
  const char* name;
  void (*run)();
};

const MoveEntry moves[] = {
  { "stand",    runStandPose    },
  { "rest",     runRestPose     },
  { "forward",  runWalkPose     },
  { "backward", runWalkBackward },
  { "left",     runTurnLeft     },
  { "right",    runTurnRight    },
  { "wave",     runWavePose     },
  { "dance",    runDancePose    },
  { "swim",     runSwimPose     },
  { "point",    runPointPose    },
  { "pushup",   runPushupPose   },
  { "bow",      runBowPose      },
  { "cute",     runCutePose     },
  { "freaky",   runFreakyPose   },
  { "worm",     runWormPose     },
  { "shake",    runShakePose    },
  { "shrug",    runShrugPose    },
  { "dead",     runDeadPose     },
  { "crab",     runCrabPose     },
  { "fight",    runFightPose    },
  { "punch",    runPunchPose    },
  { "kick",     runKickPose     },
  { "dizzy",    runDizzyPose    },
  { "fall",     runFallPose     },
  { "glitch",   runGlitchPose   },
};
const uint8_t MOVE_COUNT = sizeof(moves) / sizeof(moves[0]);


int currentFaceIndex = 0;

void updateAnim() {
  if (currentFaceIndex >= 0 && currentFaceIndex < FACE_COUNT) {
    faces[currentFaceIndex].animate();
  }
}

void robotDelay(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    client.loop();
    updateAnim();
  }
}

int findFace(const String& name) {
  for (int i = 0; i < FACE_COUNT; i++) {
    if (name.equalsIgnoreCase(faces[i].name)) return i;
  }
  return -1;
}

void runMove(const String& name) {
  for (int i = 0; i < MOVE_COUNT; i++) {
    if (name.equalsIgnoreCase(moves[i].name)) {
      Serial.print("Move: "); Serial.println(moves[i].name);
      moves[i].run();
      return;
    }
  }
  Serial.print("Unknown move: "); Serial.println(name);
}


void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  msg.trim();

  Serial.print("MQTT: "); Serial.println(msg);

  int   comma    = msg.indexOf(',');
  String movePart = (comma == -1) ? msg         : msg.substring(0, comma);
  String facePart = (comma == -1) ? ""           : msg.substring(comma + 1);
  movePart.trim();
  facePart.trim();

  if (facePart.length() > 0) {
    int idx = findFace(facePart);
    if (idx >= 0) {
      currentFaceIndex = idx;
      Serial.print("Face: "); Serial.println(faces[idx].name);
    } else {
      Serial.print("Unknown face: "); Serial.println(facePart);
    }
  }

  if (movePart.length() > 0) {
    runMove(movePart);
  }
}


void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi: " + WiFi.localIP().toString());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting...");
    String clientId = "Pepper" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed rc="); Serial.print(client.state());
      Serial.println(" retry 2s");
      delay(2000);
    }
  }
}


void setup() {
  Serial.begin(115200);

  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(500);

  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("Display init failed");
    while (1);
  }
  display.clearDisplay();
  display.display();

  runRestPose();
  delay(500);
  runStandPose();
  updateAnim();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.println("Ready. Format: movement,face");
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  updateAnim();
}