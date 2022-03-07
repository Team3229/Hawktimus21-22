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



void Limelight::LightOn(){
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
   // debugCons("LimelightOn\n");

 if (IsTargeting() == true){
         debugCons("Object found?: YES" << "\n");

          SeekTarget(true);
          visionShooter->runShooter();
            }
    else{
        debugCons("Object found?: NO" << "\n"); 
        SeekTarget(true);
        visionShooter->stopShooter();
                }
    
}

void Limelight::LightOff(){


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

GetValues();

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
          nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);

    }
  else
  {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);

  }

}


void Limelight::GetValues(){
//calculate distance to target
     

      
       m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0); //Get vertical offset from target
       double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
       double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);
       double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/(tan(angleToGoalRadians));
       double angleForPivot = (0.81*(distanceFromLimelightToGoalInches)+5.09);
         debugCons("DISTANCE IN INCHES: " << distanceFromLimelightToGoalInches << "\n");
        debugCons("ANGLE FOR PIVOT " << angleForPivot << "\n");


         if (distanceFromLimelightToGoalInches <= 68 &&  distanceFromLimelightToGoalInches >= 82)
      {
          visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
           visionShooter->runShooter();

           debugCons("FIRST DISTANCE");



          //call in pivot angle 
          
      }

      else if (distanceFromLimelightToGoalInches <= 79 || distanceFromLimelightToGoalInches >= 93)
      {
          visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
           visionShooter->runShooter();

           debugCons("SECOND DISTANCE\n");

                    //call in pivot angle 

      }
      
      else if (distanceFromLimelightToGoalInches <= 125 || distanceFromLimelightToGoalInches >= 139)
      {
           visionShooter->SHOOTER_POWERONE = .3;
          visionShooter->SHOOTER_POWERTWO = -.3;
           visionShooter->runShooter();
                  //call in pivot angle 
                             debugCons("THIRD DISTANCE\n");


      }

      else if  (distanceFromLimelightToGoalInches > 145)
      {
          visionShooter->SHOOTER_POWERONE = 1.0;
          visionShooter->SHOOTER_POWERTWO = -1.0;
           visionShooter->runShooter();
                      debugCons("VERY FAR AWAY\n");

      }

      else {

        debugCons("NOTHING");
      }



}

