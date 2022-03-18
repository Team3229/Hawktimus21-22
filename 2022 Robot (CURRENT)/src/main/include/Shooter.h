#ifndef SHOOTER_H
#define SHOOTER_H

#pragma once

#include <rev/CANSparkMax.h>


#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/controller/PIDController.h>
#include <frc/Servo.h>

#include "Debug.h"

class Shooter
{
private:
   

    rev::CANSparkMax * flyWheelUpperOne;
    rev::CANSparkMax * flyWheelUpperTwo;

    

    const int kUpperFWOneID = 5; 
    const int kUpperFWTwoID = 6;  

public:
    Shooter();
    ~Shooter();


    void runShooter();
    void stopShooter();
    void runShooterAuto();
    void shooterDash();

    double SHOOTER_POWERONE;
    double SHOOTER_POWERTWO; //manual shooter power 

    double SHOOTER_POWERONEAUTO;
    double SHOOTER_POWERTWOAUTO; //shooter global variable for auto turret 

    //PID Coeefificents
    double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;

    double SetPointOne = 0.0;
    double SetPointTwo = 0.0;

    const double MaxRPM = 5676; 


  

};

#endif