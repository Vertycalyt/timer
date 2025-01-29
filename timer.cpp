#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int plusButton = 0;       // +
const int minusButton = 1;      // -
const int startButton = 6;      // START
const int resetButton = 7;      // RESET

const int buzzer = 13;

int countdownTime = 0;
int remainingTime = countdownTime;
bool isCountingDown = false;
unsigned long previousMillis = 0;

void setup() {

  lcd.begin(16, 2);
  lcd.print("Set Time:");
  lcd.setCursor(0, 1);
  lcd.print("00:00:00");

  pinMode(plusButton, INPUT_PULLUP);
  pinMode(minusButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
}

void loop() {

  if (!isCountingDown) {

    // PLUS (+)
    if (digitalRead(plusButton) == LOW) {
      countdownTime++;
      updateTimeDisplay();
      delay(200);
    }

    // MINUS (-)
    if (digitalRead(minusButton) == LOW) {
      if (countdownTime > 0) countdownTime--;
      updateTimeDisplay();
      delay(200);
    }

    // START
    if (digitalRead(startButton) == LOW) {
      isCountingDown = true;
      remainingTime = countdownTime;
      lcd.clear();
      lcd.print("Countdown:");
      lcd.setCursor(0, 1);
      displayTime(remainingTime);
      delay(200);
    }

  } else {

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;

      if (remainingTime > 0) {
        remainingTime--;
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        displayTime(remainingTime);
      } else {
        
        lcd.setCursor(0, 1);
        lcd.print("OVER      ");
        isCountingDown = false;

        // BUZZER
        for (int i = 0; i < 5; i++) { 
          tone(buzzer, 1000);
          delay(200);
          noTone(buzzer);
          delay(200);
        }
      }
    }
  }

// RESET
  if (digitalRead(resetButton) == LOW) {
    isCountingDown = false;
    countdownTime = 0;
    remainingTime = 0;
    lcd.clear();
    lcd.print("Set Time:");
    lcd.setCursor(0, 1);
    displayTime(remainingTime);
    delay(200);
  }
}

void updateTimeDisplay() {
  lcd.setCursor(0, 1);
  displayTime(countdownTime);
}


void displayTime(int totalSeconds) {
  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;

  lcd.print(hours < 10 ? "0" : "");
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes < 10 ? "0" : "");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds < 10 ? "0" : "");
  lcd.print(seconds);
}
