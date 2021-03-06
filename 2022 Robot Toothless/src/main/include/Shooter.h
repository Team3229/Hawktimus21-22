//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#ifndef SHOOTER_H
#define SHOOTER_H

#pragma once

#include <rev/CANSparkMax.h>


#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/controller/PIDController.h>
#include <frc/Servo.h>

#include "Debug.h"
#include "Shooter.h"

class Shooter
{
    private:
    
     const int kUpperFWOneID = 5; 
    const int kUpperFWTwoID = 6;  

    rev::CANSparkMax flyWheelUpperOne{kUpperFWOneID, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax flyWheelUpperTwo{kUpperFWTwoID, rev::CANSparkMax::MotorType::kBrushless};


 

        rev::SparkMaxRelativeEncoder m_encoderShooterOne = flyWheelUpperOne.GetEncoder();
        rev::SparkMaxRelativeEncoder m_encoderShooterTwo = flyWheelUpperTwo.GetEncoder();



    public:
        Shooter();
        ~Shooter();


        void runShooter();
        void stopShooter();
        void runShooterAuto(double RPM1, double RPM2);
        void shooterDash();

        double getRPMS();

    
        double SHOOTER_POWERONE;
        double SHOOTER_POWERTWO; //manual shooter power 

        double SHOOTER_POWERONEAUTO;
        double SHOOTER_POWERTWOAUTO; //shooter global variable for auto turret 

        //PID Coeefificents
        double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;

        const double MaxRPM = 5676; 


         rev::SparkMaxPIDController m_pidControllerShooterOne = flyWheelUpperOne.GetPIDController();
         rev::SparkMaxPIDController m_pidControllerShooterTwo = flyWheelUpperTwo.GetPIDController();
        


};
#endif