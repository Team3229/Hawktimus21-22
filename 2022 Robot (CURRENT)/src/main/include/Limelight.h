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

class Limelight
{
public:
    Limelight();
    ~Limelight();

    void LightOff();
    void LightOn();
   
private:
  double m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);         //Get horizontal off set from target
  double m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);                   //Get vertical offset from target
  double m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);                   //Get area of target on screen
  double m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);                   //Get skew of target
  double m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

};

#endif // LIMELIGHT_H

