#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <FastLED.h>

#include "myWifi.h"
#include "Matrix/Config.h"

#include "Core/Shapes.h"

unsigned long MainMillis = 100; // = 3 seconds
unsigned long requestDueTime;

void setup()
{
  Serial.begin(115200);
  
  MatrixConfig::begin();

  Wifi::begin();
}

Rectangle r1(5, 5, 4, 4, RED, 0.25, true, CLOCKWISE);
Rectangle r2(5, 5, 12, 4, GREEN, 0.25, true, COUNTERCLOCKWISE);
Rectangle r3(5, 5, 20, 4, BLUE, 0.25, true, CLOCKWISE);
Rectangle r4(5, 5, 28, 4, PURPLE, 0.0, false, CLOCKWISE);

Triangle t1(5, 4, 12, RED, 0.25, true, COUNTERCLOCKWISE);
Triangle t2(5, 12, 12, GREEN, 0.25, true, CLOCKWISE);
Triangle t3(5, 20, 12, BLUE, 0.25, true, CLOCKWISE);
Triangle t4(12, 28, 12, AQUA, 1.0, false, CLOCKWISE);

SinWave sw1(5, 5, 32, 64, 64, 4, PURPLE, true, FORWARD, 0.25);
SinWave sw2(10, 10, 32, 64, 64, 12, AQUA, true, FORWARD, 0.25);

void loop()
{
  if (millis() > requestDueTime)
  {
    dma_display->fillScreen(0);
    r1.draw();
    r2.draw();
    r3.draw();
    r4.draw();
    t1.draw();
    t2.draw();
    t3.draw();
    t4.draw();

    sw1.draw();
    sw2.draw();

    requestDueTime = millis() + MainMillis;
  }
}
