#include "Climb.h"
#include <iostream>
#include <rev/SparkMaxRelativeEncoder.h>

Climb::Climb()
{
    /*
        climbLead = blue
        climbFollow = white
        climbPivot = red
    */
    climbLead = new rev::CANSparkMax(LEAD_ID,rev::CANSparkMax::MotorType::kBrushless);
	climbFollower = new rev::CANSparkMax(FOLLOWER_ID,rev::CANSparkMax::MotorType::kBrushless);
    climbPivot = new rev::CANSparkMax(PIVOT_ID,rev::CANSparkMax::MotorType::kBrushless);

    climbLead->RestoreFactoryDefaults();
    climbFollower->RestoreFactoryDefaults();
    climbPivot->RestoreFactoryDefaults();
}

Climb::~Climb()
{
    delete climbLead;
    delete climbFollower;
    delete climbPivot;
}

void Climb::ClimbUp()
{
    climbLead->Set(CLIMB_SPEED2);
    climbFollower->Set(CLIMB_SPEED2);
}
void Climb::ClimbDown()
{
    climbLead->Set(CLIMB_SPEED);
    climbFollower->Set(CLIMB_SPEED);
}
void Climb::ClimbSync(double up, double down)
{
    climbFollower->Set(up);
    climbFollower->Set(down);
}
void Climb::Pivot(double speed)
{
    climbPivot->Set(speed*PIVOT_SPEED);
}
void Climb::ClimbStop()
{
climbLead->StopMotor();
climbFollower->StopMotor();
}