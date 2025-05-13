// Defining pins
#define BUZZER_PIN 8
#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4
#define BUTTON4 5
#define BUTTON5 6

// Setup function to initialise the pins
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
}

// If statements to check which button is pressed
void loop() {
  if (digitalRead(BUTTON1) == LOW) {
    playTone(250);
  } else if (digitalRead(BUTTON2) == LOW) {
    playTone(500);
  } else if (digitalRead(BUTTON3) == LOW) {
    playTone(1000);
  } else if (digitalRead(BUTTON4) == LOW) {
    playTone(1500);
  } else if (digitalRead(BUTTON5) == LOW) {
    playTone(2000);
  } else {
    noTone(BUZZER_PIN);
  }
}

// Function to play a sound
void playTone(int freq) {
  tone(BUZZER_PIN, freq);
  delay(50);
  noTone(BUZZER_PIN);
}
