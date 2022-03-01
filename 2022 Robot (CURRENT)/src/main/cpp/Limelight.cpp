#include "Limelight.h"

Limelight::Limelight(Turret * m_turret){
    
    visionTurret = m_turret;
    LightOff();
}

Limelight::~Limelight(){

delete visionTurret;
}

void Limelight::LightOff(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
    //debugCons("LimelighOFf\n");
}

void Limelight::LightOn(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
   // debugCons("LimelightOn\n");
   
 m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);         //Get horizontal off set from target
 m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);                   //Get vertical offset from target
 m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);                   //Get area of target on screen
 m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);                   //Get skew of target
 m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

 if (IsTargeting() == true){
        debugCons("Object found?: YES" << "\n");
        debugCons("Distance away from target (IN INCHES): " << distanceFromLimelightToGoalInches << "\n"); //output to the console how far away the target is 
          //visionTurret->Turn(1); //turn turret until no target found 

            }
    else{
        debugCons("Object found?: NO" << "\n"); 
        //visionTurret->Turn(0); //stop turning the turret TEMPORARY, THIS WILL BE REPLACED BY THE SEEKING THRESHOLDS
        }
    
}

bool Limelight::IsTargeting() 
{
	if(m_shortDistance > 0)
		return true;
	else
		return false;
}

void Limelight::SeekTarget(double setPower){ //make sure to add turret turning for seeking 

if (abs(m_xOffset) < TARGET_RANGE){

}
else if (m_xOffset > 0) {

}
else if (m_xOffset < 0){

}
}
