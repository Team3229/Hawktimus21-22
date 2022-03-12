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


#include <frc/controller/PIDController.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/drive/DifferentialDrive.h>

class DriveSystem
{
public:

    DriveSystem();
    ~DriveSystem();
	
  frc::Rotation2d GetAngle() const;
  frc::DifferentialDriveWheelSpeeds GetSpeeds() const;
  frc::Pose2d GetPose() const;
  frc::DifferentialDriveKinematics GetKinematics() const;

  void SetPose(frc::Pose2d pose);
  void SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds);
  void Drive(units::meters_per_second_t speed, units::radians_per_second_t rot);
  void UpdateOdometry();
  void StopMotor();

  void drivetrainDash();

  //change these speeds for testing

  static constexpr units::meters_per_second_t kMaxSpeed = 4.0_mps;  //max speed it is allowed to calculate
  static constexpr units::radians_per_second_t kMaxAngularSpeed{wpi::math::pi*2};  // 1/2 rotation per second
  static constexpr units::meters_per_second_t kSlowMaxSpeed = 2.0_mps;

	/*
    void Drive(double& Y, double& X, double& Z);
    void Stop();

	void AutoPlaybackSwitch();
	void TeleopModeSwitch();

*/
private:
    //SparkMax's
	rev::CANSparkMax * leftLead; //Front left, leader
	rev::CANSparkMax * rightLead; //Front right, leader
	rev::CANSparkMax * leftFollower; //Back left, follower
	rev::CANSparkMax * rightFollower; //Back right, follower


	frc::DifferentialDrive * driveTrain; 

	  //double kMaxOutput = .4, kMinOutput = -.4;

    
    //Constants for ports and unique id
	const int LEFT_LEAD_ID = 1;
	const int LEFT_FOLLOWER_ID = 2;
	const int RIGHT_LEAD_ID = 3;
	const int RIGHT_FOLLOWER_ID = 4;

  
	const float SMOOTH_TIME = 0.4;
	const float SAFETY_TIMEOUT = 2.0;

static constexpr units::meter_t kTrackWidth = 27_in; //distance between left wheels to the right wheels
  static constexpr double kWheelRadius = units::meter_t(6_in/2).to<double>();  // 6 inch diameter
  static constexpr int kEncToWheel = 8.68; // _ encoder rotation = 1 wheel rotation

  double m_leftSetpoint, m_rightSetpoint;
  double m_angleSetpoint;
  double m_leftVelocity;
  double m_rightVelocity;
  const float MAX_POWER = 1.0;
  const float DRIVE_RAMP_TIME = 0.7;

  units::meter_t m_leftPosition,m_rightPosition;
  AHRS * navXGyro;
  
  //PID Controllers, only kP should be necessary, lower it reduces accleration
  frc2::PIDController m_leftPIDController{.15, 0.0, 0.0};
  frc2::PIDController m_rightPIDController{.15, 0.0, 0.0};

  frc::DifferentialDriveKinematics m_kinematics{kTrackWidth};
  frc::DifferentialDriveOdometry m_odometry{frc::Rotation2d{0_deg}};


	
};

#endif // DRIVESYSTEM_H