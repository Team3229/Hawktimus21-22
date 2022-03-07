//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#include "DriveSystem.h"

DriveSystem::DriveSystem()
{
    //Instantiate motor controllers
	leftLead = new rev::CANSparkMax(LEFT_LEAD_ID,rev::CANSparkMax::MotorType::kBrushless);
	rightLead = new rev::CANSparkMax(RIGHT_LEAD_ID,rev::CANSparkMax::MotorType::kBrushless);
	leftFollower = new rev::CANSparkMax(LEFT_FOLLOWER_ID,rev::CANSparkMax::MotorType::kBrushless);
	rightFollower = new rev::CANSparkMax(RIGHT_FOLLOWER_ID,rev::CANSparkMax::MotorType::kBrushless);

	//Restore Facory Defaults 
	leftLead->RestoreFactoryDefaults();
	rightLead->RestoreFactoryDefaults();
	leftFollower->RestoreFactoryDefaults();
	rightFollower->RestoreFactoryDefaults();

	//Closed Loop Ramp
	leftLead->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
	rightLead->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
	leftFollower->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
	rightFollower->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
	
    //Set followers
	leftFollower->Follow(*leftLead);
	rightFollower->Follow(*rightLead);

	rightFollower->SetInverted(true);
	rightLead->SetInverted(true);


	//Instantiate DriveTrain
	driveTrain = new frc::DifferentialDrive(*leftLead, *rightLead);

	//Sets max initial speed and turn off safety
	driveTrain->SetMaxOutput(MAX_OUTPUT);
	driveTrain->SetSafetyEnabled(false); 

}

DriveSystem::~DriveSystem()
{
    delete leftLead;
	delete rightLead;
	delete leftFollower;
	delete rightFollower;
	delete driveTrain;

}

void DriveSystem::Drive(double& Y, double& X, double& Z)
{
    //Drive function
	//Y = Y; // invert Y
    driveTrain->ArcadeDrive(Y, X); //might cause issues due to update? needs testing
	//debugCons("Drive mode: With Gyro\n");
}

void DriveSystem::Stop()
{
    driveTrain->StopMotor();
}

void DriveSystem::ChangeSpeed(int choice)
{
    if (choice == 1)
	{
        driveTrain->SetMaxOutput(LOW_OUTPUT);
    	//debugCons("Slow speed\n");
	}
    else if (choice == 2)
	{
        driveTrain->SetMaxOutput(MAX_OUTPUT);
    	//debugCons("Normal speed\n");
	}
    else if (choice == 3)
	{
        driveTrain->SetMaxOutput(HIGH_OUTPUT);
    	//debugCons("Fast speed\n"); 
	}
}

