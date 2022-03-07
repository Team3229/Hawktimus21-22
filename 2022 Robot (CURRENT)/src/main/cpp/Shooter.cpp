#include "Shooter.h"

Shooter::Shooter()
{
   //instantiate shooter motors
    flyWheelUpperOne = new rev::CANSparkMax(kUpperFWOneID,rev::CANSparkMax::MotorType::kBrushless);
    flyWheelUpperTwo = new rev::CANSparkMax(kUpperFWTwoID,rev::CANSparkMax::MotorType::kBrushless);
    
    //restore for facotry defaults
    flyWheelUpperOne->RestoreFactoryDefaults();
    flyWheelUpperTwo->RestoreFactoryDefaults();

   
 
}

Shooter::~Shooter()
{
    delete flyWheelUpperOne;
    delete flyWheelUpperTwo;

}

//stop shooter
void Shooter::stopShooter()
{
    flyWheelUpperOne->StopMotor();
    flyWheelUpperTwo->StopMotor();
    
}

//run shooter
void Shooter::runShooter() {
  
   
    flyWheelUpperOne->Set(SHOOTER_POWERONE);
    flyWheelUpperTwo->Set(SHOOTER_POWERTWO);
   
    
}

void Shooter::runShooterAuto(){


    flyWheelUpperOne->Set(SHOOTER_POWERONEAUTO);
    flyWheelUpperTwo->Set(SHOOTER_POWERTWOAUTO);
}

