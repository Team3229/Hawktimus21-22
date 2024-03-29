//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#pragma once

#include <string>

#include <frc/TimedRobot.h>


// Our needed includes
#include <frc/XboxController.h>
#include <Math.h>
#include <frc/timer.h>
#include "ControllerInputs.h"
#include <AHRS.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Timer.h>

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
#include "LEDS.h"
#include "Camera.h"


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

  frc::Timer* timer;
  
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

     bool m_turretAutoLock = false; 


  // Controller variables
  int m_lastUsedSpeed = 2;
   
    AHRS * navxGyro; //navX seeking

  const float GOAL_ANGLE[5] = {0.01, 90.0, 180.0, 270.0, 359.9};
  const float ANGLE_THRESH = 8.0;
  bool CanTurn = false;

//mounting angle of the limelight from perfectly vertical 
  double limelightMountAngleDegrees = 35.0;

  //distance fromt he center of the limelight lens to the floor
  double limelightLensHeightInches = 36.5;

  double goalHeightInches = 104.0;

  double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
  double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);


  double angleForPivot;

  double SHOOTER_POWERONE;
  double SHOOTER_POWERTWO;

  
  


  double m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);      //Get horizontal off set from target
  double m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);      //Get vertical offset from target
  double m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);   //Get area of target on screen
  double m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);              //Get skew of target
  double m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

  double desiredPivotAngle;

  double desiredTurretAngle;

  const float TARGET_RANGE = 4.0;
  
  double desiredColor;

  Intake m_intake;
  IntakePivot m_intakePivot;
  Turret m_turret;
  Feeder m_feeder;
  UpperFeeder m_upperFeeder;
  Shooter m_shooter;
  Limelight m_limelight{};
  Pivot m_pivot; //make sure to add to autonomous
  Climb m_climb; 
  LEDS m_leds;
  Camera m_camera;



  // Objects of subsystems
  DriveSystem chassis;

  Auto m_auto{&chassis,&m_intake,&m_intakePivot,&m_turret,&m_feeder,&m_upperFeeder,&m_shooter, &m_limelight,&m_pivot,&m_leds}; //populate these for testing make sure to change them! 
  const bool m_recordMode = true; // use this to force disable recording, useful at competitions
  
  frc::XboxController m_driveController {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController m_maniController {XBOX_USB_DRIVER_2}; //Manipulation driver

   frc::SendableChooser<std::string> m_chooser;

  
  const std::string kLeftAuto = "2BallAutoLeft.aut";
  const std::string kCenterAuto = "3BallAutoCenter.aut";
  const std::string kRightAuto = "4BallAutoRight";
  const std::string kMainRightAuto = "4MainBallAutoRight";
  const std::string kMainOneRightAuto = "4MainOneBallAutoRight";
  const std::string kMainTwoRightAuto = "4MainTwoBallAutoRight";
  const std::string kMainThirdRightAuto = "4MainThirdBallAutoRight";
  const std::string kMainFourRightAuto = "4MainFourBallAutoRight";
  const std::string kTaxiAuto = "TaxiAuto";

  const std::string kAutoroutineDefault = kRightAuto;

  bool turretAlignedCLimb = false;

  bool areweusingIntake = false;

   double EXTRARPM = 25;
   
  frc::Timer* timeSinceLastShot;
  


};