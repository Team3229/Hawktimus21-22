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
  
    const int kIntakeMotorID = 7;
    
    const double INTAKE_POWER_IN = .8; //80 percent power
    const double INTAKE_POWER_OUT = -.8;
public:
    Intake();
    ~Intake();

    void runIntake();
    void reverseIntake();

    void stopIntake();

};

class IntakePivot
{

private:
    rev::CANSparkMax * m_intakePivot;

    const int kIntakePivotMotorID = 15;

    const double INTAKE_PIVOT_POWER_IN = .70;
    const double INTAKE_PIVOT_POWER_OUT = -.70;

public:
   

    IntakePivot();
    ~IntakePivot();

    void runIntakePivot();
    void reverseIntakePivot();

    void stopPivot();

};


#endif