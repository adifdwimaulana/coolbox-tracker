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

#define WIFI_SSID "WM1312"
#define WIFI_PASSWORD "gatgat2008"

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

void loop() 
{
  //GPS();
  if(Serial.available() > 0){
    char x = Serial.read();
    if(x == 'a'){
    char data = Serial.readBytesUntil('\n', tempArr, 9); //Read the serial data and store it  
    tempArr[data] = '\0';
    temp = atof(tempArr); 
    Serial.print("Temperature = ");
    Serial.print(temp);
     Firebase.setFloat("data/roomTemperature", temp);
    } 
    else if(x == 'b'){
    char data = Serial.readBytesUntil('\n', humiArr, 9); //Read the serial data and store it  
    humiArr[data] = '\0';
    humi = atof(humiArr);
    Serial.print(" Humidity = ");
    Serial.print(humi); 
    Firebase.setFloat("data/roomHumidity", humi);
    } 
    else if(x == 'c'){
    char data = Serial.readBytesUntil('\n', tempBmpA, 9); //Read the serial data and store it  
    tempBmpA[data] = '\0';
    tempA = atof(tempBmpA);
    Serial.print(" Temperature A = ");
    Serial.print(tempA); 
     Firebase.setFloat("data/tempA", tempA);
    }  
    else if(x == 'd'){
    char data = Serial.readBytesUntil('\n', tempBmpB, 9); //Read the serial data and store it  
    tempBmpB[data] = '\0';
    tempB = atof(tempBmpB);
    Serial.print(" Temperature B = ");
    Serial.print(tempB); 
     Firebase.setFloat("data/tempB", tempB);
    } 
    else if(x == 'e'){
    char data = Serial.readBytesUntil('\n', tempBmpC, 9); //Read the serial data and store it  
    tempBmpC[data] = '\0';
    tempC = atof(tempBmpC);
    Serial.print(" Temperature C = ");
    Serial.print(tempC);
    Firebase.setFloat("data/tempC", tempC);
    } 
    else if(x == 'f'){
    char data = Serial.readBytesUntil('\n', tempBmpD, 9); //Read the serial data and store it  
    tempBmpD[data] = '\0';
    tempD = atof(tempBmpD);
    Serial.print(" Temperature D = ");
    Serial.print(tempD); 
    Firebase.setFloat("data/tempD", tempD);
    } 
    else if(x == 'g'){
    char data = Serial.readBytesUntil('\n', tekananBmpA, 9); //Read the serial data and store it  
    tekananBmpA[data] = '\0';
    tekananA = atof(tekananBmpA);
    Serial.print(" Tekanan A = ");
    Serial.print(tekananA);
     Firebase.setFloat("data/pressA", tekananA); 
    } 
    else if(x == 'h'){
    char data = Serial.readBytesUntil('\n', tekananBmpB, 9); //Read the serial data and store it  
    tekananBmpB[data] = '\0';
    tekananB = atof(tekananBmpB);
    Serial.print(" Tekanan B = ");
    Serial.print(tekananB);
     Firebase.setFloat("data/pressB", tekananB);
    } 
    else if(x == 'i'){
    char data = Serial.readBytesUntil('\n', tekananBmpC, 9); //Read the serial data and store it  
    tekananBmpC[data] = '\0';
    tekananC = atof(tekananBmpC);
    Serial.print(" Tekanan C = ");
    Serial.print(tekananC);
     Firebase.setFloat("data/pressC", tekananC);
    } 
    else if(x == 'j'){
    char data = Serial.readBytesUntil('\n', tekananBmpD, 9); //Read the serial data and store it  
    tekananBmpD[data] = '\0';
    tekananD = atof(tekananBmpD);
    Serial.print(" Tekanan D = ");
    Serial.println(tekananD); 
     Firebase.setFloat("data/pressD", tekananD);  
    }
    else if(x == 'k'){
    char data = Serial.readBytesUntil('\n', latitude, 9); //Read the serial data and store it  
    latitude[data] = '\0';
    LAT = atof(latitude);
    Serial.print(" LAT = ");
    Serial.println(LAT, 6); 
    Firebase.setFloat("location/latitude", LAT);  
    }
    else if(x == 'l'){
    char data = Serial.readBytesUntil('\n', longitude, 9); //Read the serial data and store it  
    longitude[data] = '\0';
    LONG = atof(longitude);
    Serial.print(" LONG = ");
    Serial.println(LONG, 6); 
    Firebase.setFloat("location/longitude", LONG);  
    }
  }
  if(Firebase.failed()){
  Serial.print("Firebase error: ");
  Serial.println(Firebase.error());
 }
// delay(1000);
}
