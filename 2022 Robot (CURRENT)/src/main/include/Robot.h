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
#include "ControllerInputs.h"

// Subsystem includes
#include "DriveSystem.h"
#include "Auto.h"
#include "Debug.h"



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
  const float DEAD_BAND = 0.1;

  // Controller variables
  int m_lastUsedSpeed = 2;
  

  // Objects of subsystems
  DriveSystem chassis;

  Auto m_auto{&chassis};
  const bool m_recordMode = true; // use this to force disable recording, useful at competitions
  
  frc::XboxController m_driveController {XBOX_USB_DRIVER_1}; //Chassis driver
  frc::XboxController m_maniController {XBOX_USB_DRIVER_2}; //Manipulation driver

};