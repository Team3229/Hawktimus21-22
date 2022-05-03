#include "Shooter.h"

Shooter::Shooter(){
  
    flyWheelUpperOne.RestoreFactoryDefaults();
    flyWheelUpperTwo.RestoreFactoryDefaults();


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

 

}

Shooter::~Shooter(){


}

//stop shooter
void Shooter::stopShooter(){
    flyWheelUpperOne.StopMotor();
    flyWheelUpperTwo.StopMotor();
    
}


double Shooter::getRPMS(){

      frc::SmartDashboard::PutNumber("Shooter ONE RPM ", m_encoderShooterOne.GetVelocity());
}


//based on rpms
void Shooter::runShooterAuto(double RPM1, double RPM2){

    
int shooter_type = frc::SmartDashboard::GetNumber("Shooter Power/RPM", 0);

if (shooter_type == 0){

    m_pidControllerShooterOne.SetReference(RPM1, rev::CANSparkMax::ControlType::kVelocity);
    m_pidControllerShooterTwo.SetReference(RPM2, rev::CANSparkMax::ControlType::kVelocity);

    debugCons("RPM VALUES: " << m_encoderShooterOne.GetVelocity() << "\n");

}
else{
}


}

