
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <Bounce2.h>

// OLED and RTC setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

// Pin definitions
#define RED_BTN 2
#define GREEN_BTN 3
#define BLUE_BTN 4

#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10

#define BUZZER_PIN 11

#define TRIG_PIN 6
#define ECHO_PIN 7

// Menu tracking
int currentMenu = 0;

// Stopwatch state
bool stopwatchRunning = false;
unsigned long stopwatchStart = 0;
unsigned long elapsedTime = 0;
unsigned long btnHoldStart = 0;
bool btnHeld = false;

// Screen sleep state
bool screenOn = true;
unsigned long lastInteractionTime = 0;
const unsigned long screenTimeout = 5000;

// Bounce objects
Bounce redButton = Bounce();
Bounce greenButton = Bounce();
Bounce blueButton = Bounce();

// Setup function to initialise the hardware
void setup() {
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);
  pinMode(BLUE_BTN, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  redButton.attach(RED_BTN); redButton.interval(25);
  greenButton.attach(GREEN_BTN); greenButton.interval(25);
  blueButton.attach(BLUE_BTN); blueButton.interval(25);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  rtc.begin();

  // Used to adjust the time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  renderMenu(currentMenu);
  lastInteractionTime = millis();
}

// Main loop function to handle button presses and display updates
void loop() {
  redButton.update();
  greenButton.update();
  blueButton.update();

  // Menu switching
  if (redButton.fell()) {
    playBeep();
    selectMenu(0);
  }
  if (greenButton.fell()) {
    playBeep();
    selectMenu(1);
  }
  if (blueButton.fell()) {
    playBeep();
    if (currentMenu == 2) {
      stopwatchRunning = !stopwatchRunning;
      if (stopwatchRunning) stopwatchStart = millis() - elapsedTime;
    } else {
      selectMenu(2);
    }
  }

  // Stopwatch control
  if (currentMenu == 2 && digitalRead(BLUE_BTN) == LOW) {
    if (!btnHeld) {
      btnHoldStart = millis();
      btnHeld = true;
    } else if (millis() - btnHoldStart >= 2000) {
      stopwatchRunning = false;
      elapsedTime = 0;
      btnHeld = false;
      renderMenu(2);
    }
  } else {
    btnHeld = false;
  }

  // Turn off the screen after timeout
  if (millis() - lastInteractionTime >= screenTimeout && screenOn) {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    screenOn = false;
  }

  // Check for interaction to turn the screen back on
  if (!screenOn && (redButton.fell() || greenButton.fell() || blueButton.fell() || motionDetected())) {
    display.ssd1306_command(SSD1306_DISPLAYON);
    screenOn = true;
    renderMenu(currentMenu);
    lastInteractionTime = millis();
  }

  // Update the display if the screen is on
  if (screenOn) {
    if (currentMenu == 0 || currentMenu == 1) renderMenu(currentMenu);
    else if (currentMenu == 2 && stopwatchRunning) renderStopwatch();
  }
}

// Menu selection function
void selectMenu(int menuIndex) {
  if (menuIndex == currentMenu) return;
  currentMenu = menuIndex;

  digitalWrite(RED_LED, menuIndex == 0 ? HIGH : LOW);
  digitalWrite(GREEN_LED, menuIndex == 1 ? HIGH : LOW);
  digitalWrite(BLUE_LED, menuIndex == 2 ? HIGH : LOW);

  renderMenu(currentMenu);
}

// Menu rendering function
void renderMenu(int menu) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);

  DateTime now = rtc.now();

  // Display information based on the selected menu menu
  // Time Menu
  if (menu == 0) {
    display.print("Time: ");
    display.print(now.hour()); display.print(":");
    if (now.minute() < 10) display.print("0");
    display.print(now.minute()); display.print(":");
    if (now.second() < 10) display.print("0");
    display.print(now.second());
  }

  // Date Menu
    else if (menu == 1) {
    display.print("Date: ");
    display.print(now.day()); display.print("/");
    display.print(now.month()); display.print("/");
    display.print(now.year());
  }

  // Stopwatch Menu
    else if (menu == 2) {
    display.println("Stopwatch:");
    display.setCursor(0, 30);
    unsigned long ms = stopwatchRunning ? millis() - stopwatchStart : elapsedTime;
    elapsedTime = ms;
    int seconds = (ms / 1000) % 60;
    int minutes = (ms / 60000) % 60;
    int hours = ms / 3600000;
    display.print(hours); display.print(":");
    if (minutes < 10) display.print("0");
    display.print(minutes); display.print(":");
    if (seconds < 10) display.print("0");
    display.print(seconds);
  }

  display.display();
}

// Render the stopwatch display
void renderStopwatch() {
  renderMenu(2);
}

// Plays buzzer sounds
void playBeep() {
  tone(BUZZER_PIN, 1000, 100);
}

// Detect motion using ultrasonic sensor
bool motionDetected() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  return (distance > 0 && distance < 5);
}
