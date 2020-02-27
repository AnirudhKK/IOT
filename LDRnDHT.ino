#include<DHT.h>
#include<FirebaseArduino.h>
#include<ESP8266WiFi.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASS ""
#define DHT_PIN 5
#define DHT_TYPE DHT11

int LDR_VALUE = 0;
float TEMPERATURE = 0;
float HUMIDITY = 0;

DHT dht(DHT_PIN, DHT_TYPE);
void setup(void)
{
  dht.begin();
  Serial.begin(9600);
  pinMode(A0, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("\nConnecting to AP");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected Successfully");
  Serial.print("\nIP: ");
  Serial.print(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LIGHT INTENSITY", 0);
  Firebase.setFloat("TEMPERATURE", 0);
  Firebase.setFloat("HUMIDITY", 0);
  delay(1000);
}

void loop()
{
  if(Firebase.failed())
  {
    Serial.print("\nConnection to Firebase lost!");
    Serial.print(Firebase.error());
    Serial.print("\nConnecting....");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    return;
  }
  LDR_VALUE = analogRead(A0);
  LDR_VALUE = map(LDR_VALUE,0,1023,0,100);
  HUMIDITY = dht.readHumidity();
  TEMPERATURE = dht.readTemperature();
  Firebase.setInt("LIGHT INTENSITY", LDR_VALUE);
  Firebase.setFloat("TEMPERATURE", TEMPERATURE);
  Firebase.setFloat("HUMIDITY", HUMIDITY);
  Serial.print("\nIntensity of Light: ");
  Serial.print(LDR_VALUE);
  Serial.print("\tTemperature: ");
  Serial.print(TEMPERATURE);
  Serial.print("\tHumidity: ");
  Serial.print(HUMIDITY);
  delay(1000);
}
