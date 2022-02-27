// Author: Team 3229 Programming Subteam

#include "Limelight.h"

// Connect to 10.32.29.11:5801 for control panel
// Connect to 10.32.29.11:5800 for direct camera output

Limelight::Limelight(Turret * m_turret)
{
    // Pasted from documentation
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 2);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);

    visionTurret = m_turret;
}

Limelight::~Limelight()
{
    delete visionTurret;
}

void Limelight::GetValues()
{
  m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);    
  m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);                   
  m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);                  
  m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);                   
  m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);


    debugCons("X offset: " << m_xOffset << "\n");
    //debug("Y offset: " << m_yOffset << "\n");
    debugCons("Skew angle: " << m_skew << "\n");

    debugCons("Distance variable: " << m_targetDistance << "\n");
    if (IsTargeting() == true)
    {
        debugCons("Object found?: YES" << "\n");
    }
    else
    {
        debugCons("Object found?: NO" << "\n");
    } 
    
}

bool Limelight::IsTargeting() 
{
	if(m_validObject > 0)
		return true;
	else
		return false;
}

void Limelight::SeekTarget()
{

    if (abs(m_xOffset) < TURNING_RANGE)
    {
         debugCons("TURN RIGHT\n");
    }


    else if (m_xOffset > 0)
    {
         debugCons("TURN LEFT\n");
    }
    else
    {
             debugCons("TARGET IS ALIGNED");
    }

    

        


}