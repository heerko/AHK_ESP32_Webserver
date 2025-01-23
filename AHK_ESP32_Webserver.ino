#include <LittleFS.h>
#include <DNSServer.h>
#include "WebServerUtils.h"

char g_ssid[32] = "ESP_AP";  // set AP SSID. Can be overwritten by creating a file on LittleFS with extension .ssid

// Do not touch the following variables
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
DNSServer dnsServer;
const IPAddress localIP(4, 3, 2, 1);
const IPAddress gatewayIP(4, 3, 2, 1);
const IPAddress subnetMask(255, 255, 255, 0);
const char localIPURL[] = "http://4.3.2.1";

int touchPin = T3;  // corresponds to D15 on our modules

volatile bool touchDetected = false;  // Wordt door de ISR gezet
int threshold = 50;                   // Drempelwaarde voor touch

void T3getTouch() {
  touchDetected = true;
}

void customEndPoints() {
  // Berichtenopslag en -response
  server.on("/message", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (!LittleFS.exists("/message.txt")) {
      File file = LittleFS.open("/message.txt", "w");
      if (!file) {
        Serial.println("Failed to create messages.txt for writing");
        request->send(500, "text/plain", "Failed to create file for writing");
        return;
      }
      file.close();
    }

    if (request->hasParam("message", true)) {
      const AsyncWebParameter *message = request->getParam("message", true);
      File file = LittleFS.open("/message.txt", "a");
      file.print(message->value() + "\n");
      file.close();
    } else {
      Serial.println("No message param. Nothing to add.");
    }

    String response = "Messages:\n";
    File file = LittleFS.open("/message.txt", "r");
    while (file.available()) {
      response += file.readStringUntil('\n') + "\n";
    }
    file.close();
    request->send(200, "text/plain", response);
  });
}

void setup() {
  Serial.begin(115200);
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS");
    return;
  }

  touchAttachInterrupt(T3, T3getTouch, threshold);

  listFiles();
  getSSIDFromFS();
  startSoftAccessPoint(g_ssid, NULL, localIP, gatewayIP);
  setUpDNSServer(dnsServer, localIP);
  setUpWebserver(server, localIP);
  customEndPoints();
}

void loop() {
  if (touchDetected) {
    touchDetected = false;
    int touchValue = touchRead(T3);
    String message = String("{\"touch_status\":\"true\", \"touchValue\":") + touchValue + "}";
    ws.textAll(message);
    Serial.println(message);
  }

  dnsServer.processNextRequest();
  ws.cleanupClients();
}