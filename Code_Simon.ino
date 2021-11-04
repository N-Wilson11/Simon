#define FALSE 0
#define TRUE 1

// Safe to Arduino pin mapping
#define PIN_LED_BLUE 2
#define PIN_LED_GREEN 9
#define PIN_LED_RED 4
#define PIN_LED_YELLOW 7

#define PIN_BTN_LOW 8
#define PIN_BTN_BLUE 3
#define PIN_BTN_GREEN 11
#define PIN_BTN_RED 5
#define PIN_BTN_YELLOW 13

#define PIN_BUZZER A0

typedef struct {
  int button;
  int led;
  int buzzerFrequency;
} ButtonLed;

const ButtonLed BUTTON_LEDS[4] = {
  {PIN_BTN_BLUE, PIN_LED_BLUE, 400},
  {PIN_BTN_GREEN, PIN_LED_GREEN, 800},
  {PIN_BTN_RED, PIN_LED_RED, 1200},
  {PIN_BTN_YELLOW, PIN_LED_YELLOW, 1600},
};
int code[2];
int codeLength = 0;
int n;

void setup() {
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_BTN_BLUE, INPUT_PULLUP);
  pinMode(PIN_BTN_GREEN, INPUT_PULLUP);
  pinMode(PIN_BTN_RED, INPUT_PULLUP);
  pinMode(PIN_BTN_YELLOW, INPUT_PULLUP);

  pinMode(PIN_BTN_LOW, OUTPUT);
  digitalWrite(PIN_BTN_LOW, LOW);

  // Initialize random number generator
  randomSeed(analogRead(0));
}


void soundBuzzer(unsigned int frequency, unsigned int duration, int wait) {
  tone(PIN_BUZZER, frequency, duration);
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
    if (digitalRead(BUTTON_LEDS[i].button) == LOW) {
      return i;
    }
  }

  return -1;
}

void showCode() {
  for (int i = 0; i < codeLength; i++) {
    ButtonLed bl = BUTTON_LEDS[code[i]];
    soundBuzzer(bl.buzzerFrequency, 500, FALSE);
    showLed(bl.led, 500);
  }
}

void generateNextNumber() {
  // Generate next number which is not equal to the previous 2 numbers when they are the same
  do {
    code[codeLength] = random() % 4;
  } while (codeLength > 1 && code[codeLength] == code[codeLength - 1] && code[codeLength] == code[codeLength - 2]);
  codeLength++;
  showCode();
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
      soundBuzzer(bl.buzzerFrequency, 300, FALSE);
      showLed(bl.led, 300);

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
