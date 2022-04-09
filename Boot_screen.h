

//boot screen

unsigned long bootscreen(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(5);
  tft.println("PLANT");
  delay(500);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(5);
  tft.println("ANALYTICS");
  delay(500);
  tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(3);
  tft.println();
  tft.println("ENGN208");
  delay(1000);
}
