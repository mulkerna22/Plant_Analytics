//home screen
unsigned long homescreen(){ 

unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_WHITE);
  w     = min(tft.width(), tft.height());
  start = micros();

  tft.drawLine(100, 0, 100, 160,ILI9341_BLACK );
  tft.drawLine(220, 0, 220, 160,ILI9341_BLACK );
  tft.drawLine(0, 161, 360, 161,ILI9341_BLACK );

  tft.drawRoundRect(260,0,60,65,20,ILI9341_BLACK); // (x,y,w,h,r,color)
  
  tft.setCursor(25, 60);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("Soil");
  tft.setCursor(15, 80);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(2);
  tft.println("Status");
  
  tft.setCursor(120, 60);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("Ambient");
  tft.setCursor(130, 80);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("Light");

  tft.setCursor(235, 70);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
  tft.println("Humid/");
  tft.setCursor(240, 90);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(2);
  tft.println("Temp");

  tft.setCursor(100, 195);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
  tft.println("Plant Info");
}
