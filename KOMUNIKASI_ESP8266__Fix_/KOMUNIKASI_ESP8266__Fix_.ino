#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
//#include <TinyGPS.h>

#define WIFI_SSID "KONTRAKAN ANAK2"
#define WIFI_PASSWORD "bukaopen"

#define FIREBASE_HOST "coolbox-tracker.firebaseio.com"
#define FIREBASE_AUTH "drM2QJ6pnalO1gS4bUWDm9CoryImyS0LVvUngXR9"

//TinyGPS gps;
//SoftwareSerial ss(D7, D6);

char tempArr[4];
char humiArr[4];
char tempBmpA[4];
char tempBmpB[4];
char tempBmpC[4];
char tempBmpD[4];
char tekananBmpA[4];
char tekananBmpB[4];
char tekananBmpC[4];
char tekananBmpD[4];
char latitude[8];
char longitude[8];
float temp;
float humi;
float tempA;
float tempB;
float tempC;
float tempD;
float tekananA;
float tekananB;
float tekananC;
float tekananD;
float LAT;
float LONG;
//float flat,flon;

void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
//  ss.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500); 
 }
 Serial.println("Connection Success !!");
 Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Serial.println("Firebase Success");
}

//void GPS()
//{
//  bool newData = false;
//  unsigned long chars;
//  unsigned short sentences, failed;
//
//  // For one second we parse GPS data and report some key values
//  for (unsigned long start = millis(); millis() - start < 1000;)
//  {
//    while (ss.available())
//    {
//      char c = ss.read();
//      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
//      if (gps.encode(c)) // Did a new valid sentence come in?
//        newData = true;
//    }
//  }
//
//  if (newData)
//  {
//    float flat, flon;
//    unsigned long age;
//    gps.f_get_position(&flat, &flon, &age);
//    Serial.print("LAT=");
//    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//    Serial.print(" LON=");
//    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    delay(5000);
//  }
//}

void loop() 
{
  //GPS();
  if(Serial.available() > 0){
    char x = Serial.read();
    if(x == 'a'){
    char data = Serial.readBytesUntil('\n', tempArr, 5); //Read the serial data and store it  
    tempArr[data] = '\0';
    temp = atof(tempArr); 
    Serial.print("Temperature = ");
    Serial.print(temp);
     Firebase.setFloat("roomTemperature", temp);
    } 
    else if(x == 'b'){
    char data = Serial.readBytesUntil('\n', humiArr, 5); //Read the serial data and store it  
    humiArr[data] = '\0';
    humi = atof(humiArr);
    Serial.print(" Humidity = ");
    Serial.print(humi); 
    Firebase.setFloat("roomHumidity", humi);
    } 
    else if(x == 'c'){
    char data = Serial.readBytesUntil('\n', tempBmpA, 5); //Read the serial data and store it  
    tempBmpA[data] = '\0';
    tempA = atof(tempBmpA);
    Serial.print(" Temperature A = ");
    Serial.print(tempA); 
     Firebase.setFloat("tempA", tempA);
    }  
    else if(x == 'd'){
    char data = Serial.readBytesUntil('\n', tempBmpB, 5); //Read the serial data and store it  
    tempBmpB[data] = '\0';
    tempB = atof(tempBmpB);
    Serial.print(" Temperature B = ");
    Serial.print(tempB); 
     Firebase.setFloat("tempB", tempB);
    } 
    else if(x == 'e'){
    char data = Serial.readBytesUntil('\n', tempBmpC, 5); //Read the serial data and store it  
    tempBmpC[data] = '\0';
    tempC = atof(tempBmpC);
    Serial.print(" Temperature C = ");
    Serial.print(tempC);
    Firebase.setFloat("tempC", tempC);
    } 
    else if(x == 'f'){
    char data = Serial.readBytesUntil('\n', tempBmpD, 5); //Read the serial data and store it  
    tempBmpD[data] = '\0';
    tempD = atof(tempBmpD);
    Serial.print(" Temperature D = ");
    Serial.print(tempD); 
    Firebase.setFloat("tempD", tempD);
    } 
    else if(x == 'g'){
    char data = Serial.readBytesUntil('\n', tekananBmpA, 5); //Read the serial data and store it  
    tekananBmpA[data] = '\0';
    tekananA = atof(tekananBmpA);
    Serial.print(" Tekanan A = ");
    Serial.print(tekananA);
     Firebase.setFloat("pressA", tekananA); 
    } 
    else if(x == 'h'){
    char data = Serial.readBytesUntil('\n', tekananBmpB, 5); //Read the serial data and store it  
    tekananBmpB[data] = '\0';
    tekananB = atof(tekananBmpB);
    Serial.print(" Tekanan B = ");
    Serial.print(tekananB);
     Firebase.setFloat("pressB", tekananB);
    } 
    else if(x == 'i'){
    char data = Serial.readBytesUntil('\n', tekananBmpC, 5); //Read the serial data and store it  
    tekananBmpC[data] = '\0';
    tekananC = atof(tekananBmpC);
    Serial.print(" Tekanan C = ");
    Serial.print(tekananC);
     Firebase.setFloat("pressC", tekananC);
    } 
    else if(x == 'j'){
    char data = Serial.readBytesUntil('\n', tekananBmpD, 5); //Read the serial data and store it  
    tekananBmpD[data] = '\0';
    tekananD = atof(tekananBmpD);
    Serial.print(" Tekanan D = ");
    Serial.println(tekananD); 
     Firebase.setFloat("pressD", tekananD);  
    }
    else if(x == 'k'){
    char data = Serial.readBytesUntil('\n', latitude, 5); //Read the serial data and store it  
    latitude[data] = '\0';
    LAT = atof(latitude);
    Serial.print(" LAT = ");
    Serial.println(LAT); 
    Firebase.setFloat("latitude", LAT);  
    }
    else if(x == 'l'){
    char data = Serial.readBytesUntil('\n', longitude, 5); //Read the serial data and store it  
    longitude[data] = '\0';
    LONG = atof(longitude);
    Serial.print(" LONG = ");
    Serial.println(LONG); 
    Firebase.setFloat("longitude", LONG);  
    }
  }
  if(Firebase.failed()){
  Serial.print("Firebase error: ");
  Serial.println(Firebase.error());
 }
// delay(1000);
}
