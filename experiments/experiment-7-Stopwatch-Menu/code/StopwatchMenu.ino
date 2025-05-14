// Required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <Bounce2.h>

// Set up the display and RTC
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

// Define button pins
#define RED_BTN 2
#define GREEN_BTN 3
#define BLUE_BTN 4

// Tracks the current menu
int currentMenu = 0;

// Stopwatch variables
bool stopwatchRunning = false;
unsigned long stopwatchStart = 0;
unsigned long elapsedTime = 0;
unsigned long blueButtonHoldStart = 0;
bool blueButtonHeld = false;

// Set up button debouncers using Bounce2
Bounce redButton = Bounce();
Bounce greenButton = Bounce();
Bounce blueButton = Bounce();

void setup() {
  // Set up buttons with internal pull-up resistors
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);
  pinMode(BLUE_BTN, INPUT_PULLUP);

  // Attach buttons to debouncers and set debounce interval
  redButton.attach(RED_BTN);
  greenButton.attach(GREEN_BTN);
  blueButton.attach(BLUE_BTN);
  redButton.interval(25);
  greenButton.interval(25);
  blueButton.interval(25);

  // Initialise OLED display and the RTC
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  rtc.begin();

  // Line used to adjust the time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Render the first menu (time menu)
  renderMenu(currentMenu);
}

void loop() {
  // Update button states with debounce
  redButton.update();
  greenButton.update();
  blueButton.update();

  // Detect which button was pressed and switch to the corresponding menu
  if (redButton.fell()) {
    selectMenu(0);
  } else if (greenButton.fell()) {
    selectMenu(1);
  } else if (blueButton.fell()) {
    if (currentMenu == 2) {
      stopwatchRunning = !stopwatchRunning;
      if (stopwatchRunning) stopwatchStart = millis() - elapsedTime;
    } else {
      selectMenu(2);
    }
  }

  // Stopwatch reset on long press (2 seconds hold)
  if (currentMenu == 2 && digitalRead(BLUE_BTN) == LOW) {
    if (!blueButtonHeld) {
      blueButtonHoldStart = millis();
      blueButtonHeld = true;
    } else if (millis() - blueButtonHoldStart >= 2000) {
      stopwatchRunning = false;
      elapsedTime = 0;
      blueButtonHeld = false;
      renderMenu(2);
    }
  } else {
    blueButtonHeld = false;
  }

  // Redraw logic
  if (currentMenu == 0 || currentMenu == 1) renderMenu(currentMenu);
  else if (currentMenu == 2 && stopwatchRunning) renderStopwatch();
}

// Called when a button is pressed to activate a specific menu
// Also updates the stopwatch state
void selectMenu(int menuIndex) {
  if (menuIndex == currentMenu) return;
  currentMenu = menuIndex;
  renderMenu(currentMenu);
}

// Clears thge display and shows content for the selected menu
void renderMenu(int menu) {
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Get the current time from the RTC
  DateTime now = rtc.now();

  //Logic for displaying different menus
  // Menu 1 - Time
  if (menu == 0) {
    display.print("Time: ");
    display.print(now.hour());
    display.print(":");
    if (now.minute() < 10) display.print("0");
    display.print(now.minute());
    display.print(":");
    if (now.second() < 10) display.print("0");
    display.print(now.second());

    // Menu 2 - Date
  } else if (menu == 1) {
    display.print("Date: ");
    display.print(now.day());
    display.print("/");
    display.print(now.month());
    display.print("/");
    display.print(now.year());

    // Menu 3 - Stopwatch
  } else if (menu == 2) {
    display.println("Stopwatch:");
    display.setCursor(0, 30);
    unsigned long ms = stopwatchRunning ? millis() - stopwatchStart : elapsedTime;
    elapsedTime = ms;

    int seconds = (ms / 1000) % 60;
    int minutes = (ms / 60000) % 60;
    int hours = ms / 3600000;

    display.print(hours);
    display.print(":");
    if (minutes < 10) display.print("0");
    display.print(minutes);
    display.print(":");
    if (seconds < 10) display.print("0");
    display.print(seconds);
  }

  display.display();
}

void renderStopwatch() {
  renderMenu(2);
}
