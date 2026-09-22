#include <Keypad.h>
#include <LiquidCrystal.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'o', 'u', ' ', ' '},
  {'a', 'e', 'i', ' '},
  {'1', '2', '3', ' '},
  {' ', ' ', ' ', ' '}
};

byte rowPins[ROWS] = {12, 11, 8, 7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6, 5, 4, 2}; //Columnas (pines del 2, 4 al 6)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(1, 0, A1, A2, 10, 9);

/////////////////////////////////////////////
//NOTAS MUSICALES
/////////////////////////////////////////////

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_E4  330
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_GS4 415
#define NOTE_AS4 466
#define NOTE_D4  294
#define NOTE_FS5 740
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_CS5 554

int tempo = 200;
int buzzer = 3;
int melody[] = {
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;



/////////////////////////////////////////////
//VARIABLES
/////////////////////////////////////////////

int g;
int palabra;

String problemas[] = {"h_l_", "c_d_c_", "v_sl_mbr_nd_"};
String soluciones[] = {"hilo", "caduco", "vislumbrando"};
String problema;
String solucion;
bool juego = false;
int vidas = 3;

/////////////////////////////////////////////
//LUZ ROJA
/////////////////////////////////////////////

int pinLedR = 13;

void prenderRojo(int rojo)
{
  analogWrite(pinLedR, rojo);
}

/////////////////////////////////////////////
//GANAR O PERDER(RITMO DE MUSICA)
/////////////////////////////////////////////

void game_over(){
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void win(){
  int tempo = 114;
int buzzer = 3;
int melody[] = {
  NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2,
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

/////////////////////////////////////////////
//INICIAR PROGRAMA
/////////////////////////////////////////////

void setup() {
  pinMode(pinLedR, OUTPUT); //establezco el led ROJO como salida
  lcd.begin(16, 2);
  lcd.print("BIENVENIDO!");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("al AHORCADO :)");
  delay(822);
  lcd.clear();
  lcd.print("4,5,6,7,8 son");
  delay(2500);
  lcd.setCursor(0,1);
  lcd.print("a,e,i,o,u");
  delay(2500);
  lcd.clear();
  lcd.print("Tenes 3 intentos");
  delay(1500);
  lcd.setCursor(0,1);
  lcd.print("sino, perdes :(");
  delay(1500);
  lcd.clear();
  lcd.print("   DIFICULTAD  ");
  delay(2500);
  lcd.clear();
  lcd.print("   1:Facil ");
  delay(1500);
  lcd.clear();
  lcd.print("   2:Medio ");
  delay(1500);
  lcd.clear();
  lcd.print("   3:Dificil ");
  delay(1500);
  lcd.clear();
  lcd.print("ELIJA DESAFIO");
  delay(1500);
  lcd.clear();

}

void loop() {

  //ELEGIMOS EL PROBLEMA
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '1':
        problema = problemas[0];
        solucion = soluciones[0];
        lcd.print("Su palabra es:");
        delay(2500);
        lcd.setCursor(0,1);
        lcd.print(problemas[0]);
        delay(3000);
        juego = true;
        break;

      case '2':
        problema = problemas[1];
        solucion = soluciones[1];
        lcd.print("Su palabra es:");
        delay(2500);
        lcd.setCursor(0,1);
        lcd.print(problemas[1]);
        delay(3000);
        juego = true;
        break;

      case '3':
        problema = problemas[2];
        solucion = soluciones[2];
        lcd.print("Su palabra es:");
        delay(2500);
        lcd.setCursor(0,1);
        lcd.print(problemas[2]);
        juego = true;
        delay(3000);
        break;
    }
  }

  //SELECCION DE VOCALES
  while (juego) {
    char key_uno = keypad.getKey();
    if (key_uno) {
      switch (key_uno) {
        case 'a':
          //corroborar si la "a" es solucion del problema
          if (solucion.indexOf(key_uno) != -1) {
            problema.setCharAt(solucion.indexOf(key_uno), key_uno);
            lcd.clear();
            lcd.print("    ACERTASTE");
            delay(1500);
            lcd.clear();
            lcd.print(problema);
            delay(1500);
          }
          else {
            lcd.print("    ERROR");
            //SE ACTIVA LED ROJO
            for (int i = 0 ; i < 3 ; i++) {
              prenderRojo(255);
              delay(500);
              prenderRojo(0);
              delay(250);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
            }
            delay(1500);
            vidas--;
          }
          break;

        case 'e':
           //corroborar si la "e" es solucion del problema
          if (solucion.indexOf(key_uno) != -1) {
            problema.setCharAt(solucion.indexOf(key_uno), key_uno);
            lcd.clear();
            lcd.print("    ACERTASTE");
            delay(500);
            lcd.clear();
            lcd.print(problema);
            delay(250);
            
          }
          else {
            lcd.print("    ERROR");
            //SE ACTIVA LED ROJO
            for (int i = 0 ; i < 3 ; i++) {
              prenderRojo(255);
              delay(500);
              prenderRojo(0);
              delay(250);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
            }
            delay(1500);
            vidas--;
          }
          break;

        case 'i':
           //corroborar si la "i" es solucion del problema
          if (solucion.indexOf(key_uno) != -1) {
            problema.setCharAt(solucion.indexOf(key_uno), key_uno);
            lcd.clear();
            lcd.print("    ACERTASTE");
            delay(1500);
            lcd.clear();
            lcd.print(problema);
            delay(1500);
          }
          else {
            lcd.print("    ERROR");
            //SE ACTIVA LED ROJO
            for (int i = 0 ; i < 3 ; i++) {
              prenderRojo(255);
              delay(500);
              prenderRojo(0);
              delay(250);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
            }
            delay(1500);
            vidas--;
          }
          break;

        case 'o':
           //corroborar si la "o" es solucion del problema
          if (solucion.indexOf(key_uno) != -1) {
            problema.setCharAt(solucion.indexOf(key_uno), key_uno);
            lcd.clear();
            lcd.print("    ACERTASTE");
            delay(1500);
            lcd.clear();
            lcd.print(problema);
            delay(1500);
          }
          else {
            lcd.print("    ERROR");
            //SE ACTIVA LED ROJO
            for (int i = 0 ; i < 3 ; i++) {
              prenderRojo(255);
              delay(500);
              prenderRojo(0);
              delay(250);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
            }
            delay(1500);
            vidas--;
          }
          break;
        case 'u':
           //corroborar si la "u" es solucion del problema
          if (solucion.indexOf(key_uno) != -1) {
            problema.setCharAt(solucion.indexOf(key_uno), key_uno);
            lcd.clear();
            lcd.print("    ACERTASTE");
            delay(1500);
            lcd.clear();
            lcd.print(problema);
            delay(1500);
          }
          else {
            lcd.print("    ERROR");
            //SE ACTIVA LED ROJO
            for (int i = 0 ; i < 3 ; i++) {
              prenderRojo(255);
              delay(500);
              prenderRojo(0);
              delay(250);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
              lcd.clear();
              lcd.print(problema);
              delay(1500);
            }
            delay(1500);
            vidas--;
          }
          break;
      }
    }

/////////////////////////////////////////////
//CONDICION DE VICTORIA ROYALE
/////////////////////////////////////////////

    if (problema == solucion) {
      lcd.clear();
      lcd.print("    GANASTE");
      juego = false;
      delay(1500);
      win();
    }

/////////////////////////////////////////////
//CONDICION DE DERROTA
/////////////////////////////////////////////

    if (vidas == 0) {
      lcd.clear();
      lcd.print("    GAME OVER");
      delay(1000);
      game_over();
      juego = false;
    }
  }
}
