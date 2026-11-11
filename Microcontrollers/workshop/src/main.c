// ===== 1. LIBRARIES =====
#include <Adafruit_GFX.h>        // Drawing functions (shapes, text)
#include <Adafruit_GC9A01A.h>    // Driver for this specific chip
#include <SPI.h>                 // SPI communication

// ===== 2. PIN DEFINITIONS =====
#define TFT_CS    5              // Chip Select
#define TFT_DC    2              // Data/Command
#define TFT_RST   4              // Reset

// ===== 3. CREATE THE DISPLAY OBJECT =====
// Uses the ESP32's default hardware SPI pins (SCK=18, MOSI=23)
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

// ===== 4. SETUP: runs once =====
void setup() {
  Serial.begin(115200);          // Debug output
  tft.begin();                   // Initialize the display
  tft.fillScreen(GC9A01A_BLACK); // Clear to black

  tft.setCursor(40, 100);        // Text position (x, y)
  tft.setTextColor(GC9A01A_GREEN);
  tft.setTextSize(2);            // 2x scale
  tft.println("Hello World!");
}

// ===== 5. LOOP: runs forever =====
void loop() {
  tft.fillCircle(120, 120, 100, GC9A01A_BLUE);  // center (120,120), radius 100
  delay(2000);
  tft.fillCircle(120, 120, 100, GC9A01A_RED);
  delay(2000);
}