#include "Limelight.h"

Limelight::Limelight(Turret * m_turret, Pivot * m_pivot, Shooter * m_shooter){
    
    visionTurret = m_turret;
    visionPivot = m_pivot; 
    visionShooter = m_shooter;
    LightOff();
}

Limelight::~Limelight(){

delete visionTurret;
delete visionPivot; 
delete visionShooter;
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

          SeekTarget(true);
           //make sure to add pivot angle when encoder reads values
          visionShooter->runShooter();
            }
    else{
        debugCons("Object found?: NO" << "\n"); 

        SeekTarget(true);
        visionShooter->stopShooter(); //stop running shooter if no target found
                }
    
}

bool Limelight::IsTargeting() 
{
	if(m_shortDistance > 0)
		return true;
	else
		return false;
}

//seeking methods for limelight turret turning
void Limelight::SeekTarget(double setPower){ //make sure to add turret turning for seeking pivot angles 

if (abs(m_xOffset) < TARGET_RANGE){
    visionTurret->Turn(0);
}
else if (m_xOffset > 0) {

   visionTurret->TurnLimelightRight(1);

}
else if (m_xOffset < 0){

    visionTurret->TurnLimelightLeft(1);
  }
}

void Limelight::LightToggle(){

  if (lightToggle == true)
    {
      LightOn();
    }
  else {
      LightOff();
  }

}

void Limelight::GetValues(){
//calculate distance to target
       angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
       angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
       distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
       angleForPivot = (0.81*(distanceFromLimelightToGoalInches)+5.09);

        debugCons("DISTANCE IN INCHES: " << distanceFromLimelightToGoalInches << "\n");
        debugCons("ANGLE FOR PIVOT " << angleForPivot << "\n");

}


