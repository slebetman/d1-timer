#include <Servo.h>
#include "tick.h"
#include "ramp.h"
#include "delay.h"
#include "button.h"
#include "wifi.h"
#include "web.h"
#include "vars.h"

#define SERVO_MIN 1000
#define SERVO_MAX 2000

#define THROTTLE_OFF SERVO_MIN
#define THROTTLE_FULL SERVO_MAX

Servo throttle;
Tick timer;
Ramp rampUp(THROTTLE_OFF, THROTTLE_FULL);
Ramp rampDown(THROTTLE_FULL, THROTTLE_OFF);
Delay esc;
Delay pause;
Button button(D3);
Button cancelButton(D3);
Web server(80);
Wifi wifi;

void initialize () {
  Serial.println("init");
  throttle.writeMicroseconds(THROTTLE_OFF);
  button.init();
  cancelButton.init();
  throttle.writeMicroseconds(THROTTLE_OFF);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT_PULLUP);

  initVars();
  readVars();

  Serial.begin(115200);
  delay(10);

  throttle.attach(D4);
  esc.init(2.5);
  initialize();

  // wifi.initAP("DI_MINI_00001");
  wifi.initClient("ADLY_2.4", "afiqazim");
  server.init();
}

void loop()
{
  server.run();

  if (timer.tick()) {
    if (esc.wait()) { // wait for ESC to initialize
    }
    else {
      if (button.click()) {
        if (button.once) {
            Serial.println("Click!");
            rampUp.init( vars.rampUp );
            pause.init( vars.cruise );
            rampDown.init( vars.rampDown );
        }
        run();
      }
    }
  }
}

void run () {
  if (rampUp.run()) {
    throttle.writeMicroseconds(std::round(rampUp.value));
    if (cancelButton.click()) {
      end();
    }
  }
  else if (pause.wait()) {
    if (cancelButton.click()) {
      end();
    }
  }
  else if (rampDown.run()) {
    throttle.writeMicroseconds(std::round(rampDown.value));
    if (cancelButton.click()) {
      end();
    }
  }
  else
  {
    end();
  }
}


void end () {
  Serial.println("end");
  initialize();
}
