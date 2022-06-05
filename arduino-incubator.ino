#include "DHT.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define roleLamba 8
#define roleFan 9

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  lcd.init();
  lcd.backlight();//lcd başladı
  pinMode(roleLamba,OUTPUT);
  pinMode(roleFan,OUTPUT);

}

void loop() {

  //*********dht basla
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
 delay(2000);
  //*************dht bitis

  //**************ekran basla
  lcd.home();
  lcd.print("N:");
  lcd.print(h);  // yazdırılacak yazı
  lcd.print("Sck:");
  lcd.print(t);
  lcd.setCursor(0, 1);  //yazının yazılacağı satır ve sütün sayısı
  lcd.print("Fan:");
  lcd.print("  ");
  lcd.print("Lamba:");
 
  lcd.setCursor(0, 2);
  //*******************ekran bitis


  //*********lamba aç
if (t<25)
  digitalWrite(roleLamba,HIGH);
  else
  digitalWrite(roleLamba,LOW);


//*********lamab kapat
if (t>27)
  digitalWrite(roleLamba,LOW);
  else
  digitalWrite(roleLamba,HIGH);


  //*********fan aç
if (h>70)
  digitalWrite(roleFan,HIGH);
  else
  digitalWrite(roleFan,LOW);


//*********fan kapat
if (h<60)
  digitalWrite(roleFan,LOW);
  else
  digitalWrite(roleFan,HIGH);

}
