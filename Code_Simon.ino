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
int code[12];
int codeLength = 0;
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


void soundBuzzer(unsigned int frequency, unsigned int duration, int wait) {
  tone(BUZZER, frequency, duration);
  if (wait) {
    delay(duration);
  }
}

void showLed(unsigned int pin, unsigned int duration) {
  digitalWrite(pin,  HIGH);
  delay(duration);
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
  for (int i = 0; i < codeLength; i++) {
    ButtonLed bl = BUTTON_LEDS[code[i]];
    soundBuzzer(bl.buzzerHoogte, 500, FALSE);
    showLed(bl.LED, 500);
  }
}

void generateNextNumber() {
  // Generate next number which is not equal to the previous 2 numbers when they are the same
  do {
    code[codeLength] = random() % 4;
  } while (codeLength > 1 && code[codeLength] == code[codeLength - 1] && code[codeLength] == code[codeLength - 2]);
  codeLength++;
  show_order();
  n = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  int pressed = buttonPressed();
  if (pressed >= 0) {
    if (codeLength == 0) {
      // Start new game
      generateNextNumber();
    } else {
      ButtonLed bl = BUTTON_LEDS[pressed];
      soundBuzzer(bl.buzzerHoogte, 300, FALSE);
      showLed(bl.LED, 300);

      if (code[n] == pressed) {
        // Guessed code digit correctly
        if (n == codeLength - 1) {
          // Guessed whole code correctly
          if (codeLength == 12) {
            // Maximum code length reached
            //playMegalovania();
            codeLength = 0;
          } else {
            // Increase code length
            for (int i = 800; i <= 1200; i = i + 100) {
              soundBuzzer (i, 100, TRUE);
            }
            delay(500);
            generateNextNumber();
          }
        } else {
          // Advance to next code digit to guess
          n++;
        }
      } else {
        // Guessed code digit incorrectly
        for (int i = 1600; i >= 800; i = i - 100) {
          soundBuzzer (i, 100, TRUE);
        }
        codeLength = 0;
      }
    }
  }
}
