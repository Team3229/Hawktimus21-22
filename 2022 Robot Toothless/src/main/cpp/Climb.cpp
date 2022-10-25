//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming


#include "Climb.h"
#include <iostream>
#include <rev/SparkMaxRelativeEncoder.h>

Climb::Climb()
{
   
    climbLead = new rev::CANSparkMax(LEAD_ID,rev::CANSparkMax::MotorType::kBrushless);
	climbFollower = new rev::CANSparkMax(FOLLOWER_ID,rev::CANSparkMax::MotorType::kBrushless);
    climbHigh = new rev::CANSparkMax(HIGH_ID,rev::CANSparkMax::MotorType::kBrushless);

    climbLead->RestoreFactoryDefaults();
    climbFollower->RestoreFactoryDefaults();
    climbHigh->RestoreFactoryDefaults();
}

Climb::~Climb()
{
    delete climbLead;
    delete climbFollower;
    delete climbHigh;
}

void Climb::ClimbUp(double input)
{
    climbLead->Set(CLIMB_SPEED2*input);
    climbFollower->Set(CLIMB_SPEED2*input);
}
void Climb::ClimbDown(double input)
{
    climbLead->Set(CLIMB_SPEED*input);
    climbFollower->Set(CLIMB_SPEED*input);
}
void Climb::ClimbSync(double up, double down)
{
    climbFollower->Set(up);
    climbFollower->Set(down);
}

void Climb::ClimbStop()
{
climbLead->StopMotor();
climbFollower->StopMotor();
}

void Climb::ClimbHighUP()
{
climbHigh->Set(-CLIMB_SPEED);
}

void Climb::ClimbHighDOWN(){

climbHigh->Set(CLIMBHIGH_SPEED);
}

void Climb::ClimbHighStop(){

climbHigh->StopMotor();
}