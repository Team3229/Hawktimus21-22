// Author: Team 3229 Programming Subteam

#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

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
    void Drive(double& Y, double& X, double& Z);
    void Stop();
    void ChangeSpeed(int choice);

	/*frc::SpeedControllerGroup m_left{leftLead, leftFollower};
	frc::SpeedControllerGroup m_right{rightLead, rightFollower};

	frc::DifferentialDrive m_drive{m_right, m_left}; */

private:
    //SparkMax's
	rev::CANSparkMax * leftLead; //Front left, leader
	rev::CANSparkMax * rightLead; //Front right, leader
	rev::CANSparkMax * leftFollower; //Back left, follower
	rev::CANSparkMax * rightFollower; //Back right, follower

	frc::DifferentialDrive * driveTrain; 

    
    //Constants for ports and unique id
	const int LEFT_LEAD_ID = 1;
	const int LEFT_FOLLOWER_ID = 2;
	const int RIGHT_LEAD_ID = 3;
	const int RIGHT_FOLLOWER_ID = 4;

    //Changable powers
	const float MAX_OUTPUT = 0.7;
	const float LOW_OUTPUT = 0.4;
	const float HIGH_OUTPUT = 1.0;
  	const float DRIVE_RAMP_TIME = 0.7;

	const float SMOOTH_TIME = 0.4;
	const float SAFETY_TIMEOUT = 2.0;

	//Turning powers
	double m_leftAdjPow = -0.3; //turn
    double m_rightAdjPow = 0.3; //turn
	double m_stillPow = 0.0;
};

#endif // DRIVESYSTEM_H