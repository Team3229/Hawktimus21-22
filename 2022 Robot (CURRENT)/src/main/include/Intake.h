#ifndef INTAKE_H
#define INTAKE_H

#pragma once

//phoenix motor controller includes 
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "Debug.h"

class Intake
{
private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_intakeMotor;
    
    const int kIntakeMotorID = 11;
    const double INTAKE_POWER_IN = -.8; //70 percent power
    const double INTAKE_POWER_OUT = .8;
public:
    Intake();
    ~Intake();

    void runIntake();
    void reverseIntake();

    void stopIntake();
};







#endif