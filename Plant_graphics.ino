//http://www.adafruit.com/products/1651

//Written by Alec Mulkern with help from Adafruit ILI9341 library examples, March 2021 for ENGN208 Electronics
//PlantAnalytics graphics code


//variables
int t=0;
int hum = 0;
int UV = 0;
uint16_t capread = 0;
int ALS = 0;

//libraries
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Wire.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_HTS221.h>
#include <Adafruit_LTR390.h>
#include <Adafruit_seesaw.h>
#include "Environment.h"
#include "24h_data.h"
#include "Ambient_light.h"
#include "Boot_screen.h"
#include "Home_screen.h"
#include "SoilStatus.h"

//I2C
Adafruit_HTS221 hts;
Adafruit_Sensor *hts_humidity, *hts_temp;

Adafruit_LTR390 ltr = Adafruit_LTR390();

Adafruit_seesaw ss;


void setup() {
  
  Serial.begin(9600);  

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

    if (!hts.begin_I2C()) {
    Serial.println("Failed to find HTS221 chip");
    while (1) {
      delay(10);
    }
  }

  hts_temp = hts.getTemperatureSensor();
  hts_humidity = hts.getHumiditySensor();

  tft.begin();   //start screen
  ts.begin();    //start touchscreen

  
  Serial.println("Adafruit LTR-390 test");

  if ( ! ltr.begin() ) {
    Serial.println("Couldn't find LTR sensor!");
    while (1) delay(10);
  }
  Serial.println("Found LTR sensor!");

  ltr.setMode(LTR390_MODE_ALS);
  if (ltr.getMode() == LTR390_MODE_ALS) {
    Serial.println("In ALS mode");
  } else {
    Serial.println("In UVS mode");
  }

  ltr.setGain(LTR390_GAIN_3);
  Serial.print("Gain : ");
  switch (ltr.getGain()) {
    case LTR390_GAIN_1: Serial.println(1); break;
    case LTR390_GAIN_3: Serial.println(3); break;
    case LTR390_GAIN_6: Serial.println(6); break;
    case LTR390_GAIN_9: Serial.println(9); break;
    case LTR390_GAIN_18: Serial.println(18); break;
  }

  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  Serial.print("Resolution : ");
  switch (ltr.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial.println(13); break;
    case LTR390_RESOLUTION_16BIT: Serial.println(16); break;
    case LTR390_RESOLUTION_17BIT: Serial.println(17); break;
    case LTR390_RESOLUTION_18BIT: Serial.println(18); break;
    case LTR390_RESOLUTION_19BIT: Serial.println(19); break;
    case LTR390_RESOLUTION_20BIT: Serial.println(20); break;
  }

  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

//start display
bootscreen();

homescreen();
delay (10);
}


void loop(void) {
  
//touchscreen
  if (ts.bufferEmpty()) {
    return;
  }   
  TS_Point p = ts.getPoint();
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.println("Touch Coordinates: "); Serial.print("("); Serial.print(p.x);    
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");    

  
//temp and humidity sensor
  sensors_event_t humidity;
  sensors_event_t temp;
  hts_humidity->getEvent(&humidity);
  hts_temp->getEvent(&temp);
  Serial.print("Temperature ");
  Serial.print(temp.temperature *9/5 +32);
  Serial.println(" deg F");
  t = temp.temperature *9/5 +32;
  hum = humidity.relative_humidity;
  Serial.print("Humidity: ");Serial.print(humidity.relative_humidity);Serial.println(" % rH");
  delay(100);

//UV sensor  
  if (ltr.newDataAvailable()) {
    
    ltr.setMode(LTR390_MODE_UVS);
    if (ltr.getMode() == LTR390_MODE_UVS) {
      Serial.println("In UVS mode");
    } else {
      Serial.println("In ALS mode");
    }
      
    Serial.print("UV data: "); 
    Serial.println(ltr.readUVS());
    UV = ltr.readUVS();
    delay(100);
    
    ltr.setMode(LTR390_MODE_ALS);
    
    //delay(1000);
    if (ltr.newDataAvailable()) {
      if (ltr.getMode() == LTR390_MODE_ALS) {
        Serial.println("In ALS mode");
      } else {
        Serial.println("In UVS mode");
      }
    
      Serial.print("ALS data: "); 
      Serial.println(ltr.readALS());
      ALS = ltr.readALS();
    }
  }
  delay(100);

//soil monitor
capread = ss.touchRead(0);


Serial.print("cap = ");
Serial.println(capread);
Serial.println("");
Serial.println("");

delay(10);


  
  
//button mapping
    if (p.y < 50 && p.x > 100) {
    soilStatus();
    }

    if (p.y > 70 && p.y < 150 && p.x > 100){
      lighting();
    }

    if ((p.y > 150 && p.y < 180 && p.x > 100) || (p.y > 150 && p.x > 100 && p.x < 220)){
      environment();
    }

    if (p.x < 100){
      lastDay();
    }

   if (p.y > 180 && p.x > 220){
    homescreen();
    }



 delay (900);    //pros: stops multiple screen refreshes, cons: decreases touch immediacy, 900ms is a good balance


   
}
