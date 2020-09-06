#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

// SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

int en = 5; //en = motor speed
int in1 = 2; //in1 = 
int in2 = 3;
int in3 = 9;
int in4 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Motor initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //Serial Port
//  pinMode(rxPin, INPUT);
//  pinMode(txPin, OUTPUT);

  // mySerial.begin(9600);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // if(mySerial.available()) {
  //  char c = mySerial.read();
  // if(Serial.available()) {
  //  char c = Serial.read();
  //  Serial.println(c);
    int A = analogRead(0);
    int B = analogRead(1);
    int C = analogRead(2);

    char c = ' ';
    
    if(A > 50){
      if(B > 50){
        if(C > 50){
          c = 'F'; 
        }
        else{
          c = 'B';
        }
      }
      else{
        if(C > 50){
          c = 'R'; 
        }
        else{
          c = 'L';
        }
      }
    }
    else{
      c = 'x';
    }
    
   if (c =='F') {goForward(255);digitalWrite(LED_BUILTIN, HIGH);}
   if (c =='B') {goBackward(255);digitalWrite(LED_BUILTIN, LOW);}
   if (c =='L') {turnLeft(500);}
   if (c =='R') {turnRight(500);} 
}


void turnLeft(int dur) {
  analogWrite(en, 255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(dur);

  digitalWrite(in1,LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void turnRight(int dur) {
  analogWrite(en, 255);
  digitalWrite(in1,LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(dur);

  digitalWrite(in1,LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void goForward(int speed) {
  analogWrite(en, speed);
  digitalWrite(in1,HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(1000);

  digitalWrite(in1,LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void goBackward(int speed) {
  analogWrite(en, speed);
  digitalWrite(in1,LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);

  digitalWrite(in1,LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
