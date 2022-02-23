#ifndef AUTO_H
#define AUTO_H

// c++ primary includes
#include <iostream>
#include <string>

//WPILIB/FRC includes
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
#include <Math.h>
#include "frc/Timer.h"

//Subsystem Includes
#include "DriveTrain.h"
#include "CaptureFile.h"
#include "Debug.h"
#include "ControllerInputs.h"
#include "Turret.h"
#include "Robot.h"
#include "Shooter.h"
#include "Limelight.h"
#include "Intake.h"
#include "Climb.h"


class Auto
 {
private:
  bool autoDone = false;

  // Pass in Robot-Subsystems
  // MAKE SURE TO UPDATE CONSTRUCTOR ARGS AND SUBSYSTEMS FOR THIS YEAR!!!!!!!~ - Sebastian

  Drivetrain * autoChassis; //chassis
  Turret * autoTurret; //turret 
  Intake * autoIntake; //inake
  Shooter * autoShooter; //shooter 
  //Limelight * autoLimelight; //limelight

  

  // files stuff
  // Use .aut file extension
  //can change to different names
  std::string stationFileList = "crossLineAndShoot.aut, crossLine.aut"; 
  std::string defaultFileName = "defaultAutoPath.aut";
  std::string stationText = "Auto file path: /home/lvuser/";
  std::string inputFileName = "crossLineAndShoot"; //other was crossLine

  const bool WRITE = true;
  const bool READ = false;
  CaptureFile cmdFile {};

public:
  Auto(Drivetrain *c, Turret *t, Intake *i, Shooter *s); 
  ~Auto();
  void SetupPlayback();
  void ReadFile(cmd * inputs);
  void SetupRecording();
  void Record(cmd * inputs);
  void CloseFile();
};

#endif // AUTO_H