#define BLYNK_TEMPLATE_ID "TMPL6DU3WMK_3"
#define BLYNK_TEMPLATE_NAME "WOL"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WakeOnLan.h> 


char auth[] = "INSERT_BLYK_AUTH_TOKEN";

char ssid[] = "WIFI_SSID";
char pass[] = "SSID_PASSWORD";

WiFiUDP udp;
WakeOnLan WOL(udp);  

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
}

String macToString(byte mac[]) {
  char macStr[18] = {0};
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); 
  Serial.println("Clicked");
  if (pinValue == 1) {
    byte mac[] = {0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD};
    String macAddress = macToString(mac);
    WOL.sendMagicPacket(macAddress.c_str()); 
    Serial.println("Magic Packet sent to wake up the computer.");
  }
}

void loop() {
  Blynk.run();
}
