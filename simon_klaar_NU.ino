#define FALSE 0
#define TRUE 1

// Safe to Arduino pin mapping
#define LED_BLAUW 2
#define LED_GROEN 9
#define LED_ROOD 4
#define LED_GEEL 7

#define PIN_BTN_LOW 8
#define KNOP_BLAUW 3
#define KNOP_GROEN 11
#define KNOP_ROOD 5
#define KNOP_GEEL 13

#define BUZZER A0

typedef struct {
  int knop;
  int LED;
  int buzzerHoogte;
} ButtonLed;

const ButtonLed BUTTON_LEDS[4] = {
  {KNOP_BLAUW, LED_BLAUW, 1000},
  {KNOP_GROEN, LED_GROEN, 800},
  {KNOP_ROOD, LED_ROOD, 600},
  {KNOP_GEEL, LED_GEEL, 400},
};
int max_level[200];
int level = 0;
int n;

void setup() {
  pinMode(LED_BLAUW, OUTPUT);
  pinMode(LED_GROEN, OUTPUT);
  pinMode(LED_ROOD, OUTPUT);
  pinMode(LED_GEEL, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(KNOP_BLAUW, INPUT_PULLUP);
  pinMode(KNOP_GROEN, INPUT_PULLUP);
  pinMode(KNOP_ROOD, INPUT_PULLUP);
  pinMode(KNOP_GEEL, INPUT_PULLUP);

  pinMode(PIN_BTN_LOW, OUTPUT);
  digitalWrite(PIN_BTN_LOW, LOW);

  // Initialize random number generator
  randomSeed(analogRead(0));
}


void soundBuzzer(unsigned int frequentie, unsigned int duur, int wait) {
  tone(BUZZER, frequentie, duur);

    delay(100);
 
}

void showLed(unsigned int pin, unsigned int duur) {
  digitalWrite(pin,  HIGH);
  delay(duur);
  digitalWrite(pin, LOW);
}

int buttonPressed() {
  for (int i = 0; i < 4; ++i) {
    if (digitalRead(BUTTON_LEDS[i].knop) == LOW) {
      return i;
    }
  }

  return -1;
}

void show_order() {
  for (int i = 0; i < level; i++) {
    ButtonLed buttonled = BUTTON_LEDS[max_level[i]];
    soundBuzzer(buttonled.buzzerHoogte, 250, FALSE);
    showLed(buttonled.LED, 550);
    delay(100);
  }
}

void makeNewNumber() {
  // Generate next number which is not equal to the previous 2 numbers when they are the same
  do {
    max_level[level] = random(0,4);
  } while (level > 1 && max_level[level] == max_level[level - 1] /*&& max_level[level] == max_level[level - 2]*/);
  level++;
  show_order();
  n = 0;
}

void loop() {
  // put your main max_level here, to run repeatedly:
  int pressed = buttonPressed();
  if (pressed >= 0) {
    if (level == 0) {
      // Start new game
      makeNewNumber();
    } else {
      ButtonLed buttonled = BUTTON_LEDS[pressed];
      soundBuzzer(buttonled.buzzerHoogte, 300, FALSE);
      showLed(buttonled.LED, 300);

      if (max_level[n] == pressed) {
        // Guessed max_level digit correctly
        if (n == level - 1) {
          // Guessed whole max_level correctly
          if (level == 100) {
            // Maximum max_level length reached
            //playMegalovania();
            level = 0;
          } else {
            // Increase max_level length
            for (int i = 800; i <= 1200; i = i + 100) {
              soundBuzzer (i, 100, TRUE);
            }
            delay(500);
            makeNewNumber();
          }
        } else {
          // Advance to next max_level digit to guess
          n++;
        }
      } else {
        // Geluid voor als je het fout hebt
        for (int i = 2000; i >= 650; i = i - 100) {
          soundBuzzer (i, 100, TRUE);
        }
        level = 0;
      }
    }
  }
}
