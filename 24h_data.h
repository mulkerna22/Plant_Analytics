//24h data
unsigned long lastDay() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_WHITE);
  w     = min(tft.width(), tft.height());
  start = micros();

  tft.drawRoundRect(258,2,60,65,20,ILI9341_BLACK); // (x,y,w,h,r,color)

  tft.setCursor(2, 2);
  tft.setTextColor(ILI9341_ORANGE);  tft.setTextSize(4);
  tft.println("Info");
  tft.setCursor(2,60);
  tft.setTextColor(ILI9341_BLACK); tft.setTextSize(2);
  tft.println("Watering time: 0 sec");
  tft.setCursor(2,80);
  tft.println("Lighting time: 0 h");
  tft.setCursor(2,100);
  tft.println("Average temperature: 74 F");
  tft.setCursor(2,120);
  tft.println("Temperature range: 3 F");
  tft.setCursor(2,140);
  tft.println("Water level: 0%");
  tft.setTextSize(1);
  tft.setCursor(260,230);
  tft.println("v: 1.0.1");
  
}
