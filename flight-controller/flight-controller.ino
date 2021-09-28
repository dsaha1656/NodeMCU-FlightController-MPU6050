#include <Servo.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

int potValue;
int escOut1 = D5;
int escOut2 = D6;
int escOut3 = D7;
int escOut4 = D8;

int lastSpeed = 30;
int escSpeed = 30;
int minSpeed = 0; 
int maxSpeed = 180; // 40 to 130
String inputESC = "";
int led_pin = D0;

int speedChangeDelay = 100;

void applySpeed(int sp){
  lastSpeed = sp;
  ESC1.write(sp);
  ESC2.write(sp);
  ESC3.write(sp);
  ESC4.write(sp);
  Serial.print("Applied Speed: ");
  Serial.println(sp);
}

void setup() {

  Serial.begin(9600);
  ESC1.attach(escOut1,1000,2000); 
  ESC2.attach(escOut2,1000,2000); 
  ESC3.attach(escOut3,1000,2000); 
  ESC4.attach(escOut4,1000,2000); 
  Serial.println("Attached");
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
}

void sppedU(int last, int now){
  int i=last;
  for( i=last; i<=now; i++ ){
    applySpeed(i);
    delay(speedChangeDelay);
  }
}
void sppedD(int last, int now){
  int i=last;
  for( i=last; i>=now; i-- ){
    applySpeed(i);
    delay(speedChangeDelay);
  }
}

void loop() {
  int i = 0;
  while(Serial.available()) {
    inputESC = Serial.readString();
    escSpeed = inputESC.toInt();
    if(escSpeed==30){
      Serial.println("Start Speed");
      escSpeed = (30);
      applySpeed(escSpeed);
    }
    else if(escSpeed==140){
      Serial.println("Max Speed");
      applySpeed(escSpeed);
    }else{
      Serial.print("Input Speed: ");
      Serial.print(inputESC);
      if( escSpeed > maxSpeed ){
        Serial.println("Maximum Speed Limit");
        escSpeed = maxSpeed;
      }
      if( escSpeed < minSpeed ){
        Serial.println("Minimum Speed Limit");
        escSpeed = minSpeed;
      }

      applySpeed(escSpeed);
//      if( escSpeed < lastSpeed ){
//        sppedD(lastSpeed, escSpeed);
//      }else if( escSpeed > lastSpeed ){
//        sppedU(lastSpeed, escSpeed);
//      }else{
//        applySpeed(escSpeed);
//      }
      
    }
  }
}
