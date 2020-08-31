#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "IwGutuhywCvEbpOYsP20WeloiVu_Pwgh";
char ssid[] = "@Interface323";
char pass[] = "11223344";

int S = D0;
void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com" ,8080);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
}
void loop()
{
  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
}
