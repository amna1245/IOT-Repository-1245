#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON 26
#define LED 16
#define BUZZER 34

int lastButtonState = HIGH;
int ledState = LOW;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // I2C begin for ESP32 (SDA, SCL)
  Wire.begin(21, 22);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(1); // stop if OLED not found
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("READY!");
  display.display();
}

void loop() {
  int currentState = digitalRead(BUTTON);

  // button pressed
  if (currentState == LOW && lastButtonState == HIGH) {
    delay(50); // debounce

    int counter = 0;

    while (digitalRead(BUTTON) == LOW) {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Hold: ");
      display.print(counter * 100);
      display.println("ms");
      display.display();

      delay(100);
      counter++;
    }

    // SHORT PRESS
    if (counter < 15) {
      ledState = !ledState;
      digitalWrite(LED, ledState);

      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("SHORT");
      display.display();
    }
    // LONG PRESS
    else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("LONG!");
      display.display();

      tone(BUZZER, 900);
      delay(500);
      noTone(BUZZER);
    }

    delay(400);
  }

  lastButtonState = currentState;
}
