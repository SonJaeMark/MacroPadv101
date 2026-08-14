#include <Arduino.h>
#include "ota.h"

// Define Static IP Configuration
IPAddress local_IP(192, 168, 1, 200); 
IPAddress gateway(192, 168, 1, 1);    
IPAddress subnet(255, 255, 255, 0);    
IPAddress primaryDNS(8, 8, 8, 8);     
IPAddress secondaryDNS(8, 8, 4, 4);   

void begin(){
  // Initialize Hardware Serial
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Static IP configuration failed!");
  }
  
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.println("Wifi not connected..."); 
  }
  
  ArduinoOTA.setHostname("custom_keyboard");
  ArduinoOTA.setPassword("password");
  
  // OTA Callbacks via Serial
  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
    Serial.println("Start updating " + type); 
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate Complete!");
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.begin();
  
  Serial.println("\nOTA Ready!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void update(){
  ArduinoOTA.handle();
}
