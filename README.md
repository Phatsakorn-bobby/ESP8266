#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
char auth[] = "IwGutuhywCvEbpOYsP20WeloiVu_Pwgh";
char ssid[] = "@Interface323";
char pass[] = "11223344";
BlynkTimer timer;
#define LED D4                  // LED on chip ESP8266
#define DHTPIN  D3              // pin of sensor connected to
#define DHTTYPE DHT11           // DHT22 if useDHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  dht.begin();
  timer.setInterval(2500, Sensor);
}
void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // run BlynkTimer
}
void Sensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    digitalWrite(LED, LOW);
    delay(1500);
    return;
  }
  Serial.print("Humidity is: "); Serial.println(h, 1);
  Serial.print("Temperature is: "); Serial.println(t, 1);
  digitalWrite(LED, HIGH);
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
