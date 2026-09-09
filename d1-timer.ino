#include <EEPROM.h>
#include "tick.h"
#include "wifi.h"
#include "web.h"
#include "vars.h"

#define BLINK_TIME 1000
int count = BLINK_TIME;
unsigned char on = 0;

Tick timer;
Web server(80);
Wifi wifi;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  initVars();
  readVars();

  Serial.begin(115200);
  delay(10);

  wifi.initAP("DI_MINI_00001");
  // wifi.initClient("ADLY_2.4", "afiqazim");

  server.init();
}

void loop() {
  server.run();

  if (timer.tick()) {
    if (count-- <= 0) {
      count = BLINK_TIME;
      if (on) {
        on = 0;
        digitalWrite(LED_BUILTIN, LOW);
      }
      else {
        on = 1;
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }
  }
}
