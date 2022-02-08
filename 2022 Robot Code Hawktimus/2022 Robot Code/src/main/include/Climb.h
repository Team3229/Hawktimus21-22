#ifndef CLIMB_H
#define CLIMB_H

#pragma once

#include <frc/Timer.h>
#include <rev/CANSparkMax.h>
#include "Debug.h"

class Climb {
  public:
    Climb();
    ~Climb();
    void ClimbT();

  private:
    rev:: CANSparkMax * m_climber; //middle NEO
    rev:: CANSparkMax * l_climber; //left NEO
    rev:: CANSparkMax * r_climber; //right NEO

    const int mClimbID = 1; //change these with actual port valies!! 
    const int lClimbID = 2;
    const int rClimbID = 3;
};

#endif // CLIMB_H