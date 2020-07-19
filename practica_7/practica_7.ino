#include <Keypad.h>
const byte filas = 4; //pines de filas
const byte columnas = 4; //pines columnas

char keys [filas][columnas] = { //arreglo para modelo de teclas de teclado
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesfilas[filas] = { 9, 8, 7, 6 };  //conexion de pines de arduino
byte pinescolumnas[columnas] = { 5, 4, 3, 2 };  //conexion de pines de arduino
char CLAVE[5];
byte INDICE = 0;
char clave_master[5] = "1234";

Keypad teclado = Keypad(makeKeymap (keys), pinesfilas, pinescolumnas, filas, columnas);
char tecla; //guarda tecla presionada

//sensorPir
const int ledpin = 12;
const int PIRpin = 13;
const int ledNA = 11;
const int ledAm = 10;
const int ledAzul = A5;
int pirState = LOW;
int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(ledNA, OUTPUT);
  pinMode(ledAm, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(PIRpin, INPUT);
  digitalWrite(ledAzul, LOW);
}

void loop() {
  tecla = teclado.getKey(); //obtenemos tecla
  if (tecla) {
    CLAVE[INDICE] = tecla;
    INDICE++;
    Serial.print(tecla);
  }

  if (INDICE == 4) {
    if (!strcmp(CLAVE, clave_master)) { //comparamos clave
      sensor();
      Serial.println("Acceso correcto");
      delay(1000);
    } else {
      Serial.println("Incorrecto");
      digitalWrite(ledAzul, HIGH);
      delay(1000);
      digitalWrite(ledAzul, LOW);
      delay(1000);
    }
  }
}


//funciones
void sensor() {
  int sg = analogRead(A1);
  Serial.println(sg);
  delay(750);
  if (sg > 60) {
    Serial.println(sg);
    delay(1000);
    Serial.println("Alerta");

    val = digitalRead(PIRpin);
    if (val == HIGH)   //si está activado
    {
      digitalWrite(ledNA, HIGH);  //LED ON
      digitalWrite(ledpin, LOW);
      if (pirState == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState = HIGH;
      }
    } else{ //si esta desactivado
      digitalWrite(ledNA, LOW); // LED OFF
      digitalWrite(ledpin,HIGH);
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState = LOW;
      }
    }
  }else{
    val = digitalRead(PIRpin);
    if (val == HIGH)   //si está activado
    {
      digitalWrite(ledpin, LOW);
      digitalWrite(ledAm, HIGH);  //LED ON
      delay(1000);
      digitalWrite(ledAm, LOW);
      delay(1000);
      if (pirState == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState = HIGH;
      }
    }
  }
}
