#include "Limelight.h"

Limelight::Limelight(Turret * m_turret, Pivot * m_pivot, Shooter * m_shooter){
    
    visionTurret = m_turret;
    visionPivot = m_pivot; 
    visionShooter = m_shooter;
}

Limelight::~Limelight(){

delete visionTurret;
delete visionPivot; 
delete visionShooter;
}



void Limelight::Targetting(){
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
          GetValues();
           //make sure to add pivot angle when encoder reads values
          //visionShooter->runShooter();
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

/*
void Limelight::LightToggle(){

  if (lightToggle == true)
    {
          Targetting();
          nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);

    }
  else
  {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);

  }

}
*/

void Limelight::GetValues(){
//calculate distance to target - outputs the distance to the center 

       m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0); //Get vertical offset from target
       double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
       double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
       double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
       double angleForPivot = (0.81*(distanceFromLimelightToGoalInches)+5.09);

      debugCons("Limelight Distance " << distanceFromLimelightToGoalInches << "\n");

      if (distanceFromLimelightToGoalInches <= 68 &&  distanceFromLimelightToGoalInches >= 82)
      {
          visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
          visionShooter->runShooter();

          //call in pivot angle 
      }

      else if (distanceFromLimelightToGoalInches <= 79 && distanceFromLimelightToGoalInches >= 93)
      {
          visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
          visionShooter->runShooter();

                    //call in pivot angle 

      }
      
      else if (distanceFromLimelightToGoalInches <= 125 && distanceFromLimelightToGoalInches >= 139)
      {
          visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
          visionShooter->runShooter();
                  //call in pivot angle 

      }

      else (distanceFromLimelightToGoalInches > 145);
      {
        visionShooter->SHOOTER_POWERONE = .80;
          visionShooter->SHOOTER_POWERTWO = -80;
          visionShooter->runShooter();

                    //call in pivot angle 

      }

      

}
