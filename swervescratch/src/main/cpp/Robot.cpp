// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  navxGyro = new AHRS(frc::SPI::Port::kMXP);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() 
{
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() 
{
  m_controllerInputs->driver_rightY = m_driveCon.GetRightY();
  m_controllerInputs->driver_rightX = m_driveCon.GetRightX();
  m_controllerInputs->driver_leftY = m_driveCon.GetLeftY();
  m_controllerInputs->driver_leftX = m_driveCon.GetLeftX();
  m_controllerInputs->driver_AButton = m_driveCon.GetAButton();
  m_controllerInputs->driver_BButton = m_driveCon.GetBButton();
  m_controllerInputs->driver_XButton = m_driveCon.GetXButton();
  m_controllerInputs->driver_YButton = m_driveCon.GetYButton();
  m_controllerInputs->driver_StartButton = m_driveCon.GetStartButton();
  m_controllerInputs->driver_RightBumper =
      m_driveCon.GetRightBumper();
  m_controllerInputs->driver_LeftBumper =
      m_driveCon.GetLeftBumper();
  m_controllerInputs->driver_RightTriggerAxis =
      m_driveCon.GetRightTriggerAxis();
  m_controllerInputs->driver_LeftTriggerAxis =
      m_driveCon.GetLeftTriggerAxis();
  m_controllerInputs->driver_POV = m_driveCon.GetPOV();
  m_controllerInputs->mani_rightY = m_manipCon.GetRightY();
  m_controllerInputs->mani_rightX = m_manipCon.GetRightX();
  m_controllerInputs->mani_leftY = m_manipCon.GetLeftY();
  m_controllerInputs->mani_leftX = m_manipCon.GetLeftX();
  m_controllerInputs->mani_AButton = m_manipCon.GetAButton();
  m_controllerInputs->mani_BButton = m_manipCon.GetBButton();
  m_controllerInputs->mani_XButton = m_manipCon.GetXButton();
  m_controllerInputs->mani_YButton = m_manipCon.GetYButton();
  m_controllerInputs->mani_StartButton = m_manipCon.GetStartButton();
  m_controllerInputs->mani_RightBumper =
 m_manipCon.GetRightBumper();
  m_controllerInputs->mani_LeftBumper =
      m_manipCon.GetLeftBumper();
  m_controllerInputs->mani_RightTriggerAxis =
      m_manipCon.GetRightTriggerAxis();
  m_controllerInputs->mani_LeftTriggerAxis =
      m_manipCon.GetLeftTriggerAxis();
  m_controllerInputs->mani_POV = m_manipCon.GetPOV();

    ExecuteControls();
}

void Robot::DisabledInit() {}

void Robot::ExecuteControls() 
{

}


#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
