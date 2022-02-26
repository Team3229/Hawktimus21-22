
#include "Robot.h"
#include <iostream>

void Robot::RobotInit(){}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  m_auto.SetupPlayback();
   
}

void Robot::AutonomousPeriodic() 
{
  m_auto.ReadFile(m_controllerInputs);
  debugCons("Running Auto");
  ExecuteControls();
}

void Robot::TeleopInit() 
{
  m_auto.CloseFile();
}

void Robot::TeleopPeriodic()
{    
  // Populate controller struct
  m_controllerInputs->driver_rightY = m_driveController.GetRightY();
  m_controllerInputs->driver_rightX = m_driveController.GetRightX();
  m_controllerInputs->driver_leftY = m_driveController.GetLeftY();
  m_controllerInputs->driver_leftX = m_driveController.GetLeftX();
  m_controllerInputs->driver_AButton = m_driveController.GetAButton();
  m_controllerInputs->driver_BButton = m_driveController.GetBButton();
  m_controllerInputs->driver_XButton = m_driveController.GetXButton();
  m_controllerInputs->driver_YButton = m_driveController.GetYButton();
  m_controllerInputs->driver_RightBumper =
      m_driveController.GetRightBumper();
  m_controllerInputs->driver_LeftBumper =
      m_driveController.GetLeftBumper();
  m_controllerInputs->driver_RightTriggerAxis =
      m_driveController.GetRightTriggerAxis();
  m_controllerInputs->driver_LeftTriggerAxis =
      m_driveController.GetLeftTriggerAxis();
  m_controllerInputs->driver_POV = m_driveController.GetPOV();
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

void Robot::ExecuteControls()
{
if(abs(DEAD_BAND > std::abs(m_controllerInputs->driver_rightY) && DEAD_BAND > std::abs(m_controllerInputs->driver_leftX)))
		{
        chassis.Stop();
		}
		else
		{
			 chassis.Drive(m_controllerInputs->driver_rightY, m_controllerInputs->driver_rightX, m_controllerInputs->driver_leftX);
    }
  
  // speed changer 
  if (m_driveController.GetAButton())
  {
    chassis.ChangeSpeed(2); // normal speed
    m_lastUsedSpeed = 2;
  }

  if (m_driveController.GetBButton())
  {
    chassis.ChangeSpeed(1); // slow speed
    m_lastUsedSpeed = 1;
  }

  if (m_driveController.GetXButton())
  {
    chassis.ChangeSpeed(3); // fast
    m_lastUsedSpeed = 3;
  }

   //Run the intake
  if (m_controllerInputs->mani_LeftBumper) {
    m_intake.runIntake();
  } else {
    m_intake.stopIntake(); 
  }

  //Run polycoord feeder
   if (m_controllerInputs->mani_RightBumper) {
    m_feeder.runFeeder();
  } else {
    m_feeder.stopFeeder(); 
  }

  if (std::abs(m_controllerInputs->mani_rightX) > .1) {
      m_turret.Turn(m_controllerInputs->mani_rightX/5);
    } else {
      m_turret.Turn(0);
    }

  if (std::abs(m_controllerInputs->mani_LeftTriggerAxis > .1)){
      m_shooter.runShooter();
  }
  else{
      m_shooter.stopShooter();
  }


}


#ifndef RUNNING_FRC_TESTS

int main() { return frc::StartRobot<Robot>(); }
#endif 




