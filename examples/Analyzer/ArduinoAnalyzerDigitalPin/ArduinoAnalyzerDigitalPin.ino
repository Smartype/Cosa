/**
 * @file ArduinoAnalyzerDigitalPin.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2015, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @section Description
 * Logic Analyzer based performance measurement of Arduino Digital
 * Pin. Trigger on rising edge transition on ledPin. Measurements are
 * for Arduino Uno/Nano.
 *
 * This file is part of the Arduino Che Cosa project.
 */

const uint8_t outPin = 8;
const uint8_t dataPin = 9;
const uint8_t clockPin = 10;
const uint8_t ledPin = 13;
uint8_t data;

void setup()
{
  // Initial pin mode and state
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, 0);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, 0);
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, 0);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, 0);

  // Initial data
  data = random(255);

  // Allow some time to start logic analyzer trigger
  delay(2000);

  // Trigger sampling
  digitalWrite(ledPin, 1);
  digitalWrite(ledPin, 0);
  delayMicroseconds(50);
  digitalWrite(ledPin, 1);
  digitalWrite(ledPin, 0);
  delayMicroseconds(50);
}

void loop()
{
  // Measure overhead of test case marker;
  // 5.125 us per pulse
  digitalWrite(ledPin, 1);
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // Measure four pulses;
  // 45.6250 us (10.125 us per pulse)
  digitalWrite(ledPin, 1);
  digitalWrite(outPin, 1);
  digitalWrite(outPin, 0);
  digitalWrite(outPin, 1);
  digitalWrite(outPin, 0);
  digitalWrite(outPin, 1);
  digitalWrite(outPin, 0);
  digitalWrite(outPin, 1);
  digitalWrite(outPin, 0);
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // Measure clocked serial transfer of a byte;
  // 167.5625 us (20.30 us per bit)
  digitalWrite(ledPin, 1);
  for(uint8_t bit = 0x80; bit != 0; bit >>= 1) {
    digitalWrite(dataPin, data & bit);
    digitalWrite(clockPin, 1);
    digitalWrite(clockPin, 0);
  }
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // Measure clocked serial transfer of a byte with const value;
  // 169.370 us (21.11 us per bit)
  digitalWrite(ledPin, 1);
  for(uint8_t bit = 0x80; bit != 0; bit >>= 1) {
    if (data & bit) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
    digitalWrite(clockPin, 1);
    digitalWrite(clockPin, 0);
  }
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // Measure clocked serial transfer of a byte fully unrolled;
  // 165.0 us (19.98 us per bit)
  digitalWrite(ledPin, 1);
  digitalWrite(dataPin, data & 0x80);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x40);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x20);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x10);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x08);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x04);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x02);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(dataPin, data & 0x01);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // Measure clocked serial transfer of a byte with const value,
  // fully unrolled;
  // 172.9375 us (20.98 us per bit)
  digitalWrite(ledPin, 1);
  if (data & 0x80) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x40) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x20) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x10) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x08) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x04) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x02) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  if (data & 0x01) digitalWrite(dataPin, 1); else digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 1);
  digitalWrite(clockPin, 0);
  digitalWrite(ledPin, 0);
  delayMicroseconds(10);

  // New data value
  data = random(255);
  delay(1000);
}

