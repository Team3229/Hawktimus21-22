#ifndef CLIMB_H
#define CLIMB_H

#pragma once

#include <frc/DoubleSolenoid.h>
#include <frc/Timer.h>

#include "Debug.h"

class Climb {
  public:
    Climb();
    ~Climb();
    void ToggleClimb();

  private:
    
    frc::DoubleSolenoid * m_crabclaws;

    const int FORWARD_ID = 0;
    const int REVERSE_ID = 1;
};

#endif // CLIMB_H