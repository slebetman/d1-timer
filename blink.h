#ifndef BLINK
#define BLINK

class Blink
{
private:
  int count;
  int interval;
  byte state;
  uint8_t pin;

public:
  Blink(uint8_t pin, int interval)
  {
    this->interval = interval;
    this->pin = pin;
    this->state = 0;
    stop();
  }

  void blink()
  {
    count++;

    if (count < interval)
    {
      if (state != 1) {
        state = 1;
        digitalWrite(pin, LOW);
      }
    }
    else
    {
      if (count > (interval * 2))
      {
        count = 0;
      }
      if (state != 0) {
        state = 0;
        digitalWrite(pin, HIGH);
      }
    }
  }

  void stop()
  {
    if (count != 0)
    {
      count = 0;
      if (state != 0) {
        state = 0;
        digitalWrite(pin, HIGH);
      }
    }
  }
};

#endif