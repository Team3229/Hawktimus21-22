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


