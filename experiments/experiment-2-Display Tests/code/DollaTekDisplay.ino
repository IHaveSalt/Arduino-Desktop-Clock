// Required libraries for the display
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

// Define pins
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

// Create display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.fillScreen(ILI9341_RED);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 50);
  tft.println("Hello I am a display");
}

void loop() {
}
