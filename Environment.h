#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Wire.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_HTS221.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);


// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

//tft.begin();

//environment
unsigned long environment() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();

  tft.drawRoundRect(260,0,60,65,20,ILI9341_WHITE); // (x,y,w,h,r,color)
  

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(4);
  tft.println("Environment");
  tft.setCursor(60,130);
  tft.setTextColor(ILI9341_ORANGE); tft.setTextSize(2);
  tft.println("Temperature: ");
  tft.setCursor(205,130);
  tft.print(t);
  tft.print(" F");
  tft.setCursor(60,160);
  tft.setTextColor(ILI9341_BLUE); tft.setTextSize(2);
  tft.println("Humidity: ");
  tft.setCursor(180,160);
  tft.print(hum);
  tft.print(" %");
  tft.setTextColor(ILI9341_WHITE); tft.setTextSize(2);

  
}
