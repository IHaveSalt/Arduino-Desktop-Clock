// Required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Bounce2.h>

// Set up the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Define button and LED pins
#define RED_BTN 2
#define GREEN_BTN 3
#define BLUE_BTN 4
#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10

// Tracks the current menu
int currentMenu = -1;

// Set up button debouncers using Bounce2
Bounce redButton = Bounce();
Bounce greenButton = Bounce();
Bounce blueButton = Bounce();

void setup() {
  // Set up buttons with internal pull-up resistors
  pinMode(RED_BTN, INPUT_PULLUP);
  pinMode(GREEN_BTN, INPUT_PULLUP);
  pinMode(BLUE_BTN, INPUT_PULLUP);

  // Set up LED pins as outputs and keep them off
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  // Attach buttons to debouncers and set debounce interval
  redButton.attach(RED_BTN);
  greenButton.attach(GREEN_BTN);
  blueButton.attach(BLUE_BTN);
  redButton.interval(25);
  greenButton.interval(25);
  blueButton.interval(25);

  // Initialise OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Display initial message on boot
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Display is on. Press a button");
  display.display();
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
    selectMenu(2);
  }
}

// Called when a button is pressed to activate a specific menu
// Updates LED indicators and only redraws if menu has changed
void selectMenu(int menuIndex) {
  if (menuIndex == currentMenu) return;
  currentMenu = menuIndex;
  digitalWrite(RED_LED, menuIndex == 0 ? HIGH : LOW);
  digitalWrite(GREEN_LED, menuIndex == 1 ? HIGH : LOW);
  digitalWrite(BLUE_LED, menuIndex == 2 ? HIGH : LOW);
  renderMenu(currentMenu);
}

// Clears the display and shows content for the selected menu
void renderMenu(int menu) {
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (menu == 0) {
    display.println("Menu 1: Clock");
  } else if (menu == 1) {
    display.println("Menu 2: Date");
  } else if (menu == 2) {
    display.println("Menu 3: Timer");
  }

  display.display();
}