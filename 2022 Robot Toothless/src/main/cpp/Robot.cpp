
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
     navxGyro = new AHRS(frc::SPI::Port::kMXP);

    frc::SmartDashboard::PutData(&m_chooser);

  m_chooser.SetDefaultOption("4 Ball Auto (Default Choice)", kAutoroutineDefault);
  m_chooser.AddOption("2 Ball Auto From Left", kLeftAuto);
  m_chooser.AddOption("3 Ball Auto From Center", kCenterAuto);
  m_chooser.AddOption("4 Ball Auto From Right", kRightAuto);



}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
  std::string inputFileName = m_chooser.GetSelected();
  m_auto.SetupPlayback(inputFileName);
  
   
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
  std::string inputFileName = m_chooser.GetSelected();
  m_auto.SetupRecording(inputFileName);
  
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




  //slow mode - 4mps (affects acceleration and fine control)
  if(m_controllerInputs->driver_AButton){
    m_slowDriveMode = true;
    drive_speed = DRIVE_SLOW;
  }
  //fast mode - 8 mps (affects acceleration and fine control)
  if(m_controllerInputs->driver_BButton){
    m_slowDriveMode = false;
    drive_speed = DRIVE_REGULAR;
  }


  if ((std::abs(m_controllerInputs->driver_rightY) > DEAD_BAND) || (std::abs(m_controllerInputs->driver_rightX) > DEAD_BAND)) //might need to switch to right changed from righY leftX to rightY rightX to actually turn on the sides
  {
    

     if (m_controllerInputs->driver_rightY > drive_speed) {
	     m_controllerInputs->driver_rightY = drive_speed;
       
     }
     else if (m_controllerInputs->driver_rightY < -drive_speed) {
	     m_controllerInputs->driver_rightY = -drive_speed;
     }
     if (m_controllerInputs->driver_leftX > drive_speed) {
	     m_controllerInputs->driver_leftX = drive_speed;
     }
     else if (m_controllerInputs->driver_leftX < -drive_speed) {
	     m_controllerInputs->driver_leftX = -drive_speed;
     }
     chassis.Drive(m_controllerInputs->driver_rightY, m_controllerInputs->driver_rightX, m_controllerInputs->driver_leftX);
        
  
  }
  else	{
     chassis.Stop();
  }

  /*if (m_controllerInputs->mani_YButton)
  {
    m_feeder.runFeeder();
  }
  else
  {
    m_feeder.stopFeeder();
  }*/

  //Run polycoord feeder and intake forwards driver has this control
   if (std::abs(m_controllerInputs->driver_leftY > 0.15)) {
    m_feeder.reverseFeeder();
  } 

    if (std::abs(m_controllerInputs->driver_leftY < -0.15)){
        m_intake.runIntake();
        m_feeder.runFeeder();
    }
    else {
        m_intake.stopIntake();
    }
  


 
 if (std::abs(m_controllerInputs->mani_RightTriggerAxis < .1) && (std::abs(m_controllerInputs->driver_leftY) == 0) && m_controllerInputs->mani_AButton == 0)
 {
   m_feeder.stopFeeder();
 }
  
//Run Polycoord feeder downwards 
  if (m_controllerInputs->mani_AButton || std::abs(m_controllerInputs->driver_leftY < 0.15) ){
    m_feeder.reverseFeeder(); 
  }
  else{}

  //Run upper feeder aka basically the shoot button
   if (std::abs(m_controllerInputs->mani_RightTriggerAxis > .1)) {

    m_leds.ChangeLEDColors(-0.57);
    m_feeder.runFeeder();
    m_upperFeeder.runUpperFeeder();
    
  }
   else  {
    m_upperFeeder.stopUpperFeeder(); 
    m_feeder.stopFeeder();
  }


  //turret manual turning
  if (std::abs(m_controllerInputs->mani_rightX) > .1) {

      m_turret.Turn(m_controllerInputs->mani_rightX/5);
      
    } else {
      m_turret.Turn(0); //this conflicts with turret turning of the light is left on at all times 
    }

 //shooter manual turning 
  if (std::abs(m_controllerInputs->mani_LeftTriggerAxis > .1)){
     
      m_shooter.runShooterAuto(2600, -2600 * .6);
  }
    else{
       m_shooter.stopShooter();
    }
     
      
  
//if (m_turretAutoLock = false && m_controllerInputs->mani_LeftTriggerAxis < .5 ){ //change this once you create the toggle
  //    m_shooter.stopShooter();
  //}

  if (m_controllerInputs->mani_RightBumper) //retracts pivot 
  {
    m_intakePivot.reverseIntakePivot(); 
  }
  

   if (m_controllerInputs->mani_LeftBumper) //extends pivot
   { 
    m_intakePivot.runIntakePivot();
  }

  if (std::abs(m_controllerInputs->mani_LeftBumper == 0) && std::abs(m_controllerInputs->mani_RightBumper == 0))
  {
    m_intakePivot.stopPivot();
  }

  if (m_turretAutoLock == false && m_controllerInputs->driver_RightBumper < 0.5 && m_controllerInputs->driver_LeftBumper < 0.5 && m_controllerInputs->driver_LeftTriggerAxis < 0.5 && m_controllerInputs->driver_RightTriggerAxis < 0.5 && m_controllerInputs->mani_RightTriggerAxis < .1)
  {
     m_leds.ChangeLEDColors(0.99);
  }


  //pivot turning
  if (std::abs(m_controllerInputs->mani_leftY) > .1) {

      m_pivot.Turn(m_controllerInputs->mani_leftY/5);

    } else {
      m_pivot.Turn(0);
    }

  if (m_controllerInputs->mani_XButton){

    m_turretAutoLock = true;
    debugCons("Turret Toggle On\n");

  }

  if (m_controllerInputs->mani_BButton){

    m_turretAutoLock = false;
    debugCons("Turret Toggle Off\n");
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); //turn limelight off
  }

  //limelight

    if (m_turretAutoLock == true)
  {

	bool haveTarget = false;
	bool turretAligned = false;
	bool pivotAligned = false;

	double desiredPivotAngle = 0;

   nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3); //turn limelight off
	
	if (m_limelight.GetValues()) 
	{
	   haveTarget = true;
    
	
	
    m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0); //Get horizontal offset from target
    m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0); //Get vertical offset from target
  
	//calculate horizontal turn to target
	double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
  double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
  double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
	  
  
  double RPM1 = (12.9 * distanceFromLimelightToGoalInches) + 2105;
  double RPM2 = -RPM1 * 0.6;


  m_shooter.runShooterAuto(RPM1, RPM2);
  desiredPivotAngle = 58700;
  
/*
   if (distanceFromLimelightToGoalInches <= 68) {

          //m_shooter.SetPointOne = 2554;
         // m_shooter.SetPointTwo = -2667; 
	        desiredPivotAngle = 21659;
          m_shooter.runShooterAuto(2960, -2960 * 0.6);
	        desiredPivotAngle = 58700;

	        debugCons("FIRST DISTANCE\n");          
     	 }

         else if (distanceFromLimelightToGoalInches > 68 && distanceFromLimelightToGoalInches <= 93) {

         // m_shooter.SetPointOne = 3008;
	       // m_shooter.SetPointTwo= -3575;
	        desiredPivotAngle = 41219; 
          m_shooter.runShooterAuto(3100, -3100 * 0.6);
	        desiredPivotAngle = 58700; 

	         debugCons("SECOND DISTANCE\n");          
     	 }
	  
         else if (distanceFromLimelightToGoalInches > 93 && distanceFromLimelightToGoalInches <= 109){

         // m_shooter.SetPointOne= 3008;
	       // m_shooter.SetPointTwo = -3575;
	        desiredPivotAngle = 41219;
         m_shooter.runShooterAuto(3300, -3300 * 0.6);
	        desiredPivotAngle = 58700;

	          debugCons("THIRD DISTANCE\n");          
     	 }

        else if (distanceFromLimelightToGoalInches > 109 && distanceFromLimelightToGoalInches <= 125){

         // m_shooter.SetPointOne = 2951;
	       // m_shooter.SetPointTwo = -2838;  
	        desiredPivotAngle = 41219;
            m_shooter.runShooterAuto(3600, -3600 * 0.6);
	        desiredPivotAngle = 58700;
           debugCons("Fourth Distance\n");    

      }
	  
         else if (distanceFromLimelightToGoalInches > 125 && distanceFromLimelightToGoalInches <= 141){

       //  m_shooter.SetPointOne = 3178;
	     // m_shooter.SetPointTwo = -3405; 
	      desiredPivotAngle = 42790;
        m_shooter.runShooterAuto(3700, -3700 * 0.6);
	      desiredPivotAngle = 58700;

	      debugCons("Fifth distance\n");          
     	 }

        else if (distanceFromLimelightToGoalInches > 141 && distanceFromLimelightToGoalInches <= 155){

       // m_shooter.SetPointOne = 3235;
	      //m_shooter.SetPointTwo = -3462;
	      desiredPivotAngle = 42790;
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
          
       // m_shooter.SetPointOne = 3462;
	     // m_shooter.SetPointTwo = -3746; 
	      desiredPivotAngle = 52825;
         m_shooter.runShooterAuto(4200, -4200 * .6);
	      desiredPivotAngle = 58700;

	    debugCons("VERY FAR\n");          
	    debugCons("8 distance\n");          
     	}

       else if (distanceFromLimelightToGoalInches >  216) {
          
         m_shooter.runShooterAuto(4400, -4400 * .6);
	      desiredPivotAngle = 58700;

	    debugCons("9 distance\n");          
     	}
    */


  debugCons("DISTANCE AWAY: " << distanceFromLimelightToGoalInches << "\n");

  //for human player station shots
  if (RPM1 >= 5100)
  {
    m_shooter.runShooterAuto(5100, -5100 * 0.6);
  }

  //limelight moves to target if target on screen
  if (abs(m_xOffset) < TARGET_RANGE)
  {
   m_turret.Turn(0);
   turretAligned = true;
   m_leds.ChangeLEDColors(0.71);
   
  }
  else if (m_xOffset > 0) {

   m_turret.Turn(0.4);
    m_leds.ChangeLEDColors(-0.11);

  }
  else if (m_xOffset < 0){

    m_turret.Turn(-0.4);
     m_leds.ChangeLEDColors(-0.11);
  }

	
	// check alignment of pivot
	if ((abs(m_pivot.GetAngle() - desiredPivotAngle)) < 2000) // +- 1 degree to avoid oscillating
	{
	   m_pivot.Turn(0); // stop pivoting
	   pivotAligned = true;
	}

  else{

	if (m_pivot.GetAngle() < desiredPivotAngle)
	{
	   m_pivot.Turn(1); // pivot down
	}
	else if (m_pivot.GetAngle() > desiredPivotAngle)
	{
	   m_pivot.Turn(-1);// pivot up
	}
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

  else {

    
    double m_desiredAngle = GOAL_ANGLE[int((navxGyro->GetYaw() + 180)/90)];
     if (abs((m_desiredAngle - 180) - navxGyro->GetYaw()) > ANGLE_THRESH){
		CanTurn = true;
    }
  	else{
		CanTurn = false; 
    }

    if (CanTurn == true)
	{
		if ((m_desiredAngle - 180) > navxGyro->GetYaw())
		{
			//m_turret.Turn(0.4); // right turn
      m_leds.ChangeLEDColors(-0.11); //red
		}
		else if ((m_desiredAngle - 180) < navxGyro->GetYaw())
		{
	  //	m_turret.Turn(-0.4);; // left turn
      m_leds.ChangeLEDColors(-0.11); //red
		}

      }
    }
  }
  

  //right and left climbers

  if (m_controllerInputs->driver_RightTriggerAxis > 0.5) {
    m_climb.ClimbUp();
    m_leds.ChangeLEDColors(-0.7);
  }
  else {
    m_climb.ClimbStop();
    
  }

  if (m_controllerInputs->driver_LeftTriggerAxis > 0.5)
   { 
    m_climb.ClimbDown();
     m_leds.ChangeLEDColors(-0.7);
  }


//high run climber
  if (m_controllerInputs->driver_RightBumper > 0.5)
  {
    m_climb.ClimbHighUP();
   m_leds.ChangeLEDColors(-0.7);
  }

  else {

    m_climb.ClimbHighStop();
  }

  if (m_controllerInputs->driver_LeftBumper > 0.5)
  {
    m_climb.ClimbHighDOWN();
     m_leds.ChangeLEDColors(0.51);

  }
 
}

#ifndef RUNNING_FRC_TESTS

int main() { return frc::StartRobot<Robot>(); }
#endif 