#ifndef PIVOT_H
#define PIVOT_H

#pragma once

#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>

#include "Debug.h"
#include "Drivesystem.h" //for gyro

class Pivot
{
    public:
        Pivot();
        ~Pivot();

    
        void Turn(double setPower);
        double GetAngle();

        bool canReverse;
    private:

        ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_pivotMotor;
        frc2::PIDController * m_pivotPID;
        frc::AnalogEncoder * m_pivotEncoder;

        const int kPivotEncoderID = 1;
        frc::AnalogInput pivotEncID{kPivotEncoderID}; //Analog Input
        const int kPivotMotorID = 8;

        //Turret turn rate limit
        const double kMAX_PIVOT_POWER = .2;            //max pivot turn power 2 percent
        const double kMAX_PIVOT_CORRECT_POWER = .1;    //correct when turret goes beyond max range
        //Turret Limits
        const units::degree_t kMAX_RANGE = 10_deg;
        const double kENCODER_RATIO = 73.17;
        const double kNOMINAL_TX_ERROR = 1;

        //PID
        const double kP = .05;
        const double kI = 0;
        const double kD = 0;

        //Turret find target
        bool reverseDirection;
};
#endif