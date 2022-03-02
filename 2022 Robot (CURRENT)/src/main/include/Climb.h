#ifndef CLIMB_H
#define CLIMB_H

#include <rev/CANSparkMax.h>
#include "Debug.h"

class Climb
{
public:
    Climb();
    ~Climb();

	
    void Toggle();

private:
    //SparkMax's
	rev::CANSparkMax * climbLead;
	rev::CANSparkMax * climbFollower;
    rev::SparkMaxRelativeEncoder * m_encoder;

    const int LEAD_ID = 12;
	const int FOLLOWER_ID = 13;
    const int CLIMB_ROTATIONS = 5.5;
    bool climbState = false;
};

#endif