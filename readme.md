![QR code to connect the AP](assets/APQR.png "Connect to the AP 'ultra local megabyte'")

# Ultra Local Megabyte a.k.a. Podmapping

In an age of endless feeds and algorithmic control, this workshop explores an alternative: ultra-local networks where stories exist only in the moment and in the place they were created. Using ESP32 modules, participants will craft site-specific podcasts—short audio pieces that can only be heard within a few-meter radius.

Each group will choose a space in or around the university, from hallways to copy rooms, and develop a three-minute sound piece that responds to its atmosphere and social context. Through recording, editing, and minimal web design, they will shape an intimate listening experience—one that resists the reach of global platforms and creates presence instead of distraction.

The workshop ends with a collective walk, moving between these temporary broadcast points, revealing voices that exist outside the algorithm.

## SoftAP on ESP32. 

Features:
- Websockets
- Serves files off LittleFS
- Optionally set SSID via file on LittleFS
- GPIO 15 / T3 is set up as a touch pin and touch is send over websocket

Usage
=====
Tested on ESP32 dev kit with ESP-WROOM-32. 
Settings:
- Board: ESP32 Dev Module.
- Partition scheme: No OTA 2mb/2mb.
- Leave the rest to the defaults.
- When working from the Arduino IDE use the [LittleFS upload tool](https://github.com/earlephilhower/arduino-littlefs-upload/releases) to upload the site to the ESP32.
Press [Ctrl] + [Shift] + [P] or on macOS, press [⌘] + [Shift] + [P] to open the Command Palette in the Arduino IDE, then "Upload LittleFS to Pico/ESP8266/ESP32".

Important! 
==========
Do not install Esp32 boards with version above 3.0.6, 
there seems to be a incompatibility between the newer versions 
of the ESP32 boards package and Asyncwebserver.

Dependencies
============
Install these libraries (Arduino IDE Library Manager or directly from the linked repositories) before building the sketch:
- ESPAsyncWebServer by ESP32Async — https://github.com/ESP32Async/ESPAsyncWebServer
- AsyncTCP by ESP32Async — https://github.com/ESP32Async/AsyncTCP
- ESPAsyncDNSServer by devyte — https://github.com/devyte/ESPAsyncDNSServer (Not in Arduino Library manager)
