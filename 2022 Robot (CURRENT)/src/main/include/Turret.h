#ifndef TURRET_H
#define TURRET_H

#pragma once

#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>

#include "Debug.h"
#include "Drivesystem.h" //for gyro


class Turret
{
    public:
        Turret();
        ~Turret();

        bool VisionTurn(double tX);
        void Turn(double setPower);
        void TurnLimelightRight(double setPower);
        void TurnLimelightLeft(double setPower);
        double GetAngle();
        void findTarget(double startPos);

        void turretDash();

        bool canReverse;
    private:

        ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_turretMotor;
        frc2::PIDController * m_turretPID;
        frc::AnalogEncoder * m_turEncoder;

        const int kTurretEncoderID = 0;
        frc::AnalogInput turretEncID{kTurretEncoderID}; //Analog Input
        const int kTurretMotorID = 12;

        //Turret turn rate limit
        const double kMAX_TURRET_POWER = .7;            //max turret turn power 20 percent
        const double kMAX_TURRET_CORRECT_POWER = .1;    //correct when turret goes beyond max range
        //Turret Limits
        const units::degree_t kMAX_RANGE = 180_deg;
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