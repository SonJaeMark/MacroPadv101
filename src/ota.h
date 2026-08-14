#pragma once
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define SECRET_SSID "Connecting.."
#define SECRET_PASS "L@nuz0_F@mily"

void begin();
void update();
