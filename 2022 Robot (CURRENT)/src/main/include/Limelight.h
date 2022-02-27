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


    double m_xOffset;        //Get horizontal off set from target
    double m_yOffset;                   //Get vertical offset from target
    double m_targetDistance;                   //Get area of target on screen
    double m_skew;              //Get skew of target
    double m_shortDistance;
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