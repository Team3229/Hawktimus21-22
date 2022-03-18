#include "Shooter.h"

Shooter::Shooter(){
   //instantiate shooter motors
    flyWheelUpperOne = new rev::CANSparkMax(kUpperFWOneID,rev::CANSparkMax::MotorType::kBrushless);
    flyWheelUpperTwo = new rev::CANSparkMax(kUpperFWTwoID,rev::CANSparkMax::MotorType::kBrushless);
    
    //restore for facotry defaults
    flyWheelUpperOne->RestoreFactoryDefaults();
    flyWheelUpperTwo->RestoreFactoryDefaults();

    //PID Control for shooter motors
    rev::SparkMaxPIDController m_pidControllerShooterOne = flyWheelUpperOne->GetPIDController();
    rev::SparkMaxPIDController m_pidControllerShooterTwo = flyWheelUpperTwo->GetPIDController();

    //Get encoder for flywheels
    rev::SparkMaxRelativeEncoder m_encoderShooterTwo =  flyWheelUpperOne->GetEncoder();
    rev::SparkMaxRelativeEncoder m_encoderShooterOne = flyWheelUpperTwo->GetEncoder();

    //Shooter PID coefficients

    m_pidControllerShooterOne.SetP(kP);
    m_pidControllerShooterOne.SetI(kI);
    m_pidControllerShooterOne.SetD(kD);
    m_pidControllerShooterOne.SetIZone(kIz);
    m_pidControllerShooterOne.SetFF(kFF);
    m_pidControllerShooterOne.SetOutputRange(kMinOutput, kMaxOutput);

    m_pidControllerShooterTwo.SetP(kP);
    m_pidControllerShooterTwo.SetI(kI);
    m_pidControllerShooterTwo.SetD(kD);
    m_pidControllerShooterTwo.SetIZone(kIz);
    m_pidControllerShooterTwo.SetFF(kFF);
    m_pidControllerShooterTwo.SetOutputRange(kMinOutput, kMaxOutput);
    

    //control types for the shooter PID
    m_pidControllerShooterOne.SetReference(SetPointOne, rev::ControlType::kVelocity);
    m_pidControllerShooterTwo.SetReference(SetPointTwo, rev::ControlType::kVelocity);

}

Shooter::~Shooter(){
    delete flyWheelUpperOne;
    delete flyWheelUpperTwo;

}

//stop shooter
void Shooter::stopShooter(){
    flyWheelUpperOne->StopMotor();
    flyWheelUpperTwo->StopMotor();
    
}

//run shooter based on power
void Shooter::runShooter() {


    SHOOTER_POWERONE = frc::SmartDashboard::GetNumber("Shooter Power 1", SHOOTER_POWERONE);
    SHOOTER_POWERTWO = frc::SmartDashboard::GetNumber("Shooter Power 2", SHOOTER_POWERTWO);
  
    flyWheelUpperOne->Set(SHOOTER_POWERONE);
    flyWheelUpperTwo->Set(SHOOTER_POWERTWO);
}


//based on rpms
void Shooter::runShooterAuto(){

    
int shooter_type = frc::SmartDashboard::GetNumber("Shooter Power/RPM", 0);

if (shooter_type == 0){

    SetPointOne = frc::SmartDashboard::GetNumber("Shooter Power 1", SetPointOne);
    SetPointTwo = frc::SmartDashboard::GetNumber("Shooter Power 2", SetPointTwo);

    flyWheelUpperOne->Set(SetPointOne);
    flyWheelUpperTwo->Set(SetPointTwo);

    frc::SmartDashboard::PutNumber("Shooter Power 1", SetPointOne);
    frc::SmartDashboard::PutNumber("Shooter Power 2", SetPointTwo);
}
else{

    SetPointOne = frc::SmartDashboard::GetNumber("Shooter Power 1", SetPointOne);
    SetPointOne = frc::SmartDashboard::GetNumber("Shooter Power 2", SetPointTwo);

    


    frc::SmartDashboard::PutNumber("Shooter Power 1", SetPointOne);
    frc::SmartDashboard::PutNumber("Shooter Power 2", SetPointTwo);


}


}

