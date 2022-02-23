// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  m_auto.SetupPlayback();
}

void Robot::AutonomousPeriodic() 
{
  m_auto.ReadFile(m_controllerInputs);
  ExecuteControls();
}

void Robot::TeleopInit() 
{
  m_auto.CloseFile();
}

void Robot::TeleopPeriodic() 
{
  // Populate controller struct
  m_controllerInputs->drive_rightY = m_driveController.GetRightY();
  m_controllerInputs->drive_rightX = m_driveController.GetRightX();
  m_controllerInputs->drive_leftY = m_driveController.GetLeftY();
  m_controllerInputs->drive_leftX = m_driveController.GetLeftX();
  m_controllerInputs->drive_AButton = m_driveController.GetAButton();
  m_controllerInputs->drive_BButton = m_driveController.GetBButton();
  m_controllerInputs->drive_XButton = m_driveController.GetXButton();
  m_controllerInputs->drive_YButton = m_driveController.GetYButton();
  m_controllerInputs->drive_RightBumper =
      m_driveController.GetRightBumper();
  m_controllerInputs->drive_LeftBumper =
      m_driveController.GetLeftBumper();
  m_controllerInputs->drive_RightTriggerAxis =
      m_driveController.GetRightTriggerAxis();
  m_controllerInputs->drive_LeftTriggerAxis =
      m_driveController.GetLeftTriggerAxis();
  m_controllerInputs->drive_POV = m_driveController.GetPOV();
  m_controllerInputs->mani_rightY = m_maniController.GetRightY();
  m_controllerInputs->mani_rightX = m_maniController.GetRightX();
  m_controllerInputs->mani_leftY = m_maniController.GetLeftY();
  m_controllerInputs->mani_leftX = m_maniController.GetLeftX();
  m_controllerInputs->mani_AButton = m_maniController.GetAButton();
  m_controllerInputs->mani_BButton = m_maniController.GetBButton();
  m_controllerInputs->mani_XButton = m_maniController.GetXButton();
  m_controllerInputs->mani_YButton = m_maniController.GetYButton();
  m_controllerInputs->mani_RightBumper =
 m_maniController.GetRightBumper();
  m_controllerInputs->mani_LeftBumper =
      m_maniController.GetLeftBumper();
  m_controllerInputs->mani_RightTriggerAxis =
      m_maniController.GetRightTriggerAxis();
  m_controllerInputs->mani_LeftTriggerAxis =
      m_maniController.GetLeftTriggerAxis();
  m_controllerInputs->mani_POV = m_maniController.GetPOV();
  

  m_shooter.shooterDash();
  m_drive.drivetrainDash();
  m_turret.turretDash();

  ExecuteControls();
}

void Robot::TestInit() 
{
  m_auto.SetupRecording();
}

void Robot::TestPeriodic() 
{
  if (m_recordMode) { // recording
    // Run TeleOp as normal
    TeleopPeriodic();
    // Write current struct to file
    m_auto.Record(m_controllerInputs);
  }
}

void Robot::DisabledInit()
{
  m_auto.CloseFile();
}

// TeleOp
void Robot::ExecuteControls()
{
  // Drive - ADD POWER CURVE
  if (kDRIVEDEADBAND > std::abs(m_controllerInputs->drive_rightY) && 
      kDRIVEDEADBAND > std::abs(m_controllerInputs->drive_leftX)) {
    m_drive.StopMotor();
  } else if(m_slowDriveMode){
    m_drive.Drive(m_controllerInputs->drive_rightY*m_drive.kSlowMaxSpeed,
                  -m_controllerInputs->drive_leftX*m_drive.kMaxAngularSpeed);
  } else {
    m_drive.Drive(m_controllerInputs->drive_rightY*m_drive.kMaxSpeed,
                  -m_controllerInputs->drive_leftX*m_drive.kMaxAngularSpeed);
  }
  m_drive.UpdateOdometry();
  //slow mode - 4mps (affects acceleration and fine control)
  if(m_controllerInputs->drive_AButton){
    m_slowDriveMode = true;
  }
  //fast mode - 8 mps (affects acceleration and fine control)
  if(m_controllerInputs->drive_BButton){
    m_slowDriveMode = false;
  }
  
  // Extend/retract intake
  if(m_controllerInputs->mani_AButton){
    m_intake.extendIntake();
  } else if (m_controllerInputs->mani_BButton) {
    m_intake.retractIntake();
  }

  // Run the intake
  if (m_controllerInputs->mani_LeftBumper) {
    m_intake.forceRunIntake();
  } else {
    m_intake.stopIntake(); 
  }
  
  // Toggle the climber
  //if (m_controllerInputs->mani_XButton) {
  
   // Climb.ClimbT();
  //}
  
  //Vision manip control
  
  auto rpm = frc::SmartDashboard::GetNumber("RPM",0); //test code, tune shooter

  if (m_controllerInputs->mani_YButton) { //auto aim controls, manual control disabled when held down
    
 
    //shoot
    if(m_controllerInputs->mani_RightTriggerAxis) {
     
     
      if(m_controllerInputs->mani_RightBumper){ //force reverse feed during shooting
        m_shooter.reverseFeed();
      } else {
        
      }
    } else if (m_controllerInputs->mani_RightBumper) {
      m_shooter.reverseFeed();
    } else { //no shoot
      m_shooter.stopShooter();
      m_shooter.stopFeed();
    }
  } else { //manual controls
  
    // Running the shooter
    if (m_controllerInputs->mani_RightTriggerAxis > .1) {
      m_shooter.runShooter();
    } else {
      m_shooter.stopShooter();
    }
   
    // Aiming the shooter
    if (std::abs(m_controllerInputs->mani_rightX) > .1) {
      m_turret.Turn(m_controllerInputs->mani_rightX/5);
    } else {
      m_turret.Turn(0);
    }

    // Control the feeder
    if (m_controllerInputs->mani_LeftTriggerAxis > .1) {
      m_shooter.feedShooter();
    } else if (m_controllerInputs->mani_RightBumper) { 
      m_shooter.reverseFeed();
    } else {
      m_shooter.stopFeed();
    }
  }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif 