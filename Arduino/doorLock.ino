#include <Servo.h>

Servo myservo;
unsigned long distance = 0;
unsigned long beforeBtn = 0;
unsigned long nowBtn = 0;
unsigned long time_data = 0;
unsigned long second = 0;
unsigned long start = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT); // 超音波センサ
  pinMode(5, INPUT); // ボタン
  pinMode(11, OUTPUT); // open
  pinMode(12, OUTPUT); // close
  pinMode(13, OUTPUT); // bell
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  myservo.attach(4);
  myservo.write(0);
  beforeBtn = digitalRead(5);
  Serial.begin(9600);
}

void loop() {

  nowBtn = digitalRead(5);
  // 手の検知
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  distance = pulseIn(3,HIGH) / 58; // 手の距離

  if(distance > 20) {
      start = 0;
      digitalWrite(13, LOW);
  } else if(distance < 20 && start==0) {
      start = millis();
  }
  if((start != 0 && millis()-start > 1500) || nowBtn != beforeBtn) {
      Serial.println("bell");
      digitalWrite(13, HIGH);
      start = 0;
      beforeBtn = nowBtn;
  }

  // Pythonからの入力
  byte var;
  var = Serial.read();
  switch(var) {
    case '0': // open
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      myservo.write(0);
      Serial.println("open");
      break;
    case '1': // close
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      myservo.write(180);
      Serial.println("close");
      break;
    default:
      break;
  }

  
}
