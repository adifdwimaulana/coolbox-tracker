#include <Wire.h>
#include "i2c.h"
#include "i2c_BMP280.h"
#include "TinyGPS++.h"
#include <DHT.h> 
#include <TinyGPS.h>
float lat = 28.5458,lon = 77.1703;
float flat, flon;
#define DHTPIN 8 
#define DHTTYPE DHT11
#define TCAADDR 0x70
DHT dht(DHTPIN, DHTTYPE);
int temp,humi,H;
static const uint32_t GPSBaud = 9600;
TinyGPS gps;
BMP280 bmp280s1;
BMP280 bmp280s2;
BMP280 bmp280s3;
BMP280 bmp280s4;
int relay= 9;

void GPS()
{
   bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial3.available())
    {
      char c = Serial3.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
}
}

void tcaselect(uint8_t i) 
{
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup()
{
 dht.begin();
 Serial.begin(115200);
 Serial2.begin(9600);
 Serial3.begin(GPSBaud);
 
    pinMode(relay, OUTPUT); //mengatur relay sebagai OUTPUT
    
    tcaselect(1);
    bmp280s1.initialize();
    bmp280s1.setEnabled(0);
    bmp280s1.triggerMeasurement();
    delay(100);
    
    tcaselect(0);
    bmp280s2.initialize();
    bmp280s2.setEnabled(0);
    bmp280s2.triggerMeasurement();
    delay(100);
    
    tcaselect(3);
    bmp280s3.initialize();
    bmp280s3.setEnabled(0);
    bmp280s3.triggerMeasurement();
    delay(100);
    
    tcaselect(4);
    bmp280s4.initialize();
    bmp280s4.setEnabled(0);
    bmp280s4.triggerMeasurement();
    delay(100);
 delay(500);
}
void loop()
{
  tcaselect(1);
    Serial.print("Sensor #1 - ");
    bmp280s1.awaitMeasurement();
    float temperature;
    bmp280s1.getTemperature(temperature);
    float pascal;
    bmp280s1.getPressure(pascal);
//    static float meters, metersold;
//    bmp280.getAltitude(meters);
//    metersold = (metersold * 10 + meters)/11;
    bmp280s1.triggerMeasurement();
    Serial.print(" Pressure: ");
    Serial.print(pascal);
    Serial.print(" Pa; T: ");
    Serial.print(temperature);
    Serial.println(" C");
    delay(100);

    tcaselect(0);
    Serial.print("Sensor #2 - ");
    bmp280s2.awaitMeasurement();
    float temperature2;
    bmp280s2.getTemperature(temperature2);
    float pascal2;
    bmp280s2.getPressure(pascal2);
//    static float meters, metersold;
//    bmp280.getAltitude(meters);
//    metersold = (metersold * 10 + meters)/11;
    bmp280s2.triggerMeasurement();
    Serial.print(" Pressure2: ");
    Serial.print(pascal2);
    Serial.print(" Pa; T2: ");
    Serial.print(temperature2);
    Serial.println(" C");
    delay(100);

    tcaselect(3);
    Serial.print("Sensor #3 - ");
    bmp280s3.awaitMeasurement();
    float temperature3;
    bmp280s3.getTemperature(temperature3);
    float pascal3;
    bmp280s3.getPressure(pascal3);
//    static float meters, metersold;
//    bmp280.getAltitude(meters);
//    metersold = (metersold * 10 + meters)/11;
    bmp280s3.triggerMeasurement();
    Serial.print(" Pressure3: ");
    Serial.print(pascal3);
    Serial.print(" Pa; T3: ");
    Serial.print(temperature3);
    Serial.println(" C");
    delay(100);
    
    tcaselect(4);
    Serial.print("Sensor #4 - ");
    bmp280s4.awaitMeasurement();
    float temperature4;
    bmp280s4.getTemperature(temperature4);
    float pascal4;
    bmp280s4.getPressure(pascal4);
//    static float meters, metersold;
//    bmp280.getAltitude(meters);
//    metersold = (metersold * 10 + meters)/11;
    bmp280s4.triggerMeasurement();
    Serial.print(" Pressure4: ");
    Serial.print(pascal4);
    Serial.print(" Pa; T4: ");
    Serial.print(temperature4);
    Serial.println(" C");
    delay(100);
  //////////////////////////////////////dht///////////////////////////////////
  float humi = dht.readHumidity(); 
  float temp = dht.readTemperature();
  Serial.print("H: ");
  Serial.print(humi); 
  Serial.print("% ");
  Serial.print(" T: ");
  Serial.print(temp); 
  Serial.println("C");
///////////////////////////////////////////////GPS Loop///////////////////////////////
GPS();
////////////////////////////////////////////////////////////KIRIM SERIAL////////////////////////////////////////////
Serial2.print('a');
Serial2.println(temp);  
Serial2.print('b');
Serial2.println(humi);
Serial2.print('c');
Serial2.println(temperature);
Serial2.print('d');
Serial2.println(temperature2);
Serial2.print('e');
Serial2.println(temperature3);
Serial2.print('f');
Serial2.println(temperature4);
Serial2.print('g');
Serial2.println(pascal);
Serial2.print('h');
Serial2.println(pascal2);
Serial2.print('i');
Serial2.println(pascal3);
Serial2.print('j');
Serial2.println(pascal4);
Serial2.print('k');
Serial2.println(flat, 6);
Serial2.print('l');
Serial2.println(flon, 6);
 delay(3000);
}
