// sample code from a youtuber and changed the code to make the robot dance and display the movements by Dhanesh
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2, 3);// 2:RX 3:TX, you can choose your favourite pins.


uint8_t records[8]; // save record
uint8_t buf[64];

/* define L298N motor drive control pins */
int RightMotorForward = 4;    // IN1
int RightMotorBackward = 5;   // IN2
int LeftMotorForward = 6;     // IN3
int LeftMotorBackward = 7;    // IN4

#define left    (0)
#define right   (1)
#define forword    (2)
#define backword   (3)
#define stopp   (4)
#define dance   (5)
#define roll  (6)
#define showoff (7)
void printSignature(uint8_t *buf, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {
      Serial.write(buf[i]);
    }
    else {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}


void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if (buf[0] == 0xFF) {
    Serial.print("NONE");
  }
  else if (buf[0] & 0x80) {
    Serial.print("UG ");
    Serial.print(buf[0] & (~0x80), DEC);
  }
  else {
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if (buf[3] > 0) {
    printSignature(buf + 4, buf[3]);
  }
  else {
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);

  Serial.begin(115200);
  Serial.println("Voice Control car");

  /* initialize motor control pins as output */
  pinMode(LeftMotorForward,OUTPUT);
  pinMode(RightMotorForward,OUTPUT);
  pinMode(LeftMotorBackward,OUTPUT);
  pinMode(RightMotorBackward,OUTPUT);
 

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else {
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while (1);
  }

  if (myVR.load((uint8_t)left) >= 0) {
    Serial.println("left loaded");
  }

  if (myVR.load((uint8_t)right) >= 0) {
    Serial.println("right loaded");
  }
  if (myVR.load((uint8_t)forword) >= 0) {
    Serial.println("forword loaded");
  }

  if (myVR.load((uint8_t)backword) >= 0) {
    Serial.println("backword loaded");
  }

   if (myVR.load((uint8_t)stopp) >= 0) {
    Serial.println("backword loaded");
     }
  
   if (myVR.load((uint8_t)dance) >= 0) {
    Serial.println("dance loaded");
  }
   if (myVR.load((uint8_t)roll) >= 0) {
    Serial.println("roll loaded");
  }
   if (myVR.load((uint8_t)roll) >= 0) {
    Serial.println("showoff loaded");
  }

}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    switch (buf[1]) {
      case left:
        TurnLeft();
        delay(500);
        MotorStop();
        break;
        
      case right:
        TurnRight();
         delay(500);
        MotorStop();
        break;

      case forword:
        MotorForward();
         delay(500);
        MotorStop();
        break;
        
      case backword:
        MotorBackward();
         delay(500);
        MotorStop();
        break;
             
      case dance:
       Dance();
         delay(200);
        MotorStop();
        break;

       case roll:
       Roll();
         delay(2500);
        MotorStop();
        break;
      
         case showoff:
       off();
         delay(5000);
        MotorStop();
        break;
        

      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
}

///* define L298N motor drive control pins */
//int RightMotorForward = 4;    // IN1
//int RightMotorBackward = 5;   // IN2
//int LeftMotorForward = 6;     // IN3
//int LeftMotorBackward = 7;    // IN4

/* FORWARD */
void MotorForward() {

  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);


 
}

/* BACKWARD */
void MotorBackward() {

    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);

//  digitalWrite(LeftMotorBackward, HIGH);
//  digitalWrite(RightMotorBackward, HIGH);
//  digitalWrite(LeftMotorForward, LOW);
//  digitalWrite(RightMotorForward, LOW);
}

/* TURN RIGHT */
void TurnRight() {

    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
//
// digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(RightMotorForward, HIGH);
//  digitalWrite(LeftMotorBackward, LOW);
//  digitalWrite(RightMotorBackward, LOW);

}

/* TURN LEFT */
void TurnLeft() {

  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);

//  digitalWrite(RightMotorForward, HIGH);
//  digitalWrite(LeftMotorForward, LOW);
//  digitalWrite(LeftMotorBackward, HIGH);
//  digitalWrite(RightMotorBackward, LOW);



}

/* STOP */
void MotorStop() {

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
 
}
void Dance() {
     digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
 delay(200);
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  delay(500);
     digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
 delay(200);
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);
    digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(1000);
      digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
 delay(200);
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);

}
void Roll()
{
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  delay(2500);
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
}
void off ()
{
  //left
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(400);
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);
   //backward
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(200); 
   //right
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400); 
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);
   //backward
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(200); 
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //right
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200); 
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //right
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200); 
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //right
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);
    //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //right
    digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(200);  
   //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //left
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(400);
      //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //left
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(400);
      //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //left
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(400);
      //forward
   digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
   digitalWrite(LeftMotorBackward, LOW);
   delay(400);
   //left
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(400);















}