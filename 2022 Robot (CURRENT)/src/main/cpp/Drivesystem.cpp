//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming
#include "Drivesystem.h"



DriveSystem::DriveSystem()
{
  leftLead = new rev::CANSparkMax(1,rev::CANSparkMax::MotorType::kBrushless);
  leftFollower = new rev::CANSparkMax(2,rev::CANSparkMax::MotorType::kBrushless);
  rightLead = new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushless);
  rightFollower = new rev::CANSparkMax(4,rev::CANSparkMax::MotorType::kBrushless);
  
  
  navXGyro = new AHRS(frc::SPI::Port::kMXP);
  
  leftLead->RestoreFactoryDefaults();
  leftFollower ->RestoreFactoryDefaults(); 
  rightLead->RestoreFactoryDefaults();
  rightFollower->RestoreFactoryDefaults();
 

  leftFollower->Follow(*leftLead);
  rightFollower->Follow(*rightLead);


  // Drive power curve
  leftLead ->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
  leftFollower->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
  rightLead ->SetClosedLoopRampRate(DRIVE_RAMP_TIME);
  rightFollower->SetClosedLoopRampRate(DRIVE_RAMP_TIME);


}

DriveSystem::~DriveSystem()
{
  delete leftLead;
  delete leftFollower;
  delete rightLead;
  delete rightFollower;


  delete navXGyro;
}

//returns angle in radians, updates the robot position
frc::Rotation2d DriveSystem::GetAngle() const {
  return frc::Rotation2d(units::degree_t(-navXGyro->GetYaw()));
}

//return m_left and m_right wheel speeds, for setSpeeds() in Drive()
frc::DifferentialDriveWheelSpeeds DriveSystem::GetSpeeds() const {
  return {units::meters_per_second_t(m_leftVelocity),
          units::meters_per_second_t(m_rightVelocity)};
}

//return Pose2d (for Ramsete controller)
frc::Pose2d DriveSystem::GetPose() const
{
  frc::Pose2d currentPos = m_odometry.GetPose();
  return currentPos;
}

frc::DifferentialDriveKinematics DriveSystem::GetKinematics() const
{
  return m_kinematics;
}

/**
 * sets the robot position on field, use at beginning of the match
 * @param pose, position
 */ 


void DriveSystem::SetPose(frc::Pose2d pose)
{
  m_odometry.ResetPosition(pose,GetAngle());
}


/**
 * setting the speed of left and right side to the motors
 * @param speeds, wheel speeds of diff drivetrain
 */ 

void DriveSystem::SetSpeeds(const frc::DifferentialDriveWheelSpeeds& speeds) {

  m_leftVelocity = (leftLead->GetEncoder().GetVelocity() / kEncToWheel) *2*wpi::math::pi* kWheelRadius / 60;

  m_rightVelocity = -(rightLead->GetEncoder().GetVelocity() / kEncToWheel) *2*wpi::math::pi* kWheelRadius / 60;
  
  const auto leftOutput = m_leftPIDController.Calculate( m_leftVelocity, speeds.left.to<double>());

  const auto rightOutput = -m_rightPIDController.Calculate( m_rightVelocity, speeds.right.to<double>());

  rightLead->Set(rightOutput);
  leftLead->Set(leftOutput);
}



/**
 * main drive 
 * @param speed forward speed
 * @param rot angular velocity
 */


void DriveSystem::Drive(units::meters_per_second_t speed, units::radians_per_second_t rot) 
{
  //speed = (units::meters_per_second_t) (pow((double) kMaxSpeed, (double) speed) * (double) speed);
  SetSpeeds(m_kinematics.ToWheelSpeeds({speed, 0_mps, rot}));
}

/**
 * update robot's position on the field
 */ 


void DriveSystem::UpdateOdometry() 
{
  //1 enc report = 1 full motor rotation

  //right lead declared twice
  m_leftPosition = units::meter_t(rightLead->GetEncoder().GetPosition() * (2*wpi::math::pi*kWheelRadius)/kEncToWheel);
  m_rightPosition = units::meter_t(rightLead->GetEncoder().GetPosition() * (2*wpi::math::pi*kWheelRadius)/kEncToWheel);

  m_odometry.Update(GetAngle(), m_leftPosition,m_rightPosition);
}

/**
 * stops drivetrain
 */ 


void DriveSystem::StopMotor()
{
  rightLead->StopMotor();
  leftLead->StopMotor();
}

void DriveSystem::drivetrainDash()
{
  debugDashNum("(Drive) Left Distance",m_leftPosition.to<double>());
  debugDashNum("(Drive) Right Position",m_rightPosition.to<double>());
  debugDashNum("(Drive) leftVelocity",m_leftVelocity);
  debugDashNum("(Drive) rightVelocity",m_rightVelocity);

  units::meter_t currentX = GetPose().Translation().X();
  units::meter_t currentY = GetPose().Translation().Y();
  units::degree_t currentDeg = GetPose().Rotation().Degrees();
  debugDashNum("(Drive) Pose x (m)", currentX.to<double>());
  debugDashNum("(Drive) Pose y (m)", currentY.to<double>());
  debugDashNum("(Drive) Pose angle (degree)", currentDeg.to<double>());
}

/*

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
*/
