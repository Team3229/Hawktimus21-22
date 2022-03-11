
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


if ((std::abs(m_controllerInputs->driver_rightY) > DEAD_BAND) || (std::abs(m_controllerInputs->driver_leftX) > DEAD_BAND)) //might need to switch to right 
		{
       chassis.Drive(m_controllerInputs->driver_rightY, m_controllerInputs->driver_rightX, m_controllerInputs->driver_leftX);
        
		}
else
		{
			chassis.Stop();
    }
  /*
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
  }*/

   //Run the intake
  if (m_controllerInputs->mani_LeftBumper) {
    m_intake.runIntake();
  } else {
    m_intake.stopIntake(); 
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
          m_shooter.SHOOTER_POWERONEAUTO = 0.8;
	        m_shooter.SHOOTER_POWERTWOAUTO = -0.8;
	        desiredPivotAngle = 21659;

	        debugCons("FIRST DISTANCE\n");          
     	 }

         else if (distanceFromLimelightToGoalInches > 68 && distanceFromLimelightToGoalInches <= 93)
         {
          m_shooter.SHOOTER_POWERONEAUTO = 0.9;
	        m_shooter.SHOOTER_POWERTWOAUTO = -0.9;
	        desiredPivotAngle = 27206;

	         debugCons("SECOND DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 93 && distanceFromLimelightToGoalInches <= 125)
         {
          m_shooter.SHOOTER_POWERONEAUTO = 1.0;
	        m_shooter.SHOOTER_POWERTWOAUTO = -1.0;//was 60
	        desiredPivotAngle = 41219;

	          debugCons("THIRD DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 125 && distanceFromLimelightToGoalInches <= 139)
         {
         m_shooter.SHOOTER_POWERONEAUTO = 1.0;// 80
	      m_shooter.SHOOTER_POWERTWOAUTO = -1.0;
	      desiredPivotAngle = 42790;

	      debugCons("FOURTH DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 139)
         {
           //4004
          m_shooter.SHOOTER_POWERONEAUTO = 1.0;
	      m_shooter.SHOOTER_POWERTWOAUTO = -1.0;
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
	if ((abs(m_pivot.GetAngle() - desiredPivotAngle)) < 1) // +- 1 degree to avoid oscillating
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
   //nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); //turn limelight off
  } 

/*
   //limelight hold down button
  if (m_controllerInputs->mani_XButton)
  {
  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);

 m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);         //Get horizontal off set from target
 m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);                   //Get vertical offset from target
 m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);                   //Get area of target on screen
 m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);                   //Get skew of target
 m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);


// limelight seeking
  if (abs(m_xOffset) < TARGET_RANGE)
  {
   m_turret.Turn(0);
  }
  else if (m_xOffset > 0) {

   m_turret.TurnLimelightRight(1);

  }
  else if (m_xOffset < 0){

    m_turret.TurnLimelightLeft(1);
  }

  //limelight distance calculations 
   double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
   double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
   double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
 
       

       //restructure these 
    if (distanceFromLimelightToGoalInches >= 208 && distanceFromLimelightToGoalInches <= 220) {
         m_shooter.SHOOTER_POWERONEAUTO = .40;
         m_shooter.SHOOTER_POWERTWOAUTO = -.40;
         desiredPivotAngle = abs(15320);
    
       }

       else if (distanceFromLimelightToGoalInches >= 100 && distanceFromLimelightToGoalInches <= 150){
        m_shooter.SHOOTER_POWERONEAUTO = .30;
        m_shooter.SHOOTER_POWERTWOAUTO = -.30;
       
       }

       else{
         m_shooter.SHOOTER_POWERONEAUTO = .6;
         m_shooter.SHOOTER_POWERTWOAUTO = -.6;
          }
  //run shooter after values gathered
   m_shooter.runShooterAuto();

   
      if (m_pivot.m_pivotMotor->GetSelectedSensorPosition() == abs(desiredPivotAngle))
      {
        //lock pivot in location
      m_pivot.TurnUp(0);
      m_pivot.TurnDown(0);
      }

      else if (m_pivot.m_pivotMotor->GetSelectedSensorPosition() > abs(desiredPivotAngle))
      {
        m_pivot.TurnDown(1);
      }

      else if (m_pivot.m_pivotMotor->GetSelectedSensorPosition() < abs(desiredPivotAngle))
      {
        m_pivot.TurnUp(1);
      }

      else {}
      
  }

  else 
  {
  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
  }
  */
  //climb toggle 
  
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




