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

class Auto 
{
private:
  bool autoDone = false;

  // Pass in our subsystems
  // MAKE SURE TO UPDATE CONSTRUCTOR ARGS AND SUBSYSTEMS FOR THIS YEAR
  DriveSystem * autoChassis;
  
  // files stuff
  // Use .aut file extension
  std::string stationFileList = "crossLineAndShoot.aut, crossLine.aut";
  std::string defaultFileName = "defaultAutoPath.aut";
  std::string stationText = "Auto file path: /home/lvuser/";
  std::string inputFileName = "crossLineAndShoot"; //other was crossLine

  const bool WRITE = true;
  const bool READ = false;
  CaptureFile cmdFile {};

public:
  Auto(DriveSystem *c); //make sure to pass in subsystems 
  ~Auto();
  void SetupPlayback();
  void ReadFile(cmd * inputs);
  void SetupRecording();
  void Record(cmd * inputs);
  void CloseFile();
 

};

#endif // AUTO_H