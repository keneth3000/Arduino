#include <Servo.h>

Servo servo;
int pulsador_d = 1;
int pulsador_i = 1;

void setup() {
  servo.attach(5,600,1500);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  pulsador_d = digitalRead(2);
  pulsador_i = digitalRead(3);

  if(pulsador_d == LOW){
    servo.write(180);
    delay(15);
  }
  if(pulsador_i == LOW){
    servo.write(0);
    delay(15);
  }
  if(pulsador_i == HIGH && pulsador_d == HIGH){
    servo.write(90);
    delay(15);
  }
}
