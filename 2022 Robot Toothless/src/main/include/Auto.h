//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

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
#include "LEDS.h"

class Auto 
{
private:
  bool autoDone = false;

  // Pass in our subsystems
  // MAKE SURE TO UPDATE CONSTRUCTOR ARGS AND SUBSYSTEMS FOR THIS YEAR
  DriveSystem * autoChassis;
  Intake * autoIntake;
  IntakePivot * autoIntakePivot;
  Turret * autoTurret;
  Feeder * autoFeeder;
  UpperFeeder *autoUpperFeeder;
  Shooter * autoShooter;
  Limelight * autoLimelight; 
  Pivot * autoPivot; 
  LEDS * autoLeds;
  
 
  std::string stationText = "Auto file path: /home/lvuser/";
  std::string inputFileName; //other was crossLine  "crossLineAndShoot"

  const bool WRITE = true;
  const bool READ = false;
  CaptureFile cmdFile {};

public:
  Auto(DriveSystem *c, Intake *i, IntakePivot *j, Turret *t, Feeder *f, UpperFeeder *u, Shooter *s, Limelight *l, Pivot *p, LEDS *x); //make sure to pass in subsystems 
  ~Auto();
  void SetupPlayback(std::string inputFileName);
  void ReadFile(cmd * inputs);
  void SetupRecording(std::string inputFileName);
  void Record(cmd * inputs);
  void CloseFile();
 

};

#endif // AUTO_H