// Required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Set up the display and define pins
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define TRIG_PIN 6
#define ECHO_PIN 7

// Variables for the timout
bool displayOn = true;
unsigned long lastActivity = 0;
const unsigned long timeout = 5000;

// Setup function
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

    
  lastActivity = millis();
}

void loop() {
  long dist = getDistance();

  // Turn on the display if distance is 5cm or less
  if (dist > 0 && dist <= 5) {
    if (!displayOn) {
      displayOn = true;
      display.clearDisplay();
      display.setCursor(0, 10);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.println("Display is on");
      display.display();
    }
    lastActivity = millis();
  }

  // Clear the display if no activity for 5 seconds
  if (displayOn && millis() - lastActivity >= timeout) {
    display.clearDisplay();
    display.display();
    displayOn = false;
  }

  delay(100);
}

// Gets the distance from the sensor in cm
long getDistance() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return (duration == 0) ? -1 : duration * 0.034 / 2;
}
