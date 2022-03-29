
#ifndef LEDSUBSYSTEM
#define LEDSUBSYSTEM_H

#pragma once

#include <frc/motorcontrol/Spark.h>


class LEDS
{

 public:

  LEDS();
  ~LEDS();

  void ChangeLEDColors(double setColor);

 private:

    frc::Spark * BlinkLEDDriver;

    const float BlinkinLEDDriver_PWM = 0;
  
   
};

#endif