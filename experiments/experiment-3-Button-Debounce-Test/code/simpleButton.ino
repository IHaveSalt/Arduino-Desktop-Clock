// Include the Bounce2 library and define pins
#include <Bounce2.h>
#define BUTTON_PIN 2
#define LED_PIN 8

Bounce debouncer = Bounce();
bool ledState = false;

void setup() {
  // Set up LED pin as output and initialise
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);

  // Set up button pin with internal pull up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach debouncer to the button pin and set the debounce interval
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(25);
}

// Toggle LED
void loop() {
  debouncer.update();
  if (debouncer.fell()) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}
