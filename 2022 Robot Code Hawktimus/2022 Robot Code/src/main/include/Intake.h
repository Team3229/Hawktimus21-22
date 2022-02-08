#ifndef INTAKE_H
#define INTAKE_H

#pragma once

#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Timer.h>

#include <rev/CANSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

class Intake
{
private:
    frc::Compressor * m_compressor;
    frc::DoubleSolenoid * m_intakeSolenoid;

    
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_intakeMotor1; 

    const int kIntakeMotorID = 9;
    const int kIntakePivotID = 10;
    
    const int kCompressorPCMID = 0; //uodate these
    const int kForwardIntakeID = 2; //update these
    const int kReverseIntakeID = 3; //update these
    
    bool intakeExtended = false;
    const double INTAKE_POWER_IN = -.7;
    const double INTAKE_POWER_OUT = .7;

    frc::DoubleSolenoid * m_intakepivot;
    
    const int FORWARD_ID = 0;
    const int REVERSE_ID = 1;

public:
    Intake();
    ~Intake();

    void controlComp();
    void extendIntake();
    void retractIntake();

    void runIntake();
    void reverseIntake();

    void forceRunIntake();
    void stopIntake();
};

#endif