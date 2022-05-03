//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#pragma once


#include <iostream>
#include <memory>
#include <Math.h>
#include "Debug.h"
#include "ControllerInputs.h"
#include <wpi/math>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <rev/CANSparkMax.h> 

#include <AHRS.h>
#include <frc/PowerDistribution.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>

class DriveSystem
{
public:

    DriveSystem();
    ~DriveSystem();

	
    void Drive(double Y, double X, double Z);
    void Stop();

	void AutoPlaybackSwitch();
	void TeleopModeSwitch();

private:
    //SparkMax's
	rev::CANSparkMax * leftLead; //Front left, leader
	rev::CANSparkMax * rightLead; //Front right, leader
	rev::CANSparkMax * leftFollower; //Back left, follower
	rev::CANSparkMax * rightFollower; //Back right, follower




	frc::DifferentialDrive * driveTrain; 

	  double kMaxOutput = .4, kMinOutput = -.4;

    
    //Constants for ports and unique id
	const int LEFT_LEAD_ID = 1;
	const int LEFT_FOLLOWER_ID = 2;
	const int RIGHT_LEAD_ID = 3;
	const int RIGHT_FOLLOWER_ID = 4;


	const float SMOOTH_TIME = 0.4;
	const float SAFETY_TIMEOUT = 2.0;

  const float DRIVE_REGULAR = 0.7;
  const float DRIVE_SLOW = 0.4;
  	const float DRIVE_RAMP_TIME = 5.0;



	
};


#endif // DRIVESYSTEM_H