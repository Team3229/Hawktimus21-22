#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>

//Subsystem includes 
#include "DriveTrain.h"
#include "CaptureFile.h"
#include "Debug.h"
#include "ControllerInputs.h"
#include "Turret.h"
#include "Shooter.h"
#include "Limelight.h"
#include "Intake.h"
#include "Climb.h"
#include "LED.h"
#include "Camera.h
#include "Auto.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
  void DisabledInit() override;

  void ExecuteControls();
 private:
  cmd * m_controllerInputs = new cmd;

  frc::XboxController m_driveController{0};
  frc::XboxController m_maniController{1};

  Intake m_intake;
  Turret m_turret;
  Shooter m_shooter;
  
  

  Drivetrain m_drive;

  Auto m_auto{&m_drive};
  const bool m_recordMode = true; // use this to force disable recording, useful at competitions
  
  Camera m_camera;
  Camera m_camera2;
  double m_x1,m_y1;
  const int kDRIVEDEADBAND = .15; 
  const float HOOD_INCRIMENT = 0.05;

  bool m_slowDriveMode = false;
};


/*
Game Ball Inflation
Barometer Pressure Gauge
    3.5 PSI
    6.3 Lines
    (Conversion Process)
        PSI/0.555...  = # of bars
*/