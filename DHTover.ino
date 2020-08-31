
#include <TridentTD_LineNotify.h>
#define SSID        "CMTCEN"
#define PASSWORD    "123456789"
#define LINE_TOKEN  "Gs1AxDC82DR7NiKcV6bydKc5KHvvBRrHHDs8Qacgtz8"
#include "DHT.h"
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float C = 0 ;
float C1 = 1 ;
void setup() {
  dht.begin();
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  LINE.notify("myarduino.net");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("%  Temperature: "));
  Serial.print(t); 

  
  if (t > 32.30 && C == 0) {
    String LineText;
    String string1 = "อุณหภูมิ เกินกำหนด ";
    String string2 = " °C";
    LineText = string1 + t + string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);
    C = 1 ;
    C1 = 1 ;
  }    
  
  if(t < 32 && C1 == 1 ) {
    String LineText;
    String string1 = "อุณหภูมิ ลดลง ";
    String string2 = " °C";
    LineText = string1 + t + string2;
    Serial.print("Line ");
    Serial.println(LineText);
    LINE.notify(LineText);
   C1 = 0; 
   C = 0;
}
delay(100);
}
