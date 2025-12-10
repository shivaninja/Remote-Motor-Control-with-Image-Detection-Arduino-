#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int ledPins[] = {8, 9, 10, 11, 12};  // Thumb, Index, Middle, Ring, Pinky

void setup() {
  Serial.begin(9600);

  // LED pin setup
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // OLED Setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // freeze if OLED not found
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.print("READY");
  display.display();
  delay(1000);
}

void updateOLED(int states[]) {
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("LED Status:");

  int y = 15;
  bool anyOn = false;

  for (int i = 0; i < 5; i++) {
    if (states[i] == 1) {          // Light ON means finger open
      anyOn = true;
      display.setCursor(0, y);
      display.print("LED ");
      display.print(i + 1);
      display.print(": ON");
      y += 10;
    }
  }

  if (!anyOn) {
    display.setCursor(0, 15);
    display.print("No LEDs ON");
  }

  display.display();
}

void loop() {
  if (Serial.available() >= 5) {
    int states[5];

    // Read 5 bytes from Python
    for (int i = 0; i < 5; i++) {
      states[i] = Serial.read();
      digitalWrite(ledPins[i], states[i] ? HIGH : LOW);
    }

    // Update OLED with LED status
    updateOLED(states);
  }
}
