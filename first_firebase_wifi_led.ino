#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>

//macros
#define WIFI_SSID "HUMPTY'S HUAWEI Y9"
#define WIFI_PASSWORD "hello1234"
#define FIREBASE_HOST "iot-project-faf5c.firebaseio.com/"
#define FIREBASE_AUTH "ID0guHGjIrXpuGeo17lYIJ4Oz18PJezrZE1z3781"
int LED=0; //to store variable from NodeMCU
void setup() 
{
 Serial.begin(9600);
 pinMode(16, OUTPUT);

  //connect to hotspot
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\nConnecting");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected!");
  //check IP
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  //Connect to firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //add a new int variable
  Firebase.setInt("IoT_LED",0);
}

void loop() 
{
  //to check if connected to firebase
  if(Firebase.failed())
  {
    Serial.print("\nConnection Lost!");
    Serial.print(Firebase.error());         //tells the type of error
    Serial.print("\nReconnecting..");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    return;
  }
  LED = Firebase.getInt("IoT_LED");
  if(LED == 0)
  {
      digitalWrite(16, LOW);
      Serial.print("\n LED IS OFF!");
  }
  else if(LED == 1)
  {
    digitalWrite(16, HIGH);
    Serial.print("\nLED IS ON");
  }
  delay(500);
}
