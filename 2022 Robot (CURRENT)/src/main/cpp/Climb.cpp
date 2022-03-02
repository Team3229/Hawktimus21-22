#include "Climb.h"
#include <iostream>

Climb::Climb()
{
    climbLead = new rev::CANSparkMax(LEAD_ID,rev::CANSparkMax::MotorType::kBrushless);
	climbFollower = new rev::CANSparkMax(FOLLOWER_ID,rev::CANSparkMax::MotorType::kBrushless);
    rev::SparkMaxRelativeEncoder m_encoder = climbLead->GetEncoder();

    climbLead->RestoreFactoryDefaults();
    climbFollower->RestoreFactoryDefaults();

    climbFollower->Follow(*climbLead);
}

Climb::~Climb()
{
    delete climbLead;
    delete climbFollower;
}

void Climb::Toggle()
{
    if (climbState == false){
        m_encoder->SetPosition(CLIMB_ROTATIONS);
        climbState = true;
    } else {
        m_encoder->SetPosition(0);
        climbState = false;
    };
}