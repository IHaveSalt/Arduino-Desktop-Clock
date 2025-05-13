// Required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS3231 rtc;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  rtc.begin();

  // Line used to adjust the time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  DateTime now = rtc.now();

  //Display time
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Time: ");
  display.print(now.hour());
  display.print(":");
  if (now.minute() < 10) display.print("0");
  display.print(now.minute());
  display.print(":");
  if (now.second() < 10) display.print("0");
  display.print(now.second());

  // Display date
  display.setCursor(0, 30);
  display.print("Date: ");
  display.print(now.day());
  display.print("/");
  display.print(now.month());
  display.print("/");
  display.print(now.year());

  display.display();
  delay(1000);
}
