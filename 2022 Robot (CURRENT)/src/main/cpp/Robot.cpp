
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

 if (kDRIVEDEADBAND > std::abs(m_controllerInputs->driver_rightY) && kDRIVEDEADBAND > std::abs(m_controllerInputs->driver_leftX)) {
    chassis.StopMotor();

  } 
  else if(m_slowDriveMode){
    chassis.Drive(m_controllerInputs->driver_rightY*chassis.kSlowMaxSpeed, -m_controllerInputs->driver_leftX*chassis.kMaxAngularSpeed);
  } 
  else
   {
    chassis.Drive(m_controllerInputs->driver_rightY*chassis.kMaxSpeed, -m_controllerInputs->driver_leftX*chassis.kMaxAngularSpeed);
  }
  
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
    }*/


   //Run the intake
  if (m_controllerInputs->mani_LeftBumper) {
    m_intake.runIntake();
  } else {
    m_intake.stopIntake(); 
  }

  if (m_controllerInputs->mani_YButton)
  {
    m_feeder.reverseFeeder();
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
      m_shooter.runShooter();
  }
  else{
      m_shooter.stopShooter();
  }

  if (m_controllerInputs->mani_YButton)
  {
    m_intake.runIntakePivot(); //extend 
  }
  else
  {
    m_intake.stopPivot();
  }

  if (m_controllerInputs->mani_BButton){
    m_intake.reverseIntakePivot();
  }
  else {
    m_intake.stopPivot();
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

	//calculate angle for the pivot
	//double angleForPivot = (0.81*(distanceFromLimelightToGoalInches)+5.09);
	      m_shooter.runShooterAuto();

	 // set shooter power and pivot angle based on distance
   debugCons("DISTANCE AWAY: " << distanceFromLimelightToGoalInches << "\n");
     	 if (distanceFromLimelightToGoalInches <= 68)
       	 {
          m_shooter.SHOOTER_POWERONEAUTO = 0.37;
	        m_shooter.SHOOTER_POWERTWOAUTO = -0.37;
	        desiredPivotAngle = 21659;

	        debugCons("FIRST DISTANCE\n");          
     	 }

         else if (distanceFromLimelightToGoalInches > 68 && distanceFromLimelightToGoalInches <= 93)
         {
          m_shooter.SHOOTER_POWERONEAUTO = 0.48;
	        m_shooter.SHOOTER_POWERTWOAUTO = -0.58;
	        desiredPivotAngle = 28206;

	         debugCons("SECOND DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 93 && distanceFromLimelightToGoalInches <= 109)
         {
          m_shooter.SHOOTER_POWERONEAUTO = .45;//was 48
	        m_shooter.SHOOTER_POWERTWOAUTO = -.45;//was 60
	        desiredPivotAngle = 41219;

	          debugCons("THIRD DISTANCE\n");          
     	 }

        else if (distanceFromLimelightToGoalInches > 109 && distanceFromLimelightToGoalInches <= 125)
        {
             m_shooter.SHOOTER_POWERONEAUTO = .48;//was 58
	        m_shooter.SHOOTER_POWERTWOAUTO = -.48;
	        desiredPivotAngle = 41219;
           debugCons("Fourth Distance\n");    

        }
	  
         else if (distanceFromLimelightToGoalInches > 125 && distanceFromLimelightToGoalInches <= 141)
         {
         m_shooter.SHOOTER_POWERONEAUTO = .58;// 80
	      m_shooter.SHOOTER_POWERTWOAUTO = -.58;
	      desiredPivotAngle = 42790;

	      debugCons("Fifth distance\n");          
     	 }
        else if (distanceFromLimelightToGoalInches > 141 && distanceFromLimelightToGoalInches <= 155)
        {
           m_shooter.SHOOTER_POWERONEAUTO = .52;// 80
	      m_shooter.SHOOTER_POWERTWOAUTO = -.52;
	      desiredPivotAngle = 42790;
	      debugCons("sixth distance\n");       
        }
	  
         else if (distanceFromLimelightToGoalInches > 156)
         {
           //4004
          m_shooter.SHOOTER_POWERONEAUTO =.74;
	      m_shooter.SHOOTER_POWERTWOAUTO = -.74;
	      desiredPivotAngle = 52825;
	      debugCons("VERY FAR\n");          
     	 }

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
	if ((abs(m_pivot.GetAngle() - desiredPivotAngle)) < 5) // +- 1 degree to avoid oscillating
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
	
	 // if we're ready to shoot, shoot dependent upon distance
	 // if the drivers don't want to auto-shoot, this could be a visual indication for them to shoot
	 // BUT make sure it's a different button or it will shoot at default power!
	if (haveTarget && turretAligned && pivotAligned)
	{  
	   debugCons("TAKING A SHOT\n");
	}

  }

  }
  // no limelight pressed, turn it off
  else 
  {
   nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); //turn limelight off
  } 

  if (m_driveController.GetRightTriggerAxis() > 0.5) {
    m_climb.ClimbUp();
  }
  else {
    m_climb.ClimbStop();
  }

  if (m_driveController.GetLeftTriggerAxis() > 0.5) {
    m_climb.ClimbDown();
  }

}

#ifndef RUNNING_FRC_TESTS

int main() { return frc::StartRobot<Robot>(); }
#endif 




