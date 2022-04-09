
//ambient light
unsigned long lighting() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();

  tft.drawRoundRect(260,0,60,65,20,ILI9341_WHITE); // (x,y,w,h,r,color)
  

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(4);
  tft.println("Lighting");
  tft.setCursor(80,110);
  tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println("UV: ");
  tft.setCursor(135,110);
  tft.println(UV);
  tft.setCursor(160,110);
  tft.println(" lux");
  tft.setTextColor(ILI9341_YELLOW); 
  tft.setCursor(80,130);
  tft.println("Visible: ");
  tft.setCursor(180,130);
  tft.println(ALS);
  tft.setCursor(230,130);
  tft.println("lux");
  
}
