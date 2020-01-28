#ifndef ENCODER_DATA_H
#define ENCODER_DATA_H

#include "Arduino.h"

class EncoderData {
  private:

  // sensor pin numbers
  short pinA, pinB;
  // is the output currently high?
  bool aNew, bNew;
  // was the output previously high?
  bool aPrev, bPrev;
  // number of counter-clockwise quarter rotations from initial position
  int ticks, ticksPrev;
  // current time and time at last velocity sample
  int currTime, prevTime;
  // most recent velocity, measured in cycles per second
  double velo;
  
  void initEncoder();
  void readEncoder();
  bool clockwise();
  bool counterClockwise();
  void updateCycles();
  void calcVelo();

  public:

  EncoderData(short a, short b);
  double getAngle();
  double getVelo();
  void updateEncoder();
};

#endif
