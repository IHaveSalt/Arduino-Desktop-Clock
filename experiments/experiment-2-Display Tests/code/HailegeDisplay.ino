// Required libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Define pins
#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9

// Initialise the display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("I am a Touch Display");
}

void loop() {
}
