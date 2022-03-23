
#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableValue.h>
#include "wpi/span.h"

void Robot::RobotInit(){
 nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
     frc::SmartDashboard::PutNumber("Shooter ONE RPM ", m_shooter.getRPMS());


}

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
  m_controllerInputs->driver_StartButton = m_driveController.GetStartButton();
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
  m_controllerInputs->mani_StartButton = m_maniController.GetStartButton();
  m_controllerInputs->mani_RightBumper =
 m_maniController.GetRightBumper();
  m_controllerInputs->mani_LeftBumper =
      m_maniController.GetLeftBumper();
  m_controllerInputs->mani_RightTriggerAxis =
      m_maniController.GetRightTriggerAxis();
  m_controllerInputs->mani_LeftTriggerAxis =
      m_maniController.GetLeftTriggerAxis();
  m_controllerInputs->mani_POV = m_maniController.GetPOV();

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


    if (kDRIVEDEADBAND > std::abs(m_controllerInputs->driver_rightY) &&  kDRIVEDEADBAND > std::abs(m_controllerInputs->driver_leftX)) {

    chassis.StopMotor();


  } else if(m_slowDriveMode){

    chassis.Drive(m_controllerInputs->driver_rightY*chassis.kSlowMaxSpeed, -m_controllerInputs->driver_leftX*chassis.kMaxAngularSpeed);

  } else {
    
    chassis.Drive(m_controllerInputs->driver_rightY*chassis.kMaxSpeed, -m_controllerInputs->driver_leftX*chassis.kMaxAngularSpeed);

  }

  chassis.UpdateOdometry();

  //slow mode - 4mps (affects acceleration and fine control)
  if(m_controllerInputs->driver_AButton){
    m_slowDriveMode = true;
  }
  //fast mode - 8 mps (affects acceleration and fine control)
  if(m_controllerInputs->driver_BButton){
    m_slowDriveMode = false;
  }


/*
if ((std::abs(m_controllerInputs->driver_rightY) > DEAD_BAND) || (std::abs(m_controllerInputs->driver_leftX) > DEAD_BAND)) //might need to switch to right 
		{
       chassis.Drive(m_controllerInputs->driver_rightY, m_controllerInputs->driver_rightX, m_controllerInputs->driver_leftX);
        
		}
else
		{
			chassis.Stop();
    }

*/
   //Run the intake
  if (m_controllerInputs->mani_LeftBumper) {
    m_intake.runIntake();
  } else {
    m_intake.stopIntake(); 
  }

  if (m_controllerInputs->mani_YButton)
  {
    m_feeder.runFeeder();
  }
  else
  {
    m_feeder.stopFeeder();
  }

  //Run polycoord feeder forwards
   if (m_controllerInputs->mani_RightBumper) {
    m_feeder.runFeeder();
    m_intake.runIntake();
  } else {
    m_feeder.stopFeeder(); 
    m_intake.stopIntake();
  }

  
//Run Polycoord feeder downwards 
  if (m_controllerInputs->mani_AButton){
    m_feeder.reverseFeeder(); 
  }

  //Run upper feeder 
   if (std::abs(m_controllerInputs->mani_RightTriggerAxis > .1)) {
    m_upperFeeder.runUpperFeeder();
  }
   else  {
    m_upperFeeder.stopUpperFeeder(); 
  }

  //turret manual turning
  if (std::abs(m_controllerInputs->mani_rightX) > .1) {
      m_turret.Turn(m_controllerInputs->mani_rightX/5);
    } else {
      m_turret.Turn(0);
    }

 //shooter manual turning 
  if (std::abs(m_controllerInputs->mani_LeftBumper)){
     
      m_shooter.runShooterAuto(2600, -2600 * .6);
     
      
  }
  
if (m_controllerInputs->mani_XButton == 0 && m_controllerInputs->mani_LeftBumper == 0){
      m_shooter.stopShooter();
  }

  if (m_controllerInputs->mani_YButton)
  {
    m_intakePivot.runIntakePivot(); //extend 
  }
  else
  {
    m_intakePivot.stopPivot();
  }

  if (m_controllerInputs->mani_BButton){
    m_intakePivot.reverseIntakePivot();
  }
  else {
    m_intakePivot.stopPivot();
  }

  //pivot turning
  if (std::abs(m_controllerInputs->mani_leftY) > .1) {
      m_pivot.Turn(m_controllerInputs->mani_leftY/5);
    } else {
      m_pivot.Turn(0);
    }

  //limelight
    if (m_controllerInputs->mani_XButton)
  {
	bool haveTarget = false;
	bool turretAligned = false;
	bool pivotAligned = false;
	//double SHOOTER_POWERONE = 0.3;
	//double SHOOTER_POWERTWO = -0.3;
	double desiredPivotAngle = 0;

   nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3); //turn limelight off
	
	if (m_limelight.GetValues()) // if limelight has a target
	{
	   haveTarget = true;
    // debugCons("WE HAVE A TARGET\n");
	
	
    m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0); //Get horizontal offset from target
    m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0); //Get vertical offset from target
    //debugCons("X OFFSET: " << m_xOffset);

	//calculate horizontal turn to target
	double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
  double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
  double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
	  
  
  double RPM1 = (12.9 * distanceFromLimelightToGoalInches) + 2105;
  double RPM2 = -RPM1 * 0.6;


  m_shooter.runShooterAuto(RPM1, RPM2);
  desiredPivotAngle = 58700;


  debugCons("DISTANCE AWAY: " << distanceFromLimelightToGoalInches << "\n");


  if (RPM1 >= 5000)
  {
    m_shooter.runShooterAuto(5000, -5000 * 0.6);
  }
/*
     	 if (distanceFromLimelightToGoalInches <= 68) {
  
          m_shooter.runShooterAuto(RPM1, RPM2);
          //m_shooter.runShooterAuto(2960, -2960 * 0.6);
	        desiredPivotAngle = 58700;

	        debugCons("FIRST DISTANCE\n");          
     	 }

         else if (distanceFromLimelightToGoalInches > 68 && distanceFromLimelightToGoalInches <= 93) {

          //m_shooter.runShooterAuto(3100, -3100 * 0.6);
	        desiredPivotAngle = 58700; 

	         debugCons("SECOND DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 93 && distanceFromLimelightToGoalInches <= 109){

         m_shooter.runShooterAuto(3300, -3300 * 0.6);
	        desiredPivotAngle = 58700;

	          debugCons("THIRD DISTANCE\n");          
     	 }

        else if (distanceFromLimelightToGoalInches > 109 && distanceFromLimelightToGoalInches <= 125){

            m_shooter.runShooterAuto(3600, -3600 * 0.6);
	        desiredPivotAngle = 58700;
           debugCons("Fourth Distance\n");    

      }
	  
         else if (distanceFromLimelightToGoalInches > 125 && distanceFromLimelightToGoalInches <= 141){

        m_shooter.runShooterAuto(3700, -3700 * 0.6);
	      desiredPivotAngle = 58700;

	      debugCons("Fifth distance\n");          
     	 }

        else if (distanceFromLimelightToGoalInches > 141 && distanceFromLimelightToGoalInches <= 155){

        m_shooter.runShooterAuto(3800, -3800 * .6);
	      desiredPivotAngle = 58700;

	      debugCons("sixth distance\n");       
       }
	  
        else if (distanceFromLimelightToGoalInches > 156 && distanceFromLimelightToGoalInches <= 191) {
          
         m_shooter.runShooterAuto(3950, -3950 * .6);
	      desiredPivotAngle = 58700;

	    debugCons("Seventh distance\n");          
     	}

         else if (distanceFromLimelightToGoalInches > 191 && distanceFromLimelightToGoalInches <= 216) {
          
         m_shooter.runShooterAuto(4200, -4200 * .6);
	      desiredPivotAngle = 58700;

	    debugCons("8 distance\n");          
     	}

       else if (distanceFromLimelightToGoalInches >  216) {
          
         m_shooter.runShooterAuto(4400, -4400 * .6);
	      desiredPivotAngle = 58700;

	    debugCons("9 distance\n");          
     	}*/

  //limelight moves to target if target on screen
  if (abs(m_xOffset) < TARGET_RANGE)
  {
   m_turret.Turn(0);
   turretAligned = true;
  }
  else if (m_xOffset > 0) {

   m_turret.TurnLimelightRight(1);

  }
  else if (m_xOffset < 0){

    m_turret.TurnLimelightLeft(1);
  }

	
	// check alignment of pivot
	if ((abs(m_pivot.GetAngle() - desiredPivotAngle)) < 500) // +- 1 degree to avoid oscillating
	{
	   m_pivot.Turn(0); // stop pivoting
	   pivotAligned = true;
	}
	else if (m_pivot.GetAngle() < desiredPivotAngle)
	{
	   m_pivot.Turn(-1); // pivot down
	}
	else if (m_pivot.GetAngle() > desiredPivotAngle)
	{
	   m_pivot.Turn(1);// pivot up
	}
	
	 
	if (haveTarget && turretAligned && pivotAligned){  //auto shoot without driver input wehn all values are true they start shooting, manip driver just has to perss X and robot does everything 
	   debugCons("TAKING A SHOT\n");
     
    //m_feeder.runFeeder();
    //m_upperFeeder.runUpperFeeder();
	}
  else{
     // m_upperFeeder.stopUpperFeeder();
     // m_feeder.stopFeeder();
  }

  }

  }
  else 
  {
  //nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); //turn limelight off
  } 

  if (m_controllerInputs->driver_RightTriggerAxis > 0.5) {
    m_climb.ClimbUp();
  }
  else {
    m_climb.ClimbStop();
  }

  if (m_controllerInputs->driver_LeftTriggerAxis > 0.5)
   { 
    m_climb.ClimbDown();
  }

}

#ifndef RUNNING_FRC_TESTS

int main() { return frc::StartRobot<Robot>(); }
#endif 




