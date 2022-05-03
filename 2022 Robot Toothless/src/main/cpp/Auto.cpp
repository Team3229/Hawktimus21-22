//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#include "Auto.h"

Auto::Auto(DriveSystem *c, Intake *i, IntakePivot *j, Turret *t, Feeder *f, UpperFeeder *u, Shooter *s, Limelight *l, Pivot * p, LEDS * x) 
{
  // Passes in subsystems from Robot
  autoChassis = c;
  autoTurret = t;
  autoShooter = s;
  autoIntake = i;
  autoIntakePivot = j;
  autoFeeder = f;
  autoUpperFeeder = u;
  autoLimelight = l;
  autoPivot = p;
  autoLeds = x;

}

Auto::~Auto() {
  delete autoChassis;
  delete autoTurret;
  delete autoShooter;
  delete autoIntake;
  delete autoIntakePivot; 
  delete autoFeeder;
  delete autoUpperFeeder;
  delete autoLimelight; 
  delete autoPivot;
  delete autoLeds;
 
}

void Auto::SetupPlayback(std::string inputFileName) {
  // Put in Robot::AutonomousInit
  // Get driver station info and setup
 
  debugCons("Reading auto instructions from /home/lvuser/" + inputFileName + ".aut\n");
  std::string filePath = "/home/lvuser/" + inputFileName + ".aut";
  cmdFile.Open(filePath, READ);
}

void Auto::ReadFile(cmd * inputs) {
  if (!autoDone) {
    debugCons("Reading auto file...\n");

    // Read controller inputs
    cmdFile.Read(inputs, sizeof(*inputs));

  }
}

void Auto::SetupRecording(std::string inputFileName) {
  // Put in Robot::TestInit()
  
  debugCons("Writing instructions to /home/lvuser/" + inputFileName + ".aut\n");
  std::string filePath = "/home/lvuser/" + inputFileName + ".aut";
  cmdFile.Open(filePath, WRITE);
}

void Auto::Record(cmd * inputs) {
  // Put in Robot::TestPeriodic()
  debugCons("Writing auto file...\n");

  // Write controller inputs
  cmdFile.Write(inputs, sizeof(*inputs));
}

void Auto::CloseFile() {
  // Put in Robot::DisabledInit()
  debugCons("File closed.\n");
  cmdFile.Close();
}