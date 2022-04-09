unsigned long soilStatus() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();

  tft.drawRoundRect(260,0,60,65,20,ILI9341_WHITE); // (x,y,w,h,r,color)
  

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(4);
  tft.println("SoilStatus");
  tft.setCursor(40,130);
  //tft.print(capread);

  if (capread < 700){
  tft.setTextColor(ILI9341_ORANGE); tft.setTextSize(2);
  tft.println("Please water me :(");
  }
  if (capread > 700 && capread < 850){
  tft.setTextColor(ILI9341_GREEN); tft.setTextSize(2);
  tft.println("Doing just fine thanks!");
  }
  if (capread > 850){
      tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println("Oh no, I'm soup.");
  }
}
