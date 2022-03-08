#include "Limelight.h"


Limelight::Limelight(){
}

Limelight::~Limelight(){
}

void Limelight::LightOn(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
    
   // debugCons("LimelightOn\n");
}

void Limelight::LightOff(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
   // debugCons("LimelightOff\n");
}

bool Limelight::GetValues(){
     
    double m_target = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv",0.0); //Does the limelight have a target (0 or 1)?
	
    if (m_target > 0) // has a target
    {
       double m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0); //Get horizontal offset from target
       double m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0); //Get vertical offset from target

	//calculate horizontal turn to target
	double horizontalAngleToTarget = m_xOffset;
	
	//calculate distance to target
	double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
    double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
    double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));

	//calculate angle for the pivot
	double angleForPivot = (0.81*(distanceFromLimelightToGoalInches)+5.09);
	
    debugCons("DISTANCE IN INCHES: " << distanceFromLimelightToGoalInches << "\n");
    debugCons("HORIZONTAL: " << horizontalAngleToTarget << "\n");
	debugCons("ANGLE FOR PIVOT " << angleForPivot << "\n");
	
	return true;
    }

    else 
    { // no target
	    debugCons("NO TARGET" << "\n");
	    return false;
    }

}
