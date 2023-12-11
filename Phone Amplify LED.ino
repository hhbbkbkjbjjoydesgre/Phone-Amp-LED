#include <Adafruit_NeoPixel.h>

#define PIN_LED 6
#define PIN_MIC A0
#define PIN_SWITCH 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

int micValue = 0;
bool isOn = true;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(PIN_MIC, INPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP); // Use INPUT_PULLUP for the switch to avoid external pull-up resistor
}

void loop() {
  micValue = analogRead(PIN_MIC);

  if (digitalRead(PIN_SWITCH) == LOW) {
    isOn = !isOn;
    delay(500); // Debounce delay
  }

  if (isOn) {
    // Map micValue to the LED brightness (adjust the mapping based on your microphone sensitivity)
    int brightness = map(micValue, 0, 1023, 0, 255);
    
    // Update the LED color and brightness
    strip.setBrightness(brightness);
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // Red color, you can change it
    strip.show();
  } else {
    // Turn off the LED when the system is off
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
  }

  delay(50); // Adjust the delay based on the responsiveness you desire
}
