#include <LiquidCrystal_I2C.h> /*incluir la libreria*/
#include <Keypad.h>            /*incluir la libreias*/
#include <Servo.h>

int estado = 0;
Servo servo11;                /*servo*/
const byte FILAS = 4;         /*Modelo del teclado, entre filas y columnas*/
const byte COLUMNAS = 4;
char keys[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {9, 8, 7, 6};
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char TECLA;
char CLAVE[5];
char CLAVE_MAESTRA[5] = "1111";
byte INDICE = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  servo11.attach(11, 660, 1400);
  limpiar();
}

void loop() {
  TECLA = teclado.getKey();
  if (TECLA) {
    CLAVE [INDICE] = TECLA;
    INDICE++;
    lcd.print(TECLA);
  }

  if (INDICE == 4) {
    if (!strcmp(CLAVE, CLAVE_MAESTRA)) {
      abierto();
    } else {
      error();
    }

    INDICE = 0;
  }
  if (estado == 1 && (analogRead(A3) == 0)) {
    nueva_clave();
  }
}

////////////////Funcion de Error////////////////////////
void error() {
  lcd.setCursor(0, 1);
  lcd.print("Error de clave    ");
  limpiar();
}

/////////////////Funcion abrir y cerrar/////////////////
void abierto() {
  if (estado == 0) {
    estado = 1;
    lcd.setCursor(0, 1);
    lcd.print("Abierto     ");
    servo11.write(30);            //giro de 30 grados
  } else {
    estado = 0;
    lcd.setCursor(0, 1);
    lcd.print("Cerrado           ");
    servo11.write(150);
  }

  limpiar();
}

void nueva_clave() {
  lcd.setCursor(0, 0);
  lcd.print("Nueva clave          ");
  lcd.setCursor(12, 0);
  while (INDICE <= 3) {
    TECLA = teclado.getKey();
    if (TECLA) {
      CLAVE_MAESTRA[INDICE] = TECLA;
      CLAVE [INDICE] = TECLA;
      INDICE++;
      lcd.print(TECLA);
    }
  }
  estado = 0;
  lcd.setCursor(0, 1);
  lcd.print("Clave cambiada");
  delay(2000);
  limpiar();
}


/////////////////Funcion de limpiar//////////////////////
void limpiar() {
  lcd.setCursor(0, 0);
  lcd.print("Clave:                 ");
  lcd.setCursor(9, 0);
}
