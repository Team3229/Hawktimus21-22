#ifndef CLIMB_H
#define CLIMB_H

#include <rev/CANSparkMax.h>
#include "Debug.h"
#include <rev/SparkMaxRelativeEncoder.h>

class Climb
{
public:
    Climb();
    ~Climb();

    void ClimbUp();
    void ClimbDown();
    void ClimbSync(double up, double down);
    void ClimbHighUP();
    void ClimbHighDOWN();
    void ClimbHighStop();
    void ClimbStop();

private:
    //SparkMax's
	rev::CANSparkMax * climbLead;
	rev::CANSparkMax * climbFollower;
    rev::CANSparkMax * climbHigh;

    const int LEAD_ID = 14;
	const int FOLLOWER_ID = 13;
    const int HIGH_ID = 16;

    
    const double CLIMB_SPEED = 1.0;
    const double CLIMB_SPEED2 = -1.0;


    const double CLIMBHIGH_SPEED = 1.0;

};

#endif