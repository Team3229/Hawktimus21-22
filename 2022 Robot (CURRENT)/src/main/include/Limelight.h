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

class Limelight
{
public:
    Limelight(Turret * m_turret);
    ~Limelight();

    void LightOff();
    void LightOn();

    bool IsTargeting();
    void SeekTarget(double setPower);  
   
private:

 Turret * visionTurret;

  double m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);      //Get horizontal off set from target
  double m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);      //Get vertical offset from target
  double m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);   //Get area of target on screen
  double m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);              //Get skew of target
  double m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

  //mounting angle of the limelight from perfectly vertical 
  double limelightMountAngleDegrees = 35.0;

  //distance fromt he center of the limelight lens to the floor
  double limelightLensHeightInches = 36.5;

  double goalHeightInches = 104.0;

  double angleToGoalDegrees = limelightMountAngleDegrees + m_yOffset;
  double angleToGoalRadians = angleToGoalDegrees * (3.14159 / 180.0);

  //calculate distance 
  double distanceFromLimelightToGoalInches = (goalHeightInches - limelightLensHeightInches)/tan(angleToGoalRadians);

  //threshold for turning 
  const float TARGET_RANGE = 4.0;

  const double kMAX_TURRET_POWER = .2;            //max turret turn power 20 percent
  const double kMAX_TURRET_CORRECT_POWER = .1;
};

#endif // LIMELIGHT_H

