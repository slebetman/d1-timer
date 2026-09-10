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

#define BLINK_TIME 1000
int count = BLINK_TIME;
unsigned char on = 0;

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

void initialize()
{
  throttle.writeMicroseconds(THROTTLE_OFF);
  button.init();
  cancelButton.init();
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT_PULLUP);

  initVars();
  readVars();

  throttle.attach(D4);
  initialize();

  Serial.begin(115200);
  delay(10);

  // wifi.initAP("DI_MINI_00001");
  wifi.initClient("ADLY_2.4", "afiqazim");

  server.init();
}

void loop()
{
  server.run();

  if (timer.tick())
  {
    if (esc.wait())
    { // wait for ESC to initialize
    }
    else
    {
      if (count-- <= 0)
      {
        count = BLINK_TIME;
        if (on)
        {
          on = 0;
          digitalWrite(LED_BUILTIN, LOW);
        }
        else
        {
          on = 1;
          digitalWrite(LED_BUILTIN, HIGH);
        }
      }

      if (button.click())
      {
        if (button.once)
        {
          rampUp.init(vars.rampUp);
          pause.init(vars.cruise);
          rampDown.init(vars.rampDown);
        }
        run();
      }
    }
  }
}

void run()
{
  if (rampUp.run())
  {
    throttle.writeMicroseconds(rampUp.value);
  }
  else if (pause.wait())
  {
    if (cancelButton.click())
    {
      end();
    }
  }
  else if (rampDown.run())
  {
    throttle.writeMicroseconds(rampDown.value);
    if (cancelButton.click())
    {
      end();
    }
  }
  else
  {
    end();
  }
}

void end()
{
  initialize();
}
