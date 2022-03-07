#ifndef LIMELIGHT
#define LIMELIGHT_H

#pragma once

#include <String>
#include "Debug.h"
#include <iostream>
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "math.h"

#include "Turret.h"
#include "Shooter.h"
#include "Pivot.h"

class Limelight
{
public:
    Limelight(Turret * m_turret, Pivot * m_pivot, Shooter * m_shooter);
    ~Limelight();

    void Targetting();
    void LightToggle();  
  
    bool IsTargeting();
    void SeekTarget(double setPower);  

   
   
private:
 
 Turret * visionTurret;
 Pivot * visionPivot; 
 Shooter * visionShooter;


  //calculate distance 

  //threshold for turning 
  const float TARGET_RANGE = 4.0;

  const double kMAX_TURRET_POWER = .2;            //max turret turn power 20 percent
  const double kMAX_TURRET_CORRECT_POWER = .1;

  bool lightToggle = true; 

  double desiredPivotAngle;

};

#endif // LIMELIGHT_H

