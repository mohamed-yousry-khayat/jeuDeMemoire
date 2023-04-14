#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
int Led[5] = {12, 11, 10, 9};
int Bt[5] = {6, 5, 4, 3};
int buzzerPin = 8;
boolean EtatBt[5] = {0, 0, 0, 0};
boolean Perdu;
int Gene [50];
int Jouer [50];
int NbdeJouer;
int Niveau;
int Etape;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  for (int i = 0; i <= 4; i++) {
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
    pinMode(Bt[i], INPUT_PULLUP);
  }
}

void loop() {
  int Nbrandom = random(8, 13);
  switch (Etape) {
    case 0:
      lcd.setCursor(0, 0); lcd.print("- Jeux de memoire  -");
      lcd.setCursor(0, 2); lcd.print("   Bt1 pour jouer   ");
      EtatBt[0] = digitalRead(Bt[0]);
      while (EtatBt[0] == HIGH) {
        EtatBt[0] = digitalRead(Bt[0]);
      }
      Etape++;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("Niveau: ");
      lcd.setCursor(8, 0); lcd.print(Niveau);
      lcd.setCursor(0, 2); lcd.print("  -- Memoriser --   ");
      delay(1500);
      TabCombGene[Niveau] = Nbrandom;
      for (int i = 0; i <= Niveau; i++) {
        digitalWrite(TabCombGene[i], HIGH);
        delay(200);
        digitalWrite(TabCombGene[i], LOW);
        delay(400);
      }
      delay(500);
      Etape++;
      break;
    case 2:
      Etape++;
      lcd.setCursor(0, 2); lcd.print("    -- Play --      ");
      break;
    case 3:
      for (int i = 0; i <= 4; i++) {
        EtatBt[i] = digitalRead(Bt[i]);
        if (EtatBt[i] == LOW) {
          TabCombJouer[NbdeCombJouer] = Led[i];
          digitalWrite(Led[i], HIGH);
          while (EtatBt[i] == LOW) {
            EtatBt[i] = digitalRead(Bt[i]);
          }
          delay(50);
          digitalWrite(Led[i], LOW);
          NbdeCombJouer++;
          if (NbdeCombJouer - 1 == Niveau) {
            NbdeCombJouer = 0;
            Etape++;
            break;
          }
        }
      }
      delay(10);
      break;

    case 4:
      lcd.setCursor(0, 2); lcd.print(" -- Verification -- ");
      delay(1000);
      for (int i = 0; i <= Niveau; i++) {
        if (TabCombGene[i] != TabCombJouer[i]) {
          Perdu = 1;
          break;
        }
      }
      if (Perdu == 1) {
        Etape = 5;
        digitalWrite(buzzerPin, HIGH)
        delay(500)
        digitalWrite(buzzerPin, LOW)
      }
      else {
        Etape = 6;
      }
      break;

    case 5:
      lcd.setCursor(0, 2); lcd.print("    !! Perdu !!     ");
      delay(1000);
      lcd.setCursor(0, 2); lcd.print("  Bt1 pour rejouer  ");
      EtatBt[0] = digitalRead(Bt[0]);
      while (EtatBt[0] == HIGH) {
        EtatBt[0] = digitalRead(Bt[0]);
      }
      while (EtatBt[0] == LOW) {
        Niveau = 0;
        Etape = 1;
        Perdu = 0;
        EtatBt[0] = digitalRead(Bt[0]);
      }
      break;

    case 6:
      lcd.setCursor(0, 2); lcd.print("    ** Gagner **    ");
      Niveau++;
      Etape = 1;
      delay(1000);
      break;
    default:
      break;
  }
}