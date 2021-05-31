#include "DispLib.h"
#include "HelpLib.h"
#define ERROR -999
#include "dht11.h"
dht11 sensor;
#define DHT11PIN 4
#define DHT11PIN2 5
LiquidCrystal_I2C lcd(0x27 , 20 , 4);
float t[3] = {0};
float h[3] = {0};
int i = 0;
void setup(){
Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("T(C)");
lcd.setCursor(0, 1);
lcd.print("H(%)");
}
void loop()
{

delay(1000);
int chk = sensor.read(DHT11PIN);
t[i] = sensor.temperature;
h[i] = sensor.humidity;
lcd.setCursor(5,0);
float temper = filter(t);
lcd.print(temper);
lcd.setCursor(5,1);
float hum12 = filter(h);
lcd.print(hum12);
showGraph(temper,hum12);
delay(1000);
i = (i+1) % 3;
chk = sensor.read(DHT11PIN2);
t[i] = sensor.temperature;
h[i] = sensor.humidity;
lcd.setCursor(5,0);
 temper = filter(t);
lcd.print(temper);
lcd.setCursor(5,1);
 hum12 = filter(h);
lcd.print(hum12);
Serial.println(t[i]);
i = (i+1) % 3;
showGraph(temper,hum12);


}
