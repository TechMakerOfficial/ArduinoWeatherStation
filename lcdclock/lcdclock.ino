#include <DS1302.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

#include "DHT.h"
#define DHTPIN 5     //digital pin sensor

// Uncomment whatever type you're using!

  #define DHTTYPE DHT11      // DHT 11
  //#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
  //#define DHTTYPE DHT21

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

DS1302 rtc(2, 3, 4);

DHT dht(DHTPIN, DHTTYPE);



void setup() {
  rtc.halt(false);
  rtc.writeProtect(false);
  lcd.begin(16, 2);
  
  dht.begin();
 
//rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
//rtc.setTime(11, 51, 0);     // Set the time to 12:00:00 (24hr format)
//rtc.setDate(6, 1, 2017); 

}

void loop() {

 delay(1000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" ERROR  READING ");
    return;
  }

  lcd.setCursor(4, 0);
  lcd.print(rtc.getTimeStr());
  
  lcd.setCursor(1, 1);
  
  lcd.print(h);
  lcd.print(" % ");
  
  lcd.print(t);
  lcd.print(" C");

  delay(1000);


}
