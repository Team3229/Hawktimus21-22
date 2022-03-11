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

    const float SHOOTER_POWERONE = .55;
    const float SHOOTER_POWERTWO = -.55; //manual shooter power 

    double SHOOTER_POWERONEAUTO;
    double SHOOTER_POWERTWOAUTO; //shooter global variable for auto turret 

};

#endif