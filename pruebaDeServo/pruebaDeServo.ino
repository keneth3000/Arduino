#include<Servo.h>

Servo servo;
int pos = 0;

void setup() {
  servo.attach(9);
}

void loop() {
  for(pos = 0; pos<=180; pos +=1){
    servo.write(pos);
    delay(30);
  }

  for(pos = 0; pos >= 180; pos -= 1){
    servo.write(pos);
    delay(30);
  }

}