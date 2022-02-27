// Author: Team 3229 Programming Subteam

#ifndef LIMELIGHT_H
#define LIMELIGHT_H

#include "Turret.h"
#include "Debug.h"

#include <iostream>
#include "frc/smartdashboard/Smartdashboard.h"

//limelight includes 
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"


class Limelight
{
public:
    Limelight(Turret * m_turret);
    ~Limelight();
    void GetValues();
    bool IsTargeting();
    void SeekTarget();  
    void Turn(double setPower);


private:
    
    Turret * visionTurret;


 
float m_xOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0);         //Get horizontal off set from target
float m_yOffset = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0.0);                   //Get vertical offset from target
float m_targetDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta",0.0);                   //Get area of target on screen
float m_skew = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0.0);                   //Get skew of target
float m_shortDistance = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

   float m_validObject; // yes/no is there a target on screen "tv"
   
   /**
    float m_xOffset; // x angle offset from target "tx"
	float m_yOffset; // y "ty"
    float m_skew;
    float m_targetDistance; // % of screen filled by current target "ta"
    float m_vertDistance; //"tvert"
    float m_shortDistance; // "tshort"
    */
    //threshholds and desires
    const float TURNING_RANGE = 4.0;

    // turning powers
    double m_stillPower = 0.0;
    double m_leftAdjPow = -0.3; //turn
    double m_rightAdjPow = 0.3; //turn

    const double kMAX_TURRET_POWER = .2;            //max turret turn power
    const double kMAX_TURRET_CORRECT_POWER = .1;    //correct when turret goes beyond max range

      

};

#endif // LIMELIGHT_H