const int LED_Rojo = 13;
const int LED_Amarillo = 12;
int inByte = 0;
int i = 0;

void setup() {
  Serial.begin(9600); //Esto abre el puerto serie
  pinMode(LED_Amarillo, OUTPUT);
  pinMode(LED_Rojo, OUTPUT);
  digitalWrite(LED_Amarillo, LOW);
  digitalWrite(LED_Rojo, LOW);
}

void loop() {

  if (Serial.available() > 0) {

    inByte = Serial.read();
    Serial.println(inByte);
    if (inByte == '0') {
      digitalWrite(LED_Amarillo, LOW);
    } else if (inByte == '1') {
      digitalWrite(LED_Amarillo, HIGH);
    }
    else if (inByte == '2') {
      digitalWrite(LED_Rojo, LOW);
    }
    else if (inByte == '3') {
      digitalWrite(LED_Rojo, HIGH);
    } else if (inByte == '4') {
      for (i = 0; i <= 4; i++) {
        digitalWrite(LED_Rojo, LOW);
        delay(1000);
        digitalWrite(LED_Amarillo, HIGH);
        delay(100);
        digitalWrite(LED_Rojo, HIGH);
        delay(1000);
        digitalWrite(LED_Amarillo, LOW);
        delay(100);
      }
    } else if (inByte == '8') {
      digitalWrite(LED_Amarillo, HIGH);
    }
  }
}
