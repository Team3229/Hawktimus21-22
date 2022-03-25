/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>


// Our needed includes
#include <frc/XboxController.h>
#include <Math.h>
#include <frc/timer.h>
#include "ControllerInputs.h"

// Subsystem includes
#include "DriveSystem.h"
#include "Intake.h"
#include "Auto.h"
#include "Debug.h"
#include "Turret.h"
#include "Feeder.h"
#include "Shooter.h"
#include "Pivot.h"
#include "Limelight.h"
#include "Climb.h"


class Robot : public frc::TimedRobot 
{
 public:
   void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;


  void DisabledInit() override;
  void TestInit() override;
  void TestPeriodic() override;

  void ExecuteControls();



 private:
  
  std::string m_driveSelected;

   cmd * m_controllerInputs = new cmd; // universal controler variables 

  // Constants
  const int XBOX_USB_DRIVER_1 = 0;
  const int  XBOX_USB_DRIVER_2 = 1;
  const float DEAD_BAND = 0.15;
   const int kDRIVEDEADBAND = .15; 


   const float DRIVE_REGULAR = 0.7;
  const float DRIVE_SLOW = 0.4;
  	const float DRIVE_RAMP_TIME = 5.0;


     bool m_slowDriveMode = false;
     float drive_speed = DRIVE_REGULAR;


  // Controller variables
  int m_lastUsedSpeed = 2;


//mounting angle of the limelight from perfectly vertical 
  double limelightMountAngleDegrees = 35.0;

  //distance fromt he center of the limelight lens to the floor
  double limelightLensHeightInches = 36.5;

  double goalHeightInches = 104.0;

  double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
  double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);

  //calculate distance 
  //double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/tan(angleToGoalRadians);

  double angleForPivot;

  double SHOOTER_POWERONE;
  double SHOOTER_POWERTWO;

  
  


  double m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);      //Get horizontal off set from target
  double m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);      //Get vertical offset from target
  double m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);   //Get area of target on screen
  double m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);              //Get skew of target
  double m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

  double desiredPivotAngle;

  const float TARGET_RANGE = 4.0;

  Intake m_intake;
  IntakePivot m_intakePivot;
  Turret m_turret;
  Feeder m_feeder;
  UpperFeeder m_upperFeeder;
  Shooter m_shooter;
  Limelight m_limelight{};
  Pivot m_pivot; //make sure to add to autonomous
  Climb m_climb; 


  // Objects of subsystems
  DriveSystem chassis;

  Auto m_auto{&chassis,&m_intake,&m_intakePivot,&m_turret,&m_feeder,&m_upperFeeder,&m_shooter, &m_limelight,&m_pivot}; //populate these for testing make sure to change them! 
  const bool m_recordMode = true; // use this to force disable recording, useful at competitions
  
  frc::XboxController m_driveController {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController m_maniController {XBOX_USB_DRIVER_2}; //Manipulation driver

};