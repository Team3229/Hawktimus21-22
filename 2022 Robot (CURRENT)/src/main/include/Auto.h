#ifndef AUTO_H
#define AUTO_H

// includes
#include <iostream>
#include <string>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
#include <Math.h>
#include "frc/Timer.h"

#include "DriveSystem.h"
#include "CaptureFile.h"
#include "Debug.h"
#include "ControllerInputs.h"
#include "Intake.h"
#include "Feeder.h"
#include "Turret.h"
#include "Shooter.h"
#include "Feeder.h"
#include "Limelight.h"
#include "Pivot.h"

class Auto 
{
private:
  bool autoDone = false;

  // Pass in our subsystems
  // MAKE SURE TO UPDATE CONSTRUCTOR ARGS AND SUBSYSTEMS FOR THIS YEAR
  DriveSystem * autoChassis;
  Intake * autoIntake;
  Turret * autoTurret;
  Feeder * autoFeeder;
  UpperFeeder *autoUpperFeeder;
  Shooter * autoShooter;
  Limelight * autoLimelight; 
  Pivot * autoPivot; 
  
  // files stuff
  // Use .aut file extension
  std::string stationFileList = "crossLineAndShoot.aut, crossLine.aut";
  std::string defaultFileName = "defaultAutoPath.aut";
  std::string stationText = "Auto file path: /home/lvuser/";
  std::string inputFileName = "crossLineAndShoot"; //other was crossLineAndShoot4

  //crossLineAndShoot 2 ball auto
  //crossLineAndShoot4

  const bool WRITE = true;
  const bool READ = false;
  CaptureFile cmdFile {};

public:
  Auto(DriveSystem *c, Intake *i, Turret *t, Feeder *f, UpperFeeder *u, Shooter *s, Limelight *l, Pivot *p); //make sure to pass in subsystems 
  ~Auto();
  void SetupPlayback();
  void ReadFile(cmd * inputs);
  void SetupRecording();
  void Record(cmd * inputs);
  void CloseFile();
 

};

#endif // AUTO_H