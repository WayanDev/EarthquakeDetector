#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <HCSR04.h>

//firebase
#define FIREBASE_HOST "esiot2022-98371-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Y8uURyFwNYxOorTo3rinN4jj9MzJW63kmXcqn5Aj"
#define WIFI_SSID "The_ganteng_max"
#define WIFI_PASSWORD "jagakebersihan12345"

FirebaseData fbdo; //fbdo adalah variabel. 

#define LED D7
#define  pinBuzzer D1
#define  pinSensorGempa D2 // mendefinisikan pin yang digunakan adalah pin Digital
int NilaiDigital;

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".......");
    delay(500);
  }
  Serial.println();
  Serial.print("konek");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  pinMode(pinSensorGempa, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  NilaiDigital = digitalRead(pinSensorGempa); // membaca nilai digital
  Serial.print("Nilai Output Digital = ");
  Serial.println(NilaiDigital);

  //Proses Kirim Data
  Firebase.setFloat(fbdo, "Nilai_Getar", NilaiDigital);
  
  if(NilaiDigital==1){
    Firebase.setString(fbdo, "Pesan", "Ada Getaran");
    digitalWrite(LED, HIGH);
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
  } else {
    Firebase.setString(fbdo, "Pesan", "Aman");
    digitalWrite(pinBuzzer, LOW);
    digitalWrite(LED, LOW);
  }
}
