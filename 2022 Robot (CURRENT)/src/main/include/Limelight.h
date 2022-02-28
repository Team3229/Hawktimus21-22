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
   

};

#endif // LIMELIGHT_H

