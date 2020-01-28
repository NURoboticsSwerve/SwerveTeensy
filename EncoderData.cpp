#include "EncoderData.h"

EncoderData::EncoderData(short a, short b) {
  pinA = a;
  pinB = b;
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  initEncoder();
}

double EncoderData::getAngle() {
  return 0.0;
}

double EncoderData::getVelo() {
  return velo;
}

void EncoderData::initEncoder() {
  ticks = 0;
  ticksPrev = 0;
  currTime = micros();
  prevTime = currTime;
  aPrev = digitalRead(pinA);
  bPrev = digitalRead(pinB);
}
void EncoderData::readEncoder() {
  aNew = digitalRead(pinA);
  bNew = digitalRead(pinB);
}

bool EncoderData::clockwise() {
  return (!aPrev && aNew && !bPrev)
      || (aPrev && !bPrev && bNew)
      || (aPrev && !aNew && bPrev)
      || (!aPrev && bPrev && !bNew);
}

bool EncoderData::counterClockwise() {
  return (!aPrev && aNew && bPrev)
      || (!aPrev && !bPrev && bNew)
      || (aPrev && !aNew && !bPrev)
      || (aPrev && bPrev && !bNew);
}

void EncoderData::updateCycles() {
  if (clockwise()) {
    ticks--;
  } else if (counterClockwise()) {
    ticks++;
  }
  aPrev = aNew;
  bPrev = bNew;
}

void EncoderData::calcVelo() {
  velo = 250000.0 * (ticks - ticksPrev) / (currTime - prevTime);
  prevTime = currTime;
  ticksPrev = ticks;
}

void EncoderData::updateEncoder() {
  currTime = micros();
  readEncoder();
  updateCycles();
  if (currTime - prevTime > 20000) {
    calcVelo();
    Serial.printf("ticks: %d\tcycles/sec: %lfHz\n", ticks, velo);
  }
}
