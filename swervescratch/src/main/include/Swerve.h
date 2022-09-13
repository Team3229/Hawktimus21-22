#ifndef SWERVE_H
#define SWERVE_H

#pragma once

#include <Math.h>
#include "ControllerInputs.h"
#include <wpi/math>
#include <rev/CANSparkMax.h>
#include <ctre/phoenix/sensors/CANCoder.h>

#include <AHRS.h>

class Swerve
{
public:

    Swerve();
    ~Swerve();

    void Stop();
    void Drive(double X, double Y, double Z);

private:
    //Sparks
    rev::CANSparkMax * frontLeftDrive;
    rev::CANSparkMax * frontLeftAngle;
    rev::CANSparkMax * backLeftDrive;
    rev::CANSparkMax * backLeftAngle;
    rev::CANSparkMax * frontRightDrive;
    rev::CANSparkMax * frontRightAngle;
    rev::CANSparkMax * backRightDrive;
    rev::CANSparkMax * backRightAngle;

    ctre::phoenix::sensors::CANCoder * frontLeftEncoder;
    ctre::phoenix::sensors::CANCoder * backLeftEncoder;
    ctre::phoenix::sensors::CANCoder * frontRightEncoder;
    ctre::phoenix::sensors::CANCoder * backRightEncoder;

    ctre::phoenix::sensors::CANCoder frontLeftEncoder{9};
    ctre::phoenix::sensors::CANCoder backLeftEncoder{10};
    ctre::phoenix::sensors::CANCoder frontRightEncoder{11};
    ctre::phoenix::sensors::CANCoder backRightEncoder{12};

    const int FRONT_LEFT_DRIVE_ID = 1;
    const int FRONT_LEFT_ANGLE_ID = 2;
    const int BACK_LEFT_DRIVE_ID = 3;
    const int BACK_LEFT_ANGLE_ID = 4;
    const int FRONT_RIGHT_DRIVE_ID = 5;
    const int FRONT_RIGHT_ANGLE_ID = 6;
    const int BACK_RIGHT_DRIVE_ID = 7;
    const int BACK_RIGHT_ANGLE_ID = 8;

    const double MAX_DRIVE_SPEED = 0.4;
    const double MAX_ANGLE_SPEED = 0.3;
    const double DRIVE_RAMP_TIME = 0.5;
    const double ANGLE_RAMP_TIME = 0.3;

    const double L = 20;
    const double W = 20;

    double r = sqrt((L * L) + (W * W));
};



#endif