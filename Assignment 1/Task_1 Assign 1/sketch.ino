#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LEDs
#define LED1 16
#define LED2 17
#define LED3 18

// Buttons
#define MODE_BTN 34
#define RESET_BTN 26

int mode = 0; // 0 = OFF, 1 = RUN

// For alternate blinking LEDs
bool led1On = false;

// For fading LED
int fadeValue = 0;
int fadeDir = 5;

void showState(String state){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println(state);
  display.display();
}

void setup() {
  Wire.begin(21,22);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(MODE_BTN, INPUT_PULLUP);
  pinMode(RESET_BTN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  showState("OFF");
}

void loop() {
  // RESET button pressed → turn everything OFF
  if(!digitalRead(RESET_BTN)){
    mode = 0;
    led1On = false;
    fadeValue = 0;

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    analogWrite(LED3, 0);

    showState("OFF");
    delay(50); // small debounce
  }

  // MODE button pressed → start RUN
  if(!digitalRead(MODE_BTN)){
    mode = 1;
    showState("RUN");
    delay(200); // simple debounce
  }

  if(mode == 1){
    // --- Alternate blink for LED1 & LED2 ---
    led1On = !led1On;               // change state
    digitalWrite(LED1, led1On);
    digitalWrite(LED2, !led1On);
    delay(200);                     // blink speed

    // --- Fade LED3 smoothly ---
    fadeValue += fadeDir;
    if(fadeValue >= 255 || fadeValue <= 0) fadeDir = -fadeDir; // reverse direction
    analogWrite(LED3, fadeValue);
    delay(10);                      // fade smoothness
  }
}
