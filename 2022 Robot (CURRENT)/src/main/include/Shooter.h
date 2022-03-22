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
    
     const int kUpperFWOneID = 5; 
    const int kUpperFWTwoID = 6;  

    rev::CANSparkMax flyWheelUpperOne{kUpperFWOneID, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax flyWheelUpperTwo{kUpperFWTwoID, rev::CANSparkMax::MotorType::kBrushless};


    //flyWheelUpperOne = new rev::CANSparkMax(kUpperFWOneID,rev::CANSparkMax::MotorType::kBrushless);
    //flyWheelUpperTwo = new rev::CANSparkMax(kUpperFWTwoID,rev::CANSparkMax::MotorType::kBrushless);


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

        double SetPointOne;
        double SetPointTwo;

        const double MaxRPM = 5676; 


         rev::SparkMaxPIDController m_pidControllerShooterOne = flyWheelUpperOne.GetPIDController();
         rev::SparkMaxPIDController m_pidControllerShooterTwo = flyWheelUpperTwo.GetPIDController();
        
    //restore for facotry defaults



        //easier ways to grab values for calculations

/*
        struct shooterValues
        {

            double power;
            double rpm;
            double pivot;

        };

            int MAX_DISTANCE = 20; // in tens of inches 
    
            int shooterValue = shooterValues[MAX_DISTANCE]; 

            shooterValues[0] = {0.3, 2500, 21659}; 
            shooterValues[1] = {0.3, 2500, 21659}; 
            shooterValues[2] = {0.3, 2500, 21659}; 
            shooterValues[3] = {0.4, 3500, 41219}; 
            shooterValues[4] = {0.4, 3500, 41219}; 
            shooterValues[5] = {0.5, 3800, 41219}; 
            shooterValues[6] = {0.5, 3800, 41219}; 
            shooterValues[7] = {0.6, 4000, 41219}; 
            shooterValues[8] = {0.6, 4000, 41219}; 
            shooterValues[9] = {0.6, 4000, 41219}; 
            shooterValues[10] = {0.7, 4200, 41219}; 
            shooterValues[11] = {0.7, 4200, 41219}; 
            shooterValues[12] = {0.7, 4500, 41219}; 
            shooterValues[13] = {0.7, 4500, 41219}; 
            shooterValues[14] = {0.8, 5000, 41219}; 
            shooterValues[15] = {0.8, 5000, 41219}; 
            shooterValues[16] = {0.8, 5000, 41219}; 
            shooterValues[17] = {0.9, 5500, 41219}; 
            shooterValues[18] = {0.9, 5500, 41219}; 
            shooterValues[19] = {1.0, 6000, 41219};
*/


};
#endif