int tigger = 10;
int echo = 9;
float tiempoEspera, distancia;

void setup() {
  Serial.begin(9600);
  pinMode(tigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(2, 0);
}

void loop() {
  digitalWrite(tigger, LOW);
  delayMicroseconds(2);
  digitalWrite(tigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(tigger, LOW);

  tiempoEspera = pulseIn(echo,HIGH);  // pulseIn recoje la señal del sonido
  distancia = (tiempoEspera/2)/29.15; // Formula para encontrar la distancia

  Serial.print(distancia);
  Serial.println("cm");
  delay(1000);
  if(distancia>=30 && distancia <= 400){
    analogWrite(2, 0);
  }

  if(distancia >= 26 && distancia <=300){
    analogWrite(2, 255);
  }

}
