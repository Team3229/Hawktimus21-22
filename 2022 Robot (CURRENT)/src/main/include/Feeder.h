#ifndef FEEDER_H
#define FEEDER_H

#pragma once

//phoenix motor controller includes 
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include "Debug.h"

class Feeder
{
private:
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX * m_feederMotor;
    
    const int kfeederMotorID = 11; 
    const double FEEDER_POWER_IN = -.8; //80 percent power
    const double FEEDER_POWER_OUT = .8;
public:
    Feeder();
    ~Feeder();

    void runFeeder();
    void reverseFeeder();

    void stopFeeder();
};

#endif