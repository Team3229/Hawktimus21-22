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
    void shooterDash();

      //these needs to be variable speeds for limelight
   double SHOOTER_POWERONE; //speed works very good at 50 
   double SHOOTER_POWERTWO;
};

#endif