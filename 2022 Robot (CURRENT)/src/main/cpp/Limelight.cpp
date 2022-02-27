// Author: Team 3229 Programming Subteam

#include "Limelight.h"

// Connect to 10.32.29.11:5801 for control panel
// Connect to 10.32.29.11:5800 for direct camera output

Limelight::Limelight(Turret * m_turret)
{
    // Pasted from documentation

    visionTurret = m_turret;

    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);
}

Limelight::~Limelight()
{
    delete visionTurret;
}

void Limelight::GetValues()
{
	m_xOffset = table->GetNumber("tx", 0.0);
    //m_yOffset = table->GetNumber("ty", 0.0);
    m_targetDistance = table->GetNumber("ta", 0.0);
    m_validObject = table->GetNumber("tv", 0.0);
    m_skew = table->GetNumber("ts", 0.0);

    debug("X offset: " << m_xOffset << "\n");
    //debug("Y offset: " << m_yOffset << "\n");
    debug("Skew angle: " << m_skew << "\n");

    debug("Distance variable: " << m_targetDistance << "\n");
    if (IsTargeting() == true)
        debug("Object found?: YES" << "\n");
    else
        debug("Object found?: NO" << "\n"); 
    
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
         debugCons("TURN RIGHT\n");


    else if (m_xOffset > 0)
         debugCons("TURN LEFT\n");
    else
             debugCons("TARGET IS ALIGNEDn");

    

        


}