#ifndef INTAKE_H
#define INTAKE_H

#pragma once

//phoenix motor controller includes 
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "Debug.h"
#include <rev/CANSparkMax.h>

class Intake
{
private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_intakeMotor;
    rev::CANSparkMax * m_intakePivot;

    
    const int kIntakeMotorID = 7;
    const int kIntakePivotMotorID = 15;

    const double INTAKE_PIVOT_POWER_IN = .15;
    const double INTAKE_PIVOT_POWER_OUT = -.15;

    const double INTAKE_POWER_IN = .7; //80 percent power
    const double INTAKE_POWER_OUT = -.7;
public:
    Intake();
    ~Intake();

    void runIntake();
    void reverseIntake();

    void runIntakePivot();
    void reverseIntakePivot();

    void stopIntake();
    void stopPivot();
};







#endif